#!/bin/bash

. setdirs.sh

. make-mqtt.sh release

cd ..

make -C ${SRCBOX}/mqtt release
./runmake ext o all
./runmake fnt o all
./runmake jpeg o all
./runmake libpng o all
./runmake xml o all

cd $SRCBOX/xanalys

make -f makefile.linux

mkdir -p $DSTBOX/lisp/o

cp twlibs.so $DSTBOX/lisp/o/twlibs.so
cp g2libs.so $DSTBOX/lisp/o/g2libs.so
cp gsilibs.so $DSTBOX/lisp/o/gsilibs.so
