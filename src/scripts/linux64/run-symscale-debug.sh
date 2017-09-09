#!/bin/bash

. setdirs.sh

exec gdb $DSTBOX/symscale/o/SymScale $1 $2 $3 $4 $5 $6 $7 $8
