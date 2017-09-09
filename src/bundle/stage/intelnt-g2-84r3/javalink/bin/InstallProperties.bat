@echo off
rem Install the properties file for JavaLink 
rem In the correct Home directory for this
rem installation
rem If argument "nopause" is given, don't pause.  This is useful for scripts.


if not "%JAVALINK_HOME%" == "" goto doit

if not exist envvars.bat goto problem

call envvars.bat
rem we had some problem; presumably envvars.bat told us what was wrong
if "%JAVALINK_HOME%" == "" goto end
:doit
java com.gensym.util.CreateProductProperties "%JAVALINK_HOME%\bin\.com.gensym.properties" "%JAVALINK_HOME%"
if "%1" == "nopause" goto done
pause
goto done

:problem
echo The JAVALINK_HOME environment variable is not set, and the program cannot
echo determine its home directory from the working directory.
pause
:done
