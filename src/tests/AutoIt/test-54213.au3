;--If G2 server is running Then close it
if WinExists("Gensym G2 Real-Time Rule Engine - Server") Then
	WinKill("Gensym G2 Real-Time Rule Engine - Server");
EndIf
;--Start G2 server
Run("C:\G2\dst\g2\opt\g2.exe -ok C:\G2\license\g2sitev83.ok");
WinWait("Gensym G2 Real-Time Rule Engine - Server");
WinActivate("Gensym G2 Real-Time Rule Engine - Server");
WinWaitActive("Gensym G2 Real-Time Rule Engine - Server");
sleep(10000);
;--When G2 server started,start twng.exe
Run("C:\G2\dst\twng\opt\twng.exe localhost 1111 -log c:\log_twng_1111.log", "", @SW_MAXIMIZE);
WinWait("Telewindows Client");
WinActivate("Telewindows Client");
WinWaitActive("Telewindows Client");

Sleep(1000);
;--When twng.exe started,load KB
Send("^o");
$loadkb=WinExists("Load KB");
While $loadkb==0
	sleep(1000);
	$loadkb=WinExists("Load KB");
WEnd
WinWait("Load KB");
WinActivate("Load KB");
WinWaitActive("Load KB");
Sleep(1000);
ControlSetText("Load KB","","Edit1","C:\G2\src\tests\g2-ui-grid-view-insert-rows-test.kb");
Sleep(1000);
WinActivate("Load KB");
ControlClick("Load KB","","Button2");
;--After load KB
WinActivate("Telewindows Client");
WinWaitActive("Telewindows Client");
$testws=WinExists("Telewindows Client","G2-UI-GRID-VIEW-INSERT-ROWS-TEST-TOP-LEVEL-WS");
While $testws==0
	sleep(1000);
	$testws=WinExists("Telewindows Client","G2-UI-GRID-VIEW-INSERT-ROWS-TEST-TOP-LEVEL-WS");
WEnd
Sleep(1000);
;--Run->Start
Send("!r");
Sleep(1000);
Send("s");
Sleep(1000);

;click Launch grid view button
MouseClick("left",483,92);
sleep(100);
;click first button
MouseClick("left", 359,460);
sleep(1000);
;click 2nd button
MouseClick("left", 352, 563);
;click 3rd button
sleep(1000);
MouseClick("left", 707, 465);
;click 4th button
sleep(1000);
MouseClick("left", 709, 565);
Sleep(1000);
MsgBox(4096, "Test result", "Test OK", 10)


