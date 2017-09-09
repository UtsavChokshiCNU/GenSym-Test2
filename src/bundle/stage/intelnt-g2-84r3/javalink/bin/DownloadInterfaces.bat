@echo off
if "%OS%" == "Windows_NT" setlocal

if not "%JAVALINK_HOME%" == "" goto doit

if not exist envvars.bat goto problem

call envvars.bat
rem we had some problem; presumably envvars.bat told us what was wrong
if "%JAVALINK_HOME%" == "" goto end
:doit

echo "Starting G2DownloadInterfaces."
echo "Note: using G2 Javalink code installation found in %JAVALINK_HOME%"
echo "Please wait..."

java com.gensym.beanbuilder.G2DownloadInterfaces %*

goto end

:problem
echo The JAVALINK_HOME environment variable is not set, and the program cannot
echo determine its home directory from the working directory.
pause
:end
