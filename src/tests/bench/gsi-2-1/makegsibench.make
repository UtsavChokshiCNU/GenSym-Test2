#
# MakeGSI
#
# jh, 9/13/90.  Makes a GSI for individual testing.
# cpm, 9/9/92.  Moved C source files from "ma:>jh>c>" to
#               "ma:>benchmarks>gsi-bench-2-1>".

OFLAG = -O
COMPILE_OPTS = $(OFLAG) -c  


GSI_OBJS = gsi_main.o gw_tcp.o gw_icp.o gw_ext.o gw_gsi.o gw_rpc.o 
GSI_INCLUDES = gsi_icp.h gsi_users.h features.h gsi_sys.h gsi_vars.h \
               gsi_exts.h gw_rpc.h gsi_user.h gsi_regress.h

gsi: $(GSI_OBJS)

gsi_main.o: gsi_main.c gsi_icp.h
	cc $(COMPILE_OPTS) gsi_main.c -lm
gsi_main.c:
	echo "get >ab-beta4>gsi_main.c gsi_main.c" | ftp -n ma

gw_tcp.o: gw_tcp.c features.h gsi_icp.h gw_sys.h gsi_sys.h
	cc $(COMPILE_OPTS) gw_tcp.c -lm
gw_tcp.c:
	echo "get >ab-beta4>gw_tcp.c gw_tcp.c" | ftp -n ma

gw_icp.o: gw_icp.c features.h gsi_exts.h
	cc $(COMPILE_OPTS) gw_icp.c -lm
gw_icp.c:
	echo "get >ab-beta4>gw_icp.c gw_icp.c" | ftp -n ma

gw_ext.o: gw_ext.c features.h gsi_icp.h gsi_vars.h
	cc $(COMPILE_OPTS) gw_ext.c -lm
gw_ext.c:
	echo "get >ab-beta4>gw_ext.c gw_ext.c" | ftp -n ma

gw_gsi.o: gw_gsi.c features.h gsi_icp.h gw_sys.h gsi_exts.h gw_rpc.h
	cc $(COMPILE_OPTS) gw_gsi.c -lm
gw_gsi.c:
	echo "get >ab-beta4>gw_gsi.c gw_gsi.c" | ftp -n ma

gw_rpc.o: gw_rpc.c features.h gw_rpc.h
	cc $(COMPILE_OPTS) gw_rpc.c -lm
gw_rpc.c:
	echo "get >ab-beta4>gw_rpc.c gw_rpc.c" | ftp -n ma


gsi_regress.o: gsi_regress.c gsi_icp.h gsi_user.h
	cc $(COMPILE_OPTS) gsi_regress.c -lm
gsi_regress.c:
	echo "get >benchmarks>gsi-bench-2-1>gsi_regress_for_benchmark.c gsi_regress.c" | ftp -n ma

gsi_benchmark.o: gsi_benchmark.c gsi_icp.h gsi_user.h gsi_regress.h
	cc $(COMPILE_OPTS) gsi_benchmark.c -lm
gsi_benchmark.c:
	echo "get >benchmarks>gsi-bench-2-1>gsi_benchmark.c gsi_benchmark.c" | ftp -n ma



GSIbench: gsi_benchmark.o gsi_regress.o $(GSI_OBJS)
	cc $(OFLAG) gsi_benchmark.o gsi_regress.o $(GSI_OBJS) -o GSIbench -lm




gsi_icp.h:
	echo "get >ab-beta4>gsi_icp.h gsi_icp.h" | ftp -n ma

gsi_users.h:
	echo "get >ab-beta4>gsi_users.h gsi_users.h" | ftp -n ma

gsi_user.h:
	echo "get >ab-beta4>gsi_user.h gsi_user.h" | ftp -n ma

features.h:
	echo "get >ab-beta4>features.h features.h" | ftp -n ma

gw_sys.h:
	echo "get >ab-beta4>gw_sys.h gw_sys.h" | ftp -n ma

gsi_sys.h:
	echo "get >ab-beta4>gsi_sys.h gsi_sys.h" | ftp -n ma

gsi_vars.h:
	echo "get >ab-beta4>gsi_vars.h gsi_vars.h" | ftp -n ma

gsi_exts.h:
	echo "get >ab-beta4>gsi_exts.h gsi_exts.h" | ftp -n ma

gw_rpc.h:
	echo "get >ab-beta4>gw_rpc.h gw_rpc.h" | ftp -n ma

gsi_regress.h:
	echo "get >benchmarks>gsi-bench-2-1>gw_regress.h gsi_regress.h" | ftp -n ma



