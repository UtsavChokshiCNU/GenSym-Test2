@echo off
if "%JAVA_HOME%" == "" goto nojavahome
if "%SEQUOIA_HOME%" == "" goto nosequoiahome
if "%JAVALINK_HOME%" == "" goto nojavalinkhome

@echo on
call "%SEQUOIA_HOME%\bin\start_g2" -kb "%SEQUOIA_HOME%\kbs\dialog-demo.kb" -name "Custom Dialog Demo (G2)" -tcpport 1345 -tcpipexact
@echo off
copy %SEQUOIA_HOME%\classes\com\gensym\demos\customdialogs\johnny.ser C:\temp\johnny.ser
set _CLASSPATH=%CLASSPATH%
set CLASSPATH=%JAVA_HOME%\lib\classes.zip;%JAVA_HOME%\lib\tools.jar;%SEQUOIA_HOME%\classes;%SEQUOIA_HOME%\classes\coreui.jar;%SEQUOIA_HOME%\classes\sequoia.jar;%JAVALINK_HOME%\classes;%JAVALINK_HOME%\classes\core.jar;%JAVALINK_HOME%\classes\classtools.jar;%JAVALINK_HOME%\classes\javalink.jar;%JAVALINK_HOME%\classes\beanbuilder.jar;%CLASSPATH%
set _PATH=%PATH%
set PATH=%PATH%;%JAVALINK_HOME%\bin
@echo on
%JAVA_HOME%\bin\java com.gensym.shell.Shell -host localhost -port 1345 -title "Custom Dialog Demo (T2)"
@echo off
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
