# Defines
# -------
PLATFM = sparcsol

include ${SRCBOX}/g2db/mak/unix.def

OS_VER = 5.6
DB_VER = 8.0
DB_GRP = 8
DBNAME = ORACLE
XDBDIR = /gensym/spare/bridges/sparcsol/dbs/oracle/805

# Executable:
# -----------
g2-ora80:                   settings                            \
                            gdb_main.o                          \
                            gdb_g2_server.o                     \
                            gdb_common.o                        \
                            gdb_utils.o                         \
                            gsi_brg.o                           \
                            ${SPECFC}/nsleep.o                  \
                            gdb_client_inter_ora.o              \
                            gdb_client_ora.o
	@gcc -ansi -L${GSIDIR} -o g2-ora80 gdb_main.o gdb_g2_server.o gdb_utils.o   \
         gdb_common.o gdb_client_inter_ora.o gdb_client_ora.o gsi_brg.o        \
         ${SPECFC}/nsleep.o -lgsi -lrtl -ltcp -lnogsec $(XDBDIR)/lib/scorept.o      \
         $(XDBDIR)/lib/sscoreed.o $(XDBDIR)/rdbms/lib/kpudfo.o -L$(XDBDIR)/lib/\
         -lclient -lsql -lclntsh $(XDBDIR)/lib/nautab.o $(XDBDIR)/lib/naeet.o  \
         $(XDBDIR)/lib/naect.o $(XDBDIR)/lib/naedhs.o                          \
         `cat $(XDBDIR)/lib/naldflgs` -lnetv2 -lnttcp -lnetwork -lncr  -lnetv2 \
         -lnttcp -lnetwork -lclient -lvsn -lcommon -lgeneric -lmm -lnlsrtl3    \
         -lcore4 -lnlsrtl3 -lcore4 -lnlsrtl3 -lnetv2 -lnttcp -lnetwork -lncr   \
         -lnetv2 -lnttcp -lnetwork -lclient -lvsn -lcommon -lgeneric  -lepc    \
         -lnlsrtl3 -lcore4 -lnlsrtl3 -lcore4 -lnlsrtl3 -lclient -lvsn -lcommon \
         -lgeneric -lnlsrtl3  -lcore4 -lnlsrtl3 -lcore4 -lnlsrtl3              \
         `cat $(XDBDIR)/lib/sysliblist` -R /opt/SUNWcluster/lib:$(XDBDIR)/lib  \
         -Qy -lc -laio -lm -ldl
	@chmod +x g2-ora80
	@ls -l g2-ora80

# Compilation
# -----------
gdb_main.o:                 $(GDBDIR)/gdb_main.c                \
                            $(GSIDIR)/gsi_main.h                \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_utils.h
	@gcc -ansi -c -I$(GDBDIR) -I$(GSIDIR) -D$(DBNAME) -D$(PLATFM) -DDB_VER=\"$(DB_VER)\" \
        -DGSI_VER=\"$(GSIVER)\" -DGDB_VER=\"$(GDBVER)\" -DBUILD_CODE=\"$(BLDCOD)\" $(GDBDIR)/gdb_main.c
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
	@gcc -ansi  -c -I$(GDBDIR) -I$(GSIDIR) -DKB_VER=$(KB_VER) -D$(DBNAME) $(GDBDIR)/gdb_g2_server.c
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
	@gcc -ansi  -c -I$(GDBDIR) -I$(GSIDIR) -D$(DBNAME) $(GDBDIR)/gdb_common.c
	@ls -l gdb_common.o

gdb_utils.o:                $(GDBDIR)/gdb_utils.c               \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_globals.h
	@gcc -ansi  -c -I$(GDBDIR) -I$(GSIDIR) -D$(DBNAME) $(GDBDIR)/gdb_utils.c
	@ls -l gdb_utils.o

gsi_brg.o:                  $(AUTHDR)/gsi_brg.c
	@gcc -ansi -c -D$(PLATFM) $(AUTHDR)/gsi_brg.c
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
	@gcc -ansi  -c  -I$(GDBDIR) -I$(GSIDIR) -I$(XDBDIR)/precomp/public -D$(DBNAME) $(GDBDIR)/gdb_client_inter_ora.c
	@ls -l gdb_client_inter_ora.o

gdb_client_ora.o:           gdb_client_ora.c                    \
                            $(GDBDIR)/gdb_client_ora.h          \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GSIDIR)/gsi_main.h                \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_common.h              \
                            $(GDBDIR)/gdb_g2_client.h
	@gcc -ansi -c -I$(GDBDIR) -I$(GDBDIR) -I$(GSIDIR) -I$(XDBDIR)/precomp/public -DiDBVER=$(DB_GRP) \
        -DMAXOPENCURSORS=44 -DHOLD_CURSOR="yes" -DRELEASE_CURSOR="no" -D$(DBNAME) gdb_client_ora.c
	@ls -l gdb_client_ora.o

# Precompiler
# -----------
gdb_client_ora.c:           $(GDBDIR)/gdb_client_ora.pc 
	@$(XDBDIR)/bin/proc iname=$(GDBDIR)/gdb_client_ora.pc oname=gdb_client_ora.c               \
        include=$(XDBDIR)/precomp/public include=$(GSIDIR) include=$(GDBDIR) include=$(GDBDIR) \
        sqlcheck=semantics  MAXOPENCURSORS=44 HOLD_CURSOR=yes RELEASE_CURSOR=no
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
	@echo "|  BUILDING G2-ORA80 (${BLDCOD}) on $(PLATFM)
	@echo "+================================================
	@echo "|
	@echo "| ENVIRONMENT
	@echo "|   Bridge      : $(GDBVER) ($(KB_VER))"
	@echo "|   OS Ver      : $(OS_VER)
	@echo "|   GSI         : $(GSIDIR) ($(GSIVER))"
	@echo "|
	@echo "| SOURCES
	@echo "|   Source      : $(GDBDIR)
	@echo "|   DBase       : $(XDBDIR)
	@echo "|
	@echo "+================================================


