:MakeAntlr.bat
:AUTHOR: sjw
:DATE CREATED: 4/29/99

cd %SRCBOX%\java
del antlr.jar
jar cvf antlr.jar antlr\*.class antlr\collections\*.class antlr\collections\impl\*.class
copy antlr.jar %SRCBOX%\sequoia\sequoia-intelnt-staging\java\classes\antlr.jar

goto END

:USAGE
echo Usage: MakeAntlr.bat
goto END

:END
