del *.fas

if "%1"=="x64" goto set_x64_mode
set ecl_to_use=ecl
set vcvars_to_use=x86
goto end_set_x64_mode
:set_x64_mode
set ecl_to_use=ecl64
set vcvars_to_use=x64
:end_set_x64_mode

call "C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\vcvarsall.bat" %vcvars_to_use%
..\tools\lisp\%ecl_to_use%\ecl
