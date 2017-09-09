@echo off
if "%JAVA_HOME%" == "" goto nojavahome
if "%SEQUOIA_HOME%" == "" goto nosequoiahome
if "%JAVALINK_HOME%" == "" goto nojavalinkhome

@echo on
call "%SEQUOIA_HOME%\bin\start_g2" -kb "%SEQUOIA_HOME%\kbs\beans-demo.kb" -name "Beans On Workspaces Demo (G2)" -tcpport 1288 -tcpipexact -width 600 -height 450
@echo off
set _CLASSPATH=%CLASSPATH%
set CLASSPATH=%CLASSPATH%;%JAVA_HOME%\lib\classes.zip;%JAVALINK_HOME%\classes\javalink.jar;%SEQUOIA_HOME%\classes;%SEQUOIA_HOME%\classes\sequoia.jar;%SEQUOIA_HOME%\classes\com\gensym\demos\wkspbeans\Xcal.jar;.
set _PATH=%PATH%
set PATH=%PATH%;%JAVALINK_HOME%\bin
@echo on
%JAVA_HOME%\bin\java com.gensym.shell.Shell -host localhost -port 1288 -title "Beans On Workspaces Demo (T2)"
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
