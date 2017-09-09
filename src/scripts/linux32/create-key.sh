#!/bin/bash

. setdirs.sh

KEY=$SRCBOX/bundle/tools/sbin/key

if [ ! -f $KEY ]; then
  pushd $SRCBOX/bundle/tools
  $SRCBOX/bundle/tools/ck
  popd
fi

exec $KEY
