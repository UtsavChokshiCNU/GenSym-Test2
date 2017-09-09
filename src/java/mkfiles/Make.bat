:Make.bat
:AUTHOR: sjw
:DATE CREATED: 4/28/99

:CHECK FLAGS
if .%1. == .. goto USAGE
if .%1. == .controls. set PRODUCT=intelnt-controls-o
if .%1. == .container. set PRODUCT=intelnt-container-o
if .%1. == .wksp. set PRODUCT=intelnt-wksp-o

cd %SRCBOX%\java
nmake -f mkfiles\%PRODUCT%
goto END

:USAGE
echo Usage: Make.bat <PRODUCT_NAME>
echo <PRODUCT_NAME> options are controls, container, wksp
goto END

:END
