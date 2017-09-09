#!/bin/bash

. setdirs.sh

. make-mqtt.sh release

cd ..

make -C ${SRCBOX}/mqtt release
./runmake ext o all $MAKEOPTS
./runmake fnt o all $MAKEOPTS
./runmake jpeg o all $MAKEOPTS
./runmake libpng o all $MAKEOPTS
./runmake xml o all $MAKEOPTS

cd $SRCBOX/xanalys

make -f makefile.linux64 $MAKEOPTS

mkdir -p $DSTBOX/lisp/o/x64

cp twlibs.so $DSTBOX/lisp/o/x64/twlibs.so
cp g2libs.so $DSTBOX/lisp/o/x64/g2libs.so
cp gsilibs.so $DSTBOX/lisp/o/x64/gsilibs.so
