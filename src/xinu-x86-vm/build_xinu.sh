#!/bin/sh

make clean -C compile >/dev/null;make -C compile | tail;./compile/upload.sh
