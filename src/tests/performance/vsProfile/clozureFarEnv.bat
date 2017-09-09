setlocal enabledelayedexpansion
set G2V83_OK=C:\G2\license\g2sitev83.ok
set G2_AUTO_TEST=C:\G2\src\tests\performance\results
set G2_MODULE_SEARCH_PATH= 'C:\G2\src\kbs' 'C:\G2\src\g2i\kbs' 'C:\G2\src\g2i\sites\Integrity\kbs' 'C:\G2\src\java\products\javalink\kbs' 'C:\G2\src\g2db\kbs' 'C:\G2\src\g2i\sites\Optegrity\kbs' 'C:\G2\src\g2i\sites\e-scor\kbs' 'C:\G2\src\g2pi\kbs' 'C:\G2\src\g2i\sites\ReThink\kbs' 'C:\G2\src\g2i\sites\Nol\kbs' 'C:\G2\src\g2i\sites\HLA\kbs' 'C:\G2\src\g2opc\kbs' 'C:\G2\src\gdanol\gda\kbs' 'C:\G2\src\gdanol\common\kbs' 'C:\G2\src\gdanol\nol\kbs' 'C:\G2\src\tests'
set G2_OK=C:\G2\lisence\g2sitev83.ok
set "REPORT_DIR=%G2_AUTO_TEST%"

set PATH=C:\Programs\ClozureCL;C:\G2\src\scripts\nt;C:\Program Files (x86)\Java\jdk1.6.0\bin;C:\Program Files (x86)\Java\jre6\bin

set SRCBOX=C:\G2\src\
set DSTBOX=C:\G2\dst\

set SCRIPTSBOX=%SRCBOX%
set MACHINE=Intelnt
set DISPLAY=X
set USE_VS2008=YES

cd C:\G2\src\lisp\

"c:\Program Files\Far2\Far.exe" . C:\G2\src\tests\performance\