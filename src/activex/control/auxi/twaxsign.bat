@rem @echo off

@rem :  This shell script signs the TwControl.cab file in %BT_ROOT%\stage\twax,
@rem :  and then unregisters it, so that downloading it will be required (and
@rem :  therefore one can immediately test the automatic download right after
@rem :  running this script).

@rem :  Requires %SRCBOX% to be set.

@rem :  Usage:
@rem :    Using a Command Prompt on the PC:
@rem :    Make sure the shtml file name is still correct
@rem :     c:\> cd %SRCBOX%
@rem :     c:\bt\...> cvs co [-A|-r <branch>] activex promote
@rem :     c:\bt\...> runmake activex opt
@rem :     c:\bt\...> runmake activex opt stage
@rem :     c:\bt\...> .\activex\control\auxi\twaxsign.bat   # run this script
@rem :    Verify that the cab file is good:
@rem :     c:\bt\...> chktrust.exe .\stage\twax\TwControl.cab

if "%SRCBOX%" == "" goto error

set MYNAME=Telewindows ActiveX Control
set TWAXHTTP=http://www.gensym.com/activex/twcontrol/info80.shtml
set TSERV=http://timestamp.verisign.com/scripts/timstamp.dll
set MYSPC=c:\Cabsdk\Gensym\mycredentials.spc
set MYPVK=c:\Cabsdk\Gensym\myprivatekey.pvk
set OCXLOC=%SRCBOX%\stage\twax

set OPTIONS=-spc %MYSPC% -v %MYPVK% -i %TWAXHTTP% -$ individual -t %TSERV%

echo Silently registering ActiveX control %OCXLOC%\TwControl.ocx
regsvr32 /s %OCXLOC%\TwControl.ocx

echo Signing cab file
signcode -n "%MYNAME%" %OPTIONS% %OCXLOC%\TwControl.cab

echo Silently unregistering control on local machine so download will be required
regsvr32 /u /s %OCXLOC%\TwControl.ocx

goto end

:error

echo Must set SRCBOX prior to running this script.

:end
