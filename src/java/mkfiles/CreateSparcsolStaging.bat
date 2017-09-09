: DATE CREATED: 5/5/99

set SRC-JVL-DIR=%SRCBOX%\javalink\javalink-intelnt-staging
set DST-JVL-DIR=%SRCBOX%\javalink\javalink-sparcsol-staging
set SRC-T2T-DIR=%SRCBOX%\sequoia\sequoia-intelnt-staging
set DST-T2T-DIR=%SRCBOX%\sequoia\sequoia-sparcsol-staging

: Copy platform independant javalink files from intelnt staging area
xcopy /E/I/Q/H/R %SRC-JVL-DIR%\classes %DST-JVL-DIR%\classes
xcopy /E/I/Q/H/R %SRC-JVL-DIR%\docs %DST-JVL-DIR%\docs
xcopy /E/I/Q/H/R %SRC-JVL-DIR%\kbs %DST-JVL-DIR%\kbs
: Copy platform dependant files  
copy %SRCBOX%\java\products\javalink\sparcsol\* %DST-JVL-DIR%
xcopy /E/I/Q/H/R %SRCBOX%\java\products\javalink\sparcsol\bin %DST-JVL-DIR%\bin

: Copy platform independant telewindows2 files from intelnt staging area
xcopy /E/I/Q/H/R %SRC-T2T-DIR%\java\classes %DST-T2T-DIR%\classes
xcopy /E/I/Q/H/R %SRC-T2T-DIR%\java\docs %DST-T2T-DIR%\docs
xcopy /E/I/Q/H/R %SRC-T2T-DIR%\java\kbs %DST-T2T-DIR%\kbs
: Copy platform dependant files
copy %SRCBOX%\java\products\sequoia\sparcsol\* %DST-T2T-DIR%
xcopy /E/I/Q/H/R %SRCBOX%\java\products\sequoia\sparcsol\bin %DST-T2T-DIR%\bin

copy %SRCBOX%\java\lib\libJgiInterface.so %DST-JVL-DIR%\bin\libJgiInterface.so
