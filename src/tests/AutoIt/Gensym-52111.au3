;--If G2 server is running Then close it
if WinExists("Gensym G2 Real-Time Rule Engine - Server") Then
	WinKill("Gensym G2 Real-Time Rule Engine - Server");
EndIf
;--Start G2 server
Run("C:\G2\run_g2.bat");
WinWait("Gensym G2 Real-Time Rule Engine - Server");
WinActivate("Gensym G2 Real-Time Rule Engine - Server");
WinWaitActive("Gensym G2 Real-Time Rule Engine - Server");
sleep(1000);
;--When G2 server started,start twng.exe
Run("C:\G2\dst\twng\opt\twng.exe localhost 1111 -log c:\log_twng_1111.log", "", @SW_MAXIMIZE);
WinWait("Telewindows Client");
WinActivate("Telewindows Client");
WinWaitActive("Telewindows Client");

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
ControlSetText("Load KB","","Edit1","C:\G2\src\tests\AutoIt\Gensym-52111.kb");
Sleep(1000);
WinActivate("Load KB");
ControlClick("Load KB","","Button2");

WinActivate("Telewindows Client");
WinWaitActive("Telewindows Client");
$testws=WinExists("Telewindows Client","GENSYM-47219-TOP-LEVEL-WS");
While $testws==0
	sleep(1000);
	$testws=WinExists("Telewindows Client","GENSYM-47219-TOP-LEVEL-WS");
WEnd
Sleep(1000);

Send("!r");
Sleep(2000);
Send("s");
Sleep(2000);

$dialog=WinExists("Dialog Title");
While $testws==0
	sleep(1000);
	$testws=WinExists("Dialog Title");
WEnd

$pos=WinGetPos("Dialog Title");
MouseClickDrag("left", $pos[0]+$pos[2]-2, $pos[1]+$pos[3]-2, $pos[0]+$pos[2]+100, $pos[1]+$pos[3]);

$pos1 = ControlGetPos("Dialog Title","","msctls_updown321");
$pos2 = ControlGetPos("Dialog Title","","Edit2");

If $pos1[0]==$pos2[0] Then
	MsgBox(4096, "Gensym-52111.kb", "Success, The spinner is all ok!")
Else
	MsgBox(4096, "Gensym-52111.kb", "Failed, The spinner has the bug!")
EndIf

