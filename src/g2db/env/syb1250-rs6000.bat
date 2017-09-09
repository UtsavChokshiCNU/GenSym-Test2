#!/bin/csh
if ( $?PATH == "0" ) then
	setenv PATH ""
endif
setenv PATH /gensym/bridges/rs6000/dbs/sybase/1250/OCS-12_5/bin:$PATH
if ( $?LIBPATH == "0" ) then
	setenv LIBPATH ""
endif
setenv LIBPATH /gensym/bridges/rs6000/dbs/sybase/1250/OCS-12_5/lib:/gensym/bridges/rs6000/dbs/sybase/1250/OCS-12_5/lib3p:/usr/lib:$LIBPATH
setenv SYBASE_OCS OCS-12_5
setenv SYBASE /gensym/bridges/rs6000/dbs/sybase/1250
setenv SYBASE_JRE /gensym/bridges/rs6000/dbs/sybase/1250/shared-1_0/jre1.2.2
