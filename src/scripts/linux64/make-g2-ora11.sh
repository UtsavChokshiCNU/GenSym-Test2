#!/bin/bash

. setdirs.sh

export PLATFM=linux64

# G2-Oracle 11
export LD_LIBRARY_PATH=$SRCBOX/g2db/dbs/${PLATFM}/oracle/instantclient_11_2

make_and_check() {
    make -C $SRCBOX/g2db/mak -f $SRCBOX/g2db/mak/g2-ora110-linux.mak $1 $2 $3 $4 $5 $6 $7 $8
    if [ $? -ne 0 ]; then
	echo "make -C $SRCBOX/g2db/mak -f $SRCBOX/g2db/mak/g2-ora110-linux.mak $1 failed"
	exit 1
    fi
}

make_and_check clean
make_and_check `$SRCBOX/g2db/mak/gdefs`
