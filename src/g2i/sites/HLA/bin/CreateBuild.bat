@echo off
setlocal

@echo.
@echo.
@echo	BUILDING HLA %1
@echo.

rem Required environment variables:
rem    SRCBOX: originating sandbox
rem    G2EXE: directory containing g2.exe (optional, if can be defaulted)
rem    DSTBOX: location of g2.exe, defaulted to SRCBOX if not specified.
rem    JAVA_SRCBOX: java sandbox if different from originating (use k:\bt\t2)
rem The following can't be gotten from sandboxes because the kb filenames in
rem the sources are different from those in the built and promoted product, 
rem so G2 won't find them when loading.
rem    G2_DB: Location of G2 database KBs.  Example: k:\gensym\ut\g2odbc-82r0\kbs.
rem    G2_OPCLINK: Location of opclink: Example: k:\gensym\ut\opclink-21r1.
rem    G2_CORBA: Location of corbalink: Example: k:\gensym\ut\corbalink-82r0.
rem JAVA_HOME or JAVAHOME are also required for the location of java and its
rem     supporting jar files

rem	RTI_HOME: location of include and lib directories that contain 
rem	RTI library/header files.  If not specified, default location is used

rem CVS modules required in your sandbox:
rem   g2i kbs g2pi gw 

if not exist "%DSTBOX%"         set DSTBOX=%SRCBOX%
if "%G2EXE%" == ""              set G2EXE=%DSTBOX%\g2\tape

if not exist "%G2EXE%\g2.exe" goto errorNoG2

if "%JAVA_SRCBOX%" == ""        set JAVA_SRCBOX=%SRCBOX%

if "%JAVAHOME%" == ""           set JAVAHOME=%JAVA_HOME%
if "%JAVAHOME%" == ""           goto errorNoJava

if "%RTI_HOME%" == ""		set RTI_HOME=..\RTI-DMSO-13-V6

if not exist "%JAVA_SRCBOX%\java" goto errorNoJavalink

set G2I_HOME=%SRCBOX%\g2i
set SRC_DIR=%G2I_HOME%
set BLD_DIR=%G2I_HOME%\builds
set DST_DIR=%BLD_DIR%\hla-%1

set STAGE_DIR=%DST_DIR%\staging\

set ISHIP_G2I_DIR=%DST_DIR%\iship\g2i
set ISHIP_HLA_DIR=%DST_DIR%\iship\hla

set COMMON_JMAIL_DIR=%DST_DIR%\iship\jmail_common
set COMMON_JMS_DIR=%DST_DIR%\iship\jms_common
set COMMON_SOCKMAN_DIR=%DST_DIR%\iship\sockman_common
set ISHIP_JMAIL_DIR=%DST_DIR%\iship\jmail
set ISHIP_JMS_DIR=%DST_DIR%\iship\jms
set ISHIP_SOCKMAN_DIR=%DST_DIR%\iship\sockman
set QA_DIR=%DST_DIR%\qa


set PATH=%G2I_HOME%\bin;%G2EXE%;%JAVAHOME%\bin;%PATH%

rem
rem	check args
rem


if not exist "%G2I_HOME%" 	goto errorNoSrc
if "%1" == "" 			goto show_usage


set SRC_DIR=%G2I_HOME%\sites\HLA
set BLD_DIR=%G2I_HOME%\builds

set DST_DIR=%BLD_DIR%\HLA-%1
set ISHIP_DIR=%DST_DIR%\iship
set STAGE_DIR=%DST_DIR%\staging\
set QA_DIR=%DST_DIR%\qa


@echo.
@echo	Build settings:
@echo           Source directory:	%SRC_DIR%
@echo           Target directory:	%ISHIP_DIR%
@echo.
@echo.
@echo	Ensure you updated the Readme files, documentation,
@echo	license files and splash screens as required to
@echo	reflect the current version.
@echo.

@echo.
rem pause
@echo.


rem
rem	Create min directories to store builds
rem


if not exist "%BLD_DIR%" 	md "%BLD_DIR%"
if not exist "%DST_DIR%"	goto s1

@echo.
@echo	Existing build directory exists. The script
@echo	will delete it to ensure that we do not build
@echo	on top of existing old files and then recreate
@echo	the directory structure.
@echo.

rem pause


del 	"%DST_DIR%\*.*"		/S /F /Q
echo Y | rmdir   "%DST_DIR%"	/s


:s1

if not exist "%DST_DIR%" 		md "%DST_DIR%"
if not exist "%ISHIP_DIR%" 		md "%ISHIP_DIR%"
if not exist "%STAGE_DIR%"	 	md "%STAGE_DIR%"
if not exist "%QA_DIR%"			md "%QA_DIR%"

rem
rem	Create Target directories
rem

md "%ISHIP_DIR%\bin"
md "%ISHIP_DIR%\kbs"
md "%ISHIP_DIR%\images"
md "%ISHIP_DIR%\resources"
md "%ISHIP_DIR%\examples"
md "%ISHIP_DIR%\examples\G2Demo_Federate"
md "%ISHIP_DIR%\examples\G2HelloWorld_Federate"

rem
rem	Create kb files
rem

cd	"%ISHIP_DIR%\Kbs"

set SITE_=%G2I_HOME%\sites\HLA
set KB_=%G2I_HOME%\sites\hla\kbs\hla-dev.kb
set G2IHOME_=%G2i_HOME%
set "G2_MODULE_SEARCH_PATH='%SRCBOX%\g2db\kbs' '%SITE_%' '%G2IHOME_%\sites\DevSite\kbs' '%G2IHOME_%\kbs' '%SRCBOX%\kbs' '%JAVA_SRCBOX%\java\products\javalink\common\kbs' '%SRCBOX%\g2pi\kbs' '%G2_DB%' '%G2_OPCLINK%\KBs' '%SRCBOX%\gw\kbs' '%G2_CORBA%\kbs' '%JAVA_SRCBOX%\java\products\sequoia\common\kbs'"

cd %SITE_%
"%g2exe%\g2" -log %SITE_%\Logs\g2log.txt -icon "G2i Dev" -name "G2i Dev Server" -hla-auto-build %STAGE_DIR% -kb %KB_% 

rem	Build bridge
msdev   .\bridge_src\G2_hla.dsw /make /clean "G2_HLA - Win32 Release"
msdev   .\bridge_src\G2_hla.dsw /make "G2_HLA - Win32 Release"

rem	Build examples
msdev	.\G2Demo_Federate\G2Demo.dsw /make /clean "G2Demo - Win32 Release"
msdev	.\G2Demo_Federate\G2Demo.dsw /make "G2Demo - Win32 Release"
msdev	.\G2HelloWorld_Federate\G2HelloWorld.dsw /make /clean "G2HelloWorld - Win32 Release"
msdev	.\G2HelloWorld_Federate\G2HelloWorld.dsw /make "G2HelloWorld - Win32 Release"

rem
rem	Copy files into build directory
rem

cd	"%SRC_DIR%\bin\win32"
copy	g2-hla.exe					"%ISHIP_DIR%\bin"

cd	"%SRC_DIR%\bin"
copy	StartG2HLA.bat					"%ISHIP_DIR%\bin"

cd	"%SRC_DIR%\G2Demo_Federate"
copy	*.cpp						"%ISHIP_DIR%\examples\G2Demo_Federate"
copy	*.hh						"%ISHIP_DIR%\examples\G2Demo_Federate"
copy	G2Demo.dsw					"%ISHIP_DIR%\examples\G2Demo_Federate"
copy	G2Demo.dsp					"%ISHIP_DIR%\examples\G2Demo_Federate"
copy	G2Demo.exe					"%ISHIP_DIR%\examples\G2Demo_Federate"
copy 	StartG2Demo.bat					"%ISHIP_DIR%\examples\G2Demo_Federate"

cd	"%SRC_DIR%\G2HelloWorld_Federate"
copy	*.cpp						"%ISHIP_DIR%\examples\G2HelloWorld_Federate"
copy	*.hh						"%ISHIP_DIR%\examples\G2HelloWorld_Federate"
copy	G2HelloWorld.dsw				"%ISHIP_DIR%\examples\G2HelloWorld_Federate"
copy	G2HelloWorld.dsp				"%ISHIP_DIR%\examples\G2HelloWorld_Federate"
copy	G2HelloWorld.exe				"%ISHIP_DIR%\examples\G2HelloWorld_Federate"
copy	StartG2Helloworld.bat				"%ISHIP_DIR%\examples\G2HelloWorld_Federate"

cd 	"%SRC_DIR%\resources"
copy	G2DemoFederation.fed			"%ISHIP_DIR%\resources"
copy	G2HelloWorld.fed			"%ISHIP_DIR%\resources"

cd 	"%SRC_DIR%\images"
copy	*.gif						"%ISHIP_DIR%\images"

cd	"%STAGE_DIR%"
copy	ghla.kb					"%ISHIP_DIR%\kbs"
copy	ghla-demo.kb				"%ISHIP_DIR%\examples"

rem Copy all of the QA modules to the QA directory

@echo.
@echo	Setting readonly attributes
@echo.

rem attrib +R "%ISHIP_DIR%\bin\*.*"
attrib +R "%ISHIP_DIR%\examples\*.*"
attrib +R "%ISHIP_DIR%\kbs\*.*"


if "%2" == "" goto no_unix

set U_BLD_DIR=%2\builds
set U_DST_DIR=%U_BLD_DIR%\rethink-%1
set U_ISHIP_DIR=%U_DST_DIR%\iship

if not exist "%U_BLD_DIR%" 	md "%U_BLD_DIR%"
if not exist "%U_DST_DIR%" 	md "%U_DST_DIR%"
if not exist "%U_ISHIP_DIR%" 	md "%U_ISHIP_DIR%"

cd %ISHIP_DIR%
xcopy	*.*  "%U_ISHIP_DIR%" /H /E /K




:no_unix


@echo.
@echo	Build has been created 
@echo.
@echo.
@echo	HLA build version:	%1
@echo	iship version to promote:	"%ISHIP_DIR%"


cd "%G2i_HOME%"

goto end



:errorNoSrc
@echo.
@echo.
@echo	The environment variable %ISHIP_DIR% does not exist
@echo	Please define it and then restart this shell program.
@echo.

goto end

:errorNoG2
@echo.
@echo.
@echo   The environment variable G2EXE does not exist
@echo   Please define it and then restart this shell program
@echo.
goto end

:show_usage
@echo.
@echo.
@echo Usage: CreateBuild "version-tag" 
@echo.
@echo	version-tag:	specifies the version to build
@echo			you only specify the version number,
@echo			i.e. 1.0b0, 2.0r0, 2.0, etc
@echo.
@echo	UnixPath	Unix mounted path to copy build to. It will create be
@echo			stored in the directory (dir created automatically)
@echo				<UnixPath>/builds/e-SCOR-<version-tag>/iship
@echo.
@echo 	Examples:	createbuild 1.0r0  
@echo. 			createbuild 1.0r0  u:
@echo.


:end
