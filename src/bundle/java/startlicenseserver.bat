@ECHO OFF

rem Run this with working directory being the license server
rem directory, typically c:/LicenseServer.

java -Dlogs="logs" -Djava.class.path=keygui.jar  LicenseKey  data
