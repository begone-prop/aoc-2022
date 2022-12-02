#!/bin/sh

paste -sd '+' input |
    sed 's/++/\n/g' | bc | sort -n | tail -n 1

paste -sd '+' input |
    sed 's/++/\n/g' | bc | sort -n | tail -n 3 |
    paste -sd '+' | bc
