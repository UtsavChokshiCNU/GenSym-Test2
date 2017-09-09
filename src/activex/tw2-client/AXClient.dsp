# Microsoft Developer Studio Project File - Name="AXClient" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=AXClient - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AXClient.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AXClient.mak" CFG="AXClient - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AXClient - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AXClient - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/G2COM/AXClient", GPBAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AXClient - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /W3 /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_DEBUG_QI" /D "_ATL_DEBUG_INTERFACES" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL"
# ADD MTL /nologo /D "_DEBUG" /Oicf /win32
# SUBTRACT MTL /mktyplib203
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Debug
TargetPath=.\Debug\AXClient.dll
InputPath=.\Debug\AXClient.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "AXClient - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "AXClient"
# PROP BASE Intermediate_Dir "AXClient"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /D "_ATL_DEBUG_QI" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /Od /D "WIN32" /D "_WINDOWS" /D "_USRDLL" /D "_ATL_STATIC_REGISTRY" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /Oicf /win32
# SUBTRACT MTL /mktyplib203
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /debug /nodefaultlib
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Release
TargetPath=.\Release\AXClient.dll
InputPath=.\Release\AXClient.dll
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "AXClient - Win32 Debug"
# Name "AXClient - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AXClient.cpp
# End Source File
# Begin Source File

SOURCE=.\AXClient.def
# End Source File
# Begin Source File

SOURCE=.\AXClient.idl
# ADD MTL /tlb "AXClient.tlb" /h "AXClient.h" /iid "AXClient_i.c"
# End Source File
# Begin Source File

SOURCE=.\AXClient.txt
# End Source File
# Begin Source File

SOURCE=.\Container.cpp
# End Source File
# Begin Source File

SOURCE=.\convert.cpp
# End Source File
# Begin Source File

SOURCE=.\G2Item.cpp
# End Source File
# Begin Source File

SOURCE=.\G2ItemHolder.cpp
# End Source File
# Begin Source File

SOURCE=.\G2Structure.cpp
# End Source File
# Begin Source File

SOURCE=.\G2Symbol.cpp
# End Source File
# Begin Source File

SOURCE=.\G2UiGateway.cpp
# End Source File
# Begin Source File

SOURCE=.\G2WorkspacePanel.cpp
# End Source File
# Begin Source File

SOURCE=.\GenericEventSink.cpp
# End Source File
# Begin Source File

SOURCE=.\IdManager.cpp
# End Source File
# Begin Source File

SOURCE=.\make_kit.bat
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\util.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AXClientConnectionPointImpl.h
# End Source File
# Begin Source File

SOURCE=.\Container.h
# End Source File
# Begin Source File

SOURCE=.\convert.h
# End Source File
# Begin Source File

SOURCE=.\CProxy_G2ItemEvents.h
# End Source File
# Begin Source File

SOURCE=.\CProxy_G2ItemEvents2.h
# End Source File
# Begin Source File

SOURCE=.\CProxy_G2UiGatewaySource.h
# End Source File
# Begin Source File

SOURCE=.\CProxy_G2UiGatewaySource2.h
# End Source File
# Begin Source File

SOURCE=.\CProxy_G2WorkspacePanelSource.h
# End Source File
# Begin Source File

SOURCE=.\G2Item.h
# End Source File
# Begin Source File

SOURCE=.\G2ItemHolder.h
# End Source File
# Begin Source File

SOURCE=.\G2Structure.h
# End Source File
# Begin Source File

SOURCE=.\G2Symbol.h
# End Source File
# Begin Source File

SOURCE=.\G2UiGateway.h
# End Source File
# Begin Source File

SOURCE=.\G2WorkspacePanel.h
# End Source File
# Begin Source File

SOURCE=.\GenericEventSink.h
# End Source File
# Begin Source File

SOURCE=.\helpers.h
# End Source File
# Begin Source File

SOURCE=.\IdManager.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\util.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe;rgs"
# Begin Source File

SOURCE=.\AXClient.ico
# End Source File
# Begin Source File

SOURCE=.\AXClient.rc
# End Source File
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\G2ItemHolder.rgs
# End Source File
# Begin Source File

SOURCE=.\G2Structure.rgs
# End Source File
# Begin Source File

SOURCE=.\G2Symbol.rgs
# End Source File
# Begin Source File

SOURCE=.\G2UiGateway.rgs
# End Source File
# Begin Source File

SOURCE=.\G2WorkspacePanel.rgs
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# End Group
# End Target
# End Project
# Section AXClient : {E5466320-DEC8-11D1-B49B-006008C66714}
# 	2:21:DefaultSinkHeaderFile:twconnectordispatch.h
# 	2:16:DefaultSinkClass:CTwConnectorDispatch
# End Section
# Section AXClient : {D1CD7870-CE7C-11D1-B49D-006008C5F95B}
# 	2:21:DefaultSinkHeaderFile:scriptutilitiesdispatch.h
# 	2:16:DefaultSinkClass:CScriptUtilitiesDispatch
# End Section
# Section AXClient : {A32C8EC1-CFAA-11D1-B495-006008C66714}
# 	2:5:Class:CScriptUtilitiesDispatch
# 	2:10:HeaderFile:scriptutilitiesdispatch.h
# 	2:8:ImplFile:scriptutilitiesdispatch.cpp
# End Section
# Section AXClient : {E5466323-DEC8-11D1-B49B-006008C66714}
# 	2:5:Class:CTwConnectorDispatch
# 	2:10:HeaderFile:twconnectordispatch.h
# 	2:8:ImplFile:twconnectordispatch.cpp
# End Section
