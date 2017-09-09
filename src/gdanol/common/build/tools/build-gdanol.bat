setlocal
set M=%SRCBOX%\gdanol\common\kbs
set M=%M% %SRCBOX%\gdanol\gda\kbs
set M=%M% %SRCBOX%\gdanol\nol\kbs
set M=%M% %SRCBOX%\gdanol\common\demos\kbs
set M=%M% %JAVA_SRCBOX%\java\products\javalink\common\kbs
set M=%M% k:\gensym\udev\jmail-23r1-JH04\kbs
set M=%M% k:\gensym\udev\jms-23r1-JH04\kbs
set M=%M% k:\gensym\udev\g2i-23r1-JH04\kbs
set M=%M% k:\gensym\udev\g2odbc-83r1-JH04\kbs
set M=%M% k:\gensym\udev\g2pi-83r1-JH04\kbs
set M=%M% k:\gensym\udev\opclink-83r1-JH04\kbs
set M=%M% %SRCBOX%\kbs
set M=%M% %SRCBOX%\kbs\tools

set G2_MODULE_SEARCH_PATH=%M%

%G2EXE%\g2.exe -kb %SRCBOX%\gdanol\common\build\tools\release-gdanol.kb -copy-logbook-on-console -start -log %1

