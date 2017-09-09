#!/bin/bash

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

make_and_check make-javalink-x64.sh
make_and_check make-g2-jdbc.sh
make_and_check make-g2-ora10.sh
make_and_check make-g2-ora11.sh
make_and_check make-g2-ora12.sh
make_and_check make-g2-odbc.sh
make_and_check make-corbalink-x64.sh
make_and_check build-g2fasth.sh

. setdirs.sh

pushd /g2/src/ant
make_and_check ant build-kbs
make_and_check ant build-layered-products
popd
