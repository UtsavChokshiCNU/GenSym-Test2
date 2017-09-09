echo on

set SOURCE_DIR=%SRCBOX%\java\com\gensym

if not exist %SRCBOX%\java\com\gensym\devtools\StripUndocumentedMembers.class goto CHECKFILE

:CHECKFILE
if not exist %SRCBOX%\java\com\gensym\devtools\StripUndocumentedMembers.java goto ERROR

:COMPILE
javac %SRCBOX%\java\com\gensym\devtools\StripUndocumentedMembers.java
  
java com.gensym.devtools.StripUndocumentedMembers %SOURCE_DIR%

:ERROR
echo %SRCBOX%\java\com\gensym\devtools\StripUndocumentedMembers.java not found.  Please check sandbox.
