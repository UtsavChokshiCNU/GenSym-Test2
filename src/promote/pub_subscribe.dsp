# Microsoft Developer Studio Project File - Name="pub_subscribe" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0103

CFG=pub_subscribe - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "pub_subscribe.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "pub_subscribe.mak" CFG="pub_subscribe - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "pub_subscribe - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "pub_subscribe - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "pub_subscribe - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "pub_subscribe___Win32_Release"
# PROP BASE Intermediate_Dir "pub_subscribe___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "pub_subscribe___Win32_Release"
# PROP Intermediate_Dir "pub_subscribe___Win32_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib /nologo /machine:I386 /subsystem:windows,4.0
# ADD LINK32 libcmt.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib wsock32.lib netapi32.lib rpcrt4.lib /nologo /machine:I386 /nodefaultlib /subsystem:windows,4.0

!ELSEIF  "$(CFG)" == "pub_subscribe - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "pub_subscribe___Win32_Debug"
# PROP BASE Intermediate_Dir "pub_subscribe___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "pub_subscribe___Win32_Debug"
# PROP Intermediate_Dir "pub_subscribe___Win32_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib /nologo /debug /machine:I386 /pdbtype:sept /subsystem:windows,4.0
# ADD LINK32 libcmt.lib oldnames.lib kernel32.lib advapi32.lib user32.lib gdi32.lib wsock32.lib rpcrt4.lib /nologo /debug /machine:I386 /nodefaultlib /pdbtype:sept /subsystem:windows,4.0

!ENDIF 

# Begin Target

# Name "pub_subscribe - Win32 Release"
# Name "pub_subscribe - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\gsi_main.c
# End Source File
# Begin Source File

SOURCE=.\gsi_misc.c
# End Source File
# Begin Source File

SOURCE=.\gsimmain.c
# End Source File
# Begin Source File

SOURCE=.\pub_subscribe.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=.\libtcp.lib
# End Source File
# Begin Source File

SOURCE=.\librtl.lib
# End Source File
# Begin Source File

SOURCE=.\libgsi.lib
# End Source File
# End Target
# End Project
