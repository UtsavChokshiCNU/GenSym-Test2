set SRCBOX=c:\g2\src
set LIBXML2DIR=%SRCBOX%\libxml2\win32

call vsvars32.bat
cd %LIBXML2DIR%

nmake distclean
cscript configure.js threads=no zlib=no iconv=no iso8859x=yes cruntime=/MT 
nmake libxmla 
copy /y bin.msvc\libxml2_a.lib %SRCBOX%\specific\intelnt\libxml2_a9.lib
