#!/bin/bash

. setdirs.sh

make -C $SRCBOX/bundle/c PLATFORM=$MACHINE

run_promote_and_check() {
    $SRCBOX/scripts/$1
    if [ $? -ne 0 ]; then
	echo "promote script $1 failed"
	exit 1
    fi
}

run_promote_and_check pm-g2-promote
run_promote_and_check pm-tw-promote
run_promote_and_check pm-gsi-promote
run_promote_and_check pm-bridges-promote
run_promote_and_check pm-g2i-promote

# make make-bundles accept optional arguments.
$SRCBOX/bundle/tools/make-bundles $@ g2 ${G2_VERSION} $MACHINE

if [ $? -ne 0 ]; then
    echo "Failed to make bundle"
    exit 1
fi

echo
echo "The bundle is in /g2/bundles/g2/${G2_VERSION}/cd/${MACHINE}:"
find /g2/bundles/g2/${G2_VERSION}/cd/$MACHINE

echo
echo "There's also a ISO image:"
find /g2/bundles/g2/${G2_VERSION}/image
