@echo off
echo [step 0] setup JAVA_HOME to jdk1.6.0_45
set BASE_DIR=C:\opt\dfinstaller
set JAVA_HOME=C:\Program Files (x86)\Java\jdk1.6.0_45
echo [step 1] mklink
mklink /j C:\G2\src %BASE_DIR%\g2\src
echo [step 2] build & copy installer
cd %BASE_DIR%\g2\src\ant & ant build_64_ent & cd ..\bundle\tools & make_bundle ent & mkdir %BASE_DIR%\output\installers & copy ..\stage\Gensym*.zip %BASE_DIR%\output\installers
rem 20160921 (1)
rem 20160921 (2)
rem 20161004
