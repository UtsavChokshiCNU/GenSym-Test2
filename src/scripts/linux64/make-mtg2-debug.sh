#!/bin/bash

export PRODUCT=G2

. setdirs.sh

cd ..

runmake_and_check() {
    ./runmake $1 $2 all $MAKEOPTS
    if [ $? -ne 0 ]; then
	echo "runmake $1 $2 failed"
	exit 1
    fi
}


runmake_and_check rtl o-mt
runmake_and_check ext o-mt
runmake_and_check fnt o
runmake_and_check jpeg o
runmake_and_check libpng o
runmake_and_check xml o
runmake_and_check g2 o-mt
