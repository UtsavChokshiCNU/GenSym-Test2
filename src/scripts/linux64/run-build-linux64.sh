#!/bin/sh

. setdirs.sh

cd $SRCBOX/lisp
$SRCBOX/chestnut/trans-sbcl --dynamic-space-size 1100 3rpm < 123.lisp > g2-log.txt 2>&1