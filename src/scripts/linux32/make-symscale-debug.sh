#!/bin/bash

export PRODUCT=SymScale

. setdirs.sh

cd ..

./runmake rtl o-mt all
./runmake ext o-mt all
./runmake fnt o all
./runmake jpeg o all
./runmake xml o all
./runmake symscale o all
