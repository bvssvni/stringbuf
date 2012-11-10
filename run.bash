#!/bin/bash
gcc -o test-stringbuf *.c -Wall -Wfatal-errors -O3
if [ "$?" = 0 ]; then
	time ./test-stringbuf
fi