#!/bin/bash

set -e

export LC_ALL=C

min_len=10
max_len=100

rand_len() {
    shuf -ri "${min_len}-${max_len}" |
        grep -Em 1 '[2468]$'
}

gen_line() {
    grep -aoi '[a-z]' /dev/urandom |
        head -n "$(rand_len)" | paste -sd ''
}

while true; do
    gen_line
done
