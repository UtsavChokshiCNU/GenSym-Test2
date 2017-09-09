rd /S /Q coverage

mkdir coverage

move *.spi .\coverage\
move *.spl .\coverage\
move *.dyn .\coverage\
move *.dpi .\coverage\

cd coverage

set PRJ_NAME=%1
if "%PRJ_NAME%" == "" PRJ_NAME=GENSYM

codecov -prj %PRJ_NAME% -dpi pgopti.dpi -xmlbcvrgfull output.xml -txtbcvrgfull output.txt