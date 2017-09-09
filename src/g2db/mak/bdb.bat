@echo off
setlocal
rem      Build a database bridge for Windows
rem      ===================================

rem        Validate input
rem  ------------------------------
    if NOT "%SRCBOX%" == "" GOTO OK2
    echo ** SRCBOX is not defined
    goto done

    if NOT "%DSTBOX%" == "" GOTO OK2
    echo ** DSTBOX is not defined
    goto done
:OK2
    if EXIST %SRCBOX%\G2DB GOTO OK3
    echo ** Your sourcebox does not contain g2db
    goto done

rem        Determine destination directory
rem  --------------------------------------------
:OK3
    set PROD=
    if "%1" == "o"   set PROD=odbc
    if "%1" == "11"  set PROD=sybase
    if "%1" == "125" set PROD=sybase
    if "%1" == "130" set PROD=sqlsvr
    if "%1" == "7"   set PROD=oracle
    if "%1" == "80"  set PROD=oracle
    if "%1" == "81"  set PROD=oracle
    if "%1" == "90"  set PROD=oracle
    if "%1" == "92"  set PROD=oracle
    if "%1" == "100" set PROD=oracle
    if "%1" == "110" set PROD=oracle
    if not "%PROD%" == "" goto OK4
    echo ** Missing or invalid bridge selection code
    goto Usage

rem   Make sure the destination directory exists
rem ----------------------------------------------
:OK4
    set TARGET_DIR=%DSTBOX%\g2%PROD%\opt
    if exist %TARGET_DIR% goto cdToDst
    echo Warning: The target directory %TARGET_DIR% does not exist.
    echo Creating the directory %TARGET_DIR% . . .
    mkdir %TARGET_DIR%
    echo DONE.
    if exist %TARGET_DIR% goto cdToDst
    echo ** The destination directory %TARGET_DIR% does not exist
    goto done

rem   CD to the destination directory & determine what GSIDIR should be
rem ---------------------------------------------------------------------
:cdToDst
    cd /d %TARGET_DIR%
    set GF=""
    if not exist %SRCBOX%\gsi\test  set GF="gsiab=t"
rem    call vcvars32

rem    These bridges can be built on any computer
rem    ------------------------------------------
    if "%1" == "o"  goto odbc
    if "%1" == "11"  goto sybase
    if "%1" == "125"  goto sybase
    if "%1" == "130"  goto sqlsvr

rem   Get the name of this computer
rem   -----------------------------
    set uname=
    net config workstation | %windir%\system32\find "Computer name" | %windir%\system32\find /v "Full" > setvalue.bat
    echo e 0100 "                             set uname=" > script
    echo w >> script
    echo q >> script 
    debug setvalue.bat < script > nul
    del script
    call setvalue.bat
    del setvalue.bat

rem Select which bridge to build
rem ----------------------------
    if "%1" == "7"   goto ora7
    if "%1" == "80"  goto ora80
    if "%1" == "81"  goto ora81
    if "%1" == "100" goto ora100
    if "%1" == "110" goto ora110
    if "%1" == "130"  goto sqlsvr
    goto ora9

rem  Build g2-odbc.exe
rem  -----------------
:odbc
    if not "%2" == "f" goto makeodbc
    if exist g2-odbc.exe del g2-odbc.exe
    nmake clean /f %SRCBOX%\g2db\mak\g2-odbc-3-intelnt.mak
:makeodbc
    nmake %GF%  /f %SRCBOX%\g2db\mak\g2-odbc-3-intelnt.mak
    nmake clean /f %SRCBOX%\g2db\mak\g2-odbc-3-intelnt.mak 
    goto done

rem  Build g2-sqlsvr.exe
rem  -----------------
:sqlsvr
    if not "%2" == "f" goto makesqlsvr
    if exist g2-sqlsvr.exe del g2-sqlsvr.exe
    nmake clean /f %SRCBOX%\g2db\mak\g2-sqlsvr-intelnt.mak
:makesqlsvr
    nmake %GF%  /f %SRCBOX%\g2db\mak\g2-sqlsvr-intelnt.mak
    nmake clean /f %SRCBOX%\g2db\mak\g2-sqlsvr-intelnt.mak 
    goto done

rem  Build g2-ora7.exe
rem  -----------------
:ora7
    if "%uname%" == "TITANIC" goto buildG2Ora
    echo ** g2-ora7.exe must be built on Titanic
    goto done

rem  Build g2-ora80.exe
rem  ------------------
:ora80
    if "%uname%" == "HQ-W2K-SERV" goto buildG2Ora
    echo ** g2-ora80.exe must be built on HQ-W2K-SERV
    goto done

rem  Build g2-ora81.exe
rem  ------------------
:ora81
    if "%uname%" == "IE0" goto buildG2Ora
    if "%uname%" == "GOIANIA" goto buildG2Ora
    echo ** g2-ora81.exe must be built on IE0 or GOIANIA
    goto done

rem  Build g2-ora90.exe or g2-ora92.exe
rem  ----------------------------------
:ora9
    if "%uname%" == "HQ-PROJ-2000" goto force9env
    if "%uname%" == "PORANGATU"    goto force9env
    echo ** g2-ora90.exe and g2-ora92.exe must be built on HQ-PROJ-2000 or Porangatu
    goto done

:force9env
    if "%1" == "90" call %SRCBOX%\g2db\env\ora901-intelnt.bat
    if "%1" == "92" call %SRCBOX%\g2db\env\ora920-intelnt.bat
    goto buildG2Ora

rem  Build g2-ora10.exe
rem  ------------------
:ora100
    if "%uname%" == "HQ-DV-W2K-TEST" goto buildG2Ora
    if "%uname%" == "QA-TEST-XP"     goto buildG2Ora
    echo ** g2-ora10.exe must be built on HQ-DV-W2K-TEST or QA-TEST-XP
    goto done

rem  Build g2-ora110.exe
rem  -------------------
:ora110
rem    if "%uname%" == "HQ-PROJ-2000" goto force11env
rem    if "%uname%" == "PORANGATU"    goto force11env
rem    echo ** g2-ora110.exe must be built on HQ-PROJ-2000 or Porangatu
rem    goto done

:force11env
    call %SRCBOX%\g2db\env\ora110-intelnt.bat
echo on
    goto buildG2Ora



rem  Common section for building all Oracle bridges
rem  ----------------------------------------------
:buildG2Ora
    if not "%2" == "f" goto makeora
    if exist g2-ora%1.exe del g2-ora%1.exe
    nmake clean /f %SRCBOX%\g2db\mak\g2-ora%1%-intelnt.mak
:makeora
    nmake %GF%  /f %SRCBOX%\g2db\mak\g2-ora%1%-intelnt.mak
    nmake clean /f %SRCBOX%\g2db\mak\g2-ora%1%-intelnt.mak 
    goto done


rem  Build g2-sybase.exe
rem  -------------------
:sybase
    if not "%2" == "f" goto makesyb
    if exist g2-sybase.exe del g2-sybase.exe
    if "%1" == "125" goto cleanwith125
    nmake clean /f %SRCBOX%\g2db\mak\g2-syb11-intelnt.mak
    goto makesyb
:cleanwith125
    nmake clean /f %SRCBOX%\g2db\mak\g2-syb125-intelnt.mak
:makesyb
    if "%1" == "125" goto syb125
    call %SRCBOX%\g2db\env\syb1110-intelnt.bat
    nmake %GF%  /f %SRCBOX%\g2db\mak\g2-syb11-intelnt.mak
    nmake clean /f %SRCBOX%\g2db\mak\g2-syb11-intelnt.mak
    goto done
:syb125
    call %SRCBOX%\g2db\env\syb1250-intelnt.bat
    nmake %GF%  /f %SRCBOX%\g2db\mak\g2-syb125-intelnt.mak
    nmake clean /f %SRCBOX%\g2db\mak\g2-syb125-intelnt.mak
    goto done
:Usage
    echo "   Usage: bdb <code> [f]
    echo "
    echo "          <code> specifies which bridge you wish to build.  Valid values are:
    echo "
    echo "           7  - g2-ora7   80 - g2-ora80   90 - g2-ora90
    echo "          100 - g2-ora10  110 - g2-ora110 81 - g2-ora81   92 - g2-ora92
    echo "           o  - g2-odbc   11 - g2-syb11  125 - g2-syb125
    echo "	    130 - g2-sqlsvr
    echo "
    echo "          The optional 'f' means to force the rebuild.
:done

