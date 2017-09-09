#!/bin/bash

. setdirs.sh

exec gdb $DSTBOX/g2/o/g2 $1 $2 $3 $4 $5 $6 $7 $8
