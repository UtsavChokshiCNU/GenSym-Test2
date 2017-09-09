#!/bin/bash

. setdirs.sh
export G2THREADS=`nproc`
exec gdb --args $DSTBOX/g2/o-mt/g2 $1 $2 $3 $4 $5 $6 $7 $8
