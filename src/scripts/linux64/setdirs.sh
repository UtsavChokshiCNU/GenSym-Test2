#!/bin/bash

export SRCBOX=/g2/src
export DSTBOX=/g2/dst
export G2_OK=/g2/src/license/g2sitev2015-ent.ok
export MACHINE=linux64
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

searchPath "kbs"
searchPath "kbs/sources"
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
searchPath "g2db/kbs/src"
searchPath "g2pi/kbs"
searchPath "g2opc/kbs"
searchPath "gdanol/gda/kbs"
searchPath "gdanol/common/kbs"
searchPath "gdanol/nol/kbs"
searchPath "tests"
searchPath "tests/performance"

# GENSYMCID-453: Fix all LSB compatibility issues of the Gensym Linux bundle
# Please install LSB 4.x SDK in /opt/lsb

# GENSYMCID-1852: Regression test suite (corrupt-test.kb) failed on Linux
# Long texts in KB may be corrupt when G2 is built by higher versions of GCC,
# fallback to GCC 4.4. -- Chun Tian (binghe), July 29, 2016.

export GCC_VERSION="4.4"
export GCC="gcc-${GCC_VERSION}"
export CC="lsbcc --lsb-cc=/usr/bin/gcc-${GCC_VERSION}"
export CXX="lsbc++ --lsb-cxx=/usr/bin/g++-${GCC_VERSION}"
export CPP="lsbcpp --lsb-cpp=/usr/bin/cpp-${GCC_VERSION}"
# commented out parallel make because we suspect it
# causes build failures with static libraries like
# libtcp.a, libcprim.a etc.
# - should be investigated and re-enabled if it's not the cause or it's fixed
#export MAKEOPTS="-j 2"
