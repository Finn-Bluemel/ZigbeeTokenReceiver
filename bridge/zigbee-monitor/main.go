// zigbee-monitor — reads Zigbee token messages from the ESP32-C6 receiver
// over USB serial, serves a live web monitor, and serves firmware files
// for esp-web-tools (browser-based flashing).
//
// Usage:
//   zigbee-monitor.exe [port]           e.g.  zigbee-monitor.exe COM16
//   zigbee-monitor.exe [port] [webport] e.g.  zigbee-monitor.exe COM16 9001
//
// Parses:  TOKEN 436135512 [1 2 3 4] batt:3600mV
// Firmware files served from ./firmware/ next to the executable.

package main

import (
	"bufio"
	_ "embed"
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"os"
	"path/filepath"
	"regexp"
	"strconv"
	"strings"
	"sync"
	"time"

	"go.bug.st/serial"
)

//go:embed ui/index.html
var uiHTML []byte

// ── Token event ───────────────────────────────────────────────────────────────

type TokenEvent struct {
	ChipID int    `json:"chip"`
	Slots  [4]int `json:"slots"` // DS2431 EEPROM slot numbers (0 = empty)
	BattMv int    `json:"batt"`
	Time   string `json:"time"`
}

// TOKEN 436135512 [1 2 3 4] batt:3600mV
// ChipID can be negative (derived from ESP32 MAC, stored as int32).
var tokenRe = regexp.MustCompile(`TOKEN\s+(-?\d+)\s+\[(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\]\s+batt:(\d+)mV`)

func parseLine(line string) (*TokenEvent, bool) {
	m := tokenRe.FindStringSubmatch(line)
	if m == nil {
		return nil, false
	}
	chip, _ := strconv.Atoi(m[1])
	s0, _   := strconv.Atoi(m[2])
	s1, _   := strconv.Atoi(m[3])
	s2, _   := strconv.Atoi(m[4])
	s3, _   := strconv.Atoi(m[5])
	batt, _ := strconv.Atoi(m[6])
	return &TokenEvent{
		ChipID: chip,
		Slots:  [4]int{s0, s1, s2, s3},
		BattMv: batt,
		Time:   time.Now().Format("15:04:05.000"),
	}, true
}

// ── SSE broker ────────────────────────────────────────────────────────────────

type broker struct {
	mu      sync.Mutex
	clients map[chan string]struct{}
}

func newBroker() *broker { return &broker{clients: make(map[chan string]struct{})} }

func (b *broker) subscribe() chan string {
	ch := make(chan string, 64)
	b.mu.Lock()
	b.clients[ch] = struct{}{}
	b.mu.Unlock()
	return ch
}

func (b *broker) unsubscribe(ch chan string) {
	b.mu.Lock()
	delete(b.clients, ch)
	b.mu.Unlock()
}

func (b *broker) publish(msg string) {
	b.mu.Lock()
	defer b.mu.Unlock()
	for ch := range b.clients {
		select {
		case ch <- msg:
		default:
		}
	}
}

// ── Serial reader ─────────────────────────────────────────────────────────────

func readSerial(port string, b *broker) {
	for {
		s, err := serial.Open(port, &serial.Mode{BaudRate: 115200})
		if err != nil {
			log.Printf("[serial] cannot open %s: %v — retrying in 3s", port, err)
			time.Sleep(3 * time.Second)
			continue
		}
		log.Printf("[serial] opened %s @ 115200", port)

		scanner := bufio.NewScanner(s)
		for scanner.Scan() {
			line := strings.TrimSpace(scanner.Text())
			if line == "" {
				continue
			}
			ev, ok := parseLine(line)
			if !ok {
				// Print non-token lines (status messages) to console
				if !strings.HasPrefix(line, "[receiver]") && !strings.HasPrefix(line, "[sender]") {
					log.Printf("[serial] %s", line)
				}
				continue
			}
			log.Printf("[token] chip=%d slots=%v batt=%dmV", ev.ChipID, ev.Slots, ev.BattMv)
			j, _ := json.Marshal(ev)
			b.publish(string(j))
		}

		s.Close()
		log.Printf("[serial] %s disconnected — retrying in 2s", port)
		time.Sleep(2 * time.Second)
	}
}

// ── HTTP / SSE ────────────────────────────────────────────────────────────────

func main() {
	port    := "COM16"
	webPort := "9001"

	if len(os.Args) > 1 {
		port = os.Args[1]
	}
	if len(os.Args) > 2 {
		webPort = os.Args[2]
	}

	b := newBroker()
	go readSerial(port, b)

	// Serve firmware files from ./firmware/ next to the exe (for esp-web-tools)
	exeDir, _ := filepath.Abs(filepath.Dir(os.Args[0]))
	firmwareDir := filepath.Join(exeDir, "firmware")
	http.Handle("/firmware/", http.StripPrefix("/firmware/", http.FileServer(http.Dir(firmwareDir))))

	http.HandleFunc("/events", func(w http.ResponseWriter, r *http.Request) {
		flusher, ok := w.(http.Flusher)
		if !ok {
			http.Error(w, "streaming unsupported", 500)
			return
		}
		w.Header().Set("Content-Type", "text/event-stream")
		w.Header().Set("Cache-Control", "no-cache")
		w.Header().Set("Access-Control-Allow-Origin", "*")

		ch := b.subscribe()
		defer b.unsubscribe(ch)

		fmt.Fprintf(w, "data: {\"connected\":true}\n\n")
		flusher.Flush()

		for {
			select {
			case msg := <-ch:
				fmt.Fprintf(w, "data: %s\n\n", msg)
				flusher.Flush()
			case <-r.Context().Done():
				return
			}
		}
	})

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "text/html; charset=utf-8")
		w.Write(uiHTML)
	})

	log.Printf("Zigbee Monitor  ->  http://localhost:%s   (serial: %s)", webPort, port)
	log.Fatal(http.ListenAndServe(":"+webPort, nil))
}
