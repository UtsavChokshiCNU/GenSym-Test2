# ==========================================================================
#
#               make file to create g2-ora92.exe for Windows
#
#    - make sure that SRCBOX and DSTBOX are defined
#    - cd to destination directory (typically %DSTBOX%\g2odbc\opt)
#    - Supervisor will build the bridge with:
#
#              nmake /f %SRCBOX%\g2db\mak\g2-ora92-intel.mak
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
!INCLUDE g2db-win.def

OS_VER = 4.0
DB_VER = 9.2
DB_GRP = 9
DBNAME = ORACLE

GDBDIR = $(SRCBOX)\g2db\c
AUTHDR = $(SRCBOX)\g2db\c\Authorize
XDBDIR = k:\gensym\spare\bridges\intelnt\dbs\oracle\920

OSCODE = WIN32
PLATFM = intelnt
SPECFC = $(SRCBOX)\specific\$(PLATFM)
!IF "$(GSIDIR)" == ""
!IF DEFINED(gsiab)
GSIDIR = k:\bt\ab\dst\$(PLATFM)\gsi\test
!ELSE
GSIDIR = $(SRCBOX)\dst\$(PLATFM)\gsi\test
!ENDIF
!ENDIF

# Executable
# ----------
g2-ora92.exe:               settings                            \
                            gdb_main.obj                        \
                            gdb_g2_server.obj                   \
                            gdb_common.obj                      \
                            gdb_utils.obj                       \
                            gsi_brg.obj                         \
                            $(SPECFC)\nsleep.obj                \
                            gdb_client_inter_ora.obj            \
                            gdb_client_ora.obj                  \
                            g2-ora92.res
	@link -out:g2-ora92.exe -nologo  -incremental:no -machine:I386 -nodefaultlib:libcmt                    \
        -libpath:"$(SPECFC)" -libpath:"$(GSIDIR)" -libpath:$(XDBDIR)\lib -libpath:$(XDBDIR)\precomp\lib  \
        gdb_main.obj gdb_g2_server.obj gdb_common.obj  gdb_utils.obj gsi_brg.obj $(SPECFC)\nsleep.obj    \
        gdb_client_inter_ora.obj  gdb_client_ora.obj g2-ora92.res                                        \
        librtl.lib libgsi.lib libtcp.lib libnogsec.lib advapi32.lib gdi32.lib kernel32.lib netapi32.lib  \
        shell32.lib user32.lib uuid.lib winspool.lib wsock32.lib orasql9.lib spromeps.lib rpcrt4.lib
	@echo g2-ora92.exe

# Compilation
# -----------

gdb_main.obj:               $(GDBDIR)\gdb_main.c                \
                            $(GSIDIR)\gsi_main.h                \
                            $(GDBDIR)\gdb_globals.h             \
                            $(GDBDIR)\gdb_utils.h
	@cl $(SRCBOX)\g2db\mak\gbch.c -nologo -o $(SRCBOX)\g2db\mak\gbch.exe
	@del gbch.obj
	@$(SRCBOX)\g2db\mak\gbch.exe > $(GDBDIR)\build_code.h
	@del $(SRCBOX)\g2db\mak\gbch.exe
	@cl -c -nologo -ML -W3 -GX -O2 \
        -I$(GDBDIR) -I$(GSIDIR) -D$(DBNAME) -D$(OSCODE) -DDB_VER=\"$(DB_VER)\" \
        -DGSI_VER=\"$(GSIVER)\" -D GDB_VER=\"$(GDBVER)\" $(GDBDIR)/gdb_main.c
#       -DGSI_VER=\"$(GSIVER)\" -D GDB_VER=\"$(GDBVER)\" -D BUILD_CODE=\"$(BLDCOD)\" $(GDBDIR)/gdb_main.c
	@del $(GDBDIR)\build_code.h

gdb_g2_server.obj:          $(GDBDIR)\gdb_g2_server.c           \
                            $(GSIDIR)\gsi_main.h                \
                            $(GDBDIR)\gdb_globals.h             \
                            $(GDBDIR)\gdb_utils.h               \
                            $(GDBDIR)\gdb_g2_server.h           \
                            $(GDBDIR)\gdb_messages.h            \
                            $(GDBDIR)\gdb_context.h             \
                            $(GDBDIR)\gdb_common.h              \
                            $(GDBDIR)\gdb_genda.h
	@cl -c -nologo -ML -W3 -GX -O2 -I$(GDBDIR) -I$(GSIDIR) -DKB_VER=$(KB_VER) -D$(DBNAME) $(GDBDIR)\gdb_g2_server.c

gdb_common.obj:             $(GDBDIR)\gdb_common.c              \
                            $(GSIDIR)\gsi_main.h                \
                            $(GDBDIR)\gdb_globals.h             \
                            $(GDBDIR)\gdb_genda.h               \
                            $(GDBDIR)\gdb_messages.h            \
                            $(GDBDIR)\gdb_context.h             \
                            $(GDBDIR)\gdb_common.h              \
                            $(GDBDIR)\gdb_utils.h               \
                            $(GDBDIR)\gdb_g2_client.h
	@cl -c -nologo -ML -W3 -GX -O2 -I$(GDBDIR) -I$(GSIDIR) $(GDBDIR)\gdb_common.c

gdb_utils.obj:              $(GDBDIR)\gdb_utils.c               \
                            $(GDBDIR)\gdb_globals.h
	@cl -c -nologo -ML -W3 -GX -O2 -I$(GDBDIR) -I$(GSIDIR) $(GDBDIR)\gdb_utils.c

gsi_brg.obj:                $(AUTHDR)/gsi_brg.c
	@cl -c -nologo -ML -W3 -GX -O2 -D$(OSCODE) $(AUTHDR)/gsi_brg.c

gdb_client_inter_ora.obj:   $(GDBDIR)\gdb_client_inter_ora.c    \
                            $(GDBDIR)\gdb_globals.h             \
                            $(GDBDIR)\gdb_genda.h               \
                            $(GDBDIR)\gdb_client_ora.h          \
                            $(GDBDIR)\gdb_messages.h            \
                            $(GDBDIR)\gdb_context.h             \
                            $(GSIDIR)\gsi_main.h                \
                            $(GDBDIR)\gdb_utils.h               \
                            $(GDBDIR)\gdb_common.h
	@cl -c  -nologo -ML -W3 -GX -O2 -I$(GDBDIR) -I$(GSIDIR) -I$(XDBDIR)\precomp\public -DWIN32 $(GDBDIR)\gdb_client_inter_ora.c
 
gdb_client_ora.obj:         gdb_client_ora.c                    \
                            $(GDBDIR)\gdb_globals.h             \
                            $(GDBDIR)\gdb_client_ora.h          \
                            $(GDBDIR)\gdb_globals.h             \
                            $(GDBDIR)\gdb_messages.h            \
                            $(GSIDIR)\gsi_main.h                \
                            $(GDBDIR)\gdb_context.h             \
                            $(GDBDIR)\gdb_utils.h               \
                            $(GDBDIR)\gdb_common.h              \
                            $(GDBDIR)\gdb_g2_client.h
	@cl -c -nologo -ML -W3 -GX -O2 -DWIN32 -DiDBVER=$(DB_GRP) -DORA09  \
        -DMAXOPENCURSORS=44 -DHOLD_CURSOR="yes" -DRELEASE_CURSOR="no"   \
        -I$(GDBDIR) -I$(GSIDIR) -I$(GDBDIR) -I$(XDBDIR)\precomp\public gdb_client_ora.c

# Precompiler
# -----------
gdb_client_ora.c:           $(GDBDIR)\gdb_client_ora.pc         \
                            $(GDBDIR)\gdb_client_ora.h          \
                            $(GDBDIR)\gdb_common.h              \
                            $(GDBDIR)\gdb_context.h             \
                            $(GDBDIR)\gdb_g2_client.h           \
                            $(GDBDIR)\gdb_genda.h               \
                            $(GDBDIR)\gdb_globals.h             \
                            $(GDBDIR)\gdb_messages.h            \
                            $(GDBDIR)\gdb_utils.h
	@$(XDBDIR)\bin\proc.exe $(GDBDIR)\gdb_client_ora.pc oname=gdb_client_ora.c \
       SQLCHECK=SEMANTICS MAXOPENCURSORS=44 HOLD_CURSOR=yes RELEASE_CURSOR=no
	@echo gdb_client_ora.pc


# Resources
# ---------
g2-ora92.res:               $(GDBDIR)\g2-ora92.rc               \
                            $(GDBDIR)\oracle_res.h              \
                            $(GDBDIR)\oracle.ico
	@rc.exe /l 0x409 /d "NDEBUG" /fog2-ora92.res $(GDBDIR)\g2-ora92.rc
	@echo g2-ora92.res

# Remove intermediate files
# -------------------------
clean:
    @- del *.obj
    @- del gdb_client_ora.c
    @- del g2-ora92.res
    @- del g2-ora92.lib
    @- del g2-ora92.exp

# Report:
# -------
settings:
	@echo "+================================================
	@echo "|  BUILDING G2-ORA92 on $(PLATFM)
	@echo "+================================================
	@echo "|                                                
	@echo "| ENVIRONMENT                                    
	@echo "|   Bridge      : $(GDBVER) ($(KB_VER))          
	@echo "|   OS Ver      : $(OS_VER)                      
	@echo "|   GSI         : $(GSIDIR) ($(GSIVER))          
	@echo "|                                                
	@echo "| SOURCES                                        
	@echo "|   Source      : $(GDBDIR)                      
	@echo "|   DBase       : $(XDBDIR)                      
	@echo "|                                                
	@echo "+================================================

