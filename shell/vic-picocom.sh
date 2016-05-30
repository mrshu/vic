#!/bin/bash

PORT=$1
if [ "$PORT" = "" ]; then
    echo "usage: $0 serial-port [baudrate]"
    exit 1
fi

RATE="9600"
if [ "$2" != "" ]; then
    RATE=$2
fi

command -v picocom >/dev/null 2>&1 || {
    echo >&2 "The communication is done by picocom, please install it"
    exit 1
}

picocom -b $RATE -c --imap lfcrlf --omap crlf,delbs $PORT
