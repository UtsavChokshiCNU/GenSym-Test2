@echo off

rem  sample usage >> "QuickRegressionTest.bat [-need_coverage]"

echo wsvdemo-test.kb: WorkspaceView.ocx should be registered to pass the test
echo   regsvr32 /s /c C:\Program Files\Gensym\g2-8.3r1\g2\WorkspaceView.ocx


if "" == "%~1" ( SET "FILELIST=testkbs_list.txt" ) else ( SET "FILELIST=%~1" )

echo "Running tests suit with %FILELIST%"

; copy required file for JMail test
md c:\tmp
copy PetStore.jpg c:\tmp\PetStore.jpg

; copy required file for qa-guide-tests.kb
copy qa-guide-fill-scroll-test-data.txt c:\tmp\qa-guide-fill-scroll-test-data.txt

pushd ..\scripts\nt
call set-boxes
set path=%DSTBOX%\twng\opt;%path%;C:\Program Files (x86)\Java\jdk1.6.0\bin
popd

javac RegressionTest.java
java -classpath . RegressionTest %SRCBOX%\scripts\nt -gsi %FILELIST% %1

echo "Done with Quick Regression Tests"

fc c:\results\Regr-test-summary.log .\results\Regr-test-summary.log
