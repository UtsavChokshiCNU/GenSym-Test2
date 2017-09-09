#!/bin/bash

export PRODUCT=GSI

. setdirs.sh

cd ..

./runmake rtl o all
./runmake ext o all
./runmake gsi o all





 
