@echo off
echo "Running Metrics Tests - %time%"

pushd ..\..\scripts\nt
call set-boxes
popd

set FILELIST=%SRCBOX%\tests\metrics\kbs_list_for_metrics.txt

set G2_METRICS_REPORT_BASE_DIR=%SRCBOX%\..\results\kb\metrics
rd %G2_METRICS_REPORT_BASE_DIR% /s /q
md %G2_METRICS_REPORT_BASE_DIR%

javac MetricsTest.java
java -classpath . MetricsTest %SRCBOX%\scripts\nt -files %FILELIST% %G2_METRICS_REPORT_BASE_DIR%
rem java -classpath . MetricsTest %SRCBOX%\scripts\nt -rootDir %SRCBOX%\kbs %G2_METRICS_REPORT_BASE_DIR%

echo "Done with Metrics Tests - %time%"
