#!/bin/bash

export PRODUCT=TW

. setdirs.sh

cd ..

runmake_and_check() {
    ./runmake $1 opt all $MAKEOPTS
    if [ $? -ne 0 ]; then
	echo "runmake $1 failed"
	exit 1
    fi
}


runmake_and_check rtl
runmake_and_check ext
runmake_and_check fnt
runmake_and_check jpeg
runmake_and_check libpng
runmake_and_check tw
