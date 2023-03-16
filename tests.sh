#!/bin/bash
echo "hello world"
./client -h localhost -p 1111 -m udp &
pid=$!
sleep 2s
echo "sup\n\n" > /proc/${pid}/fd/0
echo "\n" > /proc/${pid}/fd/0


