@echo off
if "%OS%" == "Windows_NT" setlocal

if "%CLASSPATH%" == "" goto noinstalljdk1

if "%JAVA_HOME%" == "" goto noinstalljdk2

if "%BEANXPORTER_HOME%" == "" goto noinstallbx

@echo on
set PATH=%PATH%;%JAVA_HOME%\bin;%BEANXPORTER_HOME%\bin
set CLASSPATH=%CLASSPATH%;%JAVA_HOME%\lib\classes.zip;%BEANXPORTER_HOME%\classes\ax2jbeans.jar;%BEANXPORTER_HOME%\classes
@echo off
java -mx80000k com.gensym.com.BeanXporter %1 %2 %3 %4 %5 %6 %7 %8 %9
goto end

:noinstalljdk1
echo Please check that JDK 1.1.6 or greater has been installed correctly and that CLASSPATH has been defined.
goto end

:noinstalljdk2
echo Please check that JAVA_HOME has been set to the installation of JDK 1.1.6 or greater.
goto end

:noinstallbx
echo BeanXporter has not been installed correctly.  Please check that BEANXPORTER_HOME has been set.
goto end

:end