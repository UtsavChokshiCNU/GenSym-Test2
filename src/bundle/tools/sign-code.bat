@echo off

set SIGNTOOL_PATH=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Bin\signtool.exe
set CERT_PATH=versata.pfx
set TIMESTAMP_URL=http://timestamp.verisign.com/scripts/timstamp.dll
set FILE_PATH=%1
set PASSTRING=/p %2

if "%2"=="" set PASSTRING=

IF "%FILE_PATH%"=="" GOTO Error
	IF exist "%FILE_PATH%" (
		"%SIGNTOOL_PATH%" sign /f "%CERT_PATH%" %PASSTRING% /t "%TIMESTAMP_URL%" /v "%FILE_PATH%"
		GOTO End
		) else GOTO Error2
:Error
	echo "You have set filename as argument"
	exit 1
:Error2
	echo "File %FILE_PATH% does not exists"
	exit 1
:End