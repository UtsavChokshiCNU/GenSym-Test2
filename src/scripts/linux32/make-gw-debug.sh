#!/bin/bash

export PRODUCT=GW

. setdirs.sh

cd ..

./runmake rtl o all
./runmake ext o all
./runmake gsi o all
./runmake gw o all
