Opt("WinDetectHiddenText", 0)   ;0=don't detect, 1=do detect
Opt("WinSearchChildren", 1)     ;0=no, 1=search children also
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
;--Make sure that twng is started
Sleep(5000);
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
ControlSetText("Load KB","","Edit1","C:\G2\src\g2i\sites\ReThink\kbs\aero.kb");
Sleep(1000);
WinActivate("Load KB");
ControlClick("Load KB","","Button2");
;--After load KB:aero.kb
WinActivate("Telewindows Client");
WinWaitActive("Telewindows Client");
Sleep(1000);
;--Try to get Simulation window
$testws=WinExists("Simulation");
$waittimes=0;
While $testws==0
	$waittimes=$waittimes+1;
	If $waittimes==500 Then 
		ExitLoop
	EndIf
	sleep(1000);
	$testws=WinExists("Simulation");
WEnd

If $testws==0 Then
	MsgBox(4096, "Test Navigator pane", "Failed")
Else
	MsgBox(4096, "Test Navigator pane", "Success")
EndIf


if WinExists("G2 ReThink Server") Then
	WinKill("G2 ReThink Server");
EndIf

