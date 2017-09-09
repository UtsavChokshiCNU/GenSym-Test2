#!/bin/csh
if ( $?PATH == "0" ) then
	setenv PATH ""
endif
setenv PATH /gensym/bridges/sparcsol/dbs/sybase/1250/OCS-12_5/bin:$PATH
setenv SYBASE_OCS OCS-12_5
setenv SYBASE /gensym/bridges/sparcsol/dbs/sybase/1250
setenv SYBASE_JRE /gensym/bridges/sparcsol/dbs/sybase/1250/shared-1_0/jre1.2.2
if ( $?LD_LIBRARY_PATH == "0" ) then
	setenv LD_LIBRARY_PATH ""
endif
setenv LD_LIBRARY_PATH /gensym/bridges/sparcsol/dbs/sybase/1250/OCS-12_5/lib:/usr/lib:$LD_LIBRARY_PATH
