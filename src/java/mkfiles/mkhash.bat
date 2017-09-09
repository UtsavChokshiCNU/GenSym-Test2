echo on
set SOURCE_DIR=%SRCBOX%
set TARGET_DIR=%SOURCE_DIR%\sequoia\sequoia-intelnt-staging

cd %SOURCE_DIR%\java
rem ....Building antlr.jar.....
del antlr.jar
jar cvf antlr.jar antlr\*.class antlr\collections\*.class antlr\collections\impl\*.class
copy antlr.jar %TARGET_DIR%\Java\classes\antlr.jar

rem not obfuscating anymore - 1/8/99 sjw
rem hashjava t2.conf
