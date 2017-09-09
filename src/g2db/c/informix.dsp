# Microsoft Developer Studio Project File - Name="informix" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=informix - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "informix.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "informix.mak" CFG="informix - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "informix - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "informix - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "informix - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\o\informix"
# PROP Intermediate_Dir "..\o\informix"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\c" /I "$(GSIDIR)" /I "$(INFORMIX_HOME)\incl\esql" /D "NDEBUG" /D BUILD_CODE=\"O25\" /D GDB_VER=\"6_0R4\" /D "__STDC__" /D DB_TYPE=\"Informix\" /D "WindowsNT" /D "WIN32" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib nsleep.obj gsi_brg.obj wsock32.lib netapi32.lib spromeps.lib librtl.lib libgsi.lib libtcp.lib isqlt07c.lib /nologo /subsystem:console /machine:I386 /nodefaultlib:"LIBCD" /out:"..\o\informix\g2-informix.exe" /libpath:"$(AUTH_DIR)" /libpath:"$(GSIDIR)" /libpath:"$(INFORMIX_HOME)\lib"

!ELSEIF  "$(CFG)" == "informix - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\informix"
# PROP Intermediate_Dir "Debug\informix"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "..\c" /I "$(GSIDIR)" /I "$(INFORMIX_HOME)\incl\esql" /D "_DEBUG" /D BUILD_CODE=\"O25\" /D GDB_VER=\"6_0R4\" /D "__STDC__" /D DB_TYPE=\"Informix\" /D "WindowsNT" /D "WIN32" /FR /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libcd.lib nsleep.obj gsi_brg.obj wsock32.lib netapi32.lib spromeps.lib librtl.lib libgsi.lib libtcp.lib isqlt07c.lib /nologo /subsystem:console /incremental:no /debug /machine:I386 /nodefaultlib:"LIBC" /out:"Debug\informix\g2-informix.exe" /pdbtype:sept /libpath:"$(AUTH_DIR)" /libpath:"$(GSIDIR)" /libpath:"$(INFORMIX_HOME)\lib"

!ENDIF 

# Begin Target

# Name "informix - Win32 Release"
# Name "informix - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "c"
# Begin Source File

SOURCE=..\o\informix\gdb_client_inf.c
# End Source File
# Begin Source File

SOURCE=.\gdb_client_inf.ec

!IF  "$(CFG)" == "informix - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Informix Precompile
InputPath=.\gdb_client_inf.ec
InputName=gdb_client_inf

"..\o\informix\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(INFORMIX_HOME)\bin\esql  -ansi -local -e $(InputName).ec 
	move $(InputName).c ..\o\informix 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "informix - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Informix Precompile
InputPath=.\gdb_client_inf.ec
InputName=gdb_client_inf

"..\o\informix\$(InputName).c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(INFORMIX_HOME)\bin\esql  -ansi -local -e $(InputName).ec 
	move $(InputName).c ..\o\informix 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\gdb_client_inter_inf.c
# End Source File
# Begin Source File

SOURCE=.\gdb_common.c
# End Source File
# Begin Source File

SOURCE=.\gdb_g2_server.c
# End Source File
# Begin Source File

SOURCE=.\gdb_main.c
# End Source File
# Begin Source File

SOURCE=.\gdb_utils.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\gdb_client_inf.h
# End Source File
# Begin Source File

SOURCE=.\gdb_client_inter_inf.h
# End Source File
# Begin Source File

SOURCE=.\gdb_common.h
# End Source File
# Begin Source File

SOURCE=.\gdb_context.h
# End Source File
# Begin Source File

SOURCE=.\gdb_g2_client.h
# End Source File
# Begin Source File

SOURCE=.\gdb_g2_server.h
# End Source File
# Begin Source File

SOURCE=.\gdb_genda.h
# End Source File
# Begin Source File

SOURCE=.\gdb_globals.h
# End Source File
# Begin Source File

SOURCE=.\gdb_messages.h
# End Source File
# Begin Source File

SOURCE=.\gdb_utils.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "rc,ico"
# Begin Source File

SOURCE=.\g2informix.rc
# End Source File
# Begin Source File

SOURCE=.\informix.ico
# End Source File
# Begin Source File

SOURCE=.\informix_res.h
# End Source File
# End Group
# End Target
# End Project
