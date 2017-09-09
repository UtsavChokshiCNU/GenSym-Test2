#!/bin/bash

cd $(dirname $0)

rm -f ../../chestnut/trans-32b3c
rm -f ../../chestnut/trans-sbcl-l32

cd ../../chestnut/src/trans

rm -f -r OBIN
mkdir OBIN
rm -f trans-sbcl

sbcl < 1.lisp
sbcl < 2.lisp

mv -f trans-sbcl ../../trans-sbcl-l32
