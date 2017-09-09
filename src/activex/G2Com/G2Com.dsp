# Microsoft Developer Studio Project File - Name="G2Com" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=G2Com - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "G2Com.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "G2Com.mak" CFG="G2Com - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "G2Com - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "G2Com - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/G2Com/1.0r1 Branch/Source", VDAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "G2Com - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "$(GSIDIR)" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "GSI_USE_NEW_SYMBOL_API" /D "UNICODE" /D "GSI_USE_WIDE_STRING_API" /D "_ATL_STATIC_REGISTRY" /FR /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 gsi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib atl.lib wsock32.lib $(GSIDIR)\gsi_misc.obj /nologo /subsystem:windows /dll /map /debug /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcmt" /out:"./Debug/G2Com.dll" /pdbtype:sept /libpath:"$(GSIDIR)" /mapinfo:lines /mapinfo:exports /opt:noref
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Debug
TargetPath=.\Debug\G2Com.dll
InputPath=.\Debug\G2Com.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "G2Com - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "G2Com___Win32_Release"
# PROP BASE Intermediate_Dir "G2Com___Win32_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O1 /I "$(GSIDIR)" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /FR /FD /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /MT /W3 /GX /O1 /I "../../gsi/c" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "UNICODE" /D "GSI_USE_WIDE_STRING_API" /D "GSI_USE_NEW_SYMBOL_API" /FR /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 gsi_misc.obj gsi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib atl.lib /nologo /subsystem:windows /dll /machine:I386 /nodefaultlib:"libc.lib" /libpath:"$(GSIDIR)"
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 gsi.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib atl.lib wsock32.lib $(GSIDIR)\gsi_misc.obj /nologo /subsystem:windows /dll /map /machine:I386 /nodefaultlib:"libc.lib" /out:"./Release/G2Com.dll" /libpath:"$(GSIDIR)" /mapinfo:lines /mapinfo:exports /opt:noref
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Release
TargetPath=.\Release\G2Com.dll
InputPath=.\Release\G2Com.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	copy G2Com.h demos\VCppDemo\G2Com.h 
	copy G2Com.tlb demos\VCppDemo\G2Com.tlb 
	copy G2Com_i.c demos\VCppDemo\G2Com_i.c 
	copy G2Com_p.c demos\VCppDemo\G2Com_p.c 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "G2Com - Win32 Debug"
# Name "G2Com - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BConReq.cpp
# End Source File
# Begin Source File

SOURCE=.\BRPCReq.cpp
# End Source File
# Begin Source File

SOURCE=.\ConnectingRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\Converter.cpp
# End Source File
# Begin Source File

SOURCE=.\Datum.cpp
# End Source File
# Begin Source File

SOURCE=.\DisconReq.cpp
# End Source File
# Begin Source File

SOURCE=.\ForcedDisconReq.cpp
# End Source File
# Begin Source File

SOURCE=.\G2Attribute.cpp
# End Source File
# Begin Source File

SOURCE=.\G2Com.cpp
# End Source File
# Begin Source File

SOURCE=.\G2Com.def
# End Source File
# Begin Source File

SOURCE=.\G2Com.idl

!IF  "$(CFG)" == "G2Com - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\G2Com.idl

BuildCmds= \
	midl /Oicf /h "G2Com.h" /iid "G2Com_i.c" "G2Com.idl"

".\G2Com.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\G2Com.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\G2Com_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "G2Com - Win32 Release"

# PROP BASE Ignore_Default_Tool 1
# PROP Ignore_Default_Tool 1
# Begin Custom Build - Performing MIDL step
InputPath=.\G2Com.idl

BuildCmds= \
	midl /Oicf /h "G2Com.h" /iid "G2Com_i.c" "G2Com.idl"

".\G2Com.tlb" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\G2Com.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)

".\G2Com_i.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\G2ComConfigurator.cpp
# End Source File
# Begin Source File

SOURCE=.\G2Container.cpp
# End Source File
# Begin Source File

SOURCE=.\G2Item.cpp
# End Source File
# Begin Source File

SOURCE=.\G2ItemRef.cpp
# End Source File
# Begin Source File

SOURCE=.\G2LAElement.cpp
# End Source File
# Begin Source File

SOURCE=.\G2ListOrArray.cpp
# End Source File
# Begin Source File

SOURCE=.\g2string.cpp
# End Source File
# Begin Source File

SOURCE=.\G2Structure.cpp
# End Source File
# Begin Source File

SOURCE=.\G2StructureEntry.cpp
# End Source File
# Begin Source File

SOURCE=.\G2Symbol.cpp
# End Source File
# Begin Source File

SOURCE=.\G2Window.cpp
# End Source File
# Begin Source File

SOURCE=.\G2Workspace.cpp
# End Source File
# Begin Source File

SOURCE=.\Gateway.cpp
# End Source File
# Begin Source File

SOURCE=.\GatewayProp.cpp
# End Source File
# Begin Source File

SOURCE=.\GsiContext.cpp
# End Source File
# Begin Source File

SOURCE=.\GsiThread.cpp
# End Source File
# Begin Source File

SOURCE=.\Lock.cpp
# End Source File
# Begin Source File

SOURCE=.\NBConReq.cpp
# End Source File
# Begin Source File

SOURCE=.\NBRPCReq.cpp
# End Source File
# Begin Source File

SOURCE=.\RequestObj.cpp
# End Source File
# Begin Source File

SOURCE=.\RetValsReq.cpp
# End Source File
# Begin Source File

SOURCE=.\RPCRequest.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BConReq.h
# End Source File
# Begin Source File

SOURCE=.\BRPCReq.h
# End Source File
# Begin Source File

SOURCE=.\ConnectingRequest.h
# End Source File
# Begin Source File

SOURCE=.\Converter.h
# End Source File
# Begin Source File

SOURCE=.\CPG2Com.h
# End Source File
# Begin Source File

SOURCE=.\Datum.h
# End Source File
# Begin Source File

SOURCE=.\DisconReq.h
# End Source File
# Begin Source File

SOURCE=.\ForcedDisconReq.h
# End Source File
# Begin Source File

SOURCE=.\G2Attribute.h
# End Source File
# Begin Source File

SOURCE=.\G2ComConfigurator.h
# End Source File
# Begin Source File

SOURCE=.\G2Container.h
# End Source File
# Begin Source File

SOURCE=.\G2Item.h
# End Source File
# Begin Source File

SOURCE=.\G2ItemRef.h
# End Source File
# Begin Source File

SOURCE=.\G2LAElement.h
# End Source File
# Begin Source File

SOURCE=.\G2ListOrArray.h
# End Source File
# Begin Source File

SOURCE=.\g2string.h
# End Source File
# Begin Source File

SOURCE=.\G2Structure.h
# End Source File
# Begin Source File

SOURCE=.\G2StructureEntry.h
# End Source File
# Begin Source File

SOURCE=.\G2Symbol.h
# End Source File
# Begin Source File

SOURCE=.\G2Window.h
# End Source File
# Begin Source File

SOURCE=.\G2Workspace.h
# End Source File
# Begin Source File

SOURCE=.\Gateway.h
# End Source File
# Begin Source File

SOURCE=.\GatewayProp.h
# End Source File
# Begin Source File

SOURCE=.\gsi_main_cpp.h
# End Source File
# Begin Source File

SOURCE=.\gsiaxlmisc.h
# End Source File
# Begin Source File

SOURCE=.\GsiContext.h
# End Source File
# Begin Source File

SOURCE=.\GsiThread.h
# End Source File
# Begin Source File

SOURCE=.\Lock.h
# End Source File
# Begin Source File

SOURCE=.\NBConReq.h
# End Source File
# Begin Source File

SOURCE=.\NBRPCReq.h
# End Source File
# Begin Source File

SOURCE=.\RequestObj.h
# End Source File
# Begin Source File

SOURCE=.\RetValsReq.h
# End Source File
# Begin Source File

SOURCE=.\RPCRequest.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\G2Com.rc
# End Source File
# Begin Source File

SOURCE=.\G2Structure.rgs
# End Source File
# Begin Source File

SOURCE=.\G2StructureEntry.rgs
# End Source File
# Begin Source File

SOURCE=.\G2Window.rgs
# End Source File
# Begin Source File

SOURCE=.\G2Workspace.rgs
# End Source File
# Begin Source File

SOURCE=.\Gateway.rgs
# End Source File
# Begin Source File

SOURCE=.\GatewayProp.rgs
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\G2Attribute.rgs
# End Source File
# Begin Source File

SOURCE=.\G2ComConfigurator.rgs
# End Source File
# Begin Source File

SOURCE=.\G2Item.rgs
# End Source File
# Begin Source File

SOURCE=.\G2ItemRef.rgs
# End Source File
# Begin Source File

SOURCE=.\G2LAElement.rgs
# End Source File
# Begin Source File

SOURCE=.\G2ListOrArray.rgs
# End Source File
# Begin Source File

SOURCE=.\G2Symbol.rgs
# End Source File
# End Target
# End Project
