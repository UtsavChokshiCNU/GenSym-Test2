#!/bin/bash
# Run this file and find your executable in current folder

rm -f ../../lisp/*.log
rm -f *.*x32fsl
rm -f *.*x64fsl
rm -rf OBIN
mkdir OBIN

MT=$1
ARCH=$2
if [ `uname -m` = "x86_64" ]; then
    if [ s"$ARCH" = s"" ]; then
        # if user not set the ARCH, set it to "64" in x86_64 environment.
        ARCH="64"
    fi
else
    # in x86 environment,the only valid value is "32".
    ARCH="32"
fi

if [ s"$ARCH" = s"64" ]; then
    COMPILER="lx86cl64"
else
    ARCH="32"
    COMPILER="lx86cl"
fi

if [ s"$MT" = s"mt" ]; then
    ../../../tools/lisp/ccl-1.7/${COMPILER} -n -l 3.lisp
    ../../../tools/lisp/ccl-1.7/${COMPILER} -n -l 4.lisp
    mv trans-mt-ccl ../../linux${ARCH}/trans-mt-ccl
else
    ../../../tools/lisp/ccl-1.7/${COMPILER} -n -l 1.lisp
    ../../../tools/lisp/ccl-1.7/${COMPILER} -n -l 2.lisp
    mv trans-ccl ../../linux${ARCH}/trans-ccl
fi