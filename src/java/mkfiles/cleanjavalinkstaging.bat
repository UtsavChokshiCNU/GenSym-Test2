set SOURCE_DIR=%SRCBOX%
set TARGET_DIR=%SOURCE_DIR%\javalink\javalink-intelnt-staging

cd %TARGET_DIR%
rm *.html
rm .com.*
cd bin
rm *.*
cd ..\classes
rm *.jar
cd com\gensym
rm -rf classes
rm -rf demos
cd ..\..\..
cd g2
rm *.exe
cd ..\kbs
rm *.kb
cd ..\docs
rem cd api
rem rm *.html
cd ..\..
