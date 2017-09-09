setenv ORACLE_HOME /gensym/bridges/sparcsol/dbs/oracle/1010
setenv OLDLIBPATH "$LD_LIBRARY_PATH"
if ( $?LD_LIBRARY_PATH == "0" ) then
    setenv LD_LIBRARY_PATH ""
endif
setenv LD_LIBRARY_PATH {$LD_LIBRARY_PATH}:/gensym/bridges/sparcsol/dbs/oracle/1010/lib32:/gensym/bridges/sparcsol/lib

if ( $?PATH == "0") then
    setenv PATH ""
endif
setenv PATH {$PATH}:{$ORACLE_HOME}/bin
