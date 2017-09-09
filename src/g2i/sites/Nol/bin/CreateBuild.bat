@echo off
setlocal

@echo.
@echo.
@echo	BUILDING NOL %1
@echo.

rem
rem	check args
rem


if not exist "%DSTBOX%"         set DSTBOX=%SRCBOX%
if "%G2EXE%" == ""              set G2EXE=%DSTBOX%\g2\tape

if not exist "%G2EXE%\g2.exe" goto errorNoG2

if "%JAVA_SRCBOX%" == ""        set JAVA_SRCBOX=%SRCBOX%

if "%JAVAHOME%" == ""           set JAVAHOME=%JAVA_HOME%
if "%JAVAHOME%" == ""           goto errorNoJava


if not exist "%JAVA_SRCBOX%\java" goto errorNoJavalink
set G2I_HOME=%SRCBOX%\g2i
set SRC_DIR=%G2I_HOME%\sites\NOL
set BLD_DIR=%G2I_HOME%\builds
set DST_DIR=%BLD_DIR%\nol-%1
set ISHIP_DIR=%DST_DIR%\iship
set STAGE_DIR=%DST_DIR%\staging\
set NOL_QA_DIR=%DST_DIR%\qa


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

rem rem pause


del 	"%DST_DIR%\*.*"		/S /F /Q
echo Y | rmdir   "%DST_DIR%"	/s


:s1

if not exist "%DST_DIR%" 		md "%DST_DIR%"
if not exist "%ISHIP_DIR%" 		md "%ISHIP_DIR%"
if not exist "%STAGE_DIR%"	 	md "%STAGE_DIR%"
if not exist "%NOL_QA_DIR%"		md "%NOL_QA_DIR%"



rem
rem	Create Target directories
rem

md "%ISHIP_DIR%\bin"
md "%ISHIP_DIR%\data"
md "%ISHIP_DIR%\classes"
md "%ISHIP_DIR%\logs"
md "%ISHIP_DIR%\kbs"
md "%ISHIP_DIR%\resources"
md "%ISHIP_DIR%\examples"


rem
rem	Create kb files
rem

cd	"%ISHIP_DIR%\Kbs"

set SITE_=%G2I_HOME%\sites\NOL
set KB_=%SITE_%\kbs\nol-dev.kb

set G2IHOME_=%G2i_HOME%
set "G2_MODULE_SEARCH_PATH='%SITE_%' '%SRCBOX%\g2db\kbs' '%G2IHOME_%\sites\nol\kbs' '%G2IHOME_%\sites\Optegrity\kbs' '%G2IHOME_%\sites\eSCOR-ReThink\kbs' '%G2IHOME_%\sites\DevSite\kbs' '%G2IHOME_%\kbs' '%SRCBOX%\kbs' '%G2_DB%' '%SRCBOX%\g2pi\kbs' '%G2_OPCLINK%' '%SRCBOX%\gw\kbs' '%G2_CORBA%\kbs' '%JAVA_SRCBOX%\java\products\javalink\common\kbs'"
set PATH=%G2EXE%;%PATH%

cd %SITE_%
g2 -log %SITE_%\Logs\g2log.txt -icon "NOL Build" -name "NOL Build Server" -nol-auto-build %STAGE_DIR% -kb %KB_% 


rem
rem	Copy files into build directory
rem

rem *** Bin directory ***
echo Copying to %SRC_DIR%\bin
cd	"%SRC_DIR%\bin"
copy    ntnol.exe				"%ISHIP_DIR%\bin"
copy 	nol.ico			 		"%ISHIP_DIR%\bin"

rem *** Data directory ***
echo Copying to %SRC_DIR%\data
cd 	"%SRC_DIR%\data"
copy	*.*					"%ISHIP_DIR%\data"

rem *** Resources directory ***
echo Copying to %SRC_DIR%\resources
cd 	"%SRC_DIR%\resources"
copy	*.txt					"%ISHIP_DIR%\resources"

rem *** Stripped KBs from Staging directory ***
echo Copying KBs to %STAGE_DIR%
cd	"%STAGE_DIR%"
copy	gnne.kb	 				"%ISHIP_DIR%\kbs"
copy	java-module.kb 				"%ISHIP_DIR%\kbs"
copy	nolspack.kb 				"%ISHIP_DIR%\kbs"
copy	nolstudio.kb 				"%ISHIP_DIR%\kbs"

rem *** Demo KBs ***
echo Copying Example KBs
copy    gnne-demo.kb				"%ISHIP_DIR%\examples"

rem *** DOING A VERY VERY BAD THING.  FIX THIS.  Copying from source.  
rem Should be in build procedure!
copy %SRC_DIR%\kbs\gnneapps.kb                  "%ISHIP_DIR%\kbs"

rem Copy all of the QA modules to the QA directory
@echo Need to fix all Optegrity QA modules to be saved to the staging directory.

@echo.
@echo	Setting readonly attributes
@echo.

attrib -R "%ISHIP_DIR%\bin\*.*"
attrib +R "%ISHIP_DIR%\classes\*.*"
attrib +R "%ISHIP_DIR%\kbs\*.*"



if "%2" == "" goto no_unix

set U_BLD_DIR=%2\builds
set U_DST_DIR=%U_BLD_DIR%\nol-%1
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
@echo	NOL build version:	%1
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
