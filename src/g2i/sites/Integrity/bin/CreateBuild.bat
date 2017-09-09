@echo off
setlocal

@echo.
@echo.
@echo	BUILDING Integrity %1
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


rem
rem	check args
rem


if not exist "%DSTBOX%"         set DSTBOX=%SRCBOX%
if "%G2EXE%" == ""              set G2EXE=%DSTBOX%\g2\tape

if not exist "%G2EXE%\g2.exe" goto errorNoG2

if "%JAVAHOME%" == ""           set JAVAHOME=%JAVA_HOME%
if "%JAVAHOME%" == ""           goto errorNoJava
if not exist "%JAVA_SRCBOX%\java" goto errorNoJavalink

set G2I_HOME=%SRCBOX%\g2i
if not exist "%G2I_HOME%" 	goto errorNoSrc
if "%1" == "" 			goto show_usage


set SRC_DIR=%G2I_HOME%\sites\Integrity
set BLD_DIR=%G2I_HOME%\builds
set DST_DIR=%BLD_DIR%\integrity-%1
set ISHIP_DIR=%DST_DIR%\iship
set STAGE_DIR=%DST_DIR%\staging\
set INTEGRITY_QA_DIR=%DST_DIR%\qa


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
if not exist "%INEGRITY_QA_DIR%"	md "%INTEGRITY_QA_DIR%"



rem
rem	Create Target directories
rem

md "%ISHIP_DIR%\bin"
md "%ISHIP_DIR%\data"
rem removing per Tasha's request md "%ISHIP_DIR%\doc"
md "%ISHIP_DIR%\classes"
md "%ISHIP_DIR%\logs"
md "%ISHIP_DIR%\kbs"
md "%ISHIP_DIR%\resources"
md "%ISHIP_DIR%\archives"
md "%ISHIP_DIR%\examples"
md "%ISHIP_DIR%\deprecated"


rem
rem	Create kb files
rem

cd	"%ISHIP_DIR%\Kbs"

set SITE_=%G2I_HOME%\sites\Integrity
set KB_=%SITE_%\kbs\Integrity-dev.kb
set G2IHOME_=%G2i_HOME%
set "PATH=%G2I_HOME%\bin;%G2EXE%;%JAVAHOME%\bin;%PATH%"
set "G2_MODULE_SEARCH_PATH='%SRCBOX%\g2db\kbs' '%SITE_%' '%G2IHOME_%\sites\Integrity\kbs' '%G2IHOME_%\sites\Optegrity\kbs' '%G2IHOME_%\sites\eSCOR-ReThink\kbs' '%G2IHOME_%\sites\DevSite\kbs' '%G2IHOME_%\kbs' '%SRCBOX%\kbs' '%JAVA_SRCBOX%\java\products\javalink\common\kbs' '%SRCBOX%\g2pi\kbs' '%G2_DB%' '%G2_OPCLINK%\' '%SRCBOX%\gw\kbs' '%G2_CORBA%\kbs' '%JAVA_SRCBOX%\java\products\sequoia\common\kbs'"
if not exist "%SITE_%\Logs"	md "%SITE_%\Logs"

cd %SITE_%
g2 -log %SITE_%\Logs\g2log.txt -icon "G2i Dev" -name "G2i Dev Server" -integrity-auto-build %STAGE_DIR% -kb %KB_% 

rem
rem	Copy files into build directory
rem

cd	"%SRC_DIR%\bin"
copy 	Integrity.ico		 		"%ISHIP_DIR%\bin\Integrity.ico"


cd 	"%SRC_DIR%\data"
copy	*.csv					"%ISHIP_DIR%\data"
copy	*.xls					"%ISHIP_DIR%\data"
copy	known-ports.txt				"%ISHIP_DIR%\data"

cd 	"%SRC_DIR%\resources"
copy	*.txt					"%ISHIP_DIR%\resources"


cd 	"%SRC_DIR%\java\classes"



rem See above.  cd	"%SRC_DIR%\Doc"


cd	"%SRC_DIR%\kbs"
rem copy	%G2I_HOME%\kbs\config.txt 		"%ISHIP_DIR%\kbs"
rem copy	%G2I_HOME%\kbs\resources-english.txt	"%ISHIP_DIR%\kbs"


cd	"%STAGE_DIR%"
copy    integrity-core.kb			"%ISHIP_DIR%\kbs"
copy    opexui.kb			"%ISHIP_DIR%\kbs"
copy    opac.kb			"%ISHIP_DIR%\kbs"
copy    opexpes.kb			"%ISHIP_DIR%\kbs"
copy    devui.kb			"%ISHIP_DIR%\kbs"
copy    opcsrui.kb			"%ISHIP_DIR%\kbs"
copy    csruisup.kb			"%ISHIP_DIR%\kbs"
copy    gqsvsup.kb			"%ISHIP_DIR%\kbs"
copy    smh.kb			"%ISHIP_DIR%\kbs"
copy    opfom.kb			"%ISHIP_DIR%\kbs"
copy    scroll.kb			"%ISHIP_DIR%\kbs"
copy    ievlnr.kb			"%ISHIP_DIR%\kbs"
rem *** No longer used: copy    opacuisu.kb			"%ISHIP_DIR%\kbs"
copy    opacore.kb			"%ISHIP_DIR%\kbs"
copy    opcs.kb			"%ISHIP_DIR%\kbs"
rem *** No longer used: copy    dxi.kb			"%ISHIP_DIR%\kbs"
rem *** No longer used: copy    opacsd.kb			"%ISHIP_DIR%\kbs"
copy    tc_core.kb			"%ISHIP_DIR%\kbs"
copy    ping.kb			"%ISHIP_DIR%\kbs"
rem *** No longer used: copy    perf_lib.kb			"%ISHIP_DIR%\kbs"
copy    pingmgr.kb			"%ISHIP_DIR%\kbs"
copy    ipra.kb			"%ISHIP_DIR%\kbs"
rem *** No longer used: copy    oxs.kb			"%ISHIP_DIR%\kbs"
copy    ora-two.kb			"%ISHIP_DIR%\kbs"
copy    opcsui.kb			"%ISHIP_DIR%\kbs"
copy    csuisup.kb			"%ISHIP_DIR%\kbs"
copy    smhui.kb			"%ISHIP_DIR%\kbs"
copy    scrollui.kb			"%ISHIP_DIR%\kbs"
copy    odg-odt.kb			"%ISHIP_DIR%\kbs"
copy    odg-core.kb			"%ISHIP_DIR%\kbs"
copy    ompe-ui.kb			"%ISHIP_DIR%\kbs"
copy    ompe.kb			"%ISHIP_DIR%\kbs"
copy    mpe.kb			"%ISHIP_DIR%\kbs"
copy    mpe-ui.kb			"%ISHIP_DIR%\kbs"
copy    ode-opac.kb			"%ISHIP_DIR%\kbs"
copy    ode-r.kb			"%ISHIP_DIR%\kbs"
copy    ode-d.kb			"%ISHIP_DIR%\kbs"
copy    "%SRC_DIR%\kbs\opweb.kb"	"%ISHIP_DIR%\deprecated"
copy    "%SRC_DIR%\kbs\gwlow.kb"	"%ISHIP_DIR%\deprecated"
copy    pp-snmp.kb			"%ISHIP_DIR%\kbs"
copy    pps.kb			"%ISHIP_DIR%\kbs"
copy    gdxi.kb			"%ISHIP_DIR%\kbs"
copy    integrity.kb     	"%ISHIP_DIR%\kbs"


copy    opx_demo.kb				"%ISHIP_DIR%\examples"
copy    opacdemo.kb				"%ISHIP_DIR%\examples"
copy    dxi_demo.kb                             "%ISHIP_DIR%\examples"
copy    mpe-demo.kb                             "%ISHIP_DIR%\examples"
copy    svcmdemo.kb                             "%ISHIP_DIR%\examples"

rem Copy all of the QA modules to the QA directory
@echo Need to fix all Integrity QA modules to be saved to the staging directory.

@echo.
@echo	Setting readonly attributes
@echo.

attrib -R "%ISHIP_DIR%\bin\*.*"
attrib +R "%ISHIP_DIR%\classes\*.*"
attrib +R "%ISHIP_DIR%\kbs\*.*"



if "%2" == "" goto no_unix

set U_BLD_DIR=%2\builds
set U_DST_DIR=%U_BLD_DIR%\integrity-%1
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
@echo	Integrity build version:	%1
@echo	iship version to promote:	"%ISHIP_DIR%"


cd "%G2i_HOME%"

goto end



:errorNoSrc
@echo.
@echo.
@echo	The environment variable %ISHIP_DIR% does not exist
@echo	Please define it and then restart this shell program.
@echo.



:errorNoJavalink
@echo.
@echo %JAVA_SRCBOX% exists but does not contain java.  Please update your sandbox.
if "%JAVA_SRCBOX%" == "%SRCBOX%" @echo Consider setting the JAVA_SRCBOX variable separately.
goto end


:errorNoJava
@echo.
@echo Cannot find either JAVA_HOME or JAVAHOME environment variable.
@echo.
goto tell_variables

:errorNoG2
@echo.
@echo %G2EXE% (G2EXE) does not contain a G2 to run.
if "%G2EXE%" == "%SRCBOX%\g2\tape" echo G2EXE and DSTBOX were defaulted from SRCBOX.  Please set them separately.
@echo.
goto tell_variables



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

:tell_variables

@echo Environment variables needed:
@echo    SRCBOX: originating sandbox.  Example: k:\bt\ab
@echo    G2EXE: location of g2 executable, if different.  Example: k:\gensym\ut\g2-80a0
@echo           May also be defaulted from DSTBOX, example k:\bt\ab\dst\intelnt.
@echo           DSTBOX will be defaulted from SRCBOX, if not provided.
@echo    G2_DB: Location of G2 database KBs.  Example: k:\gensym\ut\g2odbc-60r11.
@echo    G2_OPCLINK: Location of opclink: Example: k:\gensym\ut\opclink-21r1\KBs.
@echo    G2_CORBA: Location of corbalink: Example: k:\gensym\ut\corbalink-50r3.
@echo    JAVA_SRCBOX: java sandbox if different from originating (use k:\bt\t2)
@echo                 (will be defaulted from SRCBOX.)
@echo    JAVA_HOME or JAVAHOME: location of java installation
@echo    Some version of the G2_OK variable that will authorize your G2.

:end
