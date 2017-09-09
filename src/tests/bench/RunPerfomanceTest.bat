@echo off
echo "Running Perfomance Tests - %time%"

pushd ..\..\scripts\nt
call set-boxes
popd

set FILELIST=perfomance_testkbs_list.txt

set G2_PERFOMANCE_TEST_REPORT_DIR=%SRCBOX%\..\results\kb\perfomance

rd %G2_PERFOMANCE_TEST_REPORT_DIR% /s /q
md %G2_PERFOMANCE_TEST_REPORT_DIR%

javac PerfomanceTest.java
java -classpath . PerfomanceTest %SRCBOX%\scripts\nt -gsi %FILELIST%

echo "Done with Perfomance Tests - %time%"
