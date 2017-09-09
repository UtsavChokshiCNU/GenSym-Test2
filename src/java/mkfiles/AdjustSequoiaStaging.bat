:AdjustSequoiaStaging.bat
:AUTHOR: SJW
:CREATED: 4/29/99 

:DESCRIPTION:   

cd %SRCBOX%\sequoia\sequoia-%MACHINE%-staging
xcopy /E/I/Q/H/R docs\* Java\docs\*
xcopy /E/I/Q/H/R bin\* Java\bin\*
xcopy /E/I/Q/H/R classes\* Java\classes\*
xcopy /E/I/Q/H/R kbs\* Java\kbs\*
rd /S/Q docs
rd /S/Q docs
rd /S/Q bin
rd /S/Q classes
rd /S/Q kbs 

:USAGE
echo Usage: AdjustSequoiaStaging.bat
goto END

:END
