@echo off
echo "Running Coverage Tests"
rem  sample usage >> "CoverageTest.bat"

echo wsvdemo-test.kb: WorkspaceView.ocx should be registered to pass the test
echo   regsvr32 /s /c C:\Program Files\Gensym\g2-8.3r1\g2\WorkspaceView.ocx

pushd ..\scripts\nt
call set-boxes
popd

set FILELIST=coveragetests_list.txt

javac RegressionTest.java
java -classpath . RegressionTest %SRCBOX%\scripts\nt -gsi %FILELIST% -need_coverage

echo "Done with Coverage Tests"

fc c:\results\Cover-test-summary.log .\results\Cover-test-summary.log
