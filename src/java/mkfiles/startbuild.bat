cd %SRCBOX%

cvs co ext rtl gsi util gen specific
cvs co java
cd java
mkdir lib

cd %SRCBOX%\ext
mkdir o
cd %SRCBOX%\rtl
mkdir o
cd %SRCBOX%\gsi
mkdir o

java com.gensym.core.ProductManager -build -product core
java com.gensym.core.ProductManager -build -product javalink
java com.gensym.core.ProductManager -build -product sequoia
cd %SRCBOX%\java\com\gensym\core
cvs commit -F version.dat version.dat
cd %SRCBOX%\java\com\gensym\jgi
cvs commit -F version.dat version.dat
cd %SRCBOX%\java\com\gensym\ntw
cvs commit -F version.dat version.dat
cd %SRCBOX%\java

rem runmakejntw clean
rem runmakejntw o