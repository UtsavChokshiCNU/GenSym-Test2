#!/bin/bash

. setdirs.sh

export G2_MODULE_SEARCH_PATH="$SRCBOX/kbs/sources $SRCBOX/java/products/javalink/common/kbs"

export CLASSPATH=$SRCBOX/java:.:$CLASSPATH

java -Djava.library.path=$DSTBOX/javalink/bin com.gensym.demos.jgi.ExampleG2Gateway & 

$DSTBOX/g2/opt/g2 -ok $LICENSE -kb $SRCBOX/tests/javalink-atcc.kb


 
