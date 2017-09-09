@REM The two parameters are the two revisions to compare

mkdir rev_%1
call benchmarkRev.bat %1 UC9 > rev_%1/output.txt
copy ../src/tests/performance/results/smart-signal-report.txt rev_%1/uc9.txt

mkdir rev_%2
call benchmarkRev.bat %2 UC9 > rev_%2/output.txt
copy ../src/tests/performance/results/smart-signal-report.txt rev_%2/uc9.txt

fc rev_%1/uc9.txt rev_%2/uc9.txt