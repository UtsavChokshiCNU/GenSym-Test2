#!/bin/bash

. setdirs.sh

export PLATFM=linux

# G2-Oracle 10
export ORACLE_HOME=$SRCBOX/g2db/dbs/${PLATFM}/oracle/client_10_2
export LD_LIBRARY_PATH=$ORACLE_HOME/lib

make_and_check() {
    make -C $SRCBOX/g2db/mak -f $SRCBOX/g2db/mak/g2-ora100-linux.mak $1 $2 $3 $4 $5 $6 $7 $8
    if [ $? -ne 0 ]; then
	echo "make -C $SRCBOX/g2db/mak -f $SRCBOX/g2db/mak/g2-ora100-linux.mak $1 failed"
	exit 1
    fi
}

make_and_check clean
make_and_check `$SRCBOX/g2db/mak/gdefs`
