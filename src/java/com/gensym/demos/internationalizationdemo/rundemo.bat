@echo off
setlocal
rem this batch file expects the user to be cd'd to the directory that this file
rem is found in:
rem  <install directory>\classes\com\gensym\demos\internationalizationdemo
rem -or- 
rem to the Telewindows 2 Toolkit bin directory

if exist ..\..\..\..\..\bin\envvars.bat cd ..\..\..\..\..\bin
if not exist envvars.bat goto problem

call envvars.bat

rem this demo will enable the user to change the value of the number of moons 
rem of the planet FOOBAR in both English and German, otherwise identical to 
rem itemaccessdemo.

@echo on
call "%SEQUOIA_HOME%\bin\start_g2" -kb "%SEQUOIA_HOME%\kbs\sq-demos.kb" -name "Sequoia Demo" -tcpport 1234 -tcpipexact

"%JAVA_HOME%\bin\java" com.gensym.demos.internationalizationdemo.InternationalizationDemo localhost 1234 FOOBAR
@echo off
goto end
:problem
echo Please run this example from the Telewindows 2 Toolkit "bin" directory
echo Please use the CD command to change to that directory.
:end
