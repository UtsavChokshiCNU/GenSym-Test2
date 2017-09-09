#!/bin/bash

export PRODUCT=SymScale

. setdirs.sh

cd ..

./runmake rtl opt-mt all $MAKEOPTS
./runmake ext opt-mt all $MAKEOPTS
./runmake fnt opt all $MAKEOPTS
./runmake jpeg opt all $MAKEOPTS
./runmake libpng opt all $MAKEOPTS
./runmake xml opt all $MAKEOPTS
./runmake symscale opt all $MAKEOPTS
