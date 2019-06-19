#!/usr/bin/env bash

if [[ $# -eq 0 ]]; then
    ~/arduino-1.8.7/arduino --upload ./dummy.ino --port /dev/ttyACM0
else
    ~/arduino-1.8.7/arduino --upload ./dummy.ino --port $1
fi

