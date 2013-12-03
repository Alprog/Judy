#!/bin/bash
cd $(dirname "$(readlink -f "$0")")

gcc Main.cpp -o test `pkg-config --libs --cflags gtk+-3.0`
echo 'done'
read