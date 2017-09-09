#!/bin/bash

export PRODUCT=TW

. setdirs.sh

cd ..

./runmake rtl o all
./runmake ext o all
./runmake fnt o all
./runmake jpeg o all
./runmake tw o all

 
