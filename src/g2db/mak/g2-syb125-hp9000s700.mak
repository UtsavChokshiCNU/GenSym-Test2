# Defines
# -------
PLATFM = hp9000s700

include ${SRCBOX}/g2db/mak/unix.def

OS_VER = 11.0
DB_VER = 12.5
DBNAME = SYBASE
XDBDIR = /gensym/bridges/hp9000s700/dbs/sybase/1250

# Executable:
# -----------
g2-syb125:                  settings                            \
                            gdb_main.o                          \
                            gdb_g2_server.o                     \
                            gdb_common.o                        \
                            gdb_utils.o                         \
                            gsi_brg.o                           \
                            ${SPECFC}/nsleep.o                  \
                            gdb_client_inter_syb.o\
                            gdb_client_syb.o
	@gcc -ansi -L$(XDBDIR)/OCS-12_5/lib -L${GSIDIR} -O -Wl,+s,+vallcompatwarnings -static -Dhp9000s700       \
        -o g2-syb125 gdb_main.o gdb_g2_server.o gdb_utils.o gdb_common.o gdb_client_inter_syb.o     \
        gdb_client_syb.o gsi_brg.o ${SPECFC}/nsleep.o -lct -lcs -ltcl -lcomn -lintl -Wl,-a,default  \
        -lgsi -lrtl -ltcp -lnogsec -lcl -lm -lBSD
	@chmod +x g2-syb125
	@chatr +s enable g2-syb125
	@ls -l g2-syb125

# Compilation
# -----------
gdb_main.o:                 $(GDBDIR)/gdb_main.c                \
                            $(GSIDIR)/gsi_main.h                \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_utils.h
	@gcc -ansi -c  \
        -I$(GDBDIR) -I$(GSIDIR) -D$(DBNAME) -D$(PLATFM) -D DB_VER=\"$(DB_VER)\" \
        -D GSI_VER=\"$(GSIVER)\" -D GDB_VER=\"$(GDBVER)\" -D BUILD_CODE=\"$(BLDCOD)\" \
        $(GDBDIR)/gdb_main.c
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

gdb_client_inter_syb.o:     $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_genda.h               \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GDBDIR)/gdb_client_syb.h          \
                            $(GDBDIR)/gdb_client_inter_syb.c
	@gcc -ansi -c  -I$(GDBDIR) -I$(GSIDIR) -I$(XDBDIR)/OCS-12_5/include -D$(DBNAME) $(GDBDIR)/gdb_client_inter_syb.c
	@ls -l gdb_client_inter_syb.o 

gdb_client_syb.o:           $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GDBDIR)/gdb_client_syb.h          \
                            $(GDBDIR)/gdb_client_inter_syb.h    \
                            $(GDBDIR)/gdb_client_syb.cp         \
                            gdb_client_syb.c
	@gcc -ansi -c -D $(PLATFM) -D iDBVER=$(DB_VER) -I$(GDBDIR) -I$(GSIDIR) -I$(GDBDIR) -I$(XDBDIR)/OCS-12_5/include \
        -D$(DBNAME) -DMAXOPENCURSORS=44 -DHOLD_CURSOR=YES -DRELEASE_CURSOR=NO gdb_client_syb.c
	@ls -l gdb_client_syb.o


# Precompiler
# -----------
gdb_client_syb.c:           $(GDBDIR)/gdb_client_syb.cp 
	@$(XDBDIR)/OCS-12_5/bin/cpre -CKR_C -I $(GDBDIR) -I $(XDBDIR)/OCS-12_5/include -O gdb_client_syb.c $(GDBDIR)/gdb_client_syb.cp
	@ls -l gdb_client_syb.c

# Remove intermediate files
# -------------------------
clean :
	@- rm *.o 2> /dev/null
	@- rm gdb_client_syb.c 2> /dev/null

# Report:
# -------
settings:
	@echo "+=============================================================
	@echo "|  BUILDING G2-SYB125 (${BLDCOD}) on $(PLATFM)
	@echo "+=============================================================
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
	@echo "+===========================================================

