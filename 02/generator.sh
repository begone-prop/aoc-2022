#!/bin/sh

export LC_ALL=C

grep -ioa '[A-B][X-Z]' /dev/urandom | sed -r 's/(.)(.)/\U\1 \2/g'
