#!/bin/sh
# The Sun JDK installs itself in c:/Program Files/Java/jdk*.
# To avoid having to guess how to quote the space in that pathname,
# I made a link to the actual jdk installation dir in /usr/local/jdk
JVMINCLUDE="/usr/local/jdk/include"
CFLAGS="-m32 -I${JVMINCLUDE}/win32";export CFLAGS
rm -rf usr
h-to-ffi.sh ${JVMINCLUDE}/jni.h
