#!/bin/bash


if [ $# -ne 1 ]; then
  echo "Usage: make-mqtt.sh Target"
  echo "Supported Target values are clean,release,debug" 
else
  . ./setdirs.sh
  make -C ${SRCBOX}/mqtt $1
fi


