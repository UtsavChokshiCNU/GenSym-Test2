#!/bin/bash

export PRODUCT=GSI

. setdirs.sh

cd ..

./runmake rtl o all $MAKEOPTS
./runmake ext o all $MAKEOPTS
./runmake gsi o all $MAKEOPTS
