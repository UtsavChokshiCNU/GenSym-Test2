@echo off

rem :  This shell script signs the file in %1% using name %2%

rem :  example:  signany.bat myfile.exe "My Special File"

rem :  Note that if you don't put quotes around your name, probably something
rem :  will go wrong.  I couldn't figure out how to make it do the quote thing
rem :  right.  

rem :  This script does not support the -i option, e.g. in twaxsign.bat, we
rem :  set TWAXHTTP=http://www.gensym.com/activex/twcontrol/info80.shtml 
rem :  and then use that as as -i %TWAXHTTP% in set options


echo Signing %1, using pretty name %2

if %2 == "" goto error

set TSERV=http://timestamp.verisign.com/scripts/timstamp.dll
set MYSPC=c:\Cabsdk\Gensym\mycredentials.spc
set MYPVK=c:\Cabsdk\Gensym\myprivatekey.pvk

set OPTIONS=-spc %MYSPC% -v %MYPVK% -$ individual -t %TSERV%

echo Signing cab file
signcode -n %2 %OPTIONS% %1

goto end

:error

echo Must supply two arguments:  File to sign and pretty name to use.

:end
