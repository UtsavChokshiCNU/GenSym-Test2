#!/bin/csh
setenv SYBASE /gensym/bridges/sparcsol/dbs/sybase/1200
if ( $?PATH == "0" ) then
	setenv PATH ""
endif
setenv PATH /gensym/bridges/sparcsol/dbs/sybase/1200/OCS-12_0/bin:$PATH
setenv SYBASE_OCS OCS-12_0
if ( $?LD_LIBRARY_PATH == "0" ) then
	setenv LD_LIBRARY_PATH ""
endif
setenv LD_LIBRARY_PATH /gensym/bridges/sparcsol/dbs/sybase/1200/OCS-12_0/lib:/usr/local/openwin/lib:/usr/lib:$LD_LIBRARY_PATH
setenv SYBASE /gensym/bridges/sparcsol/dbs/sybase/1200
if ( $?PATH == "0" ) then
	setenv PATH ""
endif
setenv PATH /gensym/bridges/sparcsol/dbs/sybase/1200/OCS-12_0/bin:$PATH
setenv SYBASE_OCS OCS-12_0
if ( $?LD_LIBRARY_PATH == "0" ) then
	setenv LD_LIBRARY_PATH ""
endif
setenv LD_LIBRARY_PATH /gensym/bridges/sparcsol/dbs/sybase/1200/OCS-12_0/lib:/usr/local/openwin/lib:/usr/lib:$LD_LIBRARY_PATH
