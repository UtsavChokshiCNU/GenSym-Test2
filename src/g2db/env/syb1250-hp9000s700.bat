#!/bin/csh
if ( $?PATH == "0" ) then
	setenv PATH ""
endif
setenv PATH /gensym/bridges/hp9000s700/dbs/sybase/1250/OCS-12_5/bin:$PATH
setenv SYBASE_OCS OCS-12_5
setenv SYBASE /gensym/bridges/hp9000s700/dbs/sybase/1250
setenv SYBASE_JRE /gensym/bridges/hp9000s700/dbs/sybase/1250/shared-1_0/jre1.2.2
if ( $?SHLIB_PATH == "0" ) then
	setenv SHLIB_PATH ""
endif
setenv SHLIB_PATH /gensym/bridges/hp9000s700/dbs/sybase/1250/OCS-12_5/lib:/gensym/bridges/hp9000s700/dbs/sybase/1250/OCS-12_5/lib3p:$SHLIB_PATH
if ( $?LD_LIBRARY_PATH == "0" ) then
	setenv LD_LIBRARY_PATH ""
endif
setenv LD_LIBRARY_PATH /gensym/bridges/hp9000s700/dbs/sybase/1250/OCS-12_5/lib:/gensym/bridges/hp9000s700/dbs/sybase/1250/OCS-12_5/lib3p64:$LD_LIBRARY_PATH

setenv LANG american.iso88591

