# Defines
# -------
PLATFM = sparcsol
OSCODE = sparcsol

include ${SRCBOX}/g2db/mak/unix.def

OS_VER = 5.6
DB_VER = 8.1
DB_GRP = 8
DBNAME = ORACLE
XDBDIR = /gensym/spare/bridges/sparcsol/dbs/oracle/817

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
	@gcc -ansi -L$(XDBDIR)/lib -L${GSIDIR} -o g2-ora81                                              \
        gdb_main.o gdb_g2_server.o gdb_common.o gdb_utils.o gdb_client_inter_ora.o gdb_client_ora.o \
        gsi_brg.o ${SPECFC}/nsleep.o -lgsi -ltcp -lnogsec -lrtl -lclntst8                           \
        `cat /gensym/spare/bridges/sparcsol/dbs/oracle/817/lib/ldflags`                             \
        `cat /gensym/spare/bridges/sparcsol/dbs/oracle/817/lib/sysliblist`                          \
        -R/gensym/spare/bridges/sparcsol/dbs/oracle/817/lib -laio -lm  -lthread -ldl
	@chmod +x g2-ora81
	@ls -l g2-ora81

# Compilation
# -----------
gdb_main.o:                 $(GDBDIR)/gdb_main.c                \
                            $(GSIDIR)/gsi_main.h                \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_utils.h
	@gcc -g -ansi -c -I$(GDBDIR) -I$(GSIDIR) -D$(DBNAME) -D$(OSCODE) -DDB_VER=\"$(DB_VER)\" \
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
	@gcc -g -ansi  -c -I$(GDBDIR) -I$(GSIDIR) -DKB_VER=$(KB_VER) -D$(DBNAME) $(GDBDIR)/gdb_g2_server.c
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
	@gcc -g -ansi  -c -I$(GDBDIR) -I$(GSIDIR) -D$(DBNAME) $(GDBDIR)/gdb_common.c
	@ls -l gdb_common.o

gdb_utils.o:                $(GDBDIR)/gdb_utils.c               \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_globals.h
	@gcc -g -ansi  -c -I$(GDBDIR) -I$(GSIDIR) -D$(DBNAME) $(GDBDIR)/gdb_utils.c
	@ls -l gdb_utils.o

gsi_brg.o:                  $(AUTHDR)/gsi_brg.c
	@gcc -g -ansi -c -D$(PLATFM) $(AUTHDR)/gsi_brg.c
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
	@gcc -g -ansi  -c  -I$(GDBDIR) -I$(GSIDIR) -I$(XDBDIR)/precomp/public -D$(DBNAME) $(GDBDIR)/gdb_client_inter_ora.c
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
	@gcc -g -ansi -c -I$(GDBDIR) -I$(GDBDIR) -I$(GSIDIR) -I$(XDBDIR)/precomp/public -DiDBVER=$(DB_GRP) \
		-D$(DBNAME) -DMAXOPENCURSORS=44 -DHOLD_CURSOR="yes" -DRELEASE_CURSOR="no" gdb_client_ora.c
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
	@echo "|   DBase       : $(XDBDIR)
	@echo "|
	@echo "+================================================


