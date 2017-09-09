# Defines
# -------
PLATFM = alphaosf

include ${SRCBOX}/g2db/mak/unix.def

OS_VER = 5.1
DB_VER = 11
XDBDIR = /gensym/bridges/alphaosf/dbs/sybase/1110

DBNAME = SYBASE

# Executable:
# -----------
g2-syb11:                   settings                            \
                            gdb_main.o                          \
                            gdb_g2_server.o                     \
                            gdb_common.o                        \
                            gdb_utils.o                         \
                            gsi_brg.o                           \
                            ${SPECFC}/nsleep.o                  \
                            gdb_client_inter_syb.o              \
                            gdb_client_syb.o
	@cc -g -L$(XDBDIR)/lib -L${GSIDIR} -o g2-syb11 gdb_main.o             \
            gdb_g2_server.o gdb_common.o gdb_utils.o gdb_client_inter_syb.o   \
            gdb_client_syb.o gsi_brg.o ${SPECFC}/nsleep.o -lgsi -ltcp -lnogsec -lrtl   \
            /usr/lib/libdb.a -lct -lcs -lcomn -ltcl -lintl -lm
	@chmod +x g2-syb11
	@ls -l g2-syb11

# Compilation
# -----------
gdb_main.o:                 $(GDBDIR)/gdb_main.c                \
                            $(GSIDIR)/gsi_main.h                \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_utils.h
	@cc -c -I$(GDBDIR) -I$(GSIDIR) -D$(DBNAME) -D$(PLATFM) -DDB_VER=\"$(DB_VER)\" -DKB_VER=$(KB_VER) \
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

gdb_client_inter_syb.o:     $(GDBDIR)/gdb_client_inter_syb.c	\
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_genda.h               \
                            $(GDBDIR)/gdb_client_syb.h          \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GDBDIR)/gdb_context.h             \
                            $(GSIDIR)/gsi_main.h                \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_common.h
	@cc -c  -I$(GDBDIR) -I$(GSIDIR) -I$(XDBDIR)/include -D$(DBNAME) $(GDBDIR)/gdb_client_inter_syb.c
	@ls -l gdb_client_inter_syb.o

gdb_client_syb.o:           gdb_client_syb.c                    \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GDBDIR)/gdb_client_syb.h          \
                            $(GDBDIR)/gdb_client_inter_syb.h
	@cc -c -I$(GDBDIR) -I$(GDBDIR) -I$(XDBDIR)/include -I$(GSIDIR)      \
        -D$(DBNAME) -DMAXOPENCURSORS=44 -DHOLD_CURSOR=YES -DRELEASE_CURSOR=NO gdb_client_syb.c
	@ls -l gdb_client_syb.o

# Precompiler
# -----------
gdb_client_syb.c:           $(GDBDIR)/gdb_client_syb.cp
	@$(XDBDIR)/bin/cpre -CKR_C -I $(GDBDIR) -I $(XDBDIR)/include        \
        -O gdb_client_syb.c $(GDBDIR)/gdb_client_syb.cp
	@ls -l gdb_client_syb.c

# Remove intermediate files
# -------------------------
clean :
	@- rm *.o 2> /dev/null
	@- rm gdb_client_syb.c 2> /dev/null

# Report:
# -------
settings:
	@echo "+===========================================================
	@echo "|  BUILDING G2-SYB11 (${BLDCOD}) on $(PLATFM)
	@echo "+===========================================================
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
	@echo "+===========================================================


