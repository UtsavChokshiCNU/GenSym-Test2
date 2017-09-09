rem Start Java part of the Use Case
cd uc11
start StartModelEngine.bat 22222
rem wait port to make sure above server fully started.
call ant -buildfile ..\..\..\tests\build.xml wait-port -Dwait.maxwait=60 -Dwait.port=22222
cd ..
