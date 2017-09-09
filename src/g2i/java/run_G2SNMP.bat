pushd ..\..\scripts\nt
call set-boxes.bat
popd

rem set path=%DSTBOX%\javalink\lib;%path%
set CLASSPATH=%SRCBOX%\java;%CLASSPATH%
start ant -f build_G2SNMP.xml run
