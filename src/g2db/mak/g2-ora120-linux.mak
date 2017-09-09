# Defines
# -------
include ${SRCBOX}/g2db/mak/unix.def

OS_VER = 2
DB_VER = 12
DB_GRP = 12
DBNAME = ORACLE
XDBDIR = ${SRCBOX}/g2db/dbs/$(PLATFM)/oracle/instantclient_12_1

# Executable:
# -----------
g2-ora12:                   settings                            \
                            gdb_main.o                          \
                            gdb_g2_server.o                     \
                            gdb_common.o                        \
                            gdb_utils.o                         \
                            gsi_brg.o                           \
                            ${EXTDIR}/nsleep.o                  \
                            gdb_client_inter_ora.o              \
                            gdb_client_ora12.o
	@cd $(EXEDIR)
	@$(GCC) -L$(XDBDIR) -L${GSIDIR} -L${EXTDIR} -L${RTLDIR} -o g2-ora12 \
		-Wl,--wrap=memcpy ${EXTDIR}/nsleep.o \
		gdb_main.o gdb_g2_server.o gdb_common.o \
	        gdb_utils.o gsi_brg.o gdb_client_inter_ora.o gdb_client_ora12.o \
		-lgsi -ltcp -lnogsec -lrtl -lclntsh -ldl -lm
	@chmod +x g2-ora12
	@ls -l g2-ora12

# Compilation
# -----------
gdb_main.o:                 $(GDBDIR)/gdb_main.c                \
                            $(GSICDIR)/gsi_main.h               \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_utils.h
	@$(CC) -c -I$(GDBDIR) -I$(GSICDIR) -D$(DBNAME) -D$(PLATFM) -DDB_VER=\"$(DB_VER)\" -DKB_VER=$(KB_VER) \
        -DGSI_VER=\"$(GSIVER)\" -D GDB_VER=\"$(GDBVER)\" -D BUILD_CODE=\"$(BLDCOD)\" $(GDBDIR)/gdb_main.c
	@ls -l gdb_main.o

gdb_g2_server.o:            $(GDBDIR)/gdb_g2_server.c           \
                            $(GSICDIR)/gsi_main.h               \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_g2_server.h           \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_common.h              \
                            $(GDBDIR)/gdb_genda.h
	@$(CC) -c -I$(GDBDIR) -I$(GSICDIR) -DKB_VER=$(KB_VER) -D$(DBNAME) $(GDBDIR)/gdb_g2_server.c
	@ls -l gdb_g2_server.o

gdb_common.o:               $(GDBDIR)/gdb_common.c              \
                            $(GSICDIR)/gsi_main.h               \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_genda.h               \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_common.h              \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_g2_client.h
	@$(CC) -c -I$(GDBDIR) -I$(GSICDIR) -D$(DBNAME) $(GDBDIR)/gdb_common.c
	@ls -l gdb_common.o

gdb_utils.o:                $(GDBDIR)/gdb_utils.c               \
                            $(GDBDIR)/gdb_globals.h
	@$(CC) -c -I$(GDBDIR) -I$(GSICDIR) -D$(DBNAME) $(GDBDIR)/gdb_utils.c
	@ls -l gdb_utils.o

gsi_brg.o:                  $(AUTHDR)/gsi_brg.c
	@$(CC) -c -D$(PLATFM) $(AUTHDR)/gsi_brg.c
	@ls -l gsi_brg.o

gdb_client_inter_ora.o:     $(GDBDIR)/gdb_client_inter_ora.c    \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_genda.h               \
                            $(GDBDIR)/gdb_client_ora.h          \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GDBDIR)/gdb_context.h             \
                            $(GSICDIR)/gsi_main.h               \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_common.h
	@$(CC) -c  -I$(GDBDIR) -I$(GSICDIR) -I$(XDBDIR)/sdk/include -D$(DBNAME) $(GDBDIR)/gdb_client_inter_ora.c
	@ls -l gdb_client_inter_ora.o

gdb_client_ora12.o:         gdb_client_ora12.c                  \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_client_ora.h          \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GSICDIR)/gsi_main.h               \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_common.h              \
                            $(GDBDIR)/gdb_g2_client.h
	@$(CC) -c -D $(PLATFM) -D iDBVER=$(DB_GRP) -I$(GDBDIR) -I$(GSICDIR) -I$(GDBDIR) -I$(XDBDIR)/sdk/include \
        -DORA09 -DHYBRID -DMAXOPENCURSORS=44 -DHOLD_CURSOR="yes" -DRELEASE_CURSOR="no" -D$(DBNAME) gdb_client_ora12.c
	@ls -l gdb_client_ora12.o

# Precompiler
# -----------
gdb_client_ora12.c:         $(GDBDIR)/gdb_client_ora.pc         \
                            $(GDBDIR)/gdb_client_ora.h          \
                            $(GDBDIR)/gdb_common.h              \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_g2_client.h           \
                            $(GDBDIR)/gdb_genda.h               \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GDBDIR)/gdb_utils.h

	@$(XDBDIR)/sdk/proc iname=$(GDBDIR)/gdb_client_ora.pc oname=gdb_client_ora12.c \
        include=$(GDBDIR)  include=$(GSICDIR) include=$(XDBDIR)/sdk/include \
        SQLCHECK=SEMANTICS MAXOPENCURSORS=44 HOLD_CURSOR=yes RELEASE_CURSOR=no
	@ls -l gdb_client_ora12.c

# Remove intermediate files
# -------------------------
clean :
	@- rm *.o 2> /dev/null
	@- rm tp* 2> /dev/null
	@- rm gdb_client_ora12.c 2> /dev/null

# Report:
# -------
settings:
	@echo "+================================================"
	@echo "|  BUILDING G2-ORA12 (${BLDCOD}) on $(PLATFM)    "
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
