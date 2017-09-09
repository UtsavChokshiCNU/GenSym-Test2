@echo off
setlocal

rem Required environment variables:
rem    SRCBOX: originating sandbox
rem    G2EXE: directory containing g2.exe (optional, if can be defaulted)
rem    DSTBOX: location of g2.exe, defaulted to SRCBOX if not specified.
rem    JAVA_SRCBOX: java sandbox if different from originating (use k:\bt\t2)
rem The following can't be gotten from sandboxes because the kb filenames in
rem the sources are different from those in the built and promoted product, 
rem so G2 won't find them when loading.
rem    G2_DB: Location of G2 database KBs.  Example: k:\gensym\ut\g2odbc-60r11.
rem    G2_OPCLINK: Location of opclink: Example: k:\gensym\ut\opclink-21r1\KBs.
rem    G2_CORBA: Location of corbalink: Example: k:\gensym\ut\corbalink-50r3.
rem JAVA_HOME or JAVAHOME are also required for the location of java and its
rem     supporting jar files

rem CVS modules required in your sandbox:
rem   g2i kbs g2pi gw 


@echo.
@echo.
@echo	BUILDING G2i %1
@echo.

rem
rem	check args
rem


if "%1" == "" 			goto show_usage

if not exist "%SRCBOX%"         goto errorNoSrc

rem Look for G2 executable

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

set COMMON_JMAIL_DIR=%DST_DIR%\iship\jmail_common
set COMMON_JMS_DIR=%DST_DIR%\iship\jms_common
set COMMON_SOCKMAN_DIR=%DST_DIR%\iship\sockman_common
set COMMON_MIBPARSER_DIR=%DST_DIR%\iship\mibparser_common
set COMMON_G2SNMP_DIR=%DST_DIR%\iship\snmp_common
set ISHIP_JMAIL_DIR=%DST_DIR%\iship\jmail
set ISHIP_JMS_DIR=%DST_DIR%\iship\jms
set ISHIP_SOCKMAN_DIR=%DST_DIR%\iship\sockman
set ISHIP_MIBPARSER_DIR=%DST_DIR%\iship\mibparser
set ISHIP_G2SNMP_DIR=%DST_DIR%\iship\snmp
set G2I_QA_DIR=%DST_DIR%\qa


set PATH=%G2I_HOME%\bin;%JAVAHOME%\bin;%PATH%

@echo.
@echo	Build settings:
@echo           Source directory:	%G2I_HOME%
@echo           Target directory:	%ISHIP_G2I_DIR%
@echo           Javalink source:	%JAVA_SRCBOX%
@echo.
@echo.
@echo.
@echo	Ensure you updated the Readme files, documentation,
@echo	license files and splash screens as required to
@echo	reflect the current version.
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


del 	"%DST_DIR%\*.*"		/S /F /Q
echo Y | rmdir   "%DST_DIR%"	/s


:s1

if not exist "%DST_DIR%" 		md "%DST_DIR%"
if not exist "%DST_DIR%\iship" 		md "%DST_DIR%\iship"
if not exist "%STAGE_DIR%" 		md "%STAGE_DIR%"
if not exist "%ISHIP_G2I_DIR%" 		md "%ISHIP_G2I_DIR%"
if not exist "%COMMON_JMAIL_DIR%" 	md "%COMMON_JMAIL_DIR%"
if not exist "%COMMON_JMS_DIR%" 	md "%COMMON_JMS_DIR%"
if not exist "%COMMON_SOCKMAN_DIR%"	md "%COMMON_SOCKMAN_DIR%"
if not exist "%COMMON_MIBPARSER_DIR%"	md "%COMMON_MIBPARSER_DIR%"
if not exist "%COMMON_G2SNMP_DIR%"	md "%COMMON_G2SNMP_DIR%"
if not exist "%G2I_QA_DIR%"		md "%G2I_QA_DIR%"


rem
rem	Create Target directories
rem

md "%ISHIP_G2I_DIR%\bin"
md "%ISHIP_G2I_DIR%\classes"
md "%ISHIP_G2I_DIR%\doc"
md "%ISHIP_G2I_DIR%\kbs"
md "%ISHIP_G2I_DIR%\examples"
md "%ISHIP_G2I_DIR%\data"
md "%ISHIP_G2I_DIR%\data\http_root"
md "%ISHIP_G2I_DIR%\data\http_root\images"

md "%ISHIP_G2I_DIR%\G2Agent"
md "%ISHIP_G2I_DIR%\G2Agent\intelnt"
md "%ISHIP_G2I_DIR%\G2Agent\intelnt\bin"
md "%ISHIP_G2I_DIR%\G2Agent\src"

md "%COMMON_JMAIL_DIR%\bin"
md "%COMMON_JMAIL_DIR%\classes"
md "%COMMON_JMAIL_DIR%\doc"
md "%COMMON_JMAIL_DIR%\kbs"
md "%COMMON_JMAIL_DIR%\examples"

md "%COMMON_JMS_DIR%\bin"
md "%COMMON_JMS_DIR%\classes"
md "%COMMON_JMS_DIR%\doc"
md "%COMMON_JMS_DIR%\kbs"
md "%COMMON_JMS_DIR%\examples"

md "%COMMON_SOCKMAN_DIR%\bin"
md "%COMMON_SOCKMAN_DIR%\classes"
md "%COMMON_SOCKMAN_DIR%\doc"
md "%COMMON_SOCKMAN_DIR%\kbs"
md "%COMMON_SOCKMAN_DIR%\examples"

md "%COMMON_MIBPARSER_DIR%\bin"
md "%COMMON_MIBPARSER_DIR%\classes"
md "%COMMON_MIBPARSER_DIR%\doc"
md "%COMMON_MIBPARSER_DIR%\kbs"
md "%COMMON_MIBPARSER_DIR%\examples"

md "%COMMON_G2SNMP_DIR%\bin"
md "%COMMON_G2SNMP_DIR%\classes"
md "%COMMON_G2SNMP_DIR%\doc"
md "%COMMON_G2SNMP_DIR%\kbs"
md "%COMMON_G2SNMP_DIR%\examples"


rem
rem	Create kb files
rem

cd	"%ISHIP_G2I_DIR%\Kbs"

set SITE_=%G2I_HOME%\sites\DevSite
set KB_=%SITE_%\kbs\g2i-dev.kb

set G2IHOME_=%G2i_HOME%

set G2_MODULE_SEARCH_PATH=" '%SITE_%' '%G2IHOME_%\kbs' '%G2IHOME_%\sites\DevSite\kbs' '%G2IHOME_%\sites\Optegrity\kbs' '%G2IHOME_%\sites\Nol\kbs' '%G2IHOME_%\sites\e-SCOR\kbs' '%G2IHOME_%\sites\ReThink\kbs' '%G2IHOME_%\sites\Integrity\kbs' '%SRCBOX%\kbs' '%JAVA_SRCBOX%\java\products\javalink\common\kbs' '%SRCBOX%\g2pi\kbs' '%G2_DB%' '%G2_OPCLINK%' '%SRCBOX%\gw\kbs' '%G2_CORBA%\kbs' '%JAVA_SRCBOX%\java\products\sequoia\common\kbs'"
set PATH=%G2EXE%;%PATH%


cd %SITE_%
g2 -log %SITE_%\Logs\g2log.txt -icon "G2i Dev" -name "G2i Dev Server" -auto-build %STAGE_DIR% -kb %KB_% 



@echo.
@echo	Deleting all java compiled files (*.class)
@echo.


cd "%SRC_DIR%\java"
del /F /S *.class


cd "%SRC_DIR%"


@echo.
@echo	Recompiling CAB files
@echo.

@echo on
@call CreateCAB.bat
@echo off


@echo.
@echo	Recompiling all java files
@echo.

@echo on
@call jc
@call CreateJars
@echo off





rem
rem	Copy files into build directory
rem


cd 	"%SRC_DIR%\java\classes"

copy	G2JMail.jar			"%COMMON_JMAIL_DIR%\classes"
copy	mail.jar			"%COMMON_JMAIL_DIR%\classes"
copy	activation.jar			"%COMMON_JMAIL_DIR%\classes"

copy	G2Jms.jar			"%COMMON_JMS_DIR%\classes"

copy	SocketManager.jar		"%COMMON_SOCKMAN_DIR%\classes"

copy	jmibparser.jar			"%COMMON_MIBPARSER_DIR%\classes"
copy	MibBrowser.jar			"%COMMON_MIBPARSER_DIR%\classes"
copy	AdventNetSnmpHLAPI.jar		"%COMMON_MIBPARSER_DIR%\classes"
copy	AdventNetSnmpLLAPI.jar		"%COMMON_MIBPARSER_DIR%\classes"

copy	G2SNMP.jar			"%COMMON_G2SNMP_DIR%\classes"
copy	AdventNetSnmpLLAPI.jar		"%COMMON_G2SNMP_DIR%\classes"
copy	AdventNetSnmpHLAPI.jar		"%COMMON_G2SNMP_DIR%\classes"
copy	AdventNetSnmp.jar		"%COMMON_G2SNMP_DIR%\classes"
copy	AdventNetLogging.jar		"%COMMON_G2SNMP_DIR%\classes"


cd	"%SRC_DIR%\Doc"


cd	"%SRC_DIR%\kbs"
copy	config.txt 			"%ISHIP_G2I_DIR%\kbs"
copy	resources-english.txt		"%ISHIP_G2I_DIR%\kbs"
copy	guif-resources.txt		"%ISHIP_G2I_DIR%\kbs"
copy	gdpm-resources-english.txt	"%ISHIP_G2I_DIR%\kbs"

rem Copy only the custom data files for the GEUC module as well as
rem the CAB file and images
cd	"%SRC_DIR%\data"
copy	custom-*.csv			"%ISHIP_G2I_DIR%\data"
copy	*.xla				"%ISHIP_G2I_DIR%\data"
copy	*.cab				"%ISHIP_G2I_DIR%\data\http_root"

cd	"%SRC_DIR%\data\images"
copy	*.jpg				"%ISHIP_G2I_DIR%\data\http_root\images"
copy	*.gif				"%ISHIP_G2I_DIR%\data\http_root\images"

cd	"%SRC_DIR%\kbs"
copy	g2i-ui-demo.html		"%ISHIP_G2I_DIR%\examples"
copy	g2i-ui-demo-resource-english.txt "%ISHIP_G2I_DIR%\examples"


cd	"%STAGE_DIR%"
copy	gerr.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	grtl.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	grtl-utils.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	grtl-icons.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	guif.kb				"%ISHIP_G2I_DIR%\kbs"
copy	grlb.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	cdggrlb.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	cdg.kb	 			"%ISHIP_G2I_DIR%\kbs"
copy	gevm.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	gdsm.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	gdsm-agent.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	gdsm-db.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	gdsm-jmail.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	gdsm-jms.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	gdsm-opc.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	gdsm-pi.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	gdsm-web.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	gdsm-snmp.kb			"%ISHIP_G2I_DIR%\kbs"
copy	gedp.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	gdpm.kb 			"%ISHIP_G2I_DIR%\kbs"
rem copy	gdoc.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	grpe.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	gweb.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	gdu.kb 				"%ISHIP_G2I_DIR%\kbs"
copy	gduc.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	gdue.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	brms.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	bpms.kb 			"%ISHIP_G2I_DIR%\kbs"
copy    geuc.kb				"%ISHIP_G2I_DIR%\kbs"
copy    gweb.kb				"%ISHIP_G2I_DIR%\kbs"
copy    brms.kb				"%ISHIP_G2I_DIR%\kbs"
copy    symcure.kb			"%ISHIP_G2I_DIR%\kbs"

copy	gndo.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	gtrap.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	gmib.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	gvad.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	gtad.kb 			"%ISHIP_G2I_DIR%\kbs"

copy	gens.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	gqs.kb	 			"%ISHIP_G2I_DIR%\kbs"
copy	gqsui.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	gqsviews.kb 			"%ISHIP_G2I_DIR%\kbs"
copy	gqsdemo.kb 			"%ISHIP_G2I_DIR%\examples"
copy	glf.kb 				"%ISHIP_G2I_DIR%\kbs"
copy    cdg-modguide.kb			"%ISHIP_G2I_DIR%\examples"

copy	gedp-demo.kb			"%ISHIP_G2I_DIR%\examples"
copy	gdsm-demo.kb			"%ISHIP_G2I_DIR%\examples"
copy	gdpm-demo.kb			"%ISHIP_G2I_DIR%\examples"
copy	gevm-demo.kb			"%ISHIP_G2I_DIR%\examples"
copy	geuc-demo.kb			"%ISHIP_G2I_DIR%\examples"
copy	gdu-demo.kb			"%ISHIP_G2I_DIR%\examples"
copy	grpe-demo.kb			"%ISHIP_G2I_DIR%\examples"
copy	brms-demo.kb			"%ISHIP_G2I_DIR%\examples"
copy	bpms-demo.kb			"%ISHIP_G2I_DIR%\examples"
copy	g2i-ui-demo.kb 			"%ISHIP_G2I_DIR%\examples"

rem copy	gope.kb 		"%ISHIP_G2I_DIR%\kbs"
rem copy	gope-demo.kb		"%ISHIP_G2I_DIR%\examples"


copy	jmail.kb 			"%COMMON_JMAIL_DIR%\kbs"
copy	jmail-demo.kb			"%COMMON_JMAIL_DIR%\examples"

copy	jms.kb 				"%COMMON_JMS_DIR%\kbs"
copy	jms-demo.kb 			"%COMMON_JMS_DIR%\examples"

copy	gsockman.kb 			"%COMMON_SOCKMAN_DIR%\kbs"
copy	gsockdemo.kb 			"%COMMON_SOCKMAN_DIR%\examples"

copy	gsnmp.kb			"%COMMON_G2SNMP_DIR%\kbs"


rem copy G2Agent code
cd %SRC_DIR%\G2Agent
@call devenv /project G2Agent /rebuild Release G2Agent.sln
@call BuildMessagesDLL.bat

cd	"%SRC_DIR%\bin\intelnt"
copy	StartG2Agent.bat 		"%ISHIP_G2I_DIR%\G2Agent\intelnt\bin"

cd	"%SRC_DIR%\G2Agent\Release"
copy	G2Agent.exe	 		"%ISHIP_G2I_DIR%\G2Agent\intelnt\bin"
copy	G2AgentMessages.dll 		"%ISHIP_G2I_DIR%\G2Agent\intelnt\bin"

cd	"%SRC_DIR%\G2Agent"
copy	*.h		 		"%ISHIP_G2I_DIR%\G2Agent\src"
copy	*.c		 		"%ISHIP_G2I_DIR%\G2Agent\src"
copy	*.rc		 		"%ISHIP_G2I_DIR%\G2Agent\src"
copy	*.mc		 		"%ISHIP_G2I_DIR%\G2Agent\src"
copy	*.dsp	 		"%ISHIP_G2I_DIR%\G2Agent\src"
copy	*.dsw	 		"%ISHIP_G2I_DIR%\G2Agent\src"
copy	*.plg	 		"%ISHIP_G2I_DIR%\G2Agent\src"
copy	*.bat	 		"%ISHIP_G2I_DIR%\G2Agent\src"
copy	*.mak	 		"%ISHIP_G2I_DIR%\G2Agent\src"
copy	*.sln	 		"%ISHIP_G2I_DIR%\G2Agent\src"
copy	*.vcxproj	 		"%ISHIP_G2I_DIR%\G2Agent\src"


rem Copy all QA modules to the QA directory
cd	"%STAGE_DIR%"
copy	cdgq.kb				"%G2I_QA_DIR%"
copy	gdocq.kb			"%G2I_QA_DIR%"
copy	gdpmq.kb			"%G2I_QA_DIR%"
copy	gdsmq.kb			"%G2I_QA_DIR%"
copy	gedpq.kb			"%G2I_QA_DIR%"
copy	geucq.kb			"%G2I_QA_DIR%"
copy	gevmq.kb			"%G2I_QA_DIR%"
copy	gmibq.kb			"%G2I_QA_DIR%"
copy	gopeq.kb			"%G2I_QA_DIR%"
copy	grpeq.kb			"%G2I_QA_DIR%"
copy	grtlq.kb			"%G2I_QA_DIR%"
copy	gsockmanq.kb			"%G2I_QA_DIR%"
copy	gtadq.kb			"%G2I_QA_DIR%"
copy	gtrapq.kb			"%G2I_QA_DIR%"
copy	gvadq.kb			"%G2I_QA_DIR%"
copy	gwebq.kb			"%G2I_QA_DIR%"
copy	jmailq.kb			"%G2I_QA_DIR%"
copy	jmsq.kb				"%G2I_QA_DIR%"
copy	gduq.kb				"%G2I_QA_DIR%"
copy	gducq.kb			"%G2I_QA_DIR%"
copy	gwebq.kb			"%G2I_QA_DIR%"


@echo.
@echo	Setting readonly attributes
@echo.

attrib -R "%ISHIP_G2I_DIR%\bin\*.*"
attrib +R "%ISHIP_G2I_DIR%\classes\*.*"
attrib +R "%ISHIP_G2I_DIR%\kbs\*.*"

attrib +R "%COMMON_JMAIL_DIR%\classes\*.*"
attrib +R "%COMMON_JMAIL_DIR%\kbs\*.*"

attrib +R "%COMMON_JMS_DIR%\classes\*.*"
attrib +R "%COMMON_JMS_DIR%\kbs\*.*"

attrib +R "%COMMON_SOCKMAN_DIR%\classes\*.*"
attrib +R "%COMMON_SOCKMAN_DIR%\kbs\*.*"

attrib +R "%COMMON_MIBPARSER_DIR%\classes\*.*"

attrib +R "%COMMON_G2SNMP_DIR%\classes\*.*"

rem all common files and all files for platform independent products copied above.
rem now make duplicate copies for platform dependent products and populate "bin"
rem with platform dependent script files.

rem copy 	StartOptBridge.bat		"%ISHIP_G2I_DIR%\bin"
rem copy	FRONTMIP.DLL			"%ISHIP_G2I_DIR%\bin"
rem copy	OptProb.dll			"%ISHIP_G2I_DIR%\bin"




md "%ISHIP_JMS_DIR%"
md "%ISHIP_JMS_DIR%\intelnt"
md "%ISHIP_JMS_DIR%\sparcsol"
md "%ISHIP_JMS_DIR%\linux"
md "%ISHIP_JMS_DIR%\hp9000s700"
md "%ISHIP_JMS_DIR%\hpia64"
md "%ISHIP_JMS_DIR%\rs6000"


xcopy /s /e /k /h /f /i "%COMMON_JMS_DIR%" "%ISHIP_JMS_DIR%\intelnt"
xcopy /s /e /k /h /f /i "%COMMON_JMS_DIR%" "%ISHIP_JMS_DIR%\sparcsol"
xcopy /s /e /k /h /f /i "%COMMON_JMS_DIR%" "%ISHIP_JMS_DIR%\linux"
xcopy /s /e /k /h /f /i "%COMMON_JMS_DIR%" "%ISHIP_JMS_DIR%\hp9000s700"
xcopy /s /e /k /h /f /i "%COMMON_JMS_DIR%" "%ISHIP_JMS_DIR%\hpia64"
xcopy /s /e /k /h /f /i "%COMMON_JMS_DIR%" "%ISHIP_JMS_DIR%\rs6000"


md "%ISHIP_JMAIL_DIR%"
md "%ISHIP_JMAIL_DIR%\alphaosf"
md "%ISHIP_JMAIL_DIR%\intelnt"
md "%ISHIP_JMAIL_DIR%\sparcsol"
md "%ISHIP_JMAIL_DIR%\linux"
md "%ISHIP_JMAIL_DIR%\hp9000s700"
md "%ISHIP_JMAIL_DIR%\hpia64"
md "%ISHIP_JMAIL_DIR%\rs6000"

xcopy /s /e /k /h /f /i "%COMMON_JMAIL_DIR%" "%ISHIP_JMAIL_DIR%\alphaosf"
xcopy /s /e /k /h /f /i "%COMMON_JMAIL_DIR%" "%ISHIP_JMAIL_DIR%\intelnt"
xcopy /s /e /k /h /f /i "%COMMON_JMAIL_DIR%" "%ISHIP_JMAIL_DIR%\sparcsol"
xcopy /s /e /k /h /f /i "%COMMON_JMAIL_DIR%" "%ISHIP_JMAIL_DIR%\linux"
xcopy /s /e /k /h /f /i "%COMMON_JMAIL_DIR%" "%ISHIP_JMAIL_DIR%\hp9000s700"
xcopy /s /e /k /h /f /i "%COMMON_JMAIL_DIR%" "%ISHIP_JMAIL_DIR%\hpia64"
xcopy /s /e /k /h /f /i "%COMMON_JMAIL_DIR%" "%ISHIP_JMAIL_DIR%\rs6000"


md "%ISHIP_SOCKMAN_DIR%"
md "%ISHIP_SOCKMAN_DIR%\alphaosf"
md "%ISHIP_SOCKMAN_DIR%\intelnt"
md "%ISHIP_SOCKMAN_DIR%\sparcsol"
md "%ISHIP_SOCKMAN_DIR%\linux"
md "%ISHIP_SOCKMAN_DIR%\hp9000s700"
md "%ISHIP_SOCKMAN_DIR%\hpia64"
md "%ISHIP_SOCKMAN_DIR%\rs6000"

xcopy /s /e /k /h /f /i "%COMMON_SOCKMAN_DIR%" "%ISHIP_SOCKMAN_DIR%\alphaosf"
xcopy /s /e /k /h /f /i "%COMMON_SOCKMAN_DIR%" "%ISHIP_SOCKMAN_DIR%\intelnt"
xcopy /s /e /k /h /f /i "%COMMON_SOCKMAN_DIR%" "%ISHIP_SOCKMAN_DIR%\sparcsol"
xcopy /s /e /k /h /f /i "%COMMON_SOCKMAN_DIR%" "%ISHIP_SOCKMAN_DIR%\linux"
xcopy /s /e /k /h /f /i "%COMMON_SOCKMAN_DIR%" "%ISHIP_SOCKMAN_DIR%\hp9000s700"
xcopy /s /e /k /h /f /i "%COMMON_SOCKMAN_DIR%" "%ISHIP_SOCKMAN_DIR%\hpia64"
xcopy /s /e /k /h /f /i "%COMMON_SOCKMAN_DIR%" "%ISHIP_SOCKMAN_DIR%\rs6000"

md "%ISHIP_G2SNMP_DIR%"
md "%ISHIP_G2SNMP_DIR%\intelnt"
md "%ISHIP_G2SNMP_DIR%\sparcsol"
md "%ISHIP_G2SNMP_DIR%\hp9000s700"
md "%ISHIP_G2SNMP_DIR%\hpia64"

xcopy /s /e /k /h /f /i "%COMMON_G2SNMP_DIR%" "%ISHIP_G2SNMP_DIR%\intelnt"
xcopy /s /e /k /h /f /i "%COMMON_G2SNMP_DIR%" "%ISHIP_G2SNMP_DIR%\sparcsol"
xcopy /s /e /k /h /f /i "%COMMON_G2SNMP_DIR%" "%ISHIP_G2SNMP_DIR%\hp9000s700"
xcopy /s /e /k /h /f /i "%COMMON_G2SNMP_DIR%" "%ISHIP_G2SNMP_DIR%\hpia64"



md "%ISHIP_MIBPARSER_DIR%"
md "%ISHIP_MIBPARSER_DIR%\intelnt"

xcopy /s /e /k /h /f /i "%COMMON_MIBPARSER_DIR%" "%ISHIP_MIBPARSER_DIR%\intelnt"


rem  directories made and populated, put in platform dependent files:


cd	"%SRC_DIR%\bin\intelnt"
copy 	StartJMailBridge.bat 		"%ISHIP_JMAIL_DIR%\intelnt\bin"

copy 	StartJmsBridge-j2ee.bat  	"%ISHIP_JMS_DIR%\intelnt\bin"
copy 	StartJmsBridge-jboss.bat	"%ISHIP_JMS_DIR%\intelnt\bin"
copy 	StartJmsBridge-FioranoMQ.bat	"%ISHIP_JMS_DIR%\intelnt\bin"
copy 	StartJmsBridge-SonicMQ.bat	"%ISHIP_JMS_DIR%\intelnt\bin"
copy 	StartJmsBridge-WebSphereMQ.bat	"%ISHIP_JMS_DIR%\intelnt\bin"
copy 	StartJmsBridge-OpenJMS.bat	"%ISHIP_JMS_DIR%\intelnt\bin"

copy	SocketManager.bat		"%ISHIP_SOCKMAN_DIR%\intelnt\bin"

copy	StartJsnmpBridge.bat		"%ISHIP_G2SNMP_DIR%\intelnt\bin"

copy	StartJMibParser.bat		"%ISHIP_MIBPARSER_DIR%\intelnt\bin"

cd	"%SRC_DIR%\bin\sparcsol"
copy	socketmanager			"%ISHIP_SOCKMAN_DIR%\sparcsol\bin"
copy    startjmailbridge		"%ISHIP_JMAIL_DIR%\sparcsol\bin"
copy    startjsnmpbridge.sh		"%ISHIP_G2SNMP_DIR%\sparcsol\bin"

cd	"%SRC_DIR%\bin\linux"
copy	socketmanager			"%ISHIP_SOCKMAN_DIR%\linux\bin"
copy    startjmailbridge		"%ISHIP_JMAIL_DIR%\linux\bin"
copy    startjmsbridge-openjms		"%ISHIP_JMS_DIR%\linux\bin"
copy    startjmsbridge-j2ee		"%ISHIP_JMS_DIR%\linux\bin"
copy    startjmsbridge-jboss		"%ISHIP_JMS_DIR%\linux\bin"

cd	"%SRC_DIR%\bin\hp9000s700"
copy	socketmanager			"%ISHIP_SOCKMAN_DIR%\hp9000s700\bin"
copy    startjmailbridge		"%ISHIP_JMAIL_DIR%\hp9000s700\bin"
copy    startjmsbridge-openjms		"%ISHIP_JMS_DIR%\hp9000s700\bin"
copy    startjmsbridge-jboss		"%ISHIP_JMS_DIR%\hp9000s700\bin"
copy    startjsnmpbridge.sh		"%ISHIP_G2SNMP_DIR%\hp9000s700\bin"

cd	"%SRC_DIR%\bin\hpia64"
copy	socketmanager			"%ISHIP_SOCKMAN_DIR%\hpia64\bin"
copy    startjmailbridge		"%ISHIP_JMAIL_DIR%\hpia64\bin"
copy    startjmsbridge-openjms		"%ISHIP_JMS_DIR%\hpia64\bin"
copy    startjmsbridge-jboss		"%ISHIP_JMS_DIR%\hpia64\bin"
copy    startjsnmpbridge.sh		"%ISHIP_G2SNMP_DIR%\hpia64\bin"

cd	"%SRC_DIR%\bin\rs6000"
copy	socketmanager			"%ISHIP_SOCKMAN_DIR%\rs6000\bin"
copy    startjmailbridge		"%ISHIP_JMAIL_DIR%\rs6000\bin"

cd	"%SRC_DIR%\bin\alphaosf"
copy	socketmanager			"%ISHIP_SOCKMAN_DIR%\alphaosf\bin"
copy    startjmailbridge		"%ISHIP_JMAIL_DIR%\alphaosf\bin"


attrib -R "%ISHIP_JMAIL_DIR%\intelnt\bin\*.*"
attrib -R "%ISHIP_JMS_DIR%\intelnt\bin\*.*"
attrib -R "%ISHIP_SOCKMAN_DIR%\intelnt\bin\*.*"
attrib -R "%ISHIP_G2SNMP_DIR%\intelnt\bin\*.*"
attrib -R "%ISHIP_MIBPARSER_DIR%\intelnt\bin\*.*"


rem Start G2Agent
path %DSTBOX%\gsi\opt;%PATH%
rem start %ISHIP_G2I_DIR%\G2Agent\Intelnt\bin\G2Agent.exe


rem
rem	Create Unix command lines to promote product
rem

set U_BLD_DIR=u:\builds

if "%2" == "" goto default_unix
set U_BLD_DIR=%2\builds

:default_unix

set U_DST_DIR=%U_BLD_DIR%\g2i-%1
set U_ISHIP_G2I_DIR=%U_DST_DIR%\iship

echo /gensym/tools/promote-product -noconfirm -i g2i  ./g2i %1> "%DST_DIR%\iship\script-to-promote-to-iship"
echo /gensym/tools/promote-product -noconfirm -i jmail alphaosf ./jmail/alphaosf %1>> "%DST_DIR%\iship\script-to-promote-to-iship"
echo /gensym/tools/promote-product -noconfirm -i jmail intelnt ./jmail/intelnt %1>> "%DST_DIR%\iship\script-to-promote-to-iship"
echo /gensym/tools/promote-product -noconfirm -i jmail hp9000s700 ./jmail/hp9000s700 %1>> "%DST_DIR%\iship\script-to-promote-to-iship"
echo /gensym/tools/promote-product -noconfirm -i jmail hpia64 ./jmail/hpia64 %1>> "%DST_DIR%\iship\script-to-promote-to-iship"
echo /gensym/tools/promote-product -noconfirm -i jmail linux ./jmail/linux %1>> "%DST_DIR%\iship\script-to-promote-to-iship"
echo /gensym/tools/promote-product -noconfirm -i jmail rs6000 ./jmail/rs6000 %1>> "%DST_DIR%\iship\script-to-promote-to-iship"
echo /gensym/tools/promote-product -noconfirm -i jmail sparcsol ./jmail/sparcsol %1>> "%DST_DIR%\iship\script-to-promote-to-iship"

echo /gensym/tools/promote-product -noconfirm -i jms   intelnt ./jms/intelnt %1>> "%DST_DIR%\iship\script-to-promote-to-iship"
echo /gensym/tools/promote-product -noconfirm -i jms   hp9000s700 ./jms/hp9000s700 %1>> "%DST_DIR%\iship\script-to-promote-to-iship"
echo /gensym/tools/promote-product -noconfirm -i jms   hpia64 ./jms/hpia64 %1>> "%DST_DIR%\iship\script-to-promote-to-iship"
echo /gensym/tools/promote-product -noconfirm -i jms   linux ./jms/linux %1>> "%DST_DIR%\iship\script-to-promote-to-iship"

echo /gensym/tools/promote-product -noconfirm -i sockman   alphaosf ./sockman/alphaosf %1>> "%DST_DIR%\iship\script-to-promote-to-iship"
echo /gensym/tools/promote-product -noconfirm -i sockman   hp9000s700 ./sockman/hp9000s700 %1>> "%DST_DIR%\iship\script-to-promote-to-iship"
echo /gensym/tools/promote-product -noconfirm -i sockman   hpia64 ./sockman/hpia64 %1>> "%DST_DIR%\iship\script-to-promote-to-iship"
echo /gensym/tools/promote-product -noconfirm -i sockman   intelnt ./sockman/intelnt %1>> "%DST_DIR%\iship\script-to-promote-to-iship"
echo /gensym/tools/promote-product -noconfirm -i sockman   linux ./sockman/linux %1>> "%DST_DIR%\iship\script-to-promote-to-iship"
echo /gensym/tools/promote-product -noconfirm -i sockman   rs6000 ./sockman/rs6000 %1>> "%DST_DIR%\iship\script-to-promote-to-iship"
echo /gensym/tools/promote-product -noconfirm -i sockman   sparcsol ./sockman/sparcsol %1>> "%DST_DIR%\iship\script-to-promote-to-iship"

echo /gensym/tools/promote-product -noconfirm -i g2snmpgn   intelnt ./snmp/intelnt %1>> "%DST_DIR%\iship\script-to-promote-to-iship"
echo /gensym/tools/promote-product -noconfirm -i g2snmpgn   sparcsol ./snmp/sparcsol %1>> "%DST_DIR%\iship\script-to-promote-to-iship"
echo /gensym/tools/promote-product -noconfirm -i g2snmpgn   hp9000s700 ./snmp/hp9000s700 %1>> "%DST_DIR%\iship\script-to-promote-to-iship"
echo /gensym/tools/promote-product -noconfirm -i g2snmpgn   hpia64 ./snmp/hpia64 %1>> "%DST_DIR%\iship\script-to-promote-to-iship"

rem
rem	Copy to Unix system
rem

if "%2" == "" goto no_unix

if not exist "%U_BLD_DIR%" 		md "%U_BLD_DIR%"
if not exist "%U_DST_DIR%" 		md "%U_DST_DIR%"
if not exist "%U_ISHIP_G2I_DIR%" 	md "%U_ISHIP_G2I_DIR%"

cd %ISHIP_G2I_DIR%
xcopy	*.*  "%U_ISHIP_G2I_DIR%" /H /E /K



:no_unix


@echo.
@echo	Build has been created 
@echo.
@echo.
@echo	G2i build version:		%1
@echo	iship version to promote:	"%DST_DIR%"


cd "%G2i_HOME%"

goto end



:errorNoSrc
@echo.
@echo.
@echo	The environment variable SRCBOX does not exist
@echo	Please define it and then restart this shell program.
@echo.

goto tell_variables


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


:show_usage
@echo.
@echo.
@echo Usage: CreateBuild "version-tag" 
@echo.
@echo	version-tag:	specifies the version to build
@echo			you only specify the version number,
@echo			i.e. 10b0, 20r0, etc
@echo.
@echo	UnixPath	Unix mounted path to copy build to. It will create be
@echo			stored in the directory (dir created automatically)
@echo				"<UnixPath>/builds/e-SCOR-<version-tag>/iship"
@echo                   This is only necessary if the build was done on local disk.
@echo                   If build is on remote mounted unix disk, it's all set.
@echo.
@echo 	Examples:	createbuild 10r0  
@echo. 			createbuild 10r0  u:
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
