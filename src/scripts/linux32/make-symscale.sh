#!/bin/bash

export PRODUCT=SymScale

. setdirs.sh

cd ..

./runmake rtl opt-mt all
./runmake ext opt-mt all
./runmake fnt opt all
./runmake jpeg opt all
./runmake xml opt all
./runmake symscale opt all
