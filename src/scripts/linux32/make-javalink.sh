#!/bin/bash

export PRODUCT=G2

. setdirs.sh

export CLASSPATH=$CLASSPATH:$JAVA_HOME/lib/tools.jar:./
export CLASSPATH=$CLASSPATH:$SRCBOX/java

find $SRCBOX/java/com -type f -name "*.class" -exec rm -f {} \;

cd $SRCBOX/java


../util/jmake com/gensym/devtools devtools
if [ $? -ne 0 ]; then
    echo "../util/jmake com/gensym/devtools devtools failed"
    exit 1
fi

cd $SRCBOX/scripts

./jmake $SRCBOX/java/com/gensym javalink
if [ $? -ne 0 ]; then
    echo "./jmake $SRCBOX/java/com/gensym javalink failed"
    exit 1
fi


# ./jmake $SRCBOX/java/com/gensym sequoia
#if [ $? -ne 0 ]; then
#    echo "./jmake $SRCBOX/java/com/gensym sequoia failed"
#    exit 1
#fi

rm -r $DSTBOX/javalink

mkdir $DSTBOX/javalink
mkdir $DSTBOX/javalink/opt
mkdir $DSTBOX/javalink/bin
mkdir $DSTBOX/javalink/classes

cd $SRCBOX/java/mkfiles

make -f linux-jgi-opt
if [ $? -ne 0 ]; then
    echo "make -f linux-jgi-opt failed"
    exit 1
fi

cp $DSTBOX/javalink/opt/libJgiInterface.so $DSTBOX/javalink/bin/

cd $SRCBOX/java/scripts/JavaLink

ant make-jars
if [ $? -ne 0 ]; then
    echo "ant make-jars failed"
    exit 1
fi
