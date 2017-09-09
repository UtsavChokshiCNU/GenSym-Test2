#!/bin/csh
setenv SYBASE /gensym/bridges/sparcsol/dbs/sybase/1251
setenv SYBASE_OCS OCS-12_5
if ( $?PATH == "0" ) then
    setenv PATH ""
endif
setenv PATH /gensym/bridges/sparcsol/dbs/sybase/1251/OCS-12_5/bin:$PATH
if ( $?LD_LIBRARY_PATH == "0" ) then
    setenv LD_LIBRARY_PATH ""
endif
setenv LD_LIBRARY_PATH /gensym/bridges/sparcsol/dbs/sybase/1251/OCS-12_5/lib:/gensym/bridges/sparcsol/dbs/sybase/1251/OCS-12_5/lib3p:$LD_LIBRARY_PATH
setenv SYBASE_JRE /gensym/bridges/sparcsol/dbs/sybase/1251/shared-1_0/JRE-1_3
