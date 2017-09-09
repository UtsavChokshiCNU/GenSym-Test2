# Defines
# -------
PLATFM = linux

include ${SRCBOX}/g2db/mak/unix.def

OS_VER = 6.2
DB_VER = 8.1
DB_GRP = 8
DBNAME = ORACLE
XDBDIR = /gensym/spare/bridges/linux/dbs/oracle/817

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
	@cd $(EXEDIR)
	@cc  -L$(XDBDIR)/lib -L${GSIDIR} -o g2-ora81 gdb_main.o gdb_g2_server.o gdb_common.o  \
        gdb_utils.o gsi_brg.o ${SPECFC}/nsleep.o gdb_client_inter_ora.o gdb_client_ora.o  \
        -lgsi -ltcp -lnogsec -lrtl -lclntst8 `cat $(XDBDIR)/lib/ldflags`                  \
        `cat $(XDBDIR)/lib/sysliblist` -ldl -lm
	@chmod +x g2-ora81
	@ls -l g2-ora81

# Compilation
# -----------
gdb_main.o:                 $(GDBDIR)/gdb_main.c                \
                            $(GSIDIR)/gsi_main.h                \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_utils.h
	@cc -c -I$(GDBDIR) -I$(GSIDIR) -D$(DBNAME) -D$(PLATFM) -DDB_VER=\"$(DB_VER)\" -DKB_VER=$(KB_VER) \
        -DGSI_VER=\"$(GSIVER)\" -D GDB_VER=\"$(GDBVER)\" -D BUILD_CODE=\"$(BLDCOD)\" $(GDBDIR)/gdb_main.c
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
	@cc -c -I$(GDBDIR) -I$(GSIDIR) -DKB_VER=$(KB_VER) -D$(DBNAME) $(GDBDIR)/gdb_g2_server.c
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
	@cc -c -I$(GDBDIR) -I$(GSIDIR) -D$(DBNAME) $(GDBDIR)/gdb_common.c
	@ls -l gdb_common.o

gdb_utils.o:                $(GDBDIR)/gdb_utils.c               \
                            $(GDBDIR)/gdb_globals.h
	@cc -c -I$(GDBDIR) -I$(GSIDIR) -D$(DBNAME) $(GDBDIR)/gdb_utils.c
	@ls -l gdb_utils.o

gsi_brg.o:                  $(AUTHDR)/gsi_brg.c
	@cc -c -D$(PLATFM) $(AUTHDR)/gsi_brg.c
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
	@cc -c  -I$(GDBDIR) -I$(GSIDIR) -I$(XDBDIR)/precomp/public -D$(DBNAME) $(GDBDIR)/gdb_client_inter_ora.c
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
	@cc -c -D $(PLATFM) -D iDBVER=$(DB_GRP) -I$(GDBDIR) -I$(GSIDIR) -I$(GDBDIR) -I$(XDBDIR)/precomp/public \
        -DMAXOPENCURSORS=44 -DHOLD_CURSOR="yes" -DRELEASE_CURSOR="no" -D$(DBNAME) gdb_client_ora.c
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
        include=$(GDBDIR)  include=$(GDBDIR) include=$(XDBDIR)/precomp/public include=$(GSIDIR) \
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
	@echo "+================================================"
	@echo "|  BUILDING G2-ORA81 (${BLDCOD}) on $(PLATFM)    "
	@echo "+================================================"
	@echo "|                                                "
	@echo "| ENVIRONMENT                                    "
	@echo "|   Bridge      : $(GDBVER) ($(KB_VER))          "
	@echo "|   OS Ver      : $(OS_VER)                      "
	@echo "|   GSI         : $(GSIDIR) ($(GSIVER))          "
	@echo "|                                                "
	@echo "| SOURCES                                        "
	@echo "|   Source      : $(GDBDIR)                      "
	@echo "|   Common      : $(GDBDIR)                      "
	@echo "|   DBase       : $(XDBDIR)                      "
	@echo "|                                                "
	@echo "+================================================"

