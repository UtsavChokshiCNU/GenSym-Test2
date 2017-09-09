# Microsoft Developer Studio Project File - Name="g2opc_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=g2opc_test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "g2opc_test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "g2opc_test.mak" CFG="g2opc_test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "g2opc_test - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "g2opc_test - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "g2opc_test - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../" /I "..\..\..\OPCFoundation\CoreComponents-2.00\Include" /I "..\..\..\gsi\c" /I "..\..\..\cppunit-1.12.0\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "UNICODE" /D "GSI_USE_WIDE_STRING_API" /D "GSI_USE_NEW_SYMBOL_API" /D "_UNICODE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib rpcrt4.lib ws2_32.lib nsleep.obj spromeps.lib version.lib cppunitmt.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libc" /libpath:"../../../specific/intelnt" /libpath:"..\..\..\cppunit-1.12.0\lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "g2opc_test - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../" /I "..\..\..\OPCFoundation\CoreComponents-2.00\Include" /I "..\..\..\gsi\c" /I "..\..\..\cppunit-1.12.0\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "UNICODE" /D "GSI_USE_WIDE_STRING_API" /D "GSI_USE_NEW_SYMBOL_API" /D "_UNICODE" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib rpcrt4.lib nsleep.obj spromeps.lib version.lib libcmtd.lib cppunitd.lib /nologo /subsystem:windows /map /debug /machine:I386 /nodefaultlib:"libc" /nodefaultlib:"libcd" /nodefaultlib:"libcmt" /pdbtype:sept /libpath:"../../../specific/intelnt" /libpath:"..\..\..\cppunit-1.12.0\lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "g2opc_test - Win32 Release"
# Name "g2opc_test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\g2opc_test.cpp
# End Source File
# Begin Source File

SOURCE=.\TestConsoleHandler.cpp
# End Source File
# Begin Source File

SOURCE=.\TestG2LogMessage.cpp
# End Source File
# Begin Source File

SOURCE=.\TestGsiLoop.cpp
# End Source File
# Begin Source File

SOURCE=.\TestHiddenWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\TestOPCProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\WndRunner.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\TestConsoleHandler.h
# End Source File
# Begin Source File

SOURCE=.\TestG2LogMessage.h
# End Source File
# Begin Source File

SOURCE=.\TestGsiLoop.h
# End Source File
# Begin Source File

SOURCE=.\TestHiddenWnd.h
# End Source File
# Begin Source File

SOURCE=.\WndRunner.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\G2OPC.ico
# End Source File
# Begin Source File

SOURCE=.\opclink.rc
# End Source File
# Begin Source File

SOURCE=.\OPCMemberLogo.bmp
# End Source File
# Begin Source File

SOURCE=.\Small.ico
# End Source File
# End Group
# Begin Group "g2opc files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\CCommandLine.cpp
# End Source File
# Begin Source File

SOURCE=..\CtrlPanel.cpp
# End Source File
# Begin Source File

SOURCE=..\G2OpcClientIcon.cpp
# End Source File
# Begin Source File

SOURCE=..\G2OpcHiddenWin.cpp
# End Source File
# Begin Source File

SOURCE=..\Group.cpp
# End Source File
# Begin Source File

SOURCE=..\opc_gsi.cpp
# End Source File
# Begin Source File

SOURCE=..\opc_gsi_brg.cpp
# End Source File
# Begin Source File

SOURCE=..\opc_log.cpp
# End Source File
# Begin Source File

SOURCE=..\opc_rpcs.cpp
# End Source File
# Begin Source File

SOURCE=..\opc_utils.cpp
# End Source File
# Begin Source File

SOURCE=..\OPCDataCallback.cpp
# End Source File
# Begin Source File

SOURCE=..\OPCShutdown.cpp
# End Source File
# Begin Source File

SOURCE=..\ProgramVersion.cpp
# End Source File
# Begin Source File

SOURCE=..\Server.cpp
# End Source File
# Begin Source File

SOURCE=..\serverlist.cpp
# End Source File
# Begin Source File

SOURCE=..\StdAfx.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
