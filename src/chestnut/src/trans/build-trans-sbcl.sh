#!/bin/bash
#
# Comment:
#    The usage of this script:
#        $0 MT ARCH
#    Where MT could be empty(means not MT) or "mt" and otherwise, and ARCH could be empty or "32" and "64".
#    The default value of MT is empty,
#    The default value of ARCH is 64 in x86_64 environment and 32 in x86 environment.
#
# Example
#    * build 32bit transltor in x86_64 environment.
#       build-trans-sbcl.sh "" 32
#       build-trans-sbcl.sh mt 32
#
#    -- Xu Jingtao (xu.jingtao@glority.com) 2012.11.09

rm -f ../../lisp/*.log *.fasl

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
    OPTION=""
    COMPILER="sbcl-x64"
else
    ARCH="32"
    OPTION="--dynamic-space-size 1024"
    COMPILER="sbcl-x86"
fi

if [ s"$MT" = s"mt" ]; then
   rm -rf OTBIN
   ../../../tools/lisp/sbcl/${COMPILER} --no-userinit < 3.lisp
   ../../../tools/lisp/sbcl/${COMPILER} --no-userinit $OPTION < 4.lisp
   mv trans-mt-sbcl ../../linux${ARCH}/trans-mt-sbcl
else
   rm -rf OBIN
   ../../../tools/lisp/sbcl/${COMPILER} --no-userinit < 1.lisp
   ../../../tools/lisp/sbcl/${COMPILER} --no-userinit $OPTION < 2.lisp
   mv trans-sbcl ../../linux${ARCH}/trans-sbcl
fi
echo Building $MT translator in ARCH $ARCH finished.
