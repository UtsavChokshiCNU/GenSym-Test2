@echo off
if "" == "%~1" ( SET "KBS_LIST=smoketestkbs_list.txt" ) else ( SET "KBS_LIST=%~1" )

set "SMOKEDIR=c:\g2\src\tests\smoketests\"

FOR /f "eol=#" %%G IN (%KBS_LIST%) DO (

echo Running [%SMOKEDIR%%%G] now...

call cmd /c %SMOKEDIR%%%G

echo Finished Running [%%G]...
cd..
)
exit /b