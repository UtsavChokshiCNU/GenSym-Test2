#!/bin/bash

export PRODUCT=MTG2

. setdirs.sh

cd ..

runmake_and_check() {
    ./runmake $1 $2 all $MAKEOPTS
    if [ $? -ne 0 ]; then
	echo "runmake $1 $2 failed"
	exit 1
    fi
}

runmake_and_check rtl opt-mt
runmake_and_check ext opt-mt
runmake_and_check fnt opt
runmake_and_check jpeg opt
runmake_and_check libpng opt
runmake_and_check xml opt
runmake_and_check g2 opt-mt
