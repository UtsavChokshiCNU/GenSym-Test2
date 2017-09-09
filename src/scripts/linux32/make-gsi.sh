#!/bin/bash

export PRODUCT=GSI

. setdirs.sh

cd ..

runmake_and_check() {
    ./runmake $1 opt all
    if [ $? -ne 0 ]; then
	echo "runmake $1 failed"
	exit 1
    fi
}

runmake_and_check rtl
runmake_and_check ext
runmake_and_check gsi
