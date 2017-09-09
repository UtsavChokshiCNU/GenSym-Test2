md %SRCBOX%\stage
md %SRCBOX%\stage\opclink
md %SRCBOX%\stage\opclink\kbs
copy %SRCBOX%\g2opc\cpp\Release\g2opc.exe %SRCBOX%\stage\opclink
copy %SRCBOX%\g2opc\cpp\configfile.ini %SRCBOX%\stage\opclink
copy %SRCBOX%\g2opc\misc\run-g2opc.bat %SRCBOX%\stage\opclink
copy %SRCBOX%\g2opc\kbs\*.kb %SRCBOX%\stage\opclink\kbs
