!set JSHIELD_HOME=d:\jshield


if "%JSHIELD_HOME%" == "" goto noinstallshield

set JAVALINK_RELEASE=%SRCBOX%\javalink\javalink-solaris-staging
set JAVALINK_BUILD=%SRCBOX%\java\products\javalink\builds\sparcsol
cls
rem ....Build components...
cd %JAVALINK_BUILD%

del /Q %JAVALINK_BUILD%\distribution\*.*
del /Q %JAVALINK_BUILD%\runtime\*.*
java.exe -Dinstall.root=%JSHIELD_HOME% -classpath  %JSHIELD_HOME%\classes;%CLASSPATH% installshield.jshield.Main   "%JAVALINK_BUILD%\setup\sparcsol.ini"

cd %JAVALINK_BUILD%\distribution\
rename setup  javalink-%1
chmod +x   javalink-%1
cd %JAVALINK_BUILD%
tar cvf  javalink-%1.tar distribution
copy  javalink-%1.tar .\runtime\.
del  javalink-%1.tar

goto end


:noinstallshield
echo "Please setup JSHEILD_HOME to the root direcrtory of JAVA INSTALLSHIELD"

:end