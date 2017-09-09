# ==========================================================================
#
#              make file to create g2-odbc for Linux
#
#    - make sure that SRCBOX and DSTBOX are defined
#    - cd to destination directory (typically %DSTBOX%\g2odbc\opt)
#    - Supervisor will build the bridge with:
#
#           make -f %SRCBOX%\g2db\mak\g2-odbc-3-linux.mak
#
#    - If the environment variable GSIDIR is specified, it will be used as
#      as the location of GSI.  Otherwise, if you are building the bridge 
#      in a sandbox that does not contain a build of GSI, you should add
#      "gsiab=t" to the command line to force the version of GSI in 
#      k:\bt\ab\dst\intelnt\gsi\test to be used, e.g.,
#                  
# ==========================================================================
# Defines
# -------
include ${SRCBOX}/g2db/mak/unix.def

OS_VER = 4.0
DB_VER = 3
DBNAME = ODBC

GDBDIR = $(SRCBOX)/g2db/c
AUTHDR = $(SRCBOX)/g2db/c/authorize

OSCODE = LINUX
PLATFM = linux

GSISRC=$(SRCBOX)/gsi/c
CFLAGS=

# Executable:
# -----------
g2-odbc:                settings                          \
                        gdb_main.o                        \
                        gdb_g2_server.o                   \
                        gdb_common.o                      \
                        gdb_utils.o                       \
                        gsi_brg.o                         \
                        $(EXTDIR)/nsleep.o                \
                        gdb_client_inter_odbc.o           \
                        gdb_client_odbc.o                 
	@cd $(EXEDIR)
	@$(GCC) -Wl,--wrap=memcpy -o g2-odbc -L${GSIDIR} -L${EXTDIR} -L${RTLDIR} \
        gdb_main.o gdb_g2_server.o gdb_common.o  gdb_utils.o gsi_brg.o            \
        $(EXTDIR)/nsleep.o gdb_client_inter_odbc.o  gdb_client_odbc.o      \
        -lgsi -ltcp -liodbc -liodbcinst -lrtl -ldl -lm -lz
	@chmod +x g2-odbc
	@ls -l g2-odbc

# Compilation
# -----------
gdb_main.o:                 $(GDBDIR)/gdb_main.c                \
                            $(GSICDIR)/gsi_main.h                \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_utils.h                   
	@$(CC) $(CFLAGS) $(SRCBOX)/g2db/mak/gbch.c -o $(SRCBOX)/g2db/mak/gbch
	@rm -f gbch.o
	@$(SRCBOX)/g2db/mak/gbch > $(GDBDIR)/build_code.h
	@$(CC) $(CFLAGS) -c -I$(GSISRC) -I$(GDBDIR) -I$(GSICDIR) -D$(DBNAME) -DDB_TYPE=\"$(DBNAME)\" -D$(OSCODE) -DDB_VER=\"$(DB_VER)\"      \
            -DGSI_VER=\"$(GSIVER)\" -DGDB_VER=\"$(GDBVER)\" -DSUPPORT_GSI_CONNECTION_STR -DGSI_USE_NEW_SYMBOL_API $(GDBDIR)/gdb_main.c
	@ls -l gdb_main.o

gdb_g2_server.o:            $(GDBDIR)/gdb_g2_server.c           \
                            $(GSICDIR)/gsi_main.h                \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_g2_server.h           \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_common.h              \
                            $(GDBDIR)/gdb_genda.h
	@$(CC) $(CFLAGS) -ansi -c -DKB_VER=$(KB_VER) -I$(GSISRC) -I$(GDBDIR) -I$(GSICDIR) -D$(DBNAME) -D$(OSCODE) -DSUPPORT_GSI_CONNECTION_STR -DGSI_USE_NEW_SYMBOL_API $(GDBDIR)/gdb_g2_server.c
	@ls -l gdb_g2_server.o

gdb_common.o:               $(GDBDIR)/gdb_common.c              \
                            $(GSICDIR)/gsi_main.h                \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_genda.h               \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_common.h              \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_g2_client.h
	@$(CC) $(CFLAGS) -c -I$(GDBDIR) -I$(GSISRC) -I$(GSICDIR) -D$(DBNAME) -D$(OSCODE) -DSUPPORT_GSI_CONNECTION_STR -DGSI_USE_NEW_SYMBOL_API $(GDBDIR)/gdb_common.c
	@ls -l gdb_common.o

gdb_utils.o:                $(GDBDIR)/gdb_utils.c               \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_globals.h
	@$(CC) $(CFLAGS) -ansi -c -I$(GDBDIR) -I$(GSISRC) -I$(GSICDIR) -D$(DBNAME) -D$(OSCODE) -DSUPPORT_GSI_CONNECTION_STR -DGSI_USE_NEW_SYMBOL_API $(GDBDIR)/gdb_utils.c
	@ls -l gdb_utils.o

gsi_brg.o:                  $(AUTHDR)/gsi_brg.c
	@$(CC) $(CFLAGS) -c -D$(OSCODE) $(AUTHDR)/gsi_brg.c
	@ls -l gsi_brg.o

gdb_client_inter_odbc.o:  $(GDBDIR)/gdb_client_inter_odbc.c   \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_genda.h               \
                            $(GDBDIR)/gdb_client_odbc.h         \
                            $(GDBDIR)/gdb_client_inter_odbc.h   \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GDBDIR)/gdb_context.h             \
                            $(GSISRC)/gsi_main.h                \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_common.h
	@$(CC) $(CFLAGS) -ansi -c -I$(GSISRC) -I$(GDBDIR) -I$(GSICDIR) -D${OSCODE} -DSUPPORT_GSI_CONNECTION_STR -DGSI_USE_NEW_SYMBOL_API $(GDBDIR)/gdb_client_inter_odbc.c
	@ls -l gdb_client_inter_odbc.o

gdb_client_odbc.o:        $(GDBDIR)/gdb_client_odbc.c         \
                            $(GDBDIR)/gdb_client_odbc.h         \
                            $(GDBDIR)/gdb_client_inter_odbc.h   \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GSISRC)/gsi_main.h                \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_common.h              \
                            $(GDBDIR)/gdb_g2_client.h
	@$(CC) $(CFLAGS) -ansi -c -I$(GSISRC) -I$(GDBDIR) -I$(GSICDIR) -D$(DBNAME) -D$(OSCODE) \
        -DSUPPORT_GSI_CONNECTION_STR -DGSI_USE_NEW_SYMBOL_API $(GDBDIR)/gdb_client_odbc.c
	@ls -l gdb_client_odbc.o

# Remove intermediate files
# -------------------------
clean:
	@- rm *.o 2> /dev/null

# Report:
# -------
settings:
	@echo "+================================================"
	@echo "|  BUILDING G2-ODBC on $(PLATFM)                 "
	@echo "+================================================"
	@echo "|                                                "
	@echo "| ENVIRONMENT                                    "
	@echo "|   Bridge     : $(GDBVER) ($(KB_VER))           "
	@echo "|   OS Ver     : $(OS_VER)                       "
	@echo "|   GSI        : $(GSICDIR) $(GSIDIR) ($(GSIVER))"
	@echo "|                                                "
	@echo "| SOURCES                                        "
	@echo "|   Source     : $(GDBDIR)                       "
	@echo "|                                                "
	@echo "+================================================"

# Local Variables: ***
# mode:makefile ***
# End: ***
