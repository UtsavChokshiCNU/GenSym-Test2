rem This batch file copies required kbs for javalinkprof product distribution into
rem \javalinkprof\common\kbs from the areas in the java repos where these files
rem are commited...this batch file should be run before the javalinkprof product is made

set DST=%SRCBOX%\java\products\javalinkprof\common\kbs
set SRC=%SRCBOX%\java\products\javalink\common\kbs

rem Javalink kbs

copy  %SRC%\g2evliss.kb %DST%
copy  %SRC%\sys-mod.kb  %DST%
copy  %SRC%\uilroot.kb  %DST%
copy  %SRC%\javalink.kb %DST%

rem Javalink prof support kbs

set SRC=%SRCBOX%\java\products\javalinkprof\kbs

copy  %SRC%\g2runtime.kb %DST%
copy  %SRC%\javaprof.kb  %DST%
copy  %SRC%\jlintf.kb    %DST%
copy  %SRC%\javaintf.kb  %DST%
copy  %SRC%\jlpdemo.kb   %DST%