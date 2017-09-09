#!/bin/sh
# This is very preliminary.
CFLAGS="-m64"; export CFLAGS
rm -rf usr
xh-to-ffi.sh /usr/local/win64/include/GL/glaux.h
