
set INSTALLSHIELD_HOME="D:\InstallShield\InstallShield3"
set JAVALINK_PROF_RELEASE=%SRCBOX\javalinkprof\javalinkprof-intelnt-staging
set JAVALINK_PROF_BUILD=%SRCBOX%\java\products\javalinkprof\builds\intelnt
cls
rem ....Build components...
cd %JAVALINK_PROF_BUILD%
mkdir disk1
mkdir runtime
copy %INSTALLSHIELD_HOME%\Program\_setup.dll    setup
copy %INSTALLSHIELD_HOME%\Program\compile.exe   setup
copy %INSTALLSHIELD_HOME%\Program\icomp.exe     setup
copy %INSTALLSHIELD_HOME%\Program\Isdbgn.dll    setup
copy %INSTALLSHIELD_HOME%\Program\packlist.exe  setup
rem ..
copy %INSTALLSHIELD_HOME%\Program\_inst32i.ex_  disk1
copy %INSTALLSHIELD_HOME%\Program\_isdel.exe    disk1
copy %INSTALLSHIELD_HOME%\Program\_setup.dll    disk1
copy %INSTALLSHIELD_HOME%\Program\_setup.lib    disk1
copy %INSTALLSHIELD_HOME%\Program\Isdbgn.dll    disk1
copy %INSTALLSHIELD_HOME%\Program\setup.exe     disk1
rem -----------------------------------
echo [EXE Builder] >setup\mkexe.ini
echo SrcDir=%SRCBOX%\java\products\javalinkprof\builds\intelnt\disk1 >>setup\mkexe.ini
echo DestDir=%SRCBOX%\java\products\javalinkprof\builds\intelnt\runtime >>setup\mkexe.ini
echo CmdLine=setup.exe >>setup\mkexe.ini
rem echo Password=gensym >>setup\mkexe.ini
echo Title="G2 Javalink/Professional" >>setup\mkexe.ini
echo Compress=1 >>setup\mkexe.ini
echo 32Bit=1 >>setup\mkexe.ini

