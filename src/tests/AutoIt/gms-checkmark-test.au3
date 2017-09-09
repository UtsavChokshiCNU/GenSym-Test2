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
WinWait("Telewindows Client from SBCL!");
WinActivate("Telewindows Client from SBCL!");
WinWaitActive("Telewindows Client from SBCL!");
;--Make sure that G2 Server is mapped on kbs\sources
Sleep(5000);
Send("!e");
$editmenu=WinExists("Edit");
While $editmenu==0
	sleep(1000);
	$editmenu=WinExists("Edit");
WEnd

Sleep(1000);
Send("s");
Sleep(100);
Send("s");
Sleep(100);
Send("s");
Sleep(100);
Send("s");
Sleep(100);
Send("{ENTER}");
Sleep(1000);
Send("{TAB}");
Sleep(100);
Send("{TAB}");
Sleep(100);
Send("{TAB}");
Sleep(100);
Send("{TAB}");
Sleep(100);
Send("{TAB}");
Sleep(100);
Send("{ENTER}");
Sleep(2000);
Send("{HOME}");
Sleep(1000);
ControlSend("Telewindows Client from SBCL!","Text Editor for the module-search-path of SERVER-PARAMETERS","",'"c:\g2\src\kb\sources"');
Sleep(500);
Send("^+{ENTER}");
Sleep(1000);
Send("{ESC}");
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
ControlSetText("Load KB","","Edit1","C:\G2\src\tests\lz-htwos.kb");
Sleep(1000);
WinActivate("Load KB");
ControlClick("Load KB","","Button2");
;--After load KB:gms-checkmark-test.kb
WinActivate("Telewindows Client from SBCL!");
WinWaitActive("Telewindows Client from SBCL!");
$testws=WinExists("Telewindows Client from SBCL!","CHECKMARK-TEST-WS");
While $testws==0
	sleep(1000);
	$testws=WinExists("Telewindows Client from SBCL!","CHECKMARK-TEST-WS");
WEnd
Sleep(1000);
;--Run->Start
Send("!r");
Sleep(1000);
Send("s");
While $loadkb==0
	sleep(1000);
	$loadkb=WinExists("Options");
WEnd
ControlClick("Telewindows Client from SBCL!","","Options");
pos = ControlGetPos("Telewindows Client from SBCL!", "", "Sub menu");
$coord = PixelSearch( $pos[0]-10, $pos[1], $pos[0], $pos[1]+$pos[3], 0x00000, 10 )
If Not @error Then
	$testfinish=1;
EndIf
;--Test finished,then Run->Pause
WinActivate("Telewindows Client from SBCL!");
WinWaitActive("Telewindows Client from SBCL!");
Sleep(1000);
Send("{PAUSE}");
Sleep(1000);
$pause=WinGetText("Telewindows Client from SBCL!","Menu Bar");
;--Wait 5 seconds
WinActivate("Telewindows Client from SBCL!");
WinWaitActive("Telewindows Client from SBCL!");
$i=5;
While $i>0
	SplashTextOn("5seconds Count down","Time Remaining: "&$i,200,100,-1,-1,32);
	Sleep(1000);
	$i=$i-1;
WEnd
SplashOff();
;--Check Resume
WinActivate("Telewindows Client from SBCL!");
WinWaitActive("Telewindows Client from SBCL!");
$pos=WinGetPos("Telewindows Client from SBCL!");
$posx=$pos[2]/2;
MouseClick("left",$posx,35);
sleep(100);
Send("!r");
Sleep(100);
Send("r");
Sleep(100);
Send("{ENTER}");
Sleep(2000);
$resume=WinGetText("Telewindows Client from SBCL!","Menu Bar");
$compare=StringCompare($pause,$resume);
If $compare<>0 Then
	MsgBox(0+64,"Check resume","Resume is enabled");
	Send("{PAUSE}");
	Sleep(1000);
Else
	MsgBox(0+16,"Check resume","Resume is not enabled");
EndIf
MouseClick("left",$posx,35);
sleep(100);
Send("!r");