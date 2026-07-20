#!/usr/bin/env bash

set -u

usage() {
    echo "Dung: $0 <ten|pid> [giay]"
    echo "VD: $0 nginx 5"
    echo "VD: $0 1234 2"
}

TARGET="${1:-}"
INTERVAL="${2:-5}"

if [[ -z "$TARGET" ]]; then
    usage
    echo
    ps -eo pid,%cpu,comm --sort=-%cpu | head -n 11
    exit 1
fi

if ! [[ "$INTERVAL" =~ ^[0-9]+$ ]] || [[ "$INTERVAL" -le 0 ]]; then
    echo "Loi thoi gian."
    exit 1
fi

echo "Theo doi: $TARGET ($INTERVAL s)"
echo "Ctrl+C de thoat."
echo

while true; do
    echo "--- $(date '+%T') ---"

    if [[ "$TARGET" =~ ^[0-9]+$ ]]; then
        if ps -p "$TARGET" > /dev/null 2>&1; then
            ps -p "$TARGET" -o pid,ppid,%cpu,%mem,etime,cmd=
        else
            echo "PID $TARGET dung."
        fi
    else
        mapfile -t PIDS < <(pgrep -x "$TARGET" || true)

        if [[ ${#PIDS[@]} -eq 0 ]]; then
            echo "'$TARGET' dung."
        else
            ps -p "$(IFS=,; echo "${PIDS[*]}")" -o pid,ppid,%cpu,%mem,etime,cmd=
        fi
    fi

    echo
    sleep "$INTERVAL"
done