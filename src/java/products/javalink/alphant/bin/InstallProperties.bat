@echo off
rem Install the properties file for JavaLink 
rem In the correct Home directory for this
rem installation

if "%JAVALINK_HOME%" == "" goto nojavalinkhome
java com.gensym.util.CreateProductProperties %JAVALINK_HOME%\bin\.com.gensym.properties %JAVALINK_HOME%

goto done

:nojavalinkhome
echo The JAVALINK_HOME environment variable is not set.

:done
