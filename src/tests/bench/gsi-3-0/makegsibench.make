# Make for GSI benchmark - VERSION 3.0 REV. 0 - UNIX platform
#
# jh, 9/13/90.  Makes a GSI for individual testing.
# cpm, 9/8/92.  Updated for G2 version 3.0 to use the GSI libraries.
#               NOTE THAT THE GSI SOURCE IN "ma:>ab-3-0>" OR "ma:>ab>" IS NOT
#               NECESSARILY UP TO DATE!  Therefore, we must use the GSI 
#               libraries starting in version 3.0.
# cpm, 9/9/92   Moved the benchmark C source files to "ma:>benchmarks>gsi-bench-3-0>"
#               from "ma:>jh>c>gsi>benchmarks".
# cpm, 12/15/94 No longer copy files from MA (a lispm).  The necessary files are
#               stored in the CVS source-code repository.

# WARNING: DEFAULT_LIBS should use the library which supports the network
# protocols that are available on your machine.
# If you do not have DECNET software then use -ltcp.
# If you do not have TCP/IP software then use -ldec.
# If you have both TCP/IP and DECNET software then use -lnet.

# DEFAULT_LIBS =  -lgsi -lnet
# DEFAULT_LIBS =  -lgsi -ldec
DEFAULT_LIBS =  -lgsi -ltcp
H_FILES = $(H_DIR)gsi_icp.h $(H_DIR)gsi_user.h

# LIB_DIR = -L./
LIB_DIR = -L/gensym/ut/g2-30r0/extensions/
LIBS = $(LIB_DIR) $(DEFAULT_LIBS) $(NET_LIBS) -lm $(PLATFORM_SPECIFIC_LIBS) 
OBJ_DIR = /gensym/ut/g2-30r0/extensions/

OFLAG = -O
COMPILE_OPTS = $(OFLAG) -c  


GSIbench: gsi_benchmark.o gsi_regress_for_benchmark.o
	cc -o GSIbench $(OFLAG) gsi_benchmark.o gsi_regress_for_benchmark.o $(OBJS) $(LIBS) -lm

gsi_regress.o: gsi_regress_for_benchmark.c gsi_icp.h gsi_user.h
	cc $(COMPILE_OPTS) gsi_regress_for_benchmark.c -lm

gsi_benchmark.o: gsi_benchmark.c gsi_icp.h gsi_user.h gsi_regress.h
	cc $(COMPILE_OPTS) gsi_benchmark.c -lm

