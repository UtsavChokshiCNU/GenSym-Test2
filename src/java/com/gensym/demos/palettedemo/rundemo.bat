@echo off
setlocal
rem this batch file expects the user to be cd'd to the directory that this file
rem is found in, <install directory>\classes\com\gensym\demos\palettedemo
rem -or- 
rem to the Telewindows 2 Toolkit bin directory

if exist ..\..\..\..\..\bin\envvars.bat cd ..\..\..\..\..\bin
if not exist envvars.bat goto problem

call envvars.bat

@echo on
call "%SEQUOIA_HOME%\bin\start_g2"  -kb "%SEQUOIA_HOME%\kbs\palette-demo.kb" -tcpport 4321 -name "Sequoia Demo"

"%JAVA_HOME%\bin\java" com.gensym.demos.palettedemo.PaletteDemo -host localhost -port 4321
@echo off
goto end
:problem
echo Please run this example from the Telewindows 2 Toolkit "bin" directory
echo Please use the CD command to change to that directory.
:end
