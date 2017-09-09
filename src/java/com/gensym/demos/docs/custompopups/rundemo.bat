@echo off
if "%JAVA_HOME%" == "" goto nojavahome
if "%SEQUOIA_HOME%" == "" goto nosequoiahome
if "%JAVALINK_HOME%" == "" goto nojavalinkhome

@echo on
call "%SEQUOIA_HOME%\bin\start_g2" -kb "%SEQUOIA_HOME%\kbs\wksp-demo2.kb" -name "Workspace Demos" -tcpport 1111
@echo off
set _CLASSPATH=%CLASSPATH%
set CLASSPATH=%CLASSPATH%;%JAVA_HOME%\lib\classes.zip;%JAVALINK_HOME%\classes\javalink.jar;%SEQUOIA_HOME%\classes;%SEQUOIA_HOME%\classes\sequoia.jar;.
set _PATH=%PATH%
set PATH=%PATH%;%JAVALINK_HOME%\bin
goto cleanup

:nojavahome
echo The JAVA_HOME environment variable is not set.
goto done

:nosequoiahome
echo The SEQUOIA_HOME environment variable is not set.
goto done

:nojavalinkhome
echo The JAVALINK_HOME environment variable is not set.

:cleanup
@echo off
set CLASSPATH=%_CLASSPATH%
set PATH=%_PATH%
set _CLASSPATH=
set _PATH=

:done
