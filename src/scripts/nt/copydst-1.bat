@rem Internal file to process one dstbox directory.
@rem one arg; the directory within dstbox.

echo Processing %1%
time /t

@rem In order to deal with slash directions, using the SPIN_ID variable.
@rem But we no longer use that variable in Supervisor.  We should be able to
@rem pick it out of the SRCBOX variable, but that's too hard for now.  We
@rem can do it in a very simple way.  And even if we don't find it, and
@rem we let it be "unknown", big deal.  It's only used for the filename.

set SPIN_ID=unknown
if %SANDBOX% == d:\bt\et set SPIN_ID=et
if %SANDBOX% == d:\bt\ab set SPIN_ID=ab

@rem sometimes Winzip is on C; sometimes it's on D.  Look both places.
if exist "c:\program files\winzip\wzzip.exe" set WZIP="c:\program files\winzip\wzzip.exe"
if exist "d:\program files\winzip\wzzip.exe" set WZIP="d:\program files\winzip\wzzip.exe"

set filename=intelnt-%SPIN_ID%-dstbox-%1.zip

set localzipfile=d:\bt\ab\junk\%filename%
set sambazipfile=z:\tmp\%filename%
set unixzipfile=/home/ab/tmp/%filename%


if exist "%sambazipfile%" del "%sambazipfile%"
if exist "%localzipfile%" del "%localzipfile%"

%WZIP% -rp "%localzipfile%" %1

copy %localzipfile% %sambazipfile%

rsh sdev5 cd %SUPSANDBOX%/dst/intelnt/%1 ; unzip -o %unixzipfile%
