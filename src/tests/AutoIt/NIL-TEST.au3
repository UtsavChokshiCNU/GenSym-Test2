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
ControlSetText("Load KB","","Edit1","C:\G2\src\tests\NIL-TEST.kb");
Sleep(1000);
WinActivate("Load KB");
ControlClick("Load KB","","Button2");

;--After load KB:NIL-TEST.kb
WinActivate("Telewindows Client");
WinWaitActive("Telewindows Client");
$testws=WinExists("Telewindows Client","SHUTDOWN");
While $testws==0
	sleep(1000);
	$testws=WinExists("Telewindows Client","SHUTDOWN");
WEnd
Sleep(1000);
;--Run->Start
Send("!r");
Sleep(1000);
Send("s");

Sleep(10000);
If FileExists("C:\G2\src\tests\AutoIt\NIL") Then
    MsgBox(4096, "NIL File", "Exists")
Else
    MsgBox(4096,"NIL File", "Does NOT exists")
EndIf

