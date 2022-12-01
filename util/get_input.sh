#!/bin/sh

test -z "$AOC_COOKIE" && echo "AOC_COOKIE env. variable cannot be empty!" >&2 && exit 1
test -z "$1" && echo "No argument given" >&2 && exit 1

day="$1"
url="https://adventofcode.com/2022/day/${day}/input"

curl -s "$url" \
    -H 'User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 11_14_3; rv:122.0) Gecko/20100101 Firefox/122.0' \
    -H "Cookie: session=${AOC_COOKIE}"
