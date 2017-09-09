@echo off
setlocal

echo Uninstall Optegrity Server as NT Service

rem
rem	This batch file uninstalls the Optegrity server as an NT Service.
rem

set SITE_=%ROOTDIR%


rem
rem	Stop and remove the service
rem
"%SITE_%\g2\gservice" remove optegrity
