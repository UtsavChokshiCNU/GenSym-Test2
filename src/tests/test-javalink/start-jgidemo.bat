@echo off

if "%1" == "STD" goto :start_test
if "%1" == "ENT" goto :start_test
if "%1" == "STOP" goto :stop_test
if "%1" == "ECHO-MEMORY" goto :echo_memory

echo "Usage: start-jgidemo.bat <STD | ENT>"
exit /b

:stop_test
for /F %%p in (pid_file) do ( taskkill /F /PID %%p )
del pid_file
del mem_file
echo > stopped
exit /b

:echo_memory
for /F %%p in (pid_file) do ( wmic process where processid=%%p get WorkingSetSize | find /V "WorkingSetSize" > mem_file )
exit /b

:start_test

rem Java environment settings for STD and ENT, 32bit JVM for STD and 64bit JVM for ENT
rem Meanwhile, there is a local debug setting and remote deployment setting

rem STD environment: local debug setting
rem set STD_JAVA_HOME="C:\Program Files (x86)\Java\jre1.8.0_77"
rem STD environment: remote deployment setting
set STD_JAVA_HOME="C:\Program Files (x86)\Java\jdk1.8.0_92"

rem ENT environment: local debug setting
rem set ENT_JAVA_HOME="C:\Program Files\Java\jdk1.8.0_60"
rem ENT environment: remote deployment setting
set ENT_JAVA_HOME="C:\Program Files\Java\jdk1.8.0_92"

set TEST_FOLDER=%~dp0
set SRCBOX=%TEST_FOLDER%\..\..
set DSTBOX=%SRCBOX%\..\dst

rem set javalink running environment: create directory
mkdir %DSTBOX%\javalink\classes\com\gensym\classes\modules\jgidemo
mkdir %DSTBOX%\javalink\classes\com\gensym\classes\modules\javalink

rem set javalink running environment: copy necessary files
xcopy %SRCBOX%\java\com\gensym\classes\modules\jgidemo\*.java %DSTBOX%\javalink\classes\com\gensym\classes\modules\jgidemo\ /R /Y /Q
xcopy %SRCBOX%\java\com\gensym\classes\modules\jgidemo\*.class %DSTBOX%\javalink\classes\com\gensym\classes\modules\jgidemo\ /R /Y /Q
xcopy %SRCBOX%\java\com\gensym\classes\modules\jgidemo\*.ser %DSTBOX%\javalink\classes\com\gensym\classes\modules\jgidemo\ /R /Y /Q
xcopy %SRCBOX%\java\com\gensym\classes\modules\jgidemo\generate-classes.bat %DSTBOX%\javalink\classes\com\gensym\classes\modules\jgidemo\ /R /Y /Q
xcopy %SRCBOX%\java\com\gensym\classes\modules\javalink\*.java %DSTBOX%\javalink\classes\com\gensym\classes\modules\javalink\ /R /Y /Q
xcopy %SRCBOX%\java\com\gensym\classes\modules\javalink\*.class %DSTBOX%\javalink\classes\com\gensym\classes\modules\javalink\ /R /Y /Q
xcopy %SRCBOX%\java\com\gensym\demos\jgi\*.java %DSTBOX%\javalink\classes\com\gensym\demos\jgi\ /R /Y /Q
xcopy %SRCBOX%\java\com\gensym\demos\jgi\*.class %DSTBOX%\javalink\classes\com\gensym\demos\jgi\ /R /Y /Q
xcopy %SRCBOX%\java\com\gensym\demos\jgi\DownloadJgiDemoClasses.bat %DSTBOX%\javalink\classes\com\gensym\demos\jgi\ /R /Y /Q

rem set HOME directory for javalink
set JAVALINK_HOME=%DSTBOX%\javalink

rem set JAVA_HOME for STD and ENT running
if "%1" == "STD" goto std-setting
if "%1" == "ENT" goto ent-setting
:std-setting
set JAVA_EXE=%STD_JAVA_HOME:"=%\bin\java.exe
set JAVA_OPTS=-Djava.library.path=%JAVALINK_HOME%\lib -Xmx60M
goto run-jgidemo

:ent-setting
set JAVA_EXE=%ENT_JAVA_HOME:"=%\bin\java.exe
set JAVA_OPTS=-Djava.library.path=%JAVALINK_HOME%\lib\x64 -Xmx60M
goto run-jgidemo

:run-jgidemo

rem set executable PATH and CLASSPATH
set CLASSPATH=%JAVALINK_HOME%\classes;%JAVALINK_HOME%\classes\core.jar;%JAVALINK_HOME%\classes\classtools.jar;%JAVALINK_HOME%\classes\javalink.jar;%JAVALINK_HOME%\classes\beanbuilder.jar;

rem start jgidemo
"%JAVA_EXE%" -version
set startcmd=%JAVA_EXE% %JAVA_OPTS% -cp %CLASSPATH% com.gensym.demos.jgi.ExampleG2Gateway
for /f "tokens=2 delims==; " %%a in (' wmic process call create "%startcmd%" ^| find "ProcessId" ') do set PID=%%a
echo "%PID%" > pid_file
