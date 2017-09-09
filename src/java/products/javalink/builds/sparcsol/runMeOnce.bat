
!set JSHIELD_HOME=d:\JShield

if "%JSHIELD_HOME%" == "" goto noinstallshield

set tempClassPath = %CLASSPATH%
set CLASSPATH=%JSHIELD_HOME%\classes;%CLASSPATH%

set JAVALINK_RELEASE=%SRCBOX\javalink\javalink-sparcsol-staging
set JAVALINK_BUILD=%SRCBOX%\java\products\javalink\builds\sparcsol
cls
rem ....Build components...
cd %JAVALINK_BUILD%
mkdir runtime
mkdir distribution
rem -----------------------------------

rem create sparcsol.ini 

echo [General]>setup\sparcsol.ini
echo OutputFile=%JAVALINK_BUILD%\distribution\setup.class>>setup\sparcsol.ini
echo Copyright=Copyright (C) 1998. All rights reserved.>>setup\sparcsol.ini
echo BuildNumber=1.0 Beta 2>>setup\sparcsol.ini
echo CompanyURL=www.gensym.com>>setup\sparcsol.ini
echo ApplicationName=G2 Javalink/Gateway>>setup\sparcsol.ini
echo UnixWrapper=%JAVALINK_BUILD%\distribution\setup>>setup\sparcsol.ini
echo CompanyName=Gensym Corporation>>setup\sparcsol.ini
echo [Welcome]>>setup\sparcsol.ini
echo [CheckVM]>>setup\sparcsol.ini
echo VMUrl=http://www.javasoft.com>>setup\sparcsol.ini
echo VMId1=Sun 1.1 All OS>>setup\sparcsol.ini
echo [Target]>>setup\sparcsol.ini
echo DefaultDir=/usr/gensym/javalink>>setup\sparcsol.ini
echo [Extract]>>setup\sparcsol.ini
echo RootDir=%JAVALINK_BUILD%>>setup\sparcsol.ini
echo TextSuffix=.txt .java >>setup\sparcsol.ini
echo IgnoreSuffix=.bak .save ~ >>setup\sparcsol.ini
echo [ChangePermissions]>>setup\sparcsol.ini
echo RootClass=extensions.permissions.ChangePermissions>>setup\sparcsol.ini


mkdir %JSHIELD_HOME%\classes\extensions
mkdir %JSHIELD_HOME%\classes\extensions\permissions 
copy  %JAVALINK_BUILD%\setup\ChangePermissions.java %JSHIELD_HOME%\classes\extensions\permissions\ChangePermissions.java
cd  %JSHIELD_HOME%\classes\extensions\permissions
javac -classpath %JSHIELD_HOME%\classes;%CLASSPATH% ChangePermissions.java
cd  %JAVALINK_BUILD%

set CLASSPATH = %tempClassPath%

goto end

:noinstallshield
echo "Please setup JSHEILD_HOME to the root direcrtory of JAVA INSTALLSHIELD"

:end
