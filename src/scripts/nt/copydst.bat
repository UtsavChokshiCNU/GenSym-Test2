@setlocal

@rem Copies %DSTBOX% to %UNIXSCRBOX%\dst\intelnt, using zip in order to
@rem preserve write dates.  Zip used is WinZip Command Line Support Add-On 
@rem Version 1.1 SR-1, downloaded from http://www.winzip.com/wzcline.cgi.  
@rem Requires machine to have winzip 9.0 installed.

@rem Expects /home/ab to be mounted on z:

@rem Using rsh, which is nonstandard, but doing it this way is vastly faster than
@rem doing the unzip on the NT machine across samba.

@rem calls an internal batch file, to prevent the ZIP file from being too huge,
@rem and allow some kind of error recovery and understanding of problems


@rem First do some stage stuff:

cd /d %SRCBOX%\stage

echo y | rmdir /s %UNIXSRCBOX%\stage\twax

xcopy twax %UNIXSRCBOX%\stage\twax /e /i /k 

echo y | rmdir /s %UNIXSRCBOX%\stage\workspace-view

xcopy workspace-view %UNIXSRCBOX%\stage\workspace-view /e /i /k 

echo y | rmdir /s %UNIXSRCBOX%\stage\g2pi

xcopy g2pi %UNIXSRCBOX%\stage\g2pi /e /i /k 



@rem Now do DST, using internal file as a "procedure"

cd /d %DSTBOX%

for /D %%v in (*) do call %SCRIPTSBOX%\scripts\nt\copydst-1.bat %%v
