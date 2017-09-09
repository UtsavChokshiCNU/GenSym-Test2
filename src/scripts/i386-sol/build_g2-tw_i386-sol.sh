#!/bin/sh

. ./set_env_i386-sol.sh

#run the make

$SRCBOX/scripts/runmake ext o
$SRCBOX/scripts/runmake jpeg o
$SRCBOX/scripts/runmake fnt o
$SRCBOX/scripts/runmake rtl o
$SRCBOX/scripts/runmake xml o
$SRCBOX/scripts/runmake g2 o
$SRCBOX/scripts/runmake tw o

# the second argument can be changed to opt or dbg depending on the kind of 
# build required.

cp $SRCBOX/g2/g2site.ok $G2_OK

#Change the destination directory as per the build type.

