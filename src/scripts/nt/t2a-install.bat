@echo off
rem The Telewindows2 ActiveX controls use the Telewindows2 JavaBeans via a
rem   Java-to-ActiveX bridge. This batch file installs the ActiveX controls
rem   when using Microsoft's Java-to-ActiveX bridge and VM.


if "%MS_JAVA_HOME%" == "" goto noMsJavaHome

if "%SRCBOX%" == "" goto noSrcBox

echo Creating registry entries for Telewindows2 ActiveX controls . . .

setlocal

cd /d "%SRCBOX%\activex\tw2-client\Debug"

"%MS_JAVA_HOME%\bin\javareg" /register /class:com.gensym.controls.ScriptUtilities /control /clsid:{781EFD60-C5E7-11D2-A5AD-006097586191} /progid:ScriptUtilities.Bean /typelib:ScriptUtilities.tlb

"%MS_JAVA_HOME%\bin\javareg" /register /class:com.gensym.controls.TwActiveXConnector /control /clsid:{7B65E750-C5E7-11D2-A5AD-006097586191} /progid:TwConnector.Bean /typelib:TwConnector.tlb

"%MS_JAVA_HOME%\bin\javareg" /register /class:com.gensym.controls.ItemProxy /control /clsid:{74AED160-C5E7-11D2-A5AD-006097586191} /progid:ItemProxy.Bean /typelib:ItemProxy.tlb

"%MS_JAVA_HOME%\bin\javareg" /register /class:com.gensym.wksp.MultipleWorkspacePanel /control /clsid:{8CD6F130-C5E7-11D2-A5AD-006097586191} /progid:MultipleWorkspacePanel.Bean /typelib:MultipleWorkspacePanel.tlb

call ..\reg_axclient.bat

endlocal

goto end

:noMsJavaHome
echo The environment variable MS_JAVA_HOME must be set to the root directory
echo of the Microsoft SDK for Java
pause
goto end

:noSrcBox
echo The environment variable SRCBOX must be set to your sandbox location
pause
goto end

:end
