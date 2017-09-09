
if "%INSTALLSHIELD_HOME%" == "" goto noinstallshield

set AX2JBEANS_RELEASE=%SRCBOX%\ax2jbeans\ax2jbeans-intelnt-staging
set AX2JBEANS_BUILD=%SRCBOX%\java\products\ax2jbeans\builds\intelnt
cls
rem ....Build components...
cd %AX2JBEANS_BUILD%
setup\compile setup\setup.rul -g
copy setup\setup.ins disk1
copy setup\setup.dbg disk1
del data\data.z 2>nul
setup\icomp -i %AX2JBEANS_RELEASE%\*.* data\data.z
copy data\data.z disk1
del data\data.z
cd setup
del setup.pkg 2>nul
packlist setup.lst
copy setup.pkg ..\disk1
cd ..
copy data\*.*          disk1
cd %AX2JBEANS_BUILD%
set tmppath=%PATH%
del /Q %AX2JBEANS_BUILD%\runtime\*.* 2>nul
set path=%PATH%;%INSTALLSHIELD_HOME%\UTILITY\EXEBLDR
start /wait exebuild %AX2JBEANS_BUILD%\setup\mkexe.ini
cd %AX2JBEANS_BUILD%\runtime\
copy setupex.exe  %SRCBOX%\ax2jbeans\beanXporter-%1.exe
set path=%tmppath%
cd %AX2JBEANS_BUILD%
goto end

:noinstallshield
echo "Please setup INSTALLSHEILD_HOME to the root direcrtory of INSTALL SHIELD 3"

:end