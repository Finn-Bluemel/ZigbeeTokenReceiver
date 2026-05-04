#!/usr/bin/env python3
"""
serial_to_osc.py  —  reads token messages from the receiver ESP32-C6 (USB Serial)
                      and forwards them as OSC to the osc-bridge monitor (and
                      optionally to Unreal Engine on a second port).

Receiver outputs lines like:
    TOKEN 436135512 [1 2 3 4] batt:3600mV

OSC sent to osc-bridge (port 8000):
    address : /rfid
    args    : int32 chip, int32 s0, int32 s1, int32 s2, int32 s3, int32 batt_mv

OSC sent to Unreal (port 8001, if --unreal-port is set):
    address : /digitracks/token
    args    : int32 chip, int32 s0, int32 s1, int32 s2, int32 s3, int32 batt_mv

Usage:
    python serial_to_osc.py --port COM16
    python serial_to_osc.py --port COM16 --unreal-host 192.168.1.50 --unreal-port 8001
"""

import argparse
import re
import sys
import serial
from pythonosc import udp_client

# Matches: TOKEN 436135512 [1 2 3 4] batt:3600mV
PATTERN = re.compile(
    r"TOKEN\s+(-?\d+)"                         # token / chip id (signed)
    r"\s+\[(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\]"   # 4 slot values
    r"\s+batt:(\d+)mV"                          # battery mV
)


def parse(line: str):
    m = PATTERN.search(line)
    if not m:
        return None
    chip, s0, s1, s2, s3, batt = m.groups()
    return int(chip), int(s0), int(s1), int(s2), int(s3), int(batt)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--port",        default="COM16",      help="Serial port of receiver board")
    ap.add_argument("--baud",        default=115200, type=int)
    ap.add_argument("--bridge-host", default="127.0.0.1",  help="osc-bridge host")
    ap.add_argument("--bridge-port", default=8000,   type=int, help="osc-bridge UDP port")
    ap.add_argument("--unreal-host", default=None,          help="Unreal Engine host (optional)")
    ap.add_argument("--unreal-port", default=8001,   type=int, help="Unreal Engine OSC port")
    args = ap.parse_args()

    bridge = udp_client.SimpleUDPClient(args.bridge_host, args.bridge_port)
    unreal = udp_client.SimpleUDPClient(args.unreal_host, args.unreal_port) if args.unreal_host else None

    print(f"[bridge] Serial {args.port} @ {args.baud} baud")
    print(f"[bridge] -> osc-bridge  {args.bridge_host}:{args.bridge_port}  /rfid")
    if unreal:
        print(f"[bridge] -> Unreal      {args.unreal_host}:{args.unreal_port}  /digitracks/token")

    with serial.Serial(args.port, args.baud, timeout=2) as ser:
        while True:
            try:
                raw = ser.readline().decode("utf-8", errors="replace").strip()
            except serial.SerialException as e:
                print(f"[bridge] serial error: {e}", file=sys.stderr)
                break

            if not raw:
                continue

            # Print all lines so you can see receiver status messages too
            print(f"[bridge] RX: {raw}")

            parsed = parse(raw)
            if parsed is None:
                continue

            chip, s0, s1, s2, s3, batt = parsed
            args_list = [chip, s0, s1, s2, s3, batt]

            bridge.send_message("/rfid", args_list)
            if unreal:
                unreal.send_message("/digitracks/token", args_list)


if __name__ == "__main__":
    main()
