@echo off
echo Removing registry entries for Telewindows2 ActiveX controls . . .
regsvr32 /u AXClient.dll
