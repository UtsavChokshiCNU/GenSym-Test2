#!/bin/bash

export PRODUCT=GW

. setdirs.sh

cd ..

./runmake rtl o all $MAKEOPTS
./runmake ext o all $MAKEOPTS
./runmake gsi o all $MAKEOPTS
./runmake gw o all $MAKEOPTS
