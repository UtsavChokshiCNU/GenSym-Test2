@setlocal
@rem the most trivial possible batch file to create the hundred or so necessary
@rem directories for a fully populated G2 dstbox on a Windows machine.  It expects
@rem DSTBOX to be set.

@if NOT "%SCRIPTSBOX%" == "" goto check_scriptsbox
set SCRIPTSBOX=k:\bt\ab

:check_scriptsbox
@if not exist %SCRIPTSBOX% goto no_scripts_error

@if not exist "%DSTBOX%" goto error

for %%v in (ext fnt rtl g2 tw gsi jpeg xml twplug activex gservice twng xtp scintilla widgets g2pi) do call %SCRIPTSBOX%\scripts\nt\make-dstbox-1.bat %%v

@goto end

:no_scripts_error
@echo Could not find an appropriate SCRIPTSBOX!
@echo Please set the variable to something useful.
@goto end

:error

@echo DSTBOX does not exist!  Did you create the directory and set the variable?

:end
