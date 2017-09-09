@echo off

set PATH=C:/CABSDK/BIN;%PATH%
set MFCDIR=%VS100COMNTOOLS%..\..\VC\redist\x86\Microsoft.VC100.MFC
set CRTDIR=%VS100COMNTOOLS%..\..\VC\redist\x86\Microsoft.VC100.CRT

cd ..\TwOCX
c:\Windows\Microsoft.NET\Framework64\v4.0.30319\msbuild TelewindowsAx.sln /m /t:Rebuild /p:Configuration=Release /clp:ErrorsOnly

xcopy Release\TelewindowsAX.ocx ..\TwOCX\cab\ /R /F /Y
xcopy "%MFCDIR%\mfc100u.dll" ..\TwOCX\cab\ /R /F /Y
xcopy "%CRTDIR%\msvcr100.dll" ..\TwOCX\cab\ /R /F /Y
xcopy "%DSTBOX%/twng/opt/Twng.exe" ..\TwOCX\cab\ /R /F /Y
xcopy "%SRCBOX%/promote/bin/pegrp32g.dll" ..\TwOCX\cab\ /R /F /Y

cd ..\TwOCX\cab
makecab /f TelewindowsAX.DDF
