#!/bin/sh

. ./set_env_i386-sol.sh

$SRCBOX/scripts/runmake gsi o
#$SRCBOX/scripts/runmake gsi opt

$SRCBOX/scripts/runmake gw o
#$SRCBOX/scripts/runmake gw opt
