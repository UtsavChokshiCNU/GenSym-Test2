#!/bin/bash

export SRCBOX=/g2/src
export DSTBOX=/g2/dst
export G2_OK=/g2/src/license/g2sitev2015-std.ok
export MACHINE=linux
export G2_MODULE_SEARCH_PATH=""
export JAVA_HOME=/opt/jdk1.6.0_45
export PATH=$JAVA_HOME/bin:/opt/lsb/bin:$PATH
export G2_VERSION=2015

searchPath () {
  G2_MODULE_SEARCH_PATH="${G2_MODULE_SEARCH_PATH} '${SRCBOX}/${1}'"
}

searchPath2 () {
  G2_MODULE_SEARCH_PATH="${G2_MODULE_SEARCH_PATH} '${DSTBOX}/${1}'"
}

#searchPath "kbs/sources"
searchPath "kbs"
#searchPath "g2i/builds/e-SCOR-1r10/staging"
#searchPath "g2i/builds/HLA-1r10/staging"
#searchPath "g2i/builds/Integrity-1r10/staging"
#searchPath "g2i/builds/Nol-1r10/staging"
#searchPath "g2i/builds/Optegrity-1r10/staging"
#searchPath "g2i/builds/ReThink-1r10/staging"
#searchPath2 "g2i/staging"
#searchPath "g2i/sites/e-SCOR/kbs"
#searchPath "g2i/sites/HLA/kbs"
#searchPath "g2i/sites/Integrity/kbs"
#searchPath "g2i/sites/Nol/kbs"
#searchPath "g2i/sites/Optegrity/kbs"
#searchPath "g2i/sites/ReThink/kbs"
searchPath "g2i/kbs"
searchPath "kbs/tools"
searchPath "java/products/javalink/kbs"
searchPath "g2db/kbs"
searchPath "g2pi/kbs"
searchPath "g2opc/kbs"
searchPath "gdanol/gda/kbs"
searchPath "gdanol/common/kbs"
searchPath "gdanol/nol/kbs"
searchPath "tests"
searchPath "tests/performance"

# see scripts/linux64/setdirs.sh for explanations about these settings:

export GCC_VERSION="4.4"
export GCC="gcc-${GCC_VERSION}"
export CC="lsbcc --lsb-cc=/usr/bin/gcc-${GCC_VERSION}"
export CXX="lsbc++ --lsb-cxx=/usr/bin/g++-${GCC_VERSION}"
export CPP="lsbcpp --lsb-cpp=/usr/bin/cpp-${GCC_VERSION}"
export MAKEOPTS="-j 2"
