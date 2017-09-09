#!/bin/bash

export PRODUCT=TW

. setdirs.sh

cd ..

./runmake rtl o all $MAKEOPTS
./runmake ext o all $MAKEOPTS
./runmake fnt o all $MAKEOPTS
./runmake jpeg o all $MAKEOPTS
./runmake libpng o all $MAKEOPTS
./runmake tw o all $MAKEOPTS
