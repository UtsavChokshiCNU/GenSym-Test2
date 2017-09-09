@echo off
echo "Run Bullseye Correcting - %time%"

pushd ..\..\scripts\nt
call set-boxes
popd

set "PATH=%PATH%:%JAVA_HOME%\bin"

javac CorrectBullseyeReport.java
java -classpath . CorrectBullseyeReport %SRCBOX%\..\results\report.xml

echo "Done with Bullseye Correcting - %time%"
