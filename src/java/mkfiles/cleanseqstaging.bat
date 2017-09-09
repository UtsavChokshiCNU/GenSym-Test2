set SOURCE_DIR=%SRCBOX%
set TARGET_DIR=%SOURCE_DIR%\sequoia\sequoia-intelnt-staging

cd %TARGET_DIR%
rm *.html
cd bin
rm *.*
cd %TARGET_DIR%\classes
rm *.jar
cd %TARGET_DIR%\classes\activex
rm *.*
cd %TARGET_DIR%\classes\com\gensym
rm -rf shell
rm -rf demos
rm -rf classes
cd %TARGET_DIR%\kbs
rm *.kb
cd %TARGET_DIR%\docs
rm *.html
rm *.gif
cd %TARGET_DIR%
rm -rf vbshell
