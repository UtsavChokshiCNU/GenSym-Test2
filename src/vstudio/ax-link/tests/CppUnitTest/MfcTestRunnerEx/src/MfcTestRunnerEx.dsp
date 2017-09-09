# Microsoft Developer Studio Project File - Name="MfcTestRunnerEx" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MfcTestRunnerEx - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MfcTestRunnerEx.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MfcTestRunnerEx.mak" CFG="MfcTestRunnerEx - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MfcTestRunnerEx - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MfcTestRunnerEx - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MfcTestRunnerEx - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /Zd /O2 /I "..\..\..\..\..\..\cppunit-1.12.0\include" /I "..\..\..\..\..\..\cppunit-1.12.0\include\msvc6" /I "..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner" /D "NDEBUG" /D "_AFXEXT" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "WIN32" /D "OEMRESOURCE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ..\..\..\..\..\..\cppunit-1.12.0\lib\cppunitmd.lib winmm.lib /nologo /subsystem:windows /dll /machine:I386
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetDir=.\Release
TargetPath=.\Release\MfcTestRunnerEx.dll
TargetName=MfcTestRunnerEx
SOURCE="$(InputPath)"
PostBuild_Desc=Copying target to lib/
PostBuild_Cmds=copy "$(TargetPath)" ..\lib\$(TargetName).dll	copy "$(TargetDir)\$(TargetName).lib" ..\lib\$(TargetName).lib
# End Special Build Tool

!ELSEIF  "$(CFG)" == "MfcTestRunnerEx - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /Zi /Od /I "..\..\..\..\..\..\cppunit-1.12.0\include" /I "..\..\..\..\..\..\cppunit-1.12.0\include\msvc6" /I "..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner" /D "_DEBUG" /D "_AFXEXT" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "WIN32" /D "OEMRESOURCE" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\..\..\..\..\cppunit-1.12.0\lib\cppunitmdd.lib winmm.lib /nologo /subsystem:windows /dll /incremental:no /debug /machine:I386 /out:"Debug\MfcTestRunnerExD.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
TargetDir=.\Debug
TargetPath=.\Debug\MfcTestRunnerExD.dll
TargetName=MfcTestRunnerExD
SOURCE="$(InputPath)"
PostBuild_Desc=Copying target
PostBuild_Cmds=copy "$(TargetPath)" ..\lib\$(TargetName).dll	copy "$(TargetDir)\$(TargetName).lib" ..\lib\$(TargetName).lib
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "MfcTestRunnerEx - Win32 Release"
# Name "MfcTestRunnerEx - Win32 Debug"
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\res\errortype.bmp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\res\test_type.bmp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\res\TestRunner.rc2"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\res\tfwkui_r.bmp"
# End Source File
# End Group
# Begin Group "UserInterface"

# PROP Default_Filter ""
# Begin Group "DynamicWindow"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\DynamicWindow\cdxCDynamicBar.cpp"
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\DynamicWindow\cdxCDynamicBar.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\DynamicWindow\cdxCDynamicControlsManager.cpp"
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\DynamicWindow\cdxCDynamicControlsManager.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\DynamicWindow\cdxCDynamicDialog.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\DynamicWindow\cdxCDynamicDialog.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\DynamicWindow\cdxCDynamicFormView.cpp"
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\DynamicWindow\cdxCDynamicFormView.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\DynamicWindow\cdxCDynamicPropSheet.cpp"
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\DynamicWindow\cdxCDynamicPropSheet.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\DynamicWindow\cdxCDynamicWnd.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\DynamicWindow\cdxCDynamicWnd.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\DynamicWindow\cdxCDynamicWndEx.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\DynamicWindow\cdxCDynamicWndEx.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\DynamicWindow\cdxCSizeIconCtrl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\DynamicWindow\cdxCSizeIconCtrl.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\DynamicWindow\SizeCBar.cpp"
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\DynamicWindow\SizeCBar.h"
# End Source File
# End Group
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\ListCtrlFormatter.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\ListCtrlFormatter.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\ListCtrlSetter.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\ListCtrlSetter.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\MsDevCallerListCtrl.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\MsDevCallerListCtrl.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\ProgressBar.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\ProgressBar.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\Resource.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\ResourceLoaders.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\ResourceLoaders.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\StdAfx.cpp"
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\StdAfx.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\TestRunner.rc"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\TestRunnerApp.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\TestRunnerApp.h"
# End Source File
# Begin Source File

SOURCE=".\TestRunnerEx.def"
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\TreeHierarchyDlg.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\TreeHierarchyDlg.h"
# End Source File
# End Group
# Begin Group "Components"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\ActiveTest.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\ActiveTest.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\MfcSynchronizationObject.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\MfcTestRunner.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\include\cppunit\ui\mfc\TestRunner.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\include\msvc6\testrunner\TestRunner.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\TestRunnerModel.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\TestRunnerModel.h"
# End Source File
# End Group
# Begin Group "NewFiles"

# PROP Default_Filter "*.cpp;*.h"
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\MostRecentTests.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\MostRecentTests.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\TestRunnerDlg.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\src\msvc6\testrunner\TestRunnerDlg.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\cppunit-1.12.0\include\msvc6\DSPlugin\TestRunnerDSPluginVC6_i.c"
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "MfcTestRunnerEx"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MfcTestRunnerEx.cpp
# End Source File
# Begin Source File

SOURCE=.\MfcTestRunnerEx.h
# End Source File
# Begin Source File

SOURCE=.\TestRunnerExDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TestRunnerExDlg.h
# End Source File
# End Group
# End Target
# End Project
