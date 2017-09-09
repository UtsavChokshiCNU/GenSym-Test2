@echo off

if  "%1%" == "" (
   echo "Usage: G2TestScript.bat <logfile name>"
   goto end
)

REM Script developed by Kuliza for Gensym-3051-TAM4-IM-UC-Create a script that automatically loads a list of kbs and reports any error
REM Usage: 
REM 1. Open CMD
REM 2. Go to script directory
REM 3. Give the command, G2TestScript.bat <logfile name>
REM Example: G2TestScript.bat C:\G2\src\g2i\kbs C:\result.txt

set SITE_=C:\Program Files (x86)\Gensym\g2-8.4r2

rem
rem	Set default settings
rem

cd "%SITE_%"

set G2_PATH=g2

set ORIG_PATH=%PATH%
set PATH=bin;javalink\bin;tw2\bin;gsi;activexlink\bin;odbc\bin;oracle\bin;sybase\bin;pi\bin;opcclient;g2i\bin;corbalink;g2;jre\bin;%PATH%

set G2_MODULE_SEARCH_PATH=""
if exist "g2i\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'g2i\kbs'
if exist "jmail\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'jmail\kbs'
if exist "jms\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'jms\kbs'
if exist "g2\kbs\utils" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'g2\kbs\utils'
if exist "gda\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'gda\kbs'
if exist "gda-4.5r1\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'gda-4.5r1\kbs'
if exist "activexlink\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'activexlink\kbs'
if exist "odbc\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'odbc\kbs'
if exist "oracle\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'oracle\kbs'
if exist "pi\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'pi\kbs'
if exist "sybase\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'sybase\kbs'
if exist "opcclient\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'opcclient\kbs'
if exist "protools\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'protools\kbs'
if exist "corbalink\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'corbalink\kbs'
if exist "javalink\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'javalink\kbs'
if exist "sockman\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'sockman\kbs'
if exist "jsnmp\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'jsnmp\kbs'
if exist "tw2\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'tw2\kbs'
if exist "optegrity\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'optegrity\kbs'
if exist "nol\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'nol\kbs'
if exist "rethink\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'rethink\kbs'
if exist "escor\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'escor\kbs'
if exist "integrity\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'integrity\kbs'
if exist "gw\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'gw\kbs'
if exist "hla\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% 'hla\kbs'


if "%G2_OK%" == "" set G2_OK=G2\g2.ok

if "%G2RGN1LMT" == "" set G2RGN1LMT=40000000
if "%G2RGN2LMT" == "" set G2RGN2LMT=3500000

echo "Starting KB smoke tests" > %1

call :runG2 %1 "g2i\kbs\gqs.kb"
call :runG2 %1 "g2i\kbs\glf.kb"
call :runG2 %1 "g2i\kbs\gerr.kb"
call :runG2 %1 "g2i\kbs\grtl.kb"
call :runG2 %1 "g2i\kbs\gevm.kb"
call :runG2 %1 "g2i\kbs\gdsm.kb"
call :runG2 %1 "g2i\kbs\gdpm.kb"
call :runG2 %1 "g2i\kbs\geuc.kb"
call :runG2 %1 "g2i\kbs\gdu.kb"
call :runG2 %1 "g2i\kbs\grlb.kb"
call :runG2 %1 "g2i\kbs\gedp.kb"
call :runG2 %1 "g2i\kbs\grpe.kb"
call :runG2 %1 "g2i\kbs\gweb.kb"
call :runG2 %1 "g2i\kbs\brms.kb"
call :runG2 %1 "g2\kbs\utils\gms.kb"
call :runG2 %1 "g2\kbs\utils\gold.kb"
call :runG2 %1 "g2\kbs\utils\gold-ui.kb"
call :runG2 %1 "g2\kbs\utils\gxl.kb"
call :runG2 %1 "g2\kbs\utils\guide.kb"
call :runG2 %1 "g2\kbs\utils\gfr.kb"
call :runG2 %1 "g2\kbs\utils\gdi.kb"
call :runG2 %1 "protools\kbs\protools.kb"
call :runG2 %1 "g2\kbs\utils\uil.kb"
call :runG2 %1 "g2\kbs\utils\sys-mod.kb"

echo Batch file executed sucessfully >> %1
set PATH=%ORIG_PATH%

goto end

:runG2

   echo Testing %2...  

   if exist %2 (

      echo Starting %2 >> %1

      start %2 /b "%G2_PATH%\g2"  -name %2 -resourcefile 'g2i\kbs\resources-*.txt' -configfile 'g2i\kbs\config.txt' -start -kb %2 -exit-on-abort -log log99.txt

      ping -n 15 127.0.0.1 >> temp.txt
      del temp.txt

      taskkill /f /im g2.exe >> %1
      echo %2 loaded successfully >> %1
      goto loop1
   
   )

   echo FAILURE: No kb files found for %2 >> %1
   
   :loop1

GOTO:EOF

:end
