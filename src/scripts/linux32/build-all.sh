#!/bin/bash

set -ex
cp /g2/src/license/g2sitev2015-std.ok /g2/src/license/g2sitev2015.ok
PATH=.:$PATH


make_and_check() {
    $1 $2
    if [ $? -ne 0 ]; then
	echo "$1 $2 failed"
	exit 1
    fi
}

make_and_check make-mqtt.sh release
make_and_check make-g2.sh
make_and_check make-tw.sh
make_and_check make-gsi.sh
make_and_check make-gw.sh

make_and_check make-javalink.sh
make_and_check make-g2-jdbc.sh
make_and_check make-g2-ora10.sh
make_and_check make-g2-ora11.sh
make_and_check make-g2-ora12.sh
make_and_check make-g2-odbc.sh
make_and_check make-corbalink.sh

make_and_check build-g2fasth.sh
make_and_check make-mqtt.sh clean 
make_and_check make-mqtt.sh release 

. setdirs.sh

# this is impossible in TeamCity, please do it manually.
# ^^ I'm actually not sure this is true any more, we need to check!
#pushd /g2/src/ant
#ant build-kbs
#ant build-layered-products
#popd
