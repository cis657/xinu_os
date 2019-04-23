#!/bin/sh

make clean -C compile >/dev/null;make -C compile | tail;
cd compile
./upload.sh
