#!/bin/sh

find . -type f | xargs -Ix sed -i.bak -r 's/\r//g' x
find . -type f -name '*.bak' | xargs -Ix rm x
