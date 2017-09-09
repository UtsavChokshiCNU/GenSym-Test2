echo on
nmake -f "%SRCBOX%\java\mkfiles\intelnt-container-o" all
if not exist "%SRCBOX%\ax2jbeans" mkdir "%SRCBOX%\ax2jbeans"
if not exist "%SRCBOX%\ax2jbeans\ax2jbeans-intelnt-staging" mkdir "%SRCBOX%\ax2jbeans\ax2jbeans-intelnt-staging"
call "%SRCBOX%\java\mkfiles\packageax2jbeans.bat"
cd "%SRCBOX%\java\products\ax2jbeans\builds\intelnt"
call Ibuildax2jbeans.bat
