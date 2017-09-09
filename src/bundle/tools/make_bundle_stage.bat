@echo off
echo "Run bundle creating - %time%"

pushd ..\..\scripts\nt
call set-boxes
popd

set COPYCMD=/Y
set STAGE_DIR=%SRCBOX%\bundle\stage\intelnt-g2-84r3

rem TODO: set different JAVA_HOME based on STD or ENT.
if "%1" == "std" set "JAVA_HOME=C:\Program Files (x86)\Java\jdk1.6.0_45"
if "%1" == "ent" set "JAVA_HOME=C:\Program Files (x86)\Java\jdk1.6.0_45"
set "JRE_PATH=%JAVA_HOME%\jre"

set "PATH=%PATH%;C:\Program Files\7-Zip"

if NOT "%1" == "" goto create_stage_dir
echo "Mandatory std|ent parameter is missed"
exit 1

:create_stage_dir
@echo.
@echo.
@echo --- Check structure of bundle stage dir
if not exist "%STAGE_DIR%" md "%STAGE_DIR%"
if not exist "%STAGE_DIR%\activexlink\bin" md "%STAGE_DIR%\activexlink\bin"
if "%1" == "ent" md "%STAGE_DIR%\activexlink\bin\x64"
if not exist "%STAGE_DIR%\activexlink\demos\exceldemo" md "%STAGE_DIR%\activexlink\demos\exceldemo"
if not exist "%STAGE_DIR%\activexlink\demos\iedemo" md "%STAGE_DIR%\activexlink\demos\iedemo"
if not exist "%STAGE_DIR%\activexlink\demos\vbdemo" md "%STAGE_DIR%\activexlink\demos\vbdemo"
if not exist "%STAGE_DIR%\activexlink\demos\vbnetdemo\bin" md "%STAGE_DIR%\activexlink\demos\vbnetdemo\bin"
if not exist "%STAGE_DIR%\activexlink\demos\vbnetdemo\bin\x64" md "%STAGE_DIR%\activexlink\demos\vbnetdemo\bin\x64"
if not exist "%STAGE_DIR%\activexlink\demos\vcppdemo\res" md "%STAGE_DIR%\activexlink\demos\vcppdemo\res"
if not exist "%STAGE_DIR%\corbalink\example_clients\cpp" md "%STAGE_DIR%\corbalink\example_clients\cpp"
if not exist "%STAGE_DIR%\corbalink\example_clients\java\feature\mappingPackage" md "%STAGE_DIR%\corbalink\example_clients\java\feature\mappingPackage"
if not exist "%STAGE_DIR%\corbalink\example_clients\java\idlGlobal\eventChannelPackage" md "%STAGE_DIR%\corbalink\example_clients\java\idlGlobal\eventChannelPackage"
if not exist "%STAGE_DIR%\corbalink\idl" md "%STAGE_DIR%\corbalink\idl"
if not exist "%STAGE_DIR%\corbalink\kbs" md "%STAGE_DIR%\corbalink\kbs"
if not exist "%STAGE_DIR%\doc\bridges\activexlink" md "%STAGE_DIR%\doc\bridges\activexlink"
if not exist "%STAGE_DIR%\doc\bridges\corbalink" md "%STAGE_DIR%\doc\bridges\corbalink"
if not exist "%STAGE_DIR%\doc\bridges\db" md "%STAGE_DIR%\doc\bridges\db"
if not exist "%STAGE_DIR%\doc\bridges\hla" md "%STAGE_DIR%\doc\bridges\hla"
if not exist "%STAGE_DIR%\doc\bridges\jmail" md "%STAGE_DIR%\doc\bridges\jmail"
if not exist "%STAGE_DIR%\doc\bridges\jms\html\images" md "%STAGE_DIR%\doc\bridges\jms\html\images"
if not exist "%STAGE_DIR%\doc\bridges\odbc" md "%STAGE_DIR%\doc\bridges\odbc"
if not exist "%STAGE_DIR%\doc\bridges\opcclient" md "%STAGE_DIR%\doc\bridges\opcclient"
if not exist "%STAGE_DIR%\doc\bridges\oracle" md "%STAGE_DIR%\doc\bridges\oracle"
if not exist "%STAGE_DIR%\doc\bridges\pi" md "%STAGE_DIR%\doc\bridges\pi"
if not exist "%STAGE_DIR%\doc\bridges\snmp" md "%STAGE_DIR%\doc\bridges\snmp"
if not exist "%STAGE_DIR%\doc\bridges\sockman" md "%STAGE_DIR%\doc\bridges\sockman"
if not exist "%STAGE_DIR%\doc\bridges\sybase" md "%STAGE_DIR%\doc\bridges\sybase"
if not exist "%STAGE_DIR%\doc\bridges\weblink" md "%STAGE_DIR%\doc\bridges\weblink"
if not exist "%STAGE_DIR%\doc\escor\WinHelp" md "%STAGE_DIR%\doc\escor\WinHelp"
if not exist "%STAGE_DIR%\doc\g2\g2classref" md "%STAGE_DIR%\doc\g2\g2classref"
if not exist "%STAGE_DIR%\doc\g2\g2devguide" md "%STAGE_DIR%\doc\g2\g2devguide"
if not exist "%STAGE_DIR%\doc\g2\g2gateway" md "%STAGE_DIR%\doc\g2\g2gateway"
if not exist "%STAGE_DIR%\doc\g2\g2langrefcard" md "%STAGE_DIR%\doc\g2\g2langrefcard"
if not exist "%STAGE_DIR%\doc\g2\g2refman" md "%STAGE_DIR%\doc\g2\g2refman"
if not exist "%STAGE_DIR%\doc\g2\g2sysprocs" md "%STAGE_DIR%\doc\g2\g2sysprocs"
if not exist "%STAGE_DIR%\doc\g2\g2sysprocsrefcard" md "%STAGE_DIR%\doc\g2\g2sysprocsrefcard"
if not exist "%STAGE_DIR%\doc\g2\g2tutorials" md "%STAGE_DIR%\doc\g2\g2tutorials"
if not exist "%STAGE_DIR%\doc\g2\telewindows" md "%STAGE_DIR%\doc\g2\telewindows"
if not exist "%STAGE_DIR%\doc\g2i\bpms" md "%STAGE_DIR%\doc\g2i\bpms"
if not exist "%STAGE_DIR%\doc\g2i\brms" md "%STAGE_DIR%\doc\g2i\brms"
if not exist "%STAGE_DIR%\doc\g2i\gdpm" md "%STAGE_DIR%\doc\g2i\gdpm"
if not exist "%STAGE_DIR%\doc\g2i\gdsm" md "%STAGE_DIR%\doc\g2i\gdsm"
if not exist "%STAGE_DIR%\doc\g2i\gdu" md "%STAGE_DIR%\doc\g2i\gdu"
if not exist "%STAGE_DIR%\doc\g2i\gedp" md "%STAGE_DIR%\doc\g2i\gedp"
if not exist "%STAGE_DIR%\doc\g2i\gerr" md "%STAGE_DIR%\doc\g2i\gerr"
if not exist "%STAGE_DIR%\doc\g2i\geuc" md "%STAGE_DIR%\doc\g2i\geuc"
if not exist "%STAGE_DIR%\doc\g2i\gevm" md "%STAGE_DIR%\doc\g2i\gevm"
if not exist "%STAGE_DIR%\doc\g2i\grlb" md "%STAGE_DIR%\doc\g2i\grlb"
if not exist "%STAGE_DIR%\doc\g2i\grpe" md "%STAGE_DIR%\doc\g2i\grpe"
if not exist "%STAGE_DIR%\doc\g2i\grtl" md "%STAGE_DIR%\doc\g2i\grtl"
if not exist "%STAGE_DIR%\doc\g2i\gweb" md "%STAGE_DIR%\doc\g2i\gweb"
if not exist "%STAGE_DIR%\doc\gda\gdaapi" md "%STAGE_DIR%\doc\gda\gdaapi"
if not exist "%STAGE_DIR%\doc\gda\gdaugrm" md "%STAGE_DIR%\doc\gda\gdaugrm"
if not exist "%STAGE_DIR%\doc\integrity\WinHelp" md "%STAGE_DIR%\doc\integrity\WinHelp"
if not exist "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\beansruntime" md "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\beansruntime"
if not exist "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\classes\modules\g2evliss" md "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\classes\modules\g2evliss"
if not exist "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\core" md "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\core"
if not exist "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\dlg" md "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\dlg"
if not exist "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\dlgevent" md "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\dlgevent"
if not exist "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\jgi\dataservice" md "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\jgi\dataservice"
if not exist "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\jgi\download" md "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\jgi\download"
if not exist "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\jgi\rmi" md "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\jgi\rmi"
if not exist "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\message" md "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\message"
if not exist "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\net\g2" md "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\net\g2"
if not exist "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\net\memcache" md "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\net\memcache"
if not exist "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\types" md "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\types"
if not exist "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\util\symbol" md "%STAGE_DIR%\doc\javalink\docs\api\com\gensym\util\symbol"
if not exist "%STAGE_DIR%\doc\javalink\docs\guides\g2beanbuilder" md "%STAGE_DIR%\doc\javalink\docs\guides\g2beanbuilder"
if not exist "%STAGE_DIR%\doc\javalink\docs\guides\g2downloadinterfaces" md "%STAGE_DIR%\doc\javalink\docs\guides\g2downloadinterfaces"
if not exist "%STAGE_DIR%\doc\javalink\docs\guides\g2javalink" md "%STAGE_DIR%\doc\javalink\docs\guides\g2javalink"
if not exist "%STAGE_DIR%\doc\symcure" md "%STAGE_DIR%\doc\symcure"
if not exist "%STAGE_DIR%\doc\utilities\g2protools" md "%STAGE_DIR%\doc\utilities\g2protools"
if not exist "%STAGE_DIR%\doc\utilities\gdd" md "%STAGE_DIR%\doc\utilities\gdd"
if not exist "%STAGE_DIR%\doc\utilities\gdi" md "%STAGE_DIR%\doc\utilities\gdi"
if not exist "%STAGE_DIR%\doc\utilities\gfr" md "%STAGE_DIR%\doc\utilities\gfr"
if not exist "%STAGE_DIR%\doc\utilities\gms" md "%STAGE_DIR%\doc\utilities\gms"
if not exist "%STAGE_DIR%\doc\utilities\golddev" md "%STAGE_DIR%\doc\utilities\golddev"
if not exist "%STAGE_DIR%\doc\utilities\goldui" md "%STAGE_DIR%\doc\utilities\goldui"
if not exist "%STAGE_DIR%\doc\utilities\guideprocref" md "%STAGE_DIR%\doc\utilities\guideprocref"
if not exist "%STAGE_DIR%\doc\utilities\guideuserguide" md "%STAGE_DIR%\doc\utilities\guideuserguide"
if not exist "%STAGE_DIR%\doc\utilities\gxl" md "%STAGE_DIR%\doc\utilities\gxl"
if not exist "%STAGE_DIR%\escor\bin" md "%STAGE_DIR%\escor\bin"
if not exist "%STAGE_DIR%\escor\data" md "%STAGE_DIR%\escor\data"
if not exist "%STAGE_DIR%\escor\examples" md "%STAGE_DIR%\escor\examples"
if not exist "%STAGE_DIR%\escor\kbs\images" md "%STAGE_DIR%\escor\kbs\images"
if not exist "%STAGE_DIR%\escor\logs" md "%STAGE_DIR%\escor\logs"
if not exist "%STAGE_DIR%\escor\resources" md "%STAGE_DIR%\escor\resources"
if not exist "%STAGE_DIR%\g2\examples\html" md "%STAGE_DIR%\g2\examples\html"
if not exist "%STAGE_DIR%\g2\examples\kbs" md "%STAGE_DIR%\g2\examples\kbs"
if not exist "%STAGE_DIR%\g2\examples\vb" md "%STAGE_DIR%\g2\examples\vb"
if not exist "%STAGE_DIR%\g2\ext" md "%STAGE_DIR%\g2\ext"
if not exist "%STAGE_DIR%\g2\fonts" md "%STAGE_DIR%\g2\fonts"
if not exist "%STAGE_DIR%\g2\kbs\demos" md "%STAGE_DIR%\g2\kbs\demos"
if not exist "%STAGE_DIR%\g2\kbs\samples" md "%STAGE_DIR%\g2\kbs\samples"
if not exist "%STAGE_DIR%\g2\kbs\tutors" md "%STAGE_DIR%\g2\kbs\tutors"
if not exist "%STAGE_DIR%\g2\kbs\utils" md "%STAGE_DIR%\g2\kbs\utils"
if not exist "%STAGE_DIR%\G2 Development Installation Info" md "%STAGE_DIR%\G2 Development Installation Info"
if not exist "%STAGE_DIR%\g2i\data\http_root\images" md "%STAGE_DIR%\g2i\data\http_root\images"
if not exist "%STAGE_DIR%\g2i\examples" md "%STAGE_DIR%\g2i\examples"
if not exist "%STAGE_DIR%\g2i\g2agent\intelnt\bin" md "%STAGE_DIR%\g2i\g2agent\intelnt\bin"
if not exist "%STAGE_DIR%\g2i\g2agent\src" md "%STAGE_DIR%\g2i\g2agent\src"
if not exist "%STAGE_DIR%\g2i\kbs" md "%STAGE_DIR%\g2i\kbs"
if not exist "%STAGE_DIR%\g2mibparser\bin" md "%STAGE_DIR%\g2mibparser\bin"
if not exist "%STAGE_DIR%\g2mibparser\classes" md "%STAGE_DIR%\g2mibparser\classes"
if not exist "%STAGE_DIR%\g2mibparser\doc" md "%STAGE_DIR%\g2mibparser\doc"
if not exist "%STAGE_DIR%\g2mibparser\examples" md "%STAGE_DIR%\g2mibparser\examples"
if not exist "%STAGE_DIR%\g2mibparser\kbs" md "%STAGE_DIR%\g2mibparser\kbs"
if not exist "%STAGE_DIR%\gda\bin" md "%STAGE_DIR%\gda\bin"
if not exist "%STAGE_DIR%\gda\examples" md "%STAGE_DIR%\gda\examples"
if not exist "%STAGE_DIR%\gda\kbs" md "%STAGE_DIR%\gda\kbs"
if not exist "%STAGE_DIR%\gsi" md "%STAGE_DIR%\gsi"
if "%1" == "ent" md "%STAGE_DIR%\gsi\x64"
if not exist "%STAGE_DIR%\gw\kbs" md "%STAGE_DIR%\gw\kbs"
if not exist "%STAGE_DIR%\gw\www" md "%STAGE_DIR%\gw\www"
if not exist "%STAGE_DIR%\hla\bin" md "%STAGE_DIR%\hla\bin"
if not exist "%STAGE_DIR%\hla\examples\G2Demo_Federate" md "%STAGE_DIR%\hla\examples\G2Demo_Federate"
if not exist "%STAGE_DIR%\hla\examples\G2HelloWorld_Federate" md "%STAGE_DIR%\hla\examples\G2HelloWorld_Federate"
if not exist "%STAGE_DIR%\hla\images" md "%STAGE_DIR%\hla\images"
if not exist "%STAGE_DIR%\hla\kbs" md "%STAGE_DIR%\hla\kbs"
if not exist "%STAGE_DIR%\hla\resources" md "%STAGE_DIR%\hla\resources"
if not exist "%STAGE_DIR%\integrity\archives" md "%STAGE_DIR%\integrity\archives"
if not exist "%STAGE_DIR%\integrity\bin" md "%STAGE_DIR%\integrity\bin"
if not exist "%STAGE_DIR%\integrity\classes" md "%STAGE_DIR%\integrity\classes"
if not exist "%STAGE_DIR%\integrity\data" md "%STAGE_DIR%\integrity\data"
if not exist "%STAGE_DIR%\integrity\deprecated" md "%STAGE_DIR%\integrity\deprecated"
if not exist "%STAGE_DIR%\integrity\examples" md "%STAGE_DIR%\integrity\examples"
if not exist "%STAGE_DIR%\integrity\kbs" md "%STAGE_DIR%\integrity\kbs"
if not exist "%STAGE_DIR%\integrity\logs" md "%STAGE_DIR%\integrity\logs"
if not exist "%STAGE_DIR%\integrity\resources" md "%STAGE_DIR%\integrity\resources"
if not exist "%STAGE_DIR%\javalink\bin" md "%STAGE_DIR%\javalink\bin"
if "%1" == "ent" md "%STAGE_DIR%\javalink\bin\x64"
if not exist "%STAGE_DIR%\javalink\classes\com\gensym\classes\modules\javalink" md "%STAGE_DIR%\javalink\classes\com\gensym\classes\modules\javalink"
if not exist "%STAGE_DIR%\javalink\classes\com\gensym\classes\modules\jgidemo" md "%STAGE_DIR%\javalink\classes\com\gensym\classes\modules\jgidemo"
if not exist "%STAGE_DIR%\javalink\classes\com\gensym\demos\jgi" md "%STAGE_DIR%\javalink\classes\com\gensym\demos\jgi"
if not exist "%STAGE_DIR%\javalink\kbs" md "%STAGE_DIR%\javalink\kbs"
if not exist "%STAGE_DIR%\jdbc\bin" md "%STAGE_DIR%\jdbc\bin"
if not exist "%STAGE_DIR%\jdbc\classes" md "%STAGE_DIR%\jdbc\classes"
if not exist "%STAGE_DIR%\jdbc\kbs" md "%STAGE_DIR%\jdbc\kbs"
if not exist "%STAGE_DIR%\jmail\bin" md "%STAGE_DIR%\jmail\bin"
if not exist "%STAGE_DIR%\jmail\classes" md "%STAGE_DIR%\jmail\classes"
if not exist "%STAGE_DIR%\jmail\doc" md "%STAGE_DIR%\jmail\doc"
if not exist "%STAGE_DIR%\jmail\examples" md "%STAGE_DIR%\jmail\examples"
if not exist "%STAGE_DIR%\jmail\kbs" md "%STAGE_DIR%\jmail\kbs"
if not exist "%STAGE_DIR%\jms\bin" md "%STAGE_DIR%\jms\bin"
if not exist "%STAGE_DIR%\jms\classes" md "%STAGE_DIR%\jms\classes"
if not exist "%STAGE_DIR%\jms\doc" md "%STAGE_DIR%\jms\doc"
if not exist "%STAGE_DIR%\jms\examples" md "%STAGE_DIR%\jms\examples"
if not exist "%STAGE_DIR%\jms\kbs" md "%STAGE_DIR%\jms\kbs"
if not exist "%STAGE_DIR%\jsnmp\bin" md "%STAGE_DIR%\jsnmp\bin"
if not exist "%STAGE_DIR%\jsnmp\classes" md "%STAGE_DIR%\jsnmp\classes"
if not exist "%STAGE_DIR%\jsnmp\doc" md "%STAGE_DIR%\jsnmp\doc"
if not exist "%STAGE_DIR%\jsnmp\examples" md "%STAGE_DIR%\jsnmp\examples"
if not exist "%STAGE_DIR%\jsnmp\kbs" md "%STAGE_DIR%\jsnmp\kbs"
if not exist "%STAGE_DIR%\logs" md "%STAGE_DIR%\logs"
if not exist "%STAGE_DIR%\nol\bin" md "%STAGE_DIR%\nol\bin"
if "%1" == "ent" md "%STAGE_DIR%\nol\bin\x64"
if not exist "%STAGE_DIR%\nol\kbs" md "%STAGE_DIR%\nol\kbs"
if not exist "%STAGE_DIR%\nol\projects\examples\bakery-demo" md "%STAGE_DIR%\nol\projects\examples\bakery-demo"
if not exist "%STAGE_DIR%\nol\projects\examples\bleach-demo" md "%STAGE_DIR%\nol\projects\examples\bleach-demo"
if not exist "%STAGE_DIR%\nol\projects\examples\gnne-demo" md "%STAGE_DIR%\nol\projects\examples\gnne-demo"
if not exist "%STAGE_DIR%\nol\projects\examples\total-demo" md "%STAGE_DIR%\nol\projects\examples\total-demo"
if not exist "%STAGE_DIR%\nolstudio\bin" md "%STAGE_DIR%\nolstudio\bin"
if not exist "%STAGE_DIR%\nolstudio\projects\examples\ActiveXDemo\ExcelDemo" md "%STAGE_DIR%\nolstudio\projects\examples\ActiveXDemo\ExcelDemo"
if not exist "%STAGE_DIR%\nolstudio\projects\examples\ActiveXDemo\Optimizer" md "%STAGE_DIR%\nolstudio\projects\examples\ActiveXDemo\Optimizer"
if not exist "%STAGE_DIR%\nolstudio\projects\examples\ActiveXDemo\Predictor\rowMode" md "%STAGE_DIR%\nolstudio\projects\examples\ActiveXDemo\Predictor\rowMode"
if not exist "%STAGE_DIR%\nolstudio\projects\examples\ActiveXDemo\Predictor\timeMode" md "%STAGE_DIR%\nolstudio\projects\examples\ActiveXDemo\Predictor\timeMode"
if not exist "%STAGE_DIR%\nolstudio\projects\examples\DataSet" md "%STAGE_DIR%\nolstudio\projects\examples\DataSet"
if not exist "%STAGE_DIR%\nolstudio\projects\examples\projects" md "%STAGE_DIR%\nolstudio\projects\examples\projects"
if not exist "%STAGE_DIR%\odbc\bin" md "%STAGE_DIR%\odbc\bin"
if "%1" == "ent" md "%STAGE_DIR%\odbc\bin\x64"
if not exist "%STAGE_DIR%\odbc\kbs" md "%STAGE_DIR%\odbc\kbs"
if not exist "%STAGE_DIR%\odbc\sql" md "%STAGE_DIR%\odbc\sql"
if not exist "%STAGE_DIR%\odbc_unicode\bin" md "%STAGE_DIR%\odbc_unicode\bin"
if "%1" == "ent" md "%STAGE_DIR%\odbc_unicode\bin\x64"
if not exist "%STAGE_DIR%\odbc_unicode\kbs" md "%STAGE_DIR%\odbc_unicode\kbs"
if not exist "%STAGE_DIR%\odbc_unicode\sql" md "%STAGE_DIR%\odbc_unicode\sql"
if not exist "%STAGE_DIR%\opcclient" md "%STAGE_DIR%\opcclient"
if "%1" == "ent" md "%STAGE_DIR%\opcclient\x64"
if not exist "%STAGE_DIR%\opcclient\kbs" md "%STAGE_DIR%\opcclient\kbs"
if not exist "%STAGE_DIR%\opclink\kbs" md "%STAGE_DIR%\opclink\kbs"
if not exist "%STAGE_DIR%\optegrity\archives" md "%STAGE_DIR%\optegrity\archives"
if not exist "%STAGE_DIR%\optegrity\bin" md "%STAGE_DIR%\optegrity\bin"
if not exist "%STAGE_DIR%\optegrity\data" md "%STAGE_DIR%\optegrity\data"
if not exist "%STAGE_DIR%\optegrity\examples" md "%STAGE_DIR%\optegrity\examples"
if not exist "%STAGE_DIR%\optegrity\kbs" md "%STAGE_DIR%\optegrity\kbs"
if not exist "%STAGE_DIR%\oracle\bin" md "%STAGE_DIR%\oracle\bin"
if "%1" == "ent" md "%STAGE_DIR%\oracle\bin\x64"
if not exist "%STAGE_DIR%\oracle\kbs" md "%STAGE_DIR%\oracle\kbs"
if not exist "%STAGE_DIR%\pi\bin" md "%STAGE_DIR%\pi\bin"
if not exist "%STAGE_DIR%\pi\kbs" md "%STAGE_DIR%\pi\kbs"
if not exist "%STAGE_DIR%\protools\kbs" md "%STAGE_DIR%\protools\kbs"
if not exist "%STAGE_DIR%\rethink\bin" md "%STAGE_DIR%\rethink\bin"
if not exist "%STAGE_DIR%\rethink\data" md "%STAGE_DIR%\rethink\data"
if not exist "%STAGE_DIR%\rethink\examples" md "%STAGE_DIR%\rethink\examples"
if not exist "%STAGE_DIR%\rethink\kbs\images" md "%STAGE_DIR%\rethink\kbs\images"
if not exist "%STAGE_DIR%\rethink\logs" md "%STAGE_DIR%\rethink\logs"
if not exist "%STAGE_DIR%\rethink\resources" md "%STAGE_DIR%\rethink\resources"
if not exist "%STAGE_DIR%\sockman\bin" md "%STAGE_DIR%\sockman\bin"
if not exist "%STAGE_DIR%\sockman\classes" md "%STAGE_DIR%\sockman\classes"
if not exist "%STAGE_DIR%\sockman\doc" md "%STAGE_DIR%\sockman\doc"
if not exist "%STAGE_DIR%\sockman\examples" md "%STAGE_DIR%\sockman\examples"
if not exist "%STAGE_DIR%\sockman\kbs" md "%STAGE_DIR%\sockman\kbs"
if not exist "%STAGE_DIR%\sybase\bin" md "%STAGE_DIR%\sybase\bin"
if "%1" == "ent" md "%STAGE_DIR%\sybase\bin\x64"
if not exist "%STAGE_DIR%\sybase\kbs" md "%STAGE_DIR%\sybase\kbs"
if not exist "%STAGE_DIR%\sybase\sql" md "%STAGE_DIR%\sybase\sql"
if not exist "%STAGE_DIR%\gw" md "%STAGE_DIR%\gw"
if not exist "%STAGE_DIR%\gw\kbs" md "%STAGE_DIR%\gw\kbs"
if not exist "%STAGE_DIR%\gw\www" md "%STAGE_DIR%\gw\www"
if not exist "%STAGE_DIR%\symbols" md "%STAGE_DIR%\symbols"
if "%1" == "ent" md "%STAGE_DIR%\symbols\x64"

@echo.
@echo.
@echo --- Copy JRE: %JRE_PATH%
if exist "%STAGE_DIR%/jre" rd /S /Q "%STAGE_DIR%/jre"
xcopy "%JRE_PATH%" %STAGE_DIR%\jre\ /S /E /Y

:copy_binary
@echo.
@echo.
@echo --- Copy g2.exe, tw.exe and twng.exe
xcopy %DSTBOX%\g2\opt\g2.exe %STAGE_DIR%\g2\ /R
xcopy %DSTBOX%\g2\opt\x32\libiconv.dll %STAGE_DIR%\g2\ /R
xcopy %DSTBOX%\g2\opt\x64\libiconv.dll %STAGE_DIR%\g2\x64\ /R
xcopy %DSTBOX%\g2\opt\g2passwd.exe %STAGE_DIR%\g2\ /R
xcopy %DSTBOX%\g2\opt\gservice.exe %STAGE_DIR%\g2\ /R
xcopy %DSTBOX%\g2\opt\machine-id.exe %STAGE_DIR%\g2\ /R
xcopy %DSTBOX%\g2\opt\hostlookup.exe %STAGE_DIR%\g2\ /R
xcopy %DSTBOX%\twng\opt\Twng.exe %STAGE_DIR%\g2\ /R
xcopy %DSTBOX%\tw\opt\tw.exe %STAGE_DIR%\g2\ /R
xcopy %DSTBOX%\activex\opt\TwControl.cab %STAGE_DIR%\g2\ /R
xcopy %DSTBOX%\activex\opt\TwControl.ocx %STAGE_DIR%\g2\ /R
xcopy %SRCBOX%\promote\bin\sleep.exe %STAGE_DIR%\g2\kbs\demos\ /R
xcopy %SRCBOX%\promote\start-mill.bat %STAGE_DIR%\g2\kbs\demos\ /R
xcopy %SRCBOX%\promote\StartServer.bat %STAGE_DIR%\g2\ /R
REM
REM SymScale is not part of the installer (yet)
REM if "%1" == "ent" xcopy %SRCBOX%\promote\SymScale.bat %STAGE_DIR%\g2\ /R
REM  if "%1" == "std" del /q %STAGE_DIR%\g2\SymScale.bat
REM if "%1" == "ent" xcopy %DSTBOX%\g2\opt\SymScale.exe %STAGE_DIR%\g2\ /R
REM if "%1" == "std" del /q %STAGE_DIR%\g2\SymScale.exe

:activex
@echo.
@echo.
@echo --- Copy G2COM (ActiveXLink)
xcopy %DSTBOX%\activex\opt\G2Com.dll %STAGE_DIR%\activexlink\bin\ /R
if "%1" == "ent" xcopy %DSTBOX%\activex\opt\x64\G2Com.dll %STAGE_DIR%\activexlink\bin\x64\ /R
xcopy %DSTBOX%\gsi\opt\gsi.dll %STAGE_DIR%\activexlink\bin\ /R
if "%1" == "std" rd /s /q %STAGE_DIR%\activexlink\bin\x64
if "%1" == "ent" xcopy %DSTBOX%\gsi\opt\x64\gsi.dll %STAGE_DIR%\activexlink\bin\x64\ /R
xcopy %SRCBOX%\promote\registerControls.bat %STAGE_DIR%\g2\ /R
xcopy %SRCBOX%\promote\unregisterControls.bat %STAGE_DIR%\g2\ /R
xcopy %SRCBOX%\activex\control\examples\install.html %STAGE_DIR%\g2\ /R
xcopy %SRCBOX%\activex\control\auxi\registerTwControl.bat %STAGE_DIR%\g2\ /R
xcopy %SRCBOX%\activex\control\auxi\unregisterTwControl.bat %STAGE_DIR%\g2\ /R

@echo --- Copy G2COM demos
xcopy %SRCBOX%\activex\G2Com\demos\ExcelDemo\*.* %STAGE_DIR%\activexlink\demos\exceldemo /R
xcopy %SRCBOX%\activex\G2Com\demos\IEDemo\*.* %STAGE_DIR%\activexlink\demos\iedemo /R
xcopy %SRCBOX%\activex\G2Com\demos\VBDemo\*.* %STAGE_DIR%\activexlink\demos\vbdemo /R
xcopy %SRCBOX%\activex\G2Com\demos\vbnetdemo\*.* %STAGE_DIR%\activexlink\demos\vbnetdemo /R
xcopy %SRCBOX%\activex\G2Com\demos\vbnetdemo\bin\x86\*.* %STAGE_DIR%\activexlink\demos\vbnetdemo\bin /R
xcopy %SRCBOX%\activex\G2Com\demos\vbnetdemo\bin\x64\*.* %STAGE_DIR%\activexlink\demos\vbnetdemo\bin\x64 /R
xcopy %SRCBOX%\activex\G2Com\demos\VCppDemo\*.* %STAGE_DIR%\activexlink\demos\vcppdemo /R
xcopy %SRCBOX%\activex\G2Com\demos\VCppDemo\res\*.* %STAGE_DIR%\activexlink\demos\vcppdemo\res /R

:CorbaLink
@echo.
@echo.
@echo --- Copy CORBA (CorbaLink)
xcopy %SRCBOX%\corba\as-is\common\example_clients\cpp\* %STAGE_DIR%\corbalink\example_clients\cpp\ /R
xcopy %SRCBOX%\corba\as-is\common\example_clients\java\* %STAGE_DIR%\corbalink\example_clients\java\ /R
xcopy %SRCBOX%\corba\as-is\common\idl\* %STAGE_DIR%\corbalink\idl\ /R
xcopy %SRCBOX%\corba\as-is\common\kbs\* %STAGE_DIR%\corbalink\kbs\ /R
xcopy %SRCBOX%\corba\as-is\intelnt\example_clients\cpp\* %STAGE_DIR%\corbalink\example_clients\cpp\ /R
xcopy %SRCBOX%\corba\kbs\* %STAGE_DIR%\corbalink\kbs\ 

:OpcClient
@echo.
@echo.
@echo --- Copy G2OPC (OpcClient)
xcopy %DSTBOX%\g2opc\g2opc.exe %STAGE_DIR%\opcclient /R
xcopy %SRCBOX%\g2opc\cpp\configfile.ini %STAGE_DIR%\opcclient /R
xcopy %SRCBOX%\g2opc\misc\run-g2opc.bat %STAGE_DIR%\opcclient /R
if "%1" == "std" rd /s /q %STAGE_DIR%\opcclient\x64
if "%1" == "ent" xcopy %DSTBOX%\g2opc\x64\g2opc.exe %STAGE_DIR%\opcclient\x64 /R
if "%1" == "ent" xcopy %SRCBOX%\g2opc\cpp\configfile.ini %STAGE_DIR%\opcclient\x64 /R
if "%1" == "ent" xcopy %SRCBOX%\g2opc\misc\x64\run-g2opc.bat %STAGE_DIR%\opcclient\x64 /R
xcopy %SRCBOX%\g2opc\kbs\*.kb %STAGE_DIR%\opcclient\kbs /R

:pibridge
@echo.
@echo.
@echo --- Copy G2PI bridge
xcopy %DSTBOX%\pi\opt\g2pi.exe %STAGE_DIR%\pi\bin /R

:build_shipped_gsi
@echo.
@echo.
@echo --- build shipped version of gsi
pushd %SRCBOX%\gsi\sample
call ant setup
xcopy * %STAGE_DIR%\gsi\ /R
del /q %STAGE_DIR%\gsi\build.xml
xcopy %SRCBOX%\kbs\gsi_exam.kb %STAGE_DIR%\gsi /R
xcopy %SRCBOX%\kbs\itempass.kb %STAGE_DIR%\gsi /R
xcopy %SRCBOX%\kbs\mapchar.kb %STAGE_DIR%\gsi /R
popd

:copy_gsi
@echo.
@echo.
@echo --- Copy gsi and other libraries
xcopy %DSTBOX%\gsi\opt\gsi.lib %STAGE_DIR%\gsi /R
xcopy %DSTBOX%\gsi\opt\gsi.dll %STAGE_DIR%\gsi /R
xcopy %DSTBOX%\gsi\opt\libgsi.lib %STAGE_DIR%\gsi /R
xcopy %DSTBOX%\gsi\opt\librtl.lib %STAGE_DIR%\gsi /R
xcopy %DSTBOX%\gsi\opt\libtcp.lib %STAGE_DIR%\gsi /R
xcopy %DSTBOX%\gsi\opt\alarmer.exe %STAGE_DIR%\gsi /R
xcopy %DSTBOX%\gsi\opt\filetest.exe %STAGE_DIR%\gsi /R
xcopy %DSTBOX%\gsi\opt\itemtest.exe %STAGE_DIR%\gsi /R
xcopy %DSTBOX%\gsi\opt\mapchar.exe %STAGE_DIR%\gsi /R
xcopy %DSTBOX%\gsi\opt\matrix.exe %STAGE_DIR%\gsi /R
xcopy %DSTBOX%\gsi\opt\reposit.exe %STAGE_DIR%\gsi /R
xcopy %DSTBOX%\gsi\opt\skeleton.exe %STAGE_DIR%\gsi /R
xcopy %DSTBOX%\gsi\opt\typetest.exe %STAGE_DIR%\gsi /R
xcopy %SRCBOX%\gsi\sample\graphics.dat %STAGE_DIR%\gsi /R

:copy_gsi_x64
@echo.
@echo.
@echo --- Copy gsi and other libraries (x64)
if "%1" == "ent" xcopy %DSTBOX%\gsi\opt\x64\gsi.lib %STAGE_DIR%\gsi\x64 /R
if "%1" == "ent" xcopy %DSTBOX%\gsi\opt\x64\gsi.dll %STAGE_DIR%\gsi\x64 /R
if "%1" == "ent" xcopy %DSTBOX%\gsi\opt\x64\libgsi.lib %STAGE_DIR%\gsi\x64 /R
if "%1" == "ent" xcopy %DSTBOX%\gsi\opt\x64\librtl.lib %STAGE_DIR%\gsi\x64 /R
if "%1" == "ent" xcopy %DSTBOX%\gsi\opt\x64\libtcp.lib %STAGE_DIR%\gsi\x64 /R
if "%1" == "ent" xcopy %DSTBOX%\gsi\opt\x64\alarmer.exe %STAGE_DIR%\gsi\x64 /R
if "%1" == "ent" xcopy %DSTBOX%\gsi\opt\x64\filetest.exe %STAGE_DIR%\gsi\x64 /R
if "%1" == "ent" xcopy %DSTBOX%\gsi\opt\x64\itemtest.exe %STAGE_DIR%\gsi\x64 /R
if "%1" == "ent" xcopy %DSTBOX%\gsi\opt\x64\mapchar.exe %STAGE_DIR%\gsi\x64 /R
if "%1" == "ent" xcopy %DSTBOX%\gsi\opt\x64\matrix.exe %STAGE_DIR%\gsi\x64 /R
if "%1" == "ent" xcopy %DSTBOX%\gsi\opt\x64\reposit.exe %STAGE_DIR%\gsi\x64 /R
if "%1" == "ent" xcopy %DSTBOX%\gsi\opt\x64\skeleton.exe %STAGE_DIR%\gsi\x64 /R
if "%1" == "ent" xcopy %DSTBOX%\gsi\opt\x64\typetest.exe %STAGE_DIR%\gsi\x64 /R
if "%1" == "ent" xcopy %SRCBOX%\gsi\sample\graphics.dat %STAGE_DIR%\gsi\x64 /R
if "%1" == "std" del /s /q %STAGE_DIR%\gsi\x64

:copy_gw
xcopy %DSTBOX%\gw\opt\gw.exe %STAGE_DIR%\gw\ /R
xcopy %SRCBOX%\license\gw\gsi.ok %STAGE_DIR%\gw\ /R
xcopy %SRCBOX%\gw\kbs\gwlow.kb %STAGE_DIR%\gw\kbs\ /R
xcopy %SRCBOX%\gw\kbs\gwex1.kb %STAGE_DIR%\gw\kbs\ /R
xcopy %SRCBOX%\gw\kbs\gwex2.kb %STAGE_DIR%\gw\kbs\ /R
xcopy %SRCBOX%\gw\kbs\gwex3.kb %STAGE_DIR%\gw\kbs\ /R
xcopy %SRCBOX%\gw\doc\bridge.gif %STAGE_DIR%\gw\www\ /R

:copy_libforgn
xcopy %DSTBOX%\g2\opt\overlay.exe %STAGE_DIR%\g2\ext\ /R
xcopy %DSTBOX%\gsi\opt\libforgn.lib %STAGE_DIR%\g2\ext\ /R
xcopy %SRCBOX%\promote\fgntest.c %STAGE_DIR%\g2\ext\ /R
xcopy %SRCBOX%\kbs\fgntest.kb %STAGE_DIR%\kbs\samples\ /R
xcopy %SRCBOX%\ext\c\fgntest.tpl %STAGE_DIR%\g2\ext\ /R
xcopy %SRCBOX%\ext\c\foreign.h %STAGE_DIR%\g2\ext\ /R
xcopy %SRCBOX%\ext\c\icp.h %STAGE_DIR%\g2\ext\ /R
copy %SRCBOX%\promote\fgntest-makefile %STAGE_DIR%\g2\ext\Makefile

:copy_kbs
@echo.
@echo.
@echo --- Copy stripped utility KBs
xcopy %SRCBOX%\kbs\sys-mod.kb %STAGE_DIR%\g2\kbs\demos\ /R
xcopy %SRCBOX%\kbs\sys-mod.kb %STAGE_DIR%\g2\kbs\samples\ /R
xcopy %SRCBOX%\kbs\sys-mod.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\axldemo.kb %STAGE_DIR%\g2\kbs\demos\ /R
xcopy %SRCBOX%\kbs\gxldemo.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\gmsdemo.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\gxl.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\gms.kb %STAGE_DIR%\g2\kbs\demos\ /R
xcopy %SRCBOX%\kbs\gms.kb %STAGE_DIR%\g2\kbs\samples\ /R
xcopy %SRCBOX%\kbs\gms.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\gfr.kb %STAGE_DIR%\g2\kbs\demos\ /R
xcopy %SRCBOX%\kbs\gfr.kb %STAGE_DIR%\g2\kbs\samples\ /R
xcopy %SRCBOX%\kbs\gfr.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\g2web-demo.kb %STAGE_DIR%\g2\kbs\demos\ /R
xcopy %SRCBOX%\kbs\g2web-demo.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\g2web.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\guidemo.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\gdddemo.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\guide.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\guicolor.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\guidata.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\guigfr.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\guidelib.kb %STAGE_DIR%\g2\kbs\demos\ /R
xcopy %SRCBOX%\kbs\guidelib.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\guimove.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\guidesa.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\guislide.kb %STAGE_DIR%\g2\kbs\demos\ /R
xcopy %SRCBOX%\kbs\guislide.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\guitools.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\uil.kb %STAGE_DIR%\g2\kbs\samples\ /R
xcopy %SRCBOX%\kbs\uil.kb %STAGE_DIR%\g2\kbs\demos\ /R
xcopy %SRCBOX%\kbs\uil.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\uilcombo.kb %STAGE_DIR%\g2\kbs\samples\ /R
xcopy %SRCBOX%\kbs\uilcombo.kb %STAGE_DIR%\g2\kbs\demos\ /R
xcopy %SRCBOX%\kbs\uilcombo.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\uildefs.kb %STAGE_DIR%\g2\kbs\samples\ /R
xcopy %SRCBOX%\kbs\uildefs.kb %STAGE_DIR%\g2\kbs\demos\ /R
xcopy %SRCBOX%\kbs\uildefs.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\uillib.kb %STAGE_DIR%\g2\kbs\samples\ /R
xcopy %SRCBOX%\kbs\uillib.kb %STAGE_DIR%\g2\kbs\demos\ /R
xcopy %SRCBOX%\kbs\uillib.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\uilroot.kb %STAGE_DIR%\g2\kbs\samples\ /R
xcopy %SRCBOX%\kbs\uilroot.kb %STAGE_DIR%\g2\kbs\demos\ /R
xcopy %SRCBOX%\kbs\uilroot.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\uilsa.kb %STAGE_DIR%\g2\kbs\samples\ /R
xcopy %SRCBOX%\kbs\uilsa.kb %STAGE_DIR%\g2\kbs\demos\ /R
xcopy %SRCBOX%\kbs\uilsa.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\uilslide.kb %STAGE_DIR%\g2\kbs\samples\ /R
xcopy %SRCBOX%\kbs\uilslide.kb %STAGE_DIR%\g2\kbs\demos\ /R
xcopy %SRCBOX%\kbs\uilslide.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\uiltdlg.kb %STAGE_DIR%\g2\kbs\samples\ /R
xcopy %SRCBOX%\kbs\uiltdlg.kb %STAGE_DIR%\g2\kbs\demos\ /R
xcopy %SRCBOX%\kbs\uiltdlg.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\g2cuidev.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\g2uifile.kb %STAGE_DIR%\g2\kbs\demos\ /R
xcopy %SRCBOX%\kbs\g2uifile.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\g2uimenu.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\g2uiprnt.kb %STAGE_DIR%\g2\kbs\demos\ /R
xcopy %SRCBOX%\kbs\g2uiprnt.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\g2uitree.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\gddlib.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\gdddev.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\gddroot.kb %STAGE_DIR%\g2\kbs\demos\ /R
xcopy %SRCBOX%\kbs\gddroot.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\goldui.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\gold.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\starter.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\protools.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\protools.kb %STAGE_DIR%\protools\kbs\ /R
xcopy %SRCBOX%\kbs\ptroot.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\ptroot.kb %STAGE_DIR%\protools\kbs\ /R
xcopy %SRCBOX%\kbs\g2com.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\g2evliss.kb %STAGE_DIR%\g2\kbs\utils\ /R
xcopy %SRCBOX%\kbs\charts.kb %STAGE_DIR%\g2\kbs\samples\ /R
xcopy %SRCBOX%\kbs\space.kb %STAGE_DIR%\g2\kbs\demos\ /R

:copy_layered_products
@echo.
@echo.
@echo --- Copy layered product
@echo.

@echo.
@echo --- Copying g2i
xcopy %DSTBOX%\g2i\staging\gerr.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\grtl.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\grtl-utils.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\grtl-icons.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\guif.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\grlb.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\cdggrlb.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\cdg.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gevm.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gdsm.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gdsm-agent.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gdsm-db.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gdsm-jmail.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gdsm-jms.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gdsm-opc.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gdsm-pi.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gdsm-web.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gdsm-snmp.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gedp.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gdpm.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gdoc.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\grpe.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gweb.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gdu.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gduc.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gdue.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\brms.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\bpms.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\geuc.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gweb.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\brms.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\symcure.kb %STAGE_DIR%\g2i\kbs\ /R

xcopy %DSTBOX%\g2i\staging\gndo.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gtrap.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gmib.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gvad.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gtad.kb %STAGE_DIR%\g2i\kbs\ /R

xcopy %DSTBOX%\g2i\staging\gens.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gqs.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gqsui.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gqsviews.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gqsdemo.kb %STAGE_DIR%\g2i\examples\ /R
xcopy %DSTBOX%\g2i\staging\glf.kb %STAGE_DIR%\g2i\kbs\ /R
xcopy %DSTBOX%\g2i\staging\cdg-modguide.kb %STAGE_DIR%\g2i\examples\ /R

xcopy %DSTBOX%\g2i\staging\gedp-demo.kb %STAGE_DIR%\g2i\examples\ /R
xcopy %DSTBOX%\g2i\staging\gdsm-demo.kb %STAGE_DIR%\g2i\examples\ /R
xcopy %DSTBOX%\g2i\staging\gdpm-demo.kb %STAGE_DIR%\g2i\examples\ /R
xcopy %DSTBOX%\g2i\staging\gevm-demo.kb %STAGE_DIR%\g2i\examples\ /R
xcopy %DSTBOX%\g2i\staging\geuc-demo.kb %STAGE_DIR%\g2i\examples\ /R
xcopy %DSTBOX%\g2i\staging\gdu-demo.kb %STAGE_DIR%\g2i\examples\ /R
xcopy %DSTBOX%\g2i\staging\grpe-demo.kb %STAGE_DIR%\g2i\examples\ /R
xcopy %DSTBOX%\g2i\staging\brms-demo.kb %STAGE_DIR%\g2i\examples\ /R
xcopy %DSTBOX%\g2i\staging\bpms-demo.kb %STAGE_DIR%\g2i\examples\ /R
xcopy %DSTBOX%\g2i\staging\g2i-ui-demo.kb %STAGE_DIR%\g2i\examples\ /R
xcopy %SRCBOX%\g2i\kbs\g2i-ui-demo.html %STAGE_DIR%\g2i\examples\ /R

xcopy %DSTBOX%\g2i\staging\gope.kb %STAGE_DIR%\g2i\kbs\ /R

xcopy %DSTBOX%\g2i\staging\jmail.kb %STAGE_DIR%\jmail\kbs\ /R
xcopy %DSTBOX%\g2i\staging\jmail-demo.kb %STAGE_DIR%\jmail\examples\ /R

xcopy %DSTBOX%\g2i\staging\jms.kb %STAGE_DIR%\jms\kbs\ /R
xcopy %DSTBOX%\g2i\staging\jms-demo.kb %STAGE_DIR%\jms\examples\ /R

xcopy %DSTBOX%\g2i\staging\gsockman.kb %STAGE_DIR%\sockman\kbs\ /R
xcopy %DSTBOX%\g2i\staging\gsockdemo.kb %STAGE_DIR%\sockman\examples\ /R

xcopy %DSTBOX%\g2i\staging\gsnmp.kb %STAGE_DIR%\jsnmp\kbs\ /R
xcopy %SRCBOX%\g2i\kbs\gsnmp-demo.kb %STAGE_DIR%\jsnmp\examples\ /R

xcopy %SRCBOX%\g2i\kbs\config.txt %STAGE_DIR%\g2i\kbs\ /R /F
xcopy %SRCBOX%\g2i\kbs\cdg-resources-english.txt %STAGE_DIR%\g2i\kbs\ /R /F
xcopy %SRCBOX%\g2i\kbs\g2i-ui-demo-resource-english.txt %STAGE_DIR%\g2i\examples\ /R /F
xcopy %SRCBOX%\g2i\kbs\gdev-resources.txt %STAGE_DIR%\g2i\kbs\ /R /F
xcopy %SRCBOX%\g2i\kbs\guif-resources.txt %STAGE_DIR%\g2i\kbs\ /R /F
xcopy %SRCBOX%\g2i\kbs\gdpm-resources-english.txt %STAGE_DIR%\g2i\kbs\ /R /F
xcopy %SRCBOX%\g2i\kbs\gedp-resources-english.txt %STAGE_DIR%\g2i\kbs\ /R /F
xcopy %SRCBOX%\g2i\kbs\gevm-resources-english.txt %STAGE_DIR%\g2i\kbs\ /R /F
xcopy %SRCBOX%\g2i\kbs\resources-english.txt %STAGE_DIR%\g2i\kbs\ /R /F

xcopy %SRCBOX%\g2i\data\custom-*.csv %STAGE_DIR%\g2i\data\ /R /F
xcopy %SRCBOX%\g2i\data\*.xla %STAGE_DIR%\g2i\data\ /R /F
xcopy %SRCBOX%\g2i\data\*.cab %STAGE_DIR%\g2i\data\http_root\ /R /F

xcopy %SRCBOX%\g2i\data\images\*.jpg %STAGE_DIR%\g2i\data\http_root\images\ /R /F
xcopy %SRCBOX%\g2i\data\images\*.gif %STAGE_DIR%\g2i\data\http_root\images\ /R /F

xcopy %DSTBOX%\jmail\*.* %STAGE_DIR%\jmail\ /S /F /I /R
xcopy %DSTBOX%\jms\*.* %STAGE_DIR%\jms\ /S /F /I /R
xcopy %DSTBOX%\jsnmp\*.* %STAGE_DIR%\jsnmp\ /S /F /I /R
xcopy %DSTBOX%\sockman\*.* %STAGE_DIR%\sockman\ /S /F /I /R
xcopy %DSTBOX%\g2mibparser\*.* %STAGE_DIR%\g2mibparser\ /S /F /I /R

rem TODO: G2Agent need to be recovered -- Chun Tian (binghe), Jan 5, 2012
xcopy %SRCBOX%\g2i\bin\intelnt\StartG2Agent.bat %STAGE_DIR%\g2i\g2agent\intelnt\bin\ /R /F

@echo --- Copying GDANOL
xcopy %SRCBOX%\g2i\builds\Nol-1r10\staging\*.kb %STAGE_DIR%\nol\kbs\ /R
xcopy %SRCBOX%\kbs\tools\nol\dist\kbs\*.kb %STAGE_DIR%\nol\kbs\ /R
xcopy %SRCBOX%\kbs\tools\gda\dist\kbs\*.kb %STAGE_DIR%\gda\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Nol-1r10\staging\gnne-demo.kb %STAGE_DIR%\nol\projects\examples\gnne-demo\ /R
xcopy %SRCBOX%\gdanol\common\demos\kbs\total-demo\*.* %STAGE_DIR%\nol\projects\examples\total-demo\ /R
xcopy %SRCBOX%\gdanol\common\demos\kbs\bakery-demo\*.* %STAGE_DIR%\nol\projects\examples\bakery-demo\ /R
xcopy %SRCBOX%\gdanol\common\demos\kbs\bleach-demo\*.* %STAGE_DIR%\nol\projects\examples\bleach-demo\ /R
xcopy %DSTBOX%\nol\opt\ntnol.exe %STAGE_DIR%\nol\bin\ /R
xcopy %SRCBOX%\nolstudio\nolstudio.bat %STAGE_DIR%\nolstudio\bin\ /R
if "%1" == "ent" xcopy %DSTBOX%\nol\opt\x64\ntnol.exe %STAGE_DIR%\nol\bin\x64\ /R

@echo --- Copying e-SCOR
xcopy %SRCBOX%\g2i\builds\e-SCOR-1r10\staging\e-scor.kb %STAGE_DIR%\escor\kbs\ /R
xcopy %SRCBOX%\g2i\builds\e-SCOR-1r10\staging\escor-customiz.kb %STAGE_DIR%\escor\kbs\ /R
xcopy %SRCBOX%\g2i\builds\e-SCOR-1r10\staging\escor-demo.kb %STAGE_DIR%\escor\examples\ /R
xcopy %SRCBOX%\g2i\builds\e-SCOR-1r10\staging\escor-tutorial-acme.kb %STAGE_DIR%\escor\examples\ /R
xcopy %SRCBOX%\g2i\builds\e-SCOR-1r10\staging\escor-tutorial-simplest.kb %STAGE_DIR%\escor\examples\ /R
xcopy %SRCBOX%\g2i\builds\e-SCOR-1r10\staging\escor-tutorial-vmi.kb %STAGE_DIR%\escor\examples\ /R

@echo --- Copying Rethink
xcopy %SRCBOX%\g2i\builds\ReThink-1r10\staging\aero.kb %STAGE_DIR%\rethink\examples\ /R
xcopy %SRCBOX%\g2i\builds\ReThink-1r10\staging\bpr.kb %STAGE_DIR%\rethink\kbs\ /R
xcopy %SRCBOX%\g2i\builds\ReThink-1r10\staging\bprui.kb %STAGE_DIR%\rethink\kbs\ /R
xcopy %SRCBOX%\g2i\builds\ReThink-1r10\staging\chapter3.kb %STAGE_DIR%\rethink\examples\ /R
xcopy %SRCBOX%\g2i\builds\ReThink-1r10\staging\customiz.kb %STAGE_DIR%\rethink\kbs\ /R
xcopy %SRCBOX%\g2i\builds\ReThink-1r10\staging\menus.kb %STAGE_DIR%\rethink\kbs\ /R
xcopy %SRCBOX%\g2i\builds\ReThink-1r10\staging\methods-online.kb %STAGE_DIR%\rethink\kbs\ /R
xcopy %SRCBOX%\g2i\builds\ReThink-1r10\staging\methods.kb %STAGE_DIR%\rethink\kbs\ /R
xcopy %SRCBOX%\g2i\builds\ReThink-1r10\staging\orderful.kb %STAGE_DIR%\rethink\examples\ /R
xcopy %SRCBOX%\g2i\builds\ReThink-1r10\staging\rethink-40-doc-examples.kb %STAGE_DIR%\rethink\examples\ /R
xcopy %SRCBOX%\g2i\builds\ReThink-1r10\staging\rethink-40-online-examples.kb %STAGE_DIR%\rethink\examples\ /R
xcopy %SRCBOX%\g2i\builds\ReThink-1r10\staging\rethink-core.kb %STAGE_DIR%\rethink\kbs\ /R
xcopy %SRCBOX%\g2i\builds\ReThink-1r10\staging\rethink-online-core.kb %STAGE_DIR%\rethink\kbs\ /R
xcopy %SRCBOX%\g2i\builds\ReThink-1r10\staging\rethink-online.kb %STAGE_DIR%\rethink\kbs\ /R
xcopy %SRCBOX%\g2i\builds\ReThink-1r10\staging\rethink.kb %STAGE_DIR%\rethink\kbs\ /R

@echo --- Copying Integrity
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\csruisup.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\csuisup.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\devui.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\doc_demo.kb %STAGE_DIR%\integrity\examples\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\dxi_demo.kb %STAGE_DIR%\integrity\examples\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\gdxi.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\gqsvsup.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\ievlnr.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\integrity-core.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\integrity.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\ipra.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\mpe-demo.kb %STAGE_DIR%\integrity\examples\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\mpe-ui.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\mpe.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\ode-d.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\ode-opac.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\ode-r.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\odg-core.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\odg-odt.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\ompe-ui.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\ompe.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\opac.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\opacdemo.kb %STAGE_DIR%\integrity\examples\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\opacore.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\opcs.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\opcsrui.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\opcsui.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\opexpes.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\opexui.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\opfom.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\opx_demo.kb %STAGE_DIR%\integrity\examples\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\ora-two.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\ping.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\pingmgr.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\pp-snmp.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\pps.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\scroll.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\scrollui.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\smh.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\smhui.kb %STAGE_DIR%\integrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\svcmdemo.kb %STAGE_DIR%\integrity\\examples\ /R
xcopy %SRCBOX%\g2i\builds\Integrity-1r10\staging\tc_core.kb %STAGE_DIR%\integrity\kbs\ /R

@echo --- Copying HLA
xcopy %SRCBOX%\g2i\builds\HLA-1r10\staging\ghla.kb %STAGE_DIR%\hla\kbs\ /R
xcopy %SRCBOX%\g2i\builds\HLA-1r10\staging\ghla-demo.kb %STAGE_DIR%\hla\examples\ /R
xcopy %SRCBOX%\g2i\sites\HLA\bin\StartG2HLA.bat %STAGE_DIR%\hla\bin\ /R
xcopy %SRCBOX%\g2i\sites\HLA\resources\*.fed %STAGE_DIR%\hla\resources\ /R
xcopy %DSTBOX%\hla\opt\g2-hla.exe %STAGE_DIR%\hla\bin\ /R

xcopy %DSTBOX%\hla\opt\G2Demo.exe %STAGE_DIR%\hla\examples\G2Demo_Federate\ /R
xcopy %SRCBOX%\g2i\sites\HLA\G2Demo_Federate\*.cpp %STAGE_DIR%\hla\examples\G2Demo_Federate\ /R
xcopy %SRCBOX%\g2i\sites\HLA\G2Demo_Federate\*.hh %STAGE_DIR%\hla\examples\G2Demo_Federate\ /R
xcopy %SRCBOX%\g2i\sites\HLA\G2Demo_Federate\StartG2Demo.bat %STAGE_DIR%\hla\examples\G2Demo_Federate\ /R
xcopy %SRCBOX%\g2i\sites\HLA\G2Demo_Federate\G2Demo.sln %STAGE_DIR%\hla\examples\G2Demo_Federate\ /R
xcopy %SRCBOX%\g2i\sites\HLA\G2Demo_Federate\G2Demo.vcxproj %STAGE_DIR%\hla\examples\G2Demo_Federate\ /R
xcopy %SRCBOX%\g2i\sites\HLA\G2Demo_Federate\G2Demo.vcxproj.filters %STAGE_DIR%\hla\examples\G2Demo_Federate\ /R

xcopy %DSTBOX%\hla\opt\G2HelloWorld.exe %STAGE_DIR%\hla\examples\G2HelloWorld_Federate\ /R
xcopy %SRCBOX%\g2i\sites\HLA\G2HelloWorld_Federate\*.cpp %STAGE_DIR%\hla\examples\G2HelloWorld_Federate\ /R
xcopy %SRCBOX%\g2i\sites\HLA\G2HelloWorld_Federate\*.hh %STAGE_DIR%\hla\examples\G2HelloWorld_Federate\ /R
xcopy %SRCBOX%\g2i\sites\HLA\G2HelloWorld_Federate\StartG2HelloWorld.bat %STAGE_DIR%\hla\examples\G2HelloWorld_Federate\ /R
xcopy %SRCBOX%\g2i\sites\HLA\G2HelloWorld_Federate\G2HelloWorld.sln %STAGE_DIR%\hla\examples\G2HelloWorld_Federate\ /R
xcopy %SRCBOX%\g2i\sites\HLA\G2HelloWorld_Federate\G2HelloWorld.vcxproj %STAGE_DIR%\hla\examples\G2HelloWorld_Federate\ /R
xcopy %SRCBOX%\g2i\sites\HLA\G2HelloWorld_Federate\G2HelloWorld.vcxproj.filters %STAGE_DIR%\hla\examples\G2HelloWorld_Federate\ /R

@echo --- Copying Optegrity
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\equipmnt.kb %STAGE_DIR%\optegrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\f102demo.kb %STAGE_DIR%\optegrity\examples\ /R
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\fo2demo.kb %STAGE_DIR%\optegrity\examples\ /R
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\iato.kb %STAGE_DIR%\optegrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\icco.kb %STAGE_DIR%\optegrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\ico.kb %STAGE_DIR%\optegrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\icso.kb %STAGE_DIR%\optegrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\idco.kb %STAGE_DIR%\optegrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\iedo.kb %STAGE_DIR%\optegrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\iffo.kb %STAGE_DIR%\optegrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\iho.kb %STAGE_DIR%\optegrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\ioc.kb %STAGE_DIR%\optegrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\ipo.kb %STAGE_DIR%\optegrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\irco.kb %STAGE_DIR%\optegrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\iso.kb %STAGE_DIR%\optegrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\ito.kb %STAGE_DIR%\optegrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\ivo.kb %STAGE_DIR%\optegrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\ixo.kb %STAGE_DIR%\optegrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\opt-event.kb %STAGE_DIR%\optegrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\optegrity-core.kb %STAGE_DIR%\optegrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\optegrity.kb %STAGE_DIR%\optegrity\kbs\ /R
xcopy %SRCBOX%\g2i\builds\Optegrity-1r10\staging\sdb.kb %STAGE_DIR%\optegrity\kbs\ /R

:copy_javalink
@echo.
@echo --- Copy javalink
xcopy %DSTBOX%\javalink\lib\JgiInterface.dll %STAGE_DIR%\javalink\bin\ /R
xcopy %SRCBOX%\java\products\javalink\intelnt\bin\DownloadInterfaces.bat %STAGE_DIR%\javalink\bin\ /R
xcopy %SRCBOX%\java\products\javalink\intelnt\bin\envvars.bat %STAGE_DIR%\javalink\bin\ /R
xcopy %SRCBOX%\java\products\javalink\intelnt\bin\G2BeanBuilder.bat %STAGE_DIR%\javalink\bin\ /R
xcopy %SRCBOX%\java\products\javalink\intelnt\bin\InstallProperties.bat %STAGE_DIR%\javalink\bin\ /R
xcopy %DSTBOX%\javalink\classes\beanbuilder.jar %STAGE_DIR%\javalink\classes\ /R
xcopy %DSTBOX%\javalink\classes\classtools.jar %STAGE_DIR%\javalink\classes\ /R
xcopy %DSTBOX%\javalink\classes\core.jar %STAGE_DIR%\javalink\classes\ /R
xcopy %DSTBOX%\javalink\classes\javalink.jar %STAGE_DIR%\javalink\classes\ /R
xcopy %SRCBOX%\java\products\javalink\intelnt\bin\.com.gensym.properties %STAGE_DIR%\javalink\classes\ /R
xcopy %SRCBOX%\java\products\javalink\common\ExamplesReadme.html %STAGE_DIR%\javalink\ /R
xcopy %SRCBOX%\java\products\javalink\common\readme-javalink.html %STAGE_DIR%\javalink\ /R
xcopy %SRCBOX%\java\products\javalink\common\kbs\javalink.kb %STAGE_DIR%\javalink\kbs\ /R
xcopy %SRCBOX%\java\products\javalink\common\kbs\jgidemo.kb %STAGE_DIR%\javalink\kbs\ /R
xcopy %SRCBOX%\java\com\gensym\classes\modules\jgidemo\*.java %STAGE_DIR%\javalink\classes\com\gensym\classes\modules\jgidemo\ /R
xcopy %SRCBOX%\java\com\gensym\classes\modules\jgidemo\*.class %STAGE_DIR%\javalink\classes\com\gensym\classes\modules\jgidemo\ /R
xcopy %SRCBOX%\java\com\gensym\classes\modules\jgidemo\*.ser %STAGE_DIR%\javalink\classes\com\gensym\classes\modules\jgidemo\ /R
xcopy %SRCBOX%\java\com\gensym\classes\modules\jgidemo\generate-classes.bat %STAGE_DIR%\javalink\classes\com\gensym\classes\modules\jgidemo\ /R
xcopy %SRCBOX%\java\com\gensym\classes\modules\javalink\*.java %STAGE_DIR%\javalink\classes\com\gensym\classes\modules\javalink\ /R
xcopy %SRCBOX%\java\com\gensym\classes\modules\javalink\*.class %STAGE_DIR%\javalink\classes\com\gensym\classes\modules\javalink\ /R
xcopy %SRCBOX%\java\com\gensym\demos\jgi\*.java %STAGE_DIR%\javalink\classes\com\gensym\demos\jgi\ /R
xcopy %SRCBOX%\java\com\gensym\demos\jgi\*.class %STAGE_DIR%\javalink\classes\com\gensym\demos\jgi\ /R
xcopy %SRCBOX%\java\com\gensym\demos\jgi\DownloadJgiDemoClasses.bat %STAGE_DIR%\javalink\classes\com\gensym\demos\jgi\ /R

:copy_javalink
@echo.
@echo --- Copy javalink x64
if "%1" == "ent" xcopy %DSTBOX%\javalink\lib\x64\JgiInterface.dll %STAGE_DIR%\javalink\bin\x64\ /R
xcopy %SRCBOX%\java\products\javalink\intelnt\bin\DownloadInterfaces.bat %STAGE_DIR%\javalink\bin\x64\ /R
xcopy %SRCBOX%\java\products\javalink\intelnt\bin\x64\envvars.bat %STAGE_DIR%\javalink\bin\x64\ /R
xcopy %SRCBOX%\java\products\javalink\intelnt\bin\G2BeanBuilder.bat %STAGE_DIR%\javalink\bin\x64\ /R
xcopy %SRCBOX%\java\products\javalink\intelnt\bin\InstallProperties.bat %STAGE_DIR%\javalink\bin\x64\ /R
if "%1" == "std" del /q %STAGE_DIR%\javalink\bin\x64\*.dll

:copy_nolstudio
@echo.
@echo --- Copy NOLstudio Jars
xcopy %SRCBOX%\nolstudio\nolonline.bat %STAGE_DIR%\nolstudio\bin\ /R
xcopy %SRCBOX%\nolstudio\out\Jar\NolStudioData.jar %STAGE_DIR%\nolstudio\ /R
xcopy %SRCBOX%\nolstudio\out\Jar\NolStudioDeploy.jar %STAGE_DIR%\nolstudio\ /R
xcopy %SRCBOX%\nolstudio\out\Jar\NolStudioGUI.jar %STAGE_DIR%\nolstudio\ /R
xcopy %SRCBOX%\nolstudio\out\Jar\NolStudioMath.jar %STAGE_DIR%\nolstudio\ /R

:copy_g2db
@echo.
@echo.
@echo --- Copy g2db kbs
xcopy %SRCBOX%\kbs\g2-database.kb %STAGE_DIR%\sybase\kbs\ /R
xcopy %SRCBOX%\kbs\g2-database.kb %STAGE_DIR%\oracle\kbs\ /R
xcopy %SRCBOX%\kbs\g2-database.kb %STAGE_DIR%\odbc_unicode\kbs\ /R
xcopy %SRCBOX%\kbs\g2-database.kb %STAGE_DIR%\odbc\kbs\ /R
xcopy %SRCBOX%\kbs\g2-database.kb %STAGE_DIR%\jdbc\kbs\ /R
xcopy %DSTBOX%\jdbc\G2JDBCAuthorize.dll %STAGE_DIR%\jdbc\bin\ /R
xcopy %DSTBOX%\jdbc\g2jdbc.jar %STAGE_DIR%\jdbc\classes\ /R
xcopy %SRCBOX%\g2db\java\G2JDBC\libs\log4j-1.2.15.jar %STAGE_DIR%\jdbc\classes\ /R
xcopy %SRCBOX%\g2db\java\G2JDBC\libs\postgresql-8.3-604.jdbc3.jar %STAGE_DIR%\jdbc\classes\ /R
xcopy %SRCBOX%\java\products\jdbc\intelnt\bin\envvars.bat %STAGE_DIR%\jdbc\bin\ /R
xcopy %SRCBOX%\java\products\jdbc\intelnt\bin\g2jdbc.bat %STAGE_DIR%\jdbc\bin\ /R

xcopy %DSTBOX%\oracle\g2-ora10.exe %STAGE_DIR%\oracle\bin\ /R
if "%1" == "ent" xcopy %DSTBOX%\oracle\x64\g2-ora10.exe %STAGE_DIR%\oracle\bin\x64\ /R
xcopy %SRCBOX%\g2db\promote\run-g2-ora10.bat %STAGE_DIR%\oracle\bin\ /R
if "%1" == "ent" copy %SRCBOX%\g2db\promote\run-g2-ora10-x64.bat %STAGE_DIR%\oracle\bin\x64\run-g2-ora10.bat /Y
xcopy %DSTBOX%\oracle\g2-ora11.exe %STAGE_DIR%\oracle\bin\ /R
if "%1" == "ent" xcopy %DSTBOX%\oracle\x64\g2-ora11.exe %STAGE_DIR%\oracle\bin\x64\ /R
xcopy %SRCBOX%\g2db\promote\run-g2-ora11.bat %STAGE_DIR%\oracle\bin\ /R
if "%1" == "ent" copy %SRCBOX%\g2db\promote\run-g2-ora11-x64.bat %STAGE_DIR%\oracle\bin\x64\run-g2-ora11.bat /Y

xcopy %DSTBOX%\oracle\g2-ora12.exe %STAGE_DIR%\oracle\bin\ /R
if "%1" == "ent" xcopy %DSTBOX%\oracle\x64\g2-ora12.exe %STAGE_DIR%\oracle\bin\x64\ /R
xcopy %SRCBOX%\g2db\promote\run-g2-ora12.bat %STAGE_DIR%\oracle\bin\ /R
if "%1" == "ent" copy %SRCBOX%\g2db\promote\run-g2-ora12-x64.bat %STAGE_DIR%\oracle\bin\x64\run-g2-ora12.bat /Y

if "%1" == "std" rd /s /q %STAGE_DIR%\oracle\bin\x64

xcopy %DSTBOX%\odbc\g2-odbc.exe %STAGE_DIR%\odbc\bin\ /R
if "%1" == "ent" xcopy %DSTBOX%\odbc\x64\g2-odbc.exe %STAGE_DIR%\odbc\bin\x64\ /R
if "%1" == "std" rd /s /q %STAGE_DIR%\odbc\bin\x64
if "%1" == "ent" copy %SRCBOX%\g2db\promote\run-g2-odbc-x64.bat %STAGE_DIR%\odbc\bin\x64\run-g2-odbc.bat /Y

xcopy %DSTBOX%\odbc_unicode\g2-odbc.exe %STAGE_DIR%\odbc_unicode\bin\ /R
if "%1" == "ent" xcopy %DSTBOX%\odbc_unicode\x64\g2-odbc.exe %STAGE_DIR%\odbc_unicode\bin\x64\ /R
if "%1" == "std" rd /s /q %STAGE_DIR%\odbc_unicode\bin\x64
if "%1" == "ent" copy %SRCBOX%\g2db\promote\run-g2-odbc-unicode-x64.bat %STAGE_DIR%\odbc_unicode\bin\x64\run-g2-odbc-unicode.bat /Y

xcopy %DSTBOX%\sybase\g2-syb150.exe %STAGE_DIR%\sybase\bin\ /R
xcopy %SRCBOX%\g2db\promote\run-g2-syb150.bat %STAGE_DIR%\sybase\bin\ /R
if "%1" == "ent" xcopy %DSTBOX%\sybase\x64\g2-syb150.exe %STAGE_DIR%\sybase\bin\x64\ /R
if "%1" == "std" rd /s /q %STAGE_DIR%\sybase\bin\x64
if "%1" == "ent" copy %SRCBOX%\g2db\promote\run-g2-syb150-x64.bat %STAGE_DIR%\sybase\bin\x64\run-g2-syb150.bat /Y

:copy_docs
@echo.
@echo --- Copying documents
set SRCDOC=%SRCBOX%\documentation
set DSTDOC=%STAGE_DIR%\doc

xcopy %SRCDOC%\g2activexlink.pdf %DSTDOC%\bridges\activexlink\ /R
xcopy %SRCDOC%\g2corbalink.pdf %DSTDOC%\bridges\corbalink\ /R
xcopy %SRCDOC%\g2databasebridge.pdf %DSTDOC%\bridges\db\ /R
xcopy %SRCDOC%\g2hla.pdf %DSTDOC%\bridges\hla\ /R
xcopy %SRCDOC%\g2jmailbridge.pdf %DSTDOC%\bridges\jmail\ /R
xcopy %SRCDOC%\g2jmslink.pdf %DSTDOC%\bridges\jms\ /R
xcopy %SRCDOC%\g2odbcbridge.pdf %DSTDOC%\bridges\odbc\ /R
xcopy %SRCDOC%\g2opcclient.pdf %DSTDOC%\bridges\opcclient\ /R
xcopy %SRCDOC%\g2oraclebridge.pdf %DSTDOC%\bridges\oracle\ /R
xcopy %SRCDOC%\g2pibridge.pdf %DSTDOC%\bridges\pi\ /R
xcopy %SRCDOC%\g2snmp.pdf %DSTDOC%\bridges\snmp\ /R
xcopy %SRCDOC%\g2javasocketmanager.pdf %DSTDOC%\bridges\sockman\ /R
xcopy %SRCDOC%\g2sybasebridge.pdf %DSTDOC%\bridges\sybase\ /R
xcopy %SRCDOC%\g2weblink.pdf %DSTDOC%\bridges\weblink\ /R
xcopy %SRCDOC%\e-SCORQuickReference.pdf %DSTDOC%\escor\ /R
xcopy %SRCDOC%\e-SCORTutorials.pdf %DSTDOC%\escor\ /R
xcopy %SRCDOC%\e-SCORUsersGuide.pdf %DSTDOC%\escor\ /R
xcopy %SRCDOC%\g2classref.pdf %DSTDOC%\g2\g2classref\ /R
xcopy %SRCDOC%\g2devguide.pdf %DSTDOC%\g2\g2devguide\ /R
xcopy %SRCDOC%\g2gateway.pdf %DSTDOC%\g2\g2gateway\ /R
xcopy %SRCDOC%\g2langrefcard.pdf %DSTDOC%\g2\g2langrefcard\ /R
xcopy %SRCDOC%\g2refman.pdf %DSTDOC%\g2\g2refman\ /R
xcopy %SRCDOC%\g2sysprocs.pdf %DSTDOC%\g2\g2sysprocs\ /R
xcopy %SRCDOC%\g2sysprocsrefcard.pdf %DSTDOC%\g2\g2sysprocsrefcard\ /R
xcopy %SRCDOC%\g2tutorials.pdf %DSTDOC%\g2\g2tutorials\ /R
xcopy %SRCDOC%\telewindows.pdf %DSTDOC%\g2\telewindows\ /R
xcopy %SRCDOC%\bpms.pdf %DSTDOC%\g2i\bpms\ /R
xcopy %SRCDOC%\brms.pdf %DSTDOC%\g2i\brms\ /R
xcopy %SRCDOC%\gdpm.pdf %DSTDOC%\g2i\gdpm\ /R
xcopy %SRCDOC%\gdsm.pdf %DSTDOC%\g2i\gdsm\ /R
xcopy %SRCDOC%\gdu.pdf %DSTDOC%\g2i\gdu\ /R
xcopy %SRCDOC%\gedp.pdf %DSTDOC%\g2i\gedp\ /R
xcopy %SRCDOC%\gerr.pdf %DSTDOC%\g2i\gerr\ /R
xcopy %SRCDOC%\geuc.pdf %DSTDOC%\g2i\geuc\ /R
xcopy %SRCDOC%\gevm.pdf %DSTDOC%\g2i\gevm\ /R
xcopy %SRCDOC%\grlb.pdf %DSTDOC%\g2i\grlb\ /R
xcopy %SRCDOC%\grpe.pdf %DSTDOC%\g2i\grpe\ /R
xcopy %SRCDOC%\grtl.pdf %DSTDOC%\g2i\grtl\ /R
xcopy %SRCDOC%\gweb.pdf %DSTDOC%\g2i\gweb\ /R
xcopy %SRCDOC%\g2relnotes.pdf %DSTDOC%\ /R
xcopy %SRCDOC%\gdaapi.pdf %DSTDOC%\gda\gdaapi\ /R
xcopy %SRCDOC%\gdarefman.pdf %DSTDOC%\gda\gdaugrm\ /R
xcopy %SRCDOC%\gdaug.pdf %DSTDOC%\gda\gdaugrm\ /R
xcopy %SRCDOC%\IntegrityUsersGuide.pdf %DSTDOC%\integrity\ /R
xcopy %SRCDOC%\IntegrityUtilitiesGuide.pdf %DSTDOC%\integrity\ /R
xcopy %SRCDOC%\g2beanbuilder.pdf %DSTDOC%\javalink\docs\guides\g2beanbuilder\ /R
xcopy %SRCDOC%\g2downloadinterfaces.pdf %DSTDOC%\javalink\docs\guides\g2downloadinterfaces\ /R
xcopy %SRCDOC%\g2javalink.pdf %DSTDOC%\javalink\docs\guides\g2javalink\ /R
xcopy %SRCDOC%\GNNEUsersGuide.pdf %DSTDOC%\nol\ /R
xcopy %SRCDOC%\nolrm.pdf %DSTDOC%\nol\ /R
xcopy %SRCDOC%\nolstudioug.pdf %DSTDOC%\nol\ /R
xcopy %SRCDOC%\nolusersguide.pdf %DSTDOC%\nol\ /R
xcopy %SRCDOC%\OptegrityHeaterTutorial.pdf %DSTDOC%\optegrity\ /R
xcopy %SRCDOC%\OptegrityUsersGuide.pdf %DSTDOC%\optegrity\ /R
xcopy %SRCDOC%\CustomizingReThinkUsersGuide.pdf %DSTDOC%\rethink\ /R
xcopy %SRCDOC%\ReThinkTutorials.pdf %DSTDOC%\rethink\ /R
xcopy %SRCDOC%\ReThinkUsersGuide.pdf %DSTDOC%\rethink\ /R
xcopy %SRCDOC%\SymCureUsersGuide.pdf %DSTDOC%\symcure\ /R
xcopy %SRCDOC%\g2protools.pdf %DSTDOC%\utilities\g2protools\ /R
xcopy %SRCDOC%\gdd.pdf %DSTDOC%\utilities\gdd\ /R
xcopy %SRCDOC%\gdi.pdf %DSTDOC%\utilities\gdi\ /R
xcopy %SRCDOC%\gfr.pdf %DSTDOC%\utilities\gfr\ /R
xcopy %SRCDOC%\gms.pdf %DSTDOC%\utilities\gms\ /R
xcopy %SRCDOC%\golddev.pdf %DSTDOC%\utilities\golddev\ /R
xcopy %SRCDOC%\goldui.pdf %DSTDOC%\utilities\goldui\ /R
xcopy %SRCDOC%\guideprocref.pdf %DSTDOC%\utilities\guideprocref\ /R
xcopy %SRCDOC%\guideuserguide.pdf %DSTDOC%\utilities\guideuserguide\ /R
xcopy %SRCDOC%\gxl.pdf %DSTDOC%\utilities\gxl\ /R

:copy_pdbs
set SRCPDB=%SRCBOX%\vstudio
set DSTPDB=%STAGE_DIR%\symbols\
set DSTPDB64=%STAGE_DIR%\symbols\x64\

if "%1" == "std" rd /s /q %DSTPDB64%
if "%1" == "std" xcopy %SRCPDB%\g2\Win32\Release\g2.pdb %DSTPDB% /R
if "%1" == "ent" xcopy "%DSTBOX%\g2\opt\g2.pdb" %DSTPDB% /R
REM
REM SymScale is not part of the installer (yet)
REM if "%1" == "ent" xcopy "%DSTBOX%\g2\opt\SymScale.pdb" %DSTPDB% /R
xcopy %SRCPDB%\tw\Win32\Release\tw.pdb %DSTPDB% /R
if "%1" == "std" xcopy "%SRCPDB%\twng\Win32\Release MFC\twng.pdb" %DSTPDB% /R
if "%1" == "ent" xcopy "%SRCPDB%\twng\Win32\Release MFC - Enterprise\twng.pdb" %DSTPDB% /R
xcopy %SRCPDB%\ax-link\Win32\Release\G2Com.pdb %DSTPDB% /R
if "%1" == "ent" xcopy %SRCPDB%\ax-link\x64\Release\G2Com.pdb %DSTPDB64% /R
xcopy %SRCPDB%\gsi\Win32\Release\gsi.pdb %DSTPDB% /R
if "%1" == "ent" xcopy %SRCPDB%\gsi\x64\Release\gsi.pdb %DSTPDB64% /R
xcopy %SRCPDB%\g2db\g2-oracle10\Win32\Release\g2-ora10.pdb %DSTPDB% /R
xcopy %SRCPDB%\g2db\g2-oracle11\Win32\Release\g2-ora11.pdb %DSTPDB% /R
xcopy %SRCPDB%\g2db\g2-oracle12\Win32\Release\g2-ora12.pdb %DSTPDB% /R
if "%1" == "ent" xcopy %SRCPDB%\g2db\g2-oracle10\x64\Release\g2-ora10.pdb %DSTPDB64% /R
if "%1" == "ent" xcopy %SRCPDB%\g2db\g2-oracle11\x64\Release\g2-ora11.pdb %DSTPDB64% /R
if "%1" == "ent" xcopy %SRCPDB%\g2db\g2-oracle12\x64\Release\g2-ora12.pdb %DSTPDB64% /R

xcopy %SRCPDB%\g2db\g2-odbc\Win32\Release\odbc.pdb %DSTPDB% /R
if "%1" == "ent" xcopy %SRCPDB%\g2db\g2-odbc\x64\Release\odbc.pdb %DSTPDB64% /R
xcopy "%SRCPDB%\g2db\g2-odbc\Win32\Release - Unicode\g2-odbc.pdb" %DSTPDB% /R
if "%1" == "ent" xcopy "%SRCPDB%\g2db\g2-odbc\x64\Release - Unicode\g2-odbc.pdb" %DSTPDB64% /R

xcopy %SRCPDB%\g2opc\Win32\Release\g2opc.pdb %DSTPDB% /R
if "%1" == "ent" xcopy "%SRCPDB%\g2opc\x64\Release - Enterprise\g2opc.pdb" %DSTPDB64% /R
xcopy %SRCPDB%\pi\Win32\Release\g2pi.pdb %DSTPDB% /R
xcopy %DSTBOX%\hla\opt\g2-hla.pdb %DSTPDB% /R

xcopy %DSTBOX%\nol\opt\ntnol.pdb %DSTPDB% /R
if "%1" == "ent" xcopy %DSTBOX%\nol\opt\x64\ntnol.pdb %DSTPDB64% /R

:exit
@echo.
echo "Done with bundle creating - %time%"
