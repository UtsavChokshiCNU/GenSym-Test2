# Defines
# -------
PLATFM = hp9000s700

include ${SRCBOX}/g2db/mak/unix.def

OS_VER = 11.0
DB_VER = 8.1
DBNAME = ORACLE
XDBDIR = /home/oracle/815
LLBDIR = $(XDBDIR)/lib


# Executable:
# -----------
g2-ora81:                   settings                            \
                            gdb_main.o                          \
                            gdb_g2_server.o                     \
                            gdb_common.o                        \
                            gdb_utils.o                         \
                            gsi_brg.o                           \
                            ${SPECFC}/nsleep.o                  \
                            gdb_client_inter_ora.o              \
                            gdb_client_ora.o
	@gcc -o g2-ora81 -L$(LLBDIR) -L${GSIDIR} \
        gdb_main.o gdb_g2_server.o gdb_common.o gdb_utils.o gdb_client_inter_ora.o gdb_client_ora.o             \
        gsi_brg.o ${SPECFC}/nsleep.o -lgsi -ltcp -lnogsec -lrtl -lclient8 -lsql8 $(LLBDIR)/scorept.o $(LLBDIR)/sscoreed.o\
        /home/oracle/815/rdbms/lib/kpudfo.o $(LLBDIR)/nautab.o $(LLBDIR)/naeet.o $(LLBDIR)/naect.o              \
        $(LLBDIR)/naedhs.o `cat /home/oracle/815/network/lib/ldflags` -ln8 -lnl8 -lnro8                         \
        `cat /home/oracle/815/network/lib/ldflags` -ln8 -lnl8 -lclient8 -lvsn8 -lcommon8 -lskgxp8               \
        -lgeneric8 -lmm -lnls8  -lcore8 -lnls8 -lcore8  -lnls8   `cat /home/oracle/815/network/lib/ldflags`     \
        -ln8 -lnl8 -lnro8 `cat /home/oracle/815/network/lib/ldflags` -ln8 -lnl8 -lclient8 -lvsn8                \
        -lcommon8 -lskgxp8 -lgeneric8 $(LLBDIR)/libpls8.a $(LLBDIR)/libplp8.a $(LLBDIR)/libpls8.a               \
        -ltrace8 -lnls8  -lcore8 -lnls8 -lcore8  -lnls8  -lclient8 -lvsn8 -lcommon8 -lskgxp8 -lgeneric8 -lnls8  \
        -lcore8 -lnls8 -lcore8 -lnls8 `cat $(LLBDIR)/sysliblist` -lm -lpthread -lpls8  -lsql8 -lpthread
	@chmod +x g2-ora81
	@chatr +s enable g2-ora81
	@ls -l g2-ora81

# Compilation
# -----------
gdb_main.o:                 $(GDBDIR)/gdb_main.c                \
                            $(GSIDIR)/gsi_main.h                \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_utils.h
	@gcc -ansi -c  \
        -I$(GDBDIR) -I$(GSIDIR) -D$(DBNAME) -D$(PLATFM) -D DB_VER=\"$(DB_VER)\" \
        -D GSI_VER=\"$(GSIVER)\" -D GDB_VER=\"$(GDBVER)\" -D BUILD_CODE=\"$(BLDCOD)\" $(GDBDIR)/gdb_main.c
	@ls -l gdb_main.o

gdb_g2_server.o:            $(GDBDIR)/gdb_g2_server.c           \
                            $(GSIDIR)/gsi_main.h                \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_g2_server.h           \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_common.h              \
                            $(GDBDIR)/gdb_genda.h
	@gcc -ansi -c -I$(GDBDIR) -I$(GSIDIR) -DKB_VER=$(KB_VER) -D$(DBNAME) $(GDBDIR)/gdb_g2_server.c
	@ls -l gdb_g2_server.o

gdb_common.o:               $(GDBDIR)/gdb_common.c              \
                            $(GSIDIR)/gsi_main.h                \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_genda.h               \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_common.h              \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_g2_client.h
	@gcc -ansi -c -I$(GDBDIR) -I$(GSIDIR) -D$(DBNAME) $(GDBDIR)/gdb_common.c
	@ls -l gdb_common.o

gdb_utils.o:                $(GDBDIR)/gdb_utils.c               \
                            $(GDBDIR)/gdb_globals.h
	@gcc -ansi -c -I$(GDBDIR) -I$(GSIDIR) -D$(DBNAME) $(GDBDIR)/gdb_utils.c
	@ls -l gdb_utils.o

gsi_brg.o:                  $(AUTHDR)/gsi_brg.c
	@gcc -c -D$(PLATFM) $(AUTHDR)/gsi_brg.c
	@ls -l gsi_brg.o

gdb_client_inter_ora.o:     $(GDBDIR)/gdb_client_inter_ora.c    \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_genda.h               \
                            $(GDBDIR)/gdb_client_ora.h          \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GDBDIR)/gdb_context.h             \
                            $(GSIDIR)/gsi_main.h                \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_common.h
	@gcc -ansi -c  -I$(GDBDIR) -I$(GSIDIR) -I$(XDBDIR)/precomp/public -D$(DBNAME) $(GDBDIR)/gdb_client_inter_ora.c
	@ls -l gdb_client_inter_ora.o

gdb_client_ora.o:           gdb_client_ora.c                    \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_client_ora.h          \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GSIDIR)/gsi_main.h                \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_common.h              \
                            $(GDBDIR)/gdb_g2_client.h
	@gcc -ansi -c -D $(PLATFM) -D iDBVER=$(DB_VER) -I$(GDBDIR) -I$(GSIDIR) -I$(GDBDIR) -I$(XDBDIR)/precomp/public \
		-D$(DBNAME) -DMAXOPENCURSORS=44 -DHOLD_CURSOR=YES -DRELEASE_CURSOR=NO gdb_client_ora.c
	@ls -l gdb_client_ora.o

# Precompiler
# -----------
gdb_client_ora.c:           $(GDBDIR)/gdb_client_ora.pc         \
                            $(GDBDIR)/gdb_client_ora.h          \
                            $(GDBDIR)/gdb_common.h              \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_g2_client.h           \
                            $(GDBDIR)/gdb_genda.h               \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GDBDIR)/gdb_utils.h
	@$(XDBDIR)/bin/proc iname=$(GDBDIR)/gdb_client_ora.pc oname=gdb_client_ora.c \
           include=$(GDBDIR) include=$(GDBDIR) include=$(GSIDIR) \
		   SQLCHECK=SEMANTICS MAXOPENCURSORS=44 HOLD_CURSOR=yes RELEASE_CURSOR=no
	@ls -l gdb_client_ora.c

# Remove intermediate files
# -------------------------
clean :
	@- rm *.o 2> /dev/null
	@- rm gdb_client_ora.c 2> /dev/null

# Report:
# -------
settings:
	@echo "+================================================
	@echo "|  BUILDING G2-ORA81 (${BLDCOD}) on $(PLATFM)
	@echo "+================================================
	@echo "|
	@echo "| ENVIRONMENT
	@echo "|   Bridge      : $(GDBVER) ($(KB_VER))"
	@echo "|   OS Ver      : $(OS_VER)
	@echo "|   GSI         : $(GSIDIR) ($(GSIVER))"
	@echo "|
	@echo "| SOURCES
	@echo "|   Source      : $(GDBDIR)
	@echo "|   Common      : $(GDBDIR)
	@echo "|   DBase       : $(XDBDIR)
	@echo "|
	@echo "+================================================



