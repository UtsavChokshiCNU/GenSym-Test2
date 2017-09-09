#!/bin/bash
# Run this file and find your executable in current folder

MT=$1
ARCH=`uname -m`
if [ "$ARCH" = "x86_64" ] ; then
    LISPWORKS=lispworks-6-1-1-64-bit-cli
    BIT=64
else
    LISPWORKS=lispworks-6-0-0-cli
    BIT=32
fi    

rm ../../lisp/*.log
rm -f *.wx32fsl
rm -fr OBIN
mkdir OBIN

if [ s"$MT" = s"mt" ]; then
    $LISPWORKS -init - -load 3.lisp
    $LISPWORKS -build 4.lisp
    cp -f trans-mt-lw ../../linux$BIT/ 
else
    $LISPWORKS -init - -load 1.lisp
    $LISPWORKS -build 2.lisp
    cp -f trans-lw ../../linux$BIT/ 
fi
echo Building $MT translator finished.
