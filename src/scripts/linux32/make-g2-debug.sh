#!/bin/bash

export PRODUCT=G2

. setdirs.sh

cd ..

./runmake rtl o all
./runmake ext o all
./runmake fnt o all
./runmake jpeg o all
./runmake libpng o all
./runmake xml o all
./runmake g2 o all

 
