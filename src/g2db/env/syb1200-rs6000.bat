#!/bin/csh
setenv SYBASE /gensym/bridges/rs6000/dbs/sybase/1200
if ( $?PATH == "0" ) then
	setenv PATH ""
endif
setenv PATH /gensym/bridges/rs6000/dbs/sybase/1200/OCS-12_0/bin:$PATH
setenv SYBASE_OCS OCS-12_0
if ( $?LIBPATH == "0" ) then
	setenv LIBPATH ""
endif
setenv LIBPATH /gensym/bridges/rs6000/dbs/sybase/1200/OCS-12_0/lib:/usr/local/openwin/lib:/usr/lib:$LIBPATH
