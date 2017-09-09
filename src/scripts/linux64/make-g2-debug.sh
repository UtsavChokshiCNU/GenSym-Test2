#!/bin/bash

export PRODUCT=G2

. setdirs.sh

cd ..

./runmake rtl o all $MAKEOPTS
./runmake ext o all $MAKEOPTS
./runmake fnt o all $MAKEOPTS
./runmake jpeg o all $MAKEOPTS
./runmake libpng o all $MAKEOPTS
./runmake xml o all $MAKEOPTS
./runmake g2 o all $MAKEOPTS
