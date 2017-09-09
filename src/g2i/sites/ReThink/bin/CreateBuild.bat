@echo off
setlocal

@echo.
@echo.
@echo	BUILDING ReThink %1
@echo.

rem Required environment variables:
rem    SRCBOX: originating sandbox
rem    G2EXE: directory containing g2.exe (optional, if can be defaulted)
rem    DSTBOX: location of g2.exe, defaulted to SRCBOX if not specified.
rem    JAVA_SRCBOX: java sandbox if different from originating (use k:\bt\t2)
rem The following can't be gotten from sandboxes because the kb filenames in
rem the sources are different from those in the built and promoted product, 
rem so G2 won't find them when loading.
rem    G2_DB: Location of G2 database KBs.  Example: k:\gensym\ut\g2odbc-60r11.
rem    G2_OPCLINK: Location of opclink: Example: k:\gensym\ut\opclink-21r1.
rem    G2_CORBA: Location of corbalink: Example: k:\gensym\ut\corbalink-50r3.
rem JAVA_HOME or JAVAHOME are also required for the location of java and its
rem     supporting jar files

rem CVS modules required in your sandbox:
rem   g2i kbs g2pi gw 

if not exist "%DSTBOX%"         set DSTBOX=%SRCBOX%
if "%G2EXE%" == ""              set G2EXE=%DSTBOX%\g2\tape
if not exist "%G2EXE%\g2.exe" goto errorNoG2

if "%JAVA_SRCBOX%" == ""        set JAVA_SRCBOX=%SRCBOX%

if "%JAVAHOME%" == ""           set JAVAHOME=%JAVA_HOME%
if "%JAVAHOME%" == ""           goto errorNoJava


if not exist "%JAVA_SRCBOX%\java" goto errorNoJavalink

set G2I_HOME=%SRCBOX%\g2i
set SRC_DIR=%G2I_HOME%
set BLD_DIR=%G2I_HOME%\builds
set DST_DIR=%BLD_DIR%\g2i-%1

set STAGE_DIR=%DST_DIR%\staging\

set ISHIP_G2I_DIR=%DST_DIR%\iship\g2i
set ISHIP_NOL_DIR=%DST_DIR%\iship\nol

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


set SRC_DIR=%G2I_HOME%\sites\ReThink
set BLD_DIR=%G2I_HOME%\builds

set DST_DIR=%BLD_DIR%\rethink-%1
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
md "%ISHIP_DIR%\data"
rem md "%ISHIP_DIR%\doc"
md "%ISHIP_DIR%\logs"
md "%ISHIP_DIR%\kbs"
md "%ISHIP_DIR%\kbs\images"
md "%ISHIP_DIR%\resources"
md "%ISHIP_DIR%\examples"



rem
rem	Create kb files
rem

cd	"%ISHIP_DIR%\Kbs"

set SITE_=%G2I_HOME%\sites\ReThink
set KB_=%SITE_%\kbs\rethink-dev.kb
set G2IHOME_=%G2i_HOME%
set "G2_MODULE_SEARCH_PATH='%SRCBOX%\g2db\kbs' '%SITE_%' '%G2IHOME_%\sites\DevSite\kbs' '%G2IHOME_%\sites\Optegrity\kbs' '%G2IHOME_%\sites\e-SCOR\kbs' '%G2IHOME_%\sites\ReThink\kbs' '%G2IHOME_%\kbs' '%SRCBOX%\kbs' '%JAVA_SRCBOX%\java\products\javalink\common\kbs' '%SRCBOX%\g2pi\kbs' '%G2_DB%' '%G2_OPCLINK%\' '%SRCBOX%\gw\kbs' '%G2_CORBA%\kbs' '%JAVA_SRCBOX%\java\products\sequoia\common\kbs'"

cd "%SITE_%"
%G2EXE%\g2.exe -log %SITE_%\Logs\g2log.txt -icon "G2i Dev" -name "G2i Dev Server" -rethink-auto-build %STAGE_DIR% -kb %KB_% 

rem
rem	Copy files into build directory
rem

cd	"%SRC_DIR%\bin"
rem copy 	InstallServerAsNTService.bat 		"%ISHIP_DIR%\bin"
rem copy 	UninstallServerAsNTService.bat 		"%ISHIP_DIR%\bin"
rem copy 	StartServer.bat		 		"%ISHIP_DIR%\bin"
rem copy	StartClient.bat				"%ISHIP_DIR%\bin"
copy 	ReThink.ico		 		"%ISHIP_DIR%\bin"


cd 	"%SRC_DIR%\data"
copy	*.csv					"%ISHIP_DIR%\data"
copy	*.xls					"%ISHIP_DIR%\data"
copy	*.mdb					"%ISHIP_DIR%\data"

rem cd 	"%SRC_DIR%\doc\"
rem copy	ReThink-readme.html			"%ISHIP_DIR%"
rem copy	Master*.html				"%ISHIP_DIR%\doc"
rem copy	*.pdf					"%ISHIP_DIR%\doc"
rem copy	*.chm					"%ISHIP_DIR%\doc"


cd 	"%SRC_DIR%\resources"
copy	aeroscrt.txt				"%ISHIP_DIR%\resources"


cd 	"%SRC_DIR%\images"
copy	*.gif					"%ISHIP_DIR%\kbs\images"


cd	"%SRC_DIR%\kbs"
rem copy	%G2I_HOME%\kbs\config.txt 		"%ISHIP_DIR%\kbs"
rem copy	%G2I_HOME%\kbs\resources-english.txt	"%ISHIP_DIR%\kbs"


cd	"%SRC_DIR%\kbs"
copy	rethink.kb	 			"%ISHIP_DIR%\kbs"
copy	rethink-online.kb 			"%ISHIP_DIR%\kbs"
copy	bpr.kb					"%ISHIP_DIR%\kbs"
copy	bprui.kb				"%ISHIP_DIR%\kbs"
copy	customiz.kb				"%ISHIP_DIR%\kbs"
copy	menus.kb				"%ISHIP_DIR%\kbs"
copy	methods.kb				"%ISHIP_DIR%\kbs"
copy	methods-online.kb			"%ISHIP_DIR%\kbs"
copy	rethink-core.kb				"%ISHIP_DIR%\kbs"
copy	rethink-online-core.kb			"%ISHIP_DIR%\kbs"

copy    aero.kb					"%ISHIP_DIR%\examples"
copy    chapter3.kb				"%ISHIP_DIR%\examples"
copy    orderful.kb				"%ISHIP_DIR%\examples"
copy    rethink-40-doc-examples.kb		"%ISHIP_DIR%\examples"
copy    rethink-40-online-examples.kb		"%ISHIP_DIR%\examples"
rem copy	customizing-rethink-examples.kb		"%ISHIP_DIR%\examples"



rem Copy all of the QA modules to the QA directory


@echo.
@echo	Setting readonly attributes
@echo.

attrib +R "%ISHIP_DIR%\bin\*.*"
attrib +R "%ISHIP_DIR%\data\*.*"
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
@echo	ReThink build version:	%1
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
