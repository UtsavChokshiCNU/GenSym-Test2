echo on

set SOURCE_DIR=%SRCBOX%\java
set ACTIVEX_DIR=%SOURCE_DIR%\activex
set STAGING_DIR=%SRCBOX%\sequoia\sequoia-intelnt-staging

rem ....Build components...

cd %SOURCE_DIR%
nmake -f mkfiles\intelnt-controls-o
nmake -f mkfiles\intelnt-wksp-o
nmake -f mkfiles\intelnt-trace-o


rem ....Copying controls to the staging dir....

copy %ACTIVEX_DIR%\* %STAGING_DIR%\java\classes\activex

rem ....Fixing the reg files....

cd %STAGING_DIR%\java\classes\activex
java com.gensym.devtools.RegFileFixer
