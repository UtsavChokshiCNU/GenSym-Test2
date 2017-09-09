#!/bin/bash

# What is the product in a unit test?
export PRODUCT=g2

. ./setdirs.sh

cd ..

./runmake ext o all $MAKEOPTS
./runmake ext-test o all $MAKEOPTS
