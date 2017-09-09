#!/bin/bash

export SRCBOX=/g2/src
export DSTBOX=/g2/dst
export PLATFM=linux64

cd $SRCBOX/g2db/java/G2JDBC
make -f mak/linux-auth
