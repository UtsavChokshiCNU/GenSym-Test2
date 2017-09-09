# ==========================================================================
#
#              make file to create g2-odbc.exe for Windows
#
#    - make sure that SRCBOX and DSTBOX are defined
#    - cd to destination directory (typically %DSTBOX%\g2odbc\opt)
#    - Supervisor will build the bridge with:
#
#           nmake /f %SRCBOX%\g2db\mak\g2-odbc-3-intel.mak
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
DB_VER = 3
DBNAME = ODBC

GDBDIR = $(SRCBOX)\g2db\c
AUTHDR = $(SRCBOX)\g2db\c\authorize

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

GSISRC=$(SRCBOX)\gsi\c
SDKINC="C:\Program Files\Microsoft SDK\include"

# Executable:
# -----------
g2-odbc.exe:                settings                            \
                            gdb_main.obj                        \
                            gdb_g2_server.obj                   \
                            gdb_common.obj                      \
                            gdb_utils.obj                       \
                            gsi_brg.obj                         \
                            $(SPECFC)\nsleep.obj                \
                            gdb_client_inter_odbc.obj           \
                            gdb_client_odbc.obj                 \
                            g2odbc.res
	@link -out:g2-odbc.exe -nologo  -incremental:no -machine:I386 -nodefaultlib:libc.lib    \
        -nodefaultlib:libcmt -libpath:$(SPECFC)  -libpath:$(DSTBOX)\ext\opt -libpath:$(DSTBOX)\gsi\opt\ -libpath:$(DSTBOX)\rtl\opt\ -libpath:$(GSIDIR)                          \
        gdb_main.obj gdb_g2_server.obj gdb_common.obj  gdb_utils.obj gsi_brg.obj            \
        $(SPECFC)\nsleep.obj gdb_client_inter_odbc.obj  gdb_client_odbc.obj g2odbc.res      \
        librtl.lib libgsi.lib libtcp.lib libnogsec.lib advapi32.lib gdi32.lib kernel32.lib netapi32.lib  \
        shell32.lib user32.lib ws2_32.lib uuid.lib winspool.lib wsock32.lib odbc32.lib odbccp32.lib    \
        comdlg32.lib ole32.lib oleaut32.lib libcd.lib rpcrt4.lib spromeps.lib
	@dir /b g2-odbc.exe

# Compilation
# -----------
gdb_main.obj:               $(GDBDIR)/gdb_main.c                \
                            $(GSISRC)/gsi_main.h                \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_utils.h
	@cl $(SRCBOX)\g2db\mak\gbch.c -nologo -o $(SRCBOX)\g2db\mak\gbch.exe
	@del gbch.obj
	@$(SRCBOX)\g2db\mak\gbch.exe > $(GDBDIR)\build_code.h
	@del $(SRCBOX)\g2db\mak\gbch.exe
	@cl -c -nologo -ML -W3 -GX -O2 -I$(GSISRC) -I$(GDBDIR) -I$(GSIDIR) -D$(DBNAME) -DDB_TYPE=\"$(DBNAME)\" -D$(OSCODE) -DDB_VER=\"$(DB_VER)\" \
        -DGSI_VER=\"$(GSIVER)\" -DGDB_VER=\"$(GDBVER)\"  -DUNICODE -DSUPPORT_GSI_CONNECTION_STR -DGSI_USE_NEW_SYMBOL_API -DGSI_USE_WIDE_STRING_API $(GDBDIR)/gdb_main.c
#       -DBUILD_CODE=\"$(BLDCOD)\"
	@del $(GDBDIR)\build_code.h

gdb_g2_server.obj:          $(GDBDIR)/gdb_g2_server.c           \
                            $(GSISRC)/gsi_main.h                \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_g2_server.h           \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_common.h              \
                            $(GDBDIR)/gdb_genda.h
	@cl -c -nologo -ML -W3 -GX -O2 -DKB_VER=$(KB_VER) -I$(GSISRC) -I$(GDBDIR) -I$(GSIDIR) -DDB_TYPE=\"$(DBNAME)\" -DUNICODE -DSUPPORT_GSI_CONNECTION_STR -DGSI_USE_NEW_SYMBOL_API -DGSI_USE_WIDE_STRING_API $(GDBDIR)/gdb_g2_server.c

gdb_common.obj:             $(GDBDIR)/gdb_common.c              \
                            $(GSISRC)/gsi_main.h                \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_genda.h               \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_common.h              \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_g2_client.h
	@cl -c -nologo -ML -W3 -GX -O2 -I$(GDBDIR) -I$(GSISRC) -I$(GSIDIR) -DDB_TYPE=\"$(DBNAME)\" -DODBC -DUNICODE -DSUPPORT_GSI_CONNECTION_STR -DGSI_USE_NEW_SYMBOL_API -DGSI_USE_WIDE_STRING_API $(GDBDIR)/gdb_common.c

gdb_utils.obj:              $(GDBDIR)/gdb_utils.c               \
                            $(GDBDIR)/gdb_globals.h
	@cl -c -nologo -ML -W3 -GX -O2 -I$(GDBDIR) -I$(GSISRC) -I$(GSIDIR) -DDB_TYPE=\"$(DBNAME)\" -DUNICODE -DSUPPORT_GSI_CONNECTION_STR -DGSI_USE_NEW_SYMBOL_API -DGSI_USE_WIDE_STRING_API $(GDBDIR)/gdb_utils.c

gsi_brg.obj:                $(AUTHDR)/gsi_brg.c
	@cl -c -nologo -ML -W3 -GX -O2 -D$(OSCODE) $(AUTHDR)/gsi_brg.c

gdb_client_inter_odbc.obj:  $(GDBDIR)/gdb_client_inter_odbc.c   \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_genda.h               \
                            $(GDBDIR)/gdb_client_odbc.h         \
                            $(GDBDIR)/gdb_client_inter_odbc.h   \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GDBDIR)/gdb_context.h             \
                            $(GSISRC)/gsi_main.h                \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_common.h
	@cl -c  -nologo -ML -W3 -GX -O2 -I$(GSISRC) -I$(GDBDIR) -I$(GDBDIR) -I$(GSIDIR) -DDB_TYPE=\"$(DBNAME)\" -DUNICODE -DSUPPORT_GSI_CONNECTION_STR -DGSI_USE_NEW_SYMBOL_API -DGSI_USE_WIDE_STRING_API $(GDBDIR)/gdb_client_inter_odbc.c

gdb_client_odbc.obj:        $(GDBDIR)/gdb_client_odbc.c         \
                            $(GDBDIR)/gdb_client_odbc.h         \
                            $(GDBDIR)/gdb_client_inter_odbc.h   \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GSISRC)/gsi_main.h                \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_common.h              \
                            $(GDBDIR)/gdb_g2_client.h
	@cl -c -nologo -ML -W3 -GX -O2 -I$(GSISRC) -I$(SDKINC) -I$(GDBDIR) -I$(GDBDIR) -I$(GSIDIR) -DDB_TYPE=\"$(DBNAME)\" -DUNICODE -DSUPPORT_GSI_CONNECTION_STR -DGSI_USE_NEW_SYMBOL_API -DGSI_USE_WIDE_STRING_API $(GDBDIR)/gdb_client_odbc.c

# Resources
# ---------
g2odbc.res:         $(GDBDIR)/g2odbc.rc             $(GDBDIR)/odbc_res.h    $(GDBDIR)/odbc.ico
	@rc.exe /l 0x409 /d "NDEBUG" /fog2odbc.res $(GDBDIR)/g2odbc.rc
	@echo g2odbc.res

# Remove intermediate files
# -------------------------
clean:
    @- del *.obj
    @- del *.res
    @- del *.lib
    @- del *.exp

# Report:
# -------
settings:
	@echo "+================================================
	@echo "|  BUILDING G2-ODBC on $(PLATFM)
	@echo "+================================================
	@echo "|
	@echo "| ENVIRONMENT
	@echo "|   Bridge      : $(GDBVER) ($(KB_VER))
	@echo "|   OS Ver      : $(OS_VER)
	@echo "|   GSI         : $(GSIDIR) ($(GSIVER))
	@echo "|
	@echo "| SOURCES
	@echo "|   Source      : $(GDBDIR)
	@echo "|
	@echo "+================================================


