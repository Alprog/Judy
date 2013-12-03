#!/bin/bash

gcc Main.cpp -o test `pkg-config --libs --cflags gtk+-3.0`
read