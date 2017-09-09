#!/bin/bash

. setdirs.sh

cd /gensym/src/lisp

exec lispworks $*
