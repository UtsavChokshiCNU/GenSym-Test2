# Microsoft Developer Studio Project File - Name="Corba" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Corba - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Corba.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Corba.mak" CFG="Corba - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Corba - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Corba - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Corba - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "$(GSIDIR)" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D BUILD_CODE=\"HF28\" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libgsi.lib libtcp.lib librtl.lib libnogsec.lib wsock32.lib rpcrt4.lib gsi_misc.obj version.lib /nologo /subsystem:console /machine:I386 /nodefaultlib:"libcmt" /out:"Release/g2-corba.exe" /libpath:"$(GSIDIR)"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "$(GSIDIR)" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D BUILD_CODE=\"HG08\" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib ws2_32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libgsi.lib libtcp.lib librtl.lib libnogsec.lib rpcrt4.lib wsock32.lib gsi_misc.obj version.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"libcmt" /out:"Debug/g2-corba.exe" /pdbtype:sept /libpath:"$(GSIDIR)"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "Corba - Win32 Release"
# Name "Corba - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\builder.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\code_tokens.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\connections.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\download_ir.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\encoding.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\error_handler.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\G2Container.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\G2CorbaContainer.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g2item.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\g2string.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\gsi_compile_idl.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\gsi_fcns.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\iiop.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\init_context.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ior.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\lex_1.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\locator.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\orbtype.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\parse.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\parse_tree_node.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\pause.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\recv_req.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\reg_obj.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\reg_proxy.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\send_req.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\shutdown_context.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\sockbase.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\startup.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D CORBALINK_VER=\"8_2R0\" /D G2KB_VER=\"1.1r0\" /D G2KB_IDL_VER=\"8.2r0.1\" /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D CORBALINK_VER=\"8_2R0\" /D G2KB_VER=\"1.1r0\" /D G2KB_IDL_VER=\"8.2r0.1\" /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\token.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\utils.cpp

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ytab.c

!IF  "$(CFG)" == "Corba - Win32 Release"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HF28\"

!ELSEIF  "$(CFG)" == "Corba - Win32 Debug"

# ADD CPP /D BUILD_CODE=\"HG11\"
# SUBTRACT CPP /D BUILD_CODE=\"HG08\"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\corba.ico
# End Source File
# Begin Source File

SOURCE=.\g2corba.rc
# End Source File
# End Group
# End Target
# End Project
