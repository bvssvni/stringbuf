#!/bin/bash
gcc -o test-stringbuf *.c -Wall -Wfatal-errors -O3
if (( $? )); then
	time ./test-stringbuf
fi