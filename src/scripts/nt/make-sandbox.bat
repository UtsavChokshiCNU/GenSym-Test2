@echo off

rem * This batch file creates a sandbox

set MACHINE=intelnt
set CVSROOT=sdev4:/gensym/ab-repos
set USE_SRC=no

if not "%SB_ROOT%" == "" goto check_sbroot
echo Error: SB_ROOT must be set
goto end

:check_sbroot
if exist %SB_ROOT% goto sbroot_set
echo Error: SB_ROOT %SB_ROOT% does not exist
goto end

:sbroot_set
if not "%1" == "" goto do_make
echo Error: must provide sandbox name
echo e.g. make-sandbox ab
goto end

:do_make
cd %SB_ROOT%
mkdir %1
cd %1
mkdir dst
mkdir dst\%MACHINE%

if "%USE_SRC%" == "no" goto do_checkout
mkdir src
cd src

:do_checkout

:anything
cvs co -A vstudio specific/intelnt ext rtl

:twng
cvs co -A fnt jpeg tw scintilla xtp widgets twng dyndialogs

:g2
cvs co -A xml g2

:axl
cvs co -A activex

:runmake
cvs co -A gen

:end
