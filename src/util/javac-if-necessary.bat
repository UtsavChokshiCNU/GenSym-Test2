@echo off

set JAVAFILE=%~pn1
shift
set basename = %JAVAFILE%
if EXIST %JAVAFILE%.class goto :compiled

echo COMPILING %JAVAFILE%.java
javac -J"-mx80000k" %JAVAFILE%.java

goto :end

:compiled
rem *** echo %JAVAFILE%.java Compiled Already

:end
