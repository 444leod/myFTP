#!/bin/bash

input=$(mktemp -u)
mkfifo -m 600 "$input"

(tail -f "$input" | nc -C localhost 8080 > output &) >/dev/null 2>/dev/null

echo -ne "USER Ano" > "$input"
sleep 1
echo -ne "nymous\r\nPA" > "$input"
sleep 1
echo -ne "SS\r\n" > "$input"
sleep 1

rm -f "$input"
killall tail nc 2>/dev/null
