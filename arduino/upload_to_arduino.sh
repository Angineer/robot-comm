#!/usr/bin/env bash
if [[ $# -eq 0 ]]; then
    echo "Usage: upload_to_arduino.sh file <port>"
elif [[ $# -eq 1 ]]; then
    ~/arduino-1.8.7/arduino --upload $1 --port /dev/ttyACM0
else
    ~/arduino-1.8.7/arduino --upload $1 --port $2
fi
