#!/bin/bash

if [ "$1" == "STD" -o "$1" == "ENT" ]; then
  install_dir="$(cd `dirname $0`; pwd)"
  SRC_BOX="${install_dir}/../../"
  DST_BOX="${install_dir}/../../../dst"
  export CLASSPATH="${SRC_BOX}/java:.:${CLASSPATH}"
  java -version
  java -Djava.library.path=${DST_BOX}/javalink/bin -Xmx60M com.gensym.demos.jgi.ExampleG2Gateway &
  exit 0
fi

if [ "$1" == "STOP" ]; then
  echo "stop jgidemo bridge"
  ps aux | grep 'ExampleG2Gateway' | grep -v 'grep' | awk '{print $2}' | xargs -I {} kill -9 {}
  rm -rf mem_file
  touch stopped
  exit 0
fi

if [ "$1" == "ECHO-MEMORY" ]; then
  echo "stat memory usage of jgidemo bridge"
  ps aux | grep 'ExampleG2Gateway' | grep -v 'grep' | awk '{print $2}' | xargs -I {} ps -o rss= -p {} | awk '{print $1*1024}'  > mem_file
  exit 0
fi
