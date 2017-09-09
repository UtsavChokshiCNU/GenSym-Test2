@REM A single batch to launch both applications for profiling
cd ../../../scripts/nt
call StartServer.bat
@REM Let the listener initialize
CHOICE /T 3 /C ync /D y
call ant -buildfile c:\G2\src\tests\build.xml wait-port -Dwait.maxwait=30 -Dwait.port=1111
IF %ERRORLEVEL%==0 call c:\G2\dst\TWNG\opt\twng.exe localhost 1111 -log C:\G2\src\tests\performance\vsProfile\logs\twng_1111_log.txt