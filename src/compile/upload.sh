#!/bin/sh

echo 'Copying Xinu to TFTP'
cp ../compile/xinu /srv/tftp/xinu.boot
echo 'Successfully copied Xinu to TFTP'
