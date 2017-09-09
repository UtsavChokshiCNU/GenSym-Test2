#!/bin/bash

. setdirs.sh

export PLATFM=linux64

mkdir -p $DSTBOX/jdbc

pushd $SRCBOX/g2db/java/G2JDBC

ant build-jar
if [ $? -ne 0 ]; then
    echo "ant build-jar failed"
    exit 1
fi
make -f mak/linux-auth $MAKEOPTS
if [ $? -ne 0 ]; then
    echo "make -f mak/linux-auth $MAKEOPTS failed"
    exit 1
fi
