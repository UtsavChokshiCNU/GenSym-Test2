pushd ..\..\scripts\nt
call set-boxes.bat
popd

set CLASSPATH=%SRCBOX%\java;%CLASSPATH%
ant -f build_G2SNMP.xml
