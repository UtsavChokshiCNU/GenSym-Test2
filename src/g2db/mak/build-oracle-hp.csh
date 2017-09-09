#!/bin/csh -f
setenv ORACLE_HOME /home/oracle7/734
setenv ORACLE_SID oracle7
setenv TWO_TASK p:
setenv PATH ${PATH}:$ORACLE_HOME

setenv CORELIBS "-lsql -lsqlnet -lncr -lsqlnet -lclient -lcommon -lgeneric -lsqlnet -lncr -lsqlnet -lclient -lcommon -lgeneric -lepc -lnlsrtl3 -lc3v6 -lcore3 -lnlsrtl3 -lcore3 -lnlsrtl3 -lpthread"
# -l:libcl.a -l:librt.sl -lpthread -l:libnss_dns.1 -l:libdld.sl -lm -lpthread"
#setenv CORELIBS "-lsql $ORACLE_HOME/lib/osntab.o -lsqlnet -lora -lsqlnet -lora -lnlsrtl3 -lc3v6 -lcore3 -lnlsrtl3 -lcore3 -lcl"

setenv USER_ID "scott/tiger@ejansen1_orcl"

setenv PRECOMP $ORACLE_HOME/bin/proc

setenv GSIDIR /gensym/ut/gsi-51r5
setenv GSILIBS "$GSIDIR/libgsi.a $GSIDIR/librtl.a $GSIDIR/libtcp.a $GSIDIR/libgnosec.a"
setenv AUTH_LIB /vmsdisc/pd/tools/opt/hp9000s700/tools.a

#hp
setenv PLATFORM_LIBS -l:libdld.sl
setenv DB_CFLAGS "+w2 -Aa -z +DA1.0 +DS1.1"
setenv DB_LDFLAGS "-Wl,-a,archive -Dhp9000s700"

make -f ./g2-oracle-unix.mak
