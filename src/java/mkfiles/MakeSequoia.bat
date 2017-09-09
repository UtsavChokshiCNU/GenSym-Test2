:MakeSequoia.bat
:AUTHOR: sjw
:DATE CREATED: 4/29/99

cd %SRCBOX%\java
del /Q %SRCBOX%\java\classes\sequoia.jar
nmake -f %SRCBOX%\java\mkfiles\intelnt-sequoia-o
copy classes\sequoia.jar %SRCBOX%\sequoia\sequoia-intelnt-staging\java\classes\sequoia.jar

goto END

:USAGE
echo Usage: MakeSequoia.bat
goto END

:END
