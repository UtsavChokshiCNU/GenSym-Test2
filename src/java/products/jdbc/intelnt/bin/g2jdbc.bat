@echo off
if "%OS%" == "Windows_NT" setlocal

if not exist envvars.bat goto problem

call envvars.bat
rem we had some problem; presumably envvars.bat told us what was wrong
if "%JAVALINK_HOME%" == "" goto end
if "%G2JDBC_HOME%" == "" goto end
:doit

echo "Starting G2 JDBC bridge."
echo "Note: using G2 Javalink code installation found in %JAVALINK_HOME%"
echo "Please wait..."

java core.G2JDBCBridge -driver org.postgresql.Driver -port 22041 %*

goto end

:problem
echo The JAVALINK_HOME or G2JDBC_HOME environment variable(s) is not set, and the program cannot
echo determine its home directory from the working directory.
pause
:end
