#!/bin/bash

. setdirs.sh
export G2THREADS=`nproc`
exec $DSTBOX/g2/opt-mt/g2 $1 $2 $3 $4 $5 $6 $7 $8
