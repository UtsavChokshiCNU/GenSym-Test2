if "%INSTALLSHIELD_HOME%" == "" goto noinstallshield

set AX2JBEANS_RELEASE=%SRCBOX\ax2jbeans\ax2jbeans-intelnt-staging
set AX2JBEANS_BUILD=%SRCBOX%\java\products\ax2jbeans\builds\intelnt
cls
rem ....Build components...
cd %AX2JBEANS_BUILD%
mkdir disk1
mkdir runtime
copy "%INSTALLSHIELD_HOME%\Program\_setup.dll"   setup
copy "%INSTALLSHIELD_HOME%\Program\compile.exe"  setup
copy "%INSTALLSHIELD_HOME%\Program\icomp.exe"    setup
copy "%INSTALLSHIELD_HOME%\Program\Isdbgn.dll"   setup
copy "%INSTALLSHIELD_HOME%\Program\packlist.exe" setup
rem ..
copy "%INSTALLSHIELD_HOME%\Program\_inst32i.ex_" disk1
copy "%INSTALLSHIELD_HOME%\Program\_isdel.exe"   disk1
copy "%INSTALLSHIELD_HOME%\Program\_setup.dll"   disk1
copy "%INSTALLSHIELD_HOME%\Program\_setup.lib"   disk1
copy "%INSTALLSHIELD_HOME%\Program\Isdbgn.dll"   disk1
copy "%INSTALLSHIELD_HOME%\Program\setup.exe"    disk1
rem -----------------------------------
rem create exebuild script

echo [EXE Builder] >setup\mkexe.ini
echo SrcDir=%SRCBOX%\java\products\ax2jbeans\builds\intelnt\disk1 >>setup\mkexe.ini
echo DestDir=%SRCBOX%\java\products\ax2jbeans\builds\intelnt\runtime >>setup\mkexe.ini
echo CmdLine=setup.exe >>setup\mkexe.ini
rem echo Password=gensym >>setup\mkexe.ini
echo Title="Gensym BeanXporter" >>setup\mkexe.ini
echo Compress=1 >>setup\mkexe.ini
echo 32Bit=1 >>setup\mkexe.ini
goto end

:noinstallshield
echo "Please setup INSTALLSHEILD_HOME to the root direcrtory of INSTALL SHIELD 3"

:end