@echo off

SET PATH=%Path%;..\..\jre\bin;..\..\jre\bin\client
RegSvr32 .\NolOnline.dll


