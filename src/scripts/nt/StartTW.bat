call %~dp0\set-boxes.bat

start %DSTBOX%\tw\opt\tw.exe localhost 1111 -log log_tw_1111.log -fonts '%SRCBOX%\promote\fonts'
