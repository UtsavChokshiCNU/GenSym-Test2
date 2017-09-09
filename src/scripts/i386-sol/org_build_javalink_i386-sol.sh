#!/bin/sh

. ./set_env_i386-sol.sh

# 1. Use these to build JavaLink:
$SRCBOX/scripts/runmake ext o all
$SRCBOX/scripts/runmake rtl o all
$SRCBOX/scripts/runmake gsi o
$SRCBOX/scripts/runmake ext opt all
$SRCBOX/scripts/runmake rtl opt all
$SRCBOX/scripts/runmake gsi opt

cd $JAVA_SRCBOX
$SRCBOX/util/jmake com/gensym/devtools devtools
$SRCBOX/util/jmake .                   javalink
$SRCBOX/util/jmake .                   sequoia
$JAVA_HOME/bin/java  -mx100m com.gensym.devtools.JavaMake -srcbox $SRCBOX -root . -product javalink -quiet
$JAVA_HOME/bin/java  -mx100m com.gensym.devtools.JavaMake -srcbox $SRCBOX -root . -product sequoia -quiet

# libJgiInterface.so is here:
#mkdir $DSTBOX/java
#mkdir $DSTBOX/java/o
#mkdir $DSTBOX/java/opt

#cd $JAVA_SRCBOX/mkfiles
#make -f i386-sol-jgi-o
#make -f i386-sol-jgi-opt


# 2. or use this script to make that above all at once:
#cd $JAVA_SRCBOX
#$JAVA_SRCBOX/scripts/jgi-build
#$JAVA_SRCBOX/scripts/jgi-build -nojavac

