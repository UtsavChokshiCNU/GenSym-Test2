
if "%INSTALLSHIELD_HOME%" == "" goto noinstallshield

set JAVALINK_PROF_RELEASE=%SRCBOX%\javalinkprof\javalinkprof-intelnt-staging
set JAVALINK_PROF_BUILD=%SRCBOX%\java\products\javalinkprof\builds\intelnt
cls
rem ....Build components...
cd %JAVALINK_PROF_BUILD%
setup\compile setup\setup.rul -g
copy setup\setup.ins disk1
copy setup\setup.dbg disk1
del data\data.z
setup\icomp -i %JAVALINK_PROF_RELEASE%\*.* data\data.z
copy data\data.z disk1
del data\data.z
cd setup
del setup.pkg
packlist setup.lst
copy setup.pkg ..\disk1
cd ..
copy data\*.*          disk1
cd %JAVALINK_PROF_BUILD%
set tmppath=%PATH%
del /Q %JAVALINK_PROF_BUILD%\runtime\*.*
set path=%PATH%;%INSTALLSHIELD_HOME%\UTILITY\EXEBLDR
start /wait exebuild %JAVALINK_PROF_BUILD%\setup\mkexe.ini
cd %JAVALINK_PROF_BUILD%\runtime\
copy setupex.exe  %SRCBOX%\javalinkprof\javalink-professional%1.exe
set path=%tmppath%
cd %JAVALINK_PROF_BUILD%
goto end

:noinstallshield
echo "Please setup INSTALLSHEILD_HOME to the root direcrtory of INSTALL SHIELD 3"

:end
