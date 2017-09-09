@echo off
if "%OS%" == "Windows_NT" setlocal

if "%CLASSPATH%" == "" goto  noinstalljdk1

if "%BEANXPORTER_HOME%" == "" goto noinstallbx

set PATH=%PATH%;%BEANXPORTER_HOME%\bin
set CLASSPATH=%CLASSPATH%;classes;%BEANXPORTER_HOME%\classes\ax2jbeans.jar
@echo on
java sun.beanbox.BeanBoxFrame 
@echo off

:noinstalljdk1
echo "Please check that JDK 1.1.6 or greater has been installed correctly and that CLASSPATH has been defined"
goto end

:noinstalljdk2
echo "Please check that JDK 1.1.6 or greater has been installed correctly and that JAVA_HOME has been defined"
goto end

:noinstallbx
echo "BeanXporter has not been installed correctly please check that BEANXPORTER_HOME has been defined"
goto end

:end