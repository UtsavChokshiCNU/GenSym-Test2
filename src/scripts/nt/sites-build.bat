cls

call set-boxes

set SCRIPTSBOX=%SRCBOX%
set DISPLAY=X
set G2EXE=%DSTBOX%\g2\opt
set G2_OPCLINK=%SRCBOX%\g2opc\kbs

call vcvars32
call iclvars
call setenv

set RTI_HOME=C:\Program Files\DMSO\RTI1.3NG-V6\Win2000-VC6

if "%1"==""        goto build_all
if "%1"=="eSCOR"     goto build_eSCOR
if "%1"=="NOL"     goto build_NOL
if "%1%"=="Optegrity"  goto build_optegrity
if "%1%"=="rethink"  goto build_rethink
if "%1%"=="Integrity"  goto build_integrity

:build_all

cd %SRCBOX%\g2i\bin

call createbuild 1r10

cd %SRCBOX%\g2i\sites\e-SCOR\bin

call createbuild 1r10

cd %SRCBOX%\g2i\sites\Integrity\bin

call createbuild 1r10

cd %SRCBOX%\g2i\sites\Optegrity\bin

call createbuild 1r10

cd %SRCBOX%\g2i\sites\Nol\bin

call createbuild 1r10

cd %SRCBOX%\g2i\sites\HLA\bin

call createbuild 1r10

cd %SRCBOX%\scripts\nt

goto end

:build_NOL

cd %SRCBOX%\g2i\sites\Nol\bin

call createbuild 1r10

cd %SRCBOX%\scripts\nt

goto end

:build_eSCOR
cd %SRCBOX%\g2i\sites\e-SCOR\bin

call createbuild 1r10

cd %SRCBOX%\scripts\nt

goto end

:build_optegrity
cd %SRCBOX%\g2i\sites\Optegrity\bin

call createbuild 1r10

cd %SRCBOX%\scripts\nt

goto end

:build_rethink
cd %SRCBOX%\g2i\sites\ReThink\bin

call createbuild 1r10

cd %SRCBOX%\scripts\nt

goto end

:build_integrity

cd %SRCBOX%\g2i\sites\Integrity\bin


call createbuild 1r10

cd %SRCBOX%\scripts\nt

goto end

:end

