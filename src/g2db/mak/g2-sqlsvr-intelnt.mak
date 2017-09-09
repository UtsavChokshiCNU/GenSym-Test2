# ==========================================================================
#
#              make file to create g2-sqlsvr.exe for Windows
#
#    - make sure that SRCBOX and DSTBOX are defined
#    - cd to destination directory (typically %DSTBOX%\g2sqlsvr\opt)
#    - Supervisor will build the bridge with:
#
#           nmake /f %SRCBOX%\g2db\mak\g2-sqlsvr-intel.mak
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
GSI_USE_NEW_SYMBOL_API = GSI_USE_NEW_SYMBOL_API
UNICODE = UNICODE
GSI_USE_WIDE_STRING_API = GSI_USE_WIDE_STRING_API
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

# Executable:
# -----------
g2-sqlsvr.exe:              settings                            \
                            gdb_main.obj                        \
                            gdb_g2_server.obj                   \
                            gdb_common.obj                      \
                            gdb_utils.obj                       \
                            gsi_brg.obj                         \
                            $(SPECFC)\nsleep.obj                \
                            gdb_client_inter_sqlsvr.obj         \
                            gdb_client_sqlsvr.obj       \
                gdb_sqlsvr.obj                  \
                            g2sqlsvr.res
    @link -out:g2-sqlsvr.exe -nologo  -incremental:no -machine:I386 -nodefaultlib:libc.lib    \
        -nodefaultlib:libcmt -libpath:$(SPECFC) -libpath:$(GSIDIR)                          \
        gdb_main.obj gdb_g2_server.obj gdb_common.obj  gdb_utils.obj gsi_brg.obj            \
        $(SPECFC)\nsleep.obj gdb_client_inter_sqlsvr.obj  gdb_client_sqlsvr.obj gdb_sqlsvr.obj g2sqlsvr.res      \
        librtl.lib libgsi.lib libtcp.lib libnogsec.lib advapi32.lib gdi32.lib kernel32.lib netapi32.lib  \
        shell32.lib user32.lib uuid.lib winspool.lib wsock32.lib odbc32.lib odbccp32.lib     \
        comdlg32.lib ole32.lib oleaut32.lib libcd.lib rpcrt4.lib spromeps.lib shlwapi.lib
    @dir /b g2-sqlsvr.exe

# Compilation
# -----------
gdb_main.obj:               $(GDBDIR)/gdb_main.c                \
                            $(GSIDIR)/gsi_main.h                \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_utils.h
    @cl $(SRCBOX)\g2db\mak\gbch.c -nologo -o $(SRCBOX)\g2db\mak\gbch.exe
    @del gbch.obj
    @$(SRCBOX)\g2db\mak\gbch.exe > $(GDBDIR)\build_code.h
    @del $(SRCBOX)\g2db\mak\gbch.exe
	@cl -c -nologo -ML -W3 -GX -O2 -I$(GDBDIR) -I$(GSIDIR) -D$(DBNAME) -DDB_TYPE=\"$(DBNAME)\" -D$(OSCODE) -D$(UNICODE) -D$(GSI_USE_NEW_SYMBOL_API) -D$(GSI_USE_WIDE_STRING_API) -DDB_VER=\"$(DB_VER)\" \
        -DGSI_VER=\"$(GSIVER)\" -DGDB_VER=\"$(GDBVER)\"  $(GDBDIR)/gdb_main.c
#       -DBUILD_CODE=\"$(BLDCOD)\"
    @del $(GDBDIR)\build_code.h

gdb_g2_server.obj:          $(GDBDIR)/gdb_g2_server.c           \
                            $(GSIDIR)/gsi_main.h                \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_g2_server.h           \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_common.h              \
                            $(GDBDIR)/gdb_genda.h
	@cl -c -nologo -ML -W3 -GX -O2 -DKB_VER=$(KB_VER) -I$(GDBDIR) -I$(GSIDIR) -D$(UNICODE) -D$(GSI_USE_NEW_SYMBOL_API) -D$(GSI_USE_WIDE_STRING_API) -DDB_TYPE=\"$(DBNAME)\" $(GDBDIR)/gdb_g2_server.c

gdb_common.obj:             $(GDBDIR)/gdb_common.c              \
                            $(GSIDIR)/gsi_main.h                \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_genda.h               \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_common.h              \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_g2_client.h
	@cl -c -nologo -ML -W3 -GX -O2 -I$(GDBDIR) -I$(GSIDIR) -D$(UNICODE) -D$(GSI_USE_NEW_SYMBOL_API) -D$(GSI_USE_WIDE_STRING_API) -DDB_TYPE=\"$(DBNAME)\" -DSQLSVR $(GDBDIR)/gdb_common.c

gdb_utils.obj:              $(GDBDIR)/gdb_utils.c               \
                            $(GDBDIR)/gdb_globals.h
	@cl -c -nologo -ML -W3 -GX -O2 -I$(GDBDIR) -I$(GSIDIR) -D$(UNICODE) -D$(GSI_USE_NEW_SYMBOL_API) -D$(GSI_USE_WIDE_STRING_API) -DDB_TYPE=\"$(DBNAME)\" $(GDBDIR)/gdb_utils.c

gsi_brg.obj:                $(AUTHDR)/gsi_brg.c
    @cl -c -nologo -ML -W3 -GX -O2 -D$(OSCODE) $(AUTHDR)/gsi_brg.c

gdb_client_inter_sqlsvr.obj:  $(GDBDIR)/gdb_client_sqlsvr.c   \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_genda.h               \
                            $(GDBDIR)/gdb_client_sqlsvr.h         \
                            $(GDBDIR)/gdb_client_inter_sqlsvr.h   \
                            $(GDBDIR)/gdb_sqlsvr.h   \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GDBDIR)/gdb_context.h             \
                            $(GSIDIR)/gsi_main.h                \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_common.h
	@cl -c  -nologo -ML -W3 -GX -O2 -I$(GDBDIR) -I$(GDBDIR) -I$(GSIDIR) -D$(UNICODE) -D$(GSI_USE_NEW_SYMBOL_API) -D$(GSI_USE_WIDE_STRING_API) -DDB_TYPE=\"$(DBNAME)\" $(GDBDIR)/gdb_client_inter_sqlsvr.c

gdb_client_sqlsvr.obj:        $(GDBDIR)/gdb_client_sqlsvr.c         \
                            $(GDBDIR)/gdb_client_sqlsvr.h         \
                            $(GDBDIR)/gdb_client_inter_sqlsvr.h   \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GSIDIR)/gsi_main.h                \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_common.h              \
                            $(GDBDIR)/gdb_g2_client.h
	@cl -c -nologo -ML -W3 -GX -O2 -I$(GDBDIR) -I$(GDBDIR) -I$(GSIDIR) -D$(UNICODE) -D$(GSI_USE_NEW_SYMBOL_API) -D$(GSI_USE_WIDE_STRING_API) -DDB_TYPE=\"$(DBNAME)\" $(GDBDIR)/gdb_client_sqlsvr.c

gdb_sqlsvr.obj:        $(GDBDIR)/gdb_sqlsvr.cpp         \
                            $(GDBDIR)/gdb_sqlsvr.h         \
                            $(GDBDIR)/gdb_client_inter_sqlsvr.h   \
                            $(GDBDIR)/gdb_globals.h             \
                            $(GDBDIR)/gdb_messages.h            \
                            $(GSIDIR)/gsi_main.h                \
                            $(GDBDIR)/gdb_context.h             \
                            $(GDBDIR)/gdb_utils.h               \
                            $(GDBDIR)/gdb_common.h              \
                            $(GDBDIR)/gdb_g2_client.h
	@cl -c -nologo -ML -W3 -GX -O2 -I$(GDBDIR) -I$(GDBDIR) -I$(GSIDIR) -D$(UNICODE) -D$(GSI_USE_NEW_SYMBOL_API) -D$(GSI_USE_WIDE_STRING_API) -DDB_TYPE=\"$(DBNAME)\" $(GDBDIR)/gdb_sqlsvr.cpp

# Resources
# ---------
g2sqlsvr.res:         $(GDBDIR)/g2sqlsvr.rc             $(GDBDIR)/sqlsvr_res.h    $(GDBDIR)/sqlsvr.ico
    @rc.exe /l 0x409 /d "NDEBUG" /fog2sqlsvr.res $(GDBDIR)/g2sqlsvr.rc
    @echo g2sqlsvr.res

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
    @echo "|  BUILDING G2-SQLSVR on $(PLATFM)
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
