@echo off

if not defined GENSYM_HOME set GENSYM_HOME=%CD%\..\..\..\..

if defined USE_INSTALLED_VERSION goto begin_installed
set home_javalink=%GENSYM_HOME%\dst\javalink
set javalink_binaries=%home_javalink%\lib
goto end_installed

:begin_installed
set home_javalink=%GENSYM_HOME%\javalink
set javalink_binaries=%home_javalink%\bin
:end_installed

set javalink_classes=%home_javalink%\classes

set home_jre_bin=%java_home%\bin
set classpath=%classpath%;%javalink_classes%\core.jar
set classpath=%classpath%;%javalink_classes%\javalink.jar
set classpath=%classpath%;%javalink_classes%\classtools.jar
set classpath=%classpath%;.\bin

set PATH=%home_jre_bin%;%javalink_binaries%

del *.txt
rd /s /q bin
md bin
"%home_jre_bin%\javac.exe" -d bin src\*.java
"%home_jre_bin%\java.exe" ModelEngine -listenerport %1 -log me_log.txt
exit
