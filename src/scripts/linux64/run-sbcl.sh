#!/bin/bash

. setdirs.sh

cd $SRCBOX/lisp

# In order for this to work, (defconstant tls-size 4096)
# should be changed to (defconstant tls-size (* 4 4096))
# in /src/compiler/generic/parms.lisp
# and SBCL recompiled.
sbcl --dynamic-space-size 2048
