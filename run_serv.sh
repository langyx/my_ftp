#!/bin/bash
trap 'make fclean && mr && echo "Done"' SIGINT
make
n=$((RANDOM%2000+2000))
echo "========="
echo "STARTED AT ==== $n"
echo "========="
./server $n a/ &
netcat localhost $n
