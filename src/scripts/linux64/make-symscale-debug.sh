#!/bin/bash

export PRODUCT=SymScale

. setdirs.sh

cd ..

./runmake rtl o-mt all $MAKEOPTS
./runmake ext o-mt all $MAKEOPTS
./runmake fnt o all $MAKEOPTS
./runmake jpeg o all $MAKEOPTS
./runmake xml o all $MAKEOPTS
./runmake symscale o all $MAKEOPTS
