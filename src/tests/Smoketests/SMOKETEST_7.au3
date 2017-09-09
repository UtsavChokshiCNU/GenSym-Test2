;--If G2 server is running Then close it
if WinExists("G2 Server (development mode)") Then
	WinKill("G2 Server (development mode)");
EndIf
;--Start G2 server
$startbat='"C:\G2\src\scripts\nt\StartServer.bat"'

;--$result = RegWrite("HKEY_CURRENT_USER\Environment", "G2_AUTO_TEST", "REG_SZ", 'C:\results');
Run(@ComSpec & ' /c '  & $startbat, 'C:\\G2\\src\\scripts\\nt\\')

WinWait("G2 Server (development mode)");
WinActivate("G2 Server (development mode)");
WinWaitActive("G2 Server (development mode)");
sleep(5000);
;--When G2 server started,start twng.exe
Run("C:\G2\dst\twng\opt\twng.exe localhost 1111 -log c:\log_twng_1111.log", "", @SW_MAXIMIZE);
WinWait("Telewindows Client");
WinActivate("Telewindows Client");
WinWaitActive("Telewindows Client");
;--When twng.exe started,load KB
Send("^o");
$loadkb=WinExists("Load KB");
While $loadkb==0
	sleep(2000);
	$loadkb=WinExists("Load KB");
WEnd
WinWait("Load KB");
WinActivate("Load KB");
WinWaitActive("Load KB");
Sleep(2000);
ControlSetText("Load KB","","Edit1","C:\g2\src\tests\examplekbs\g2i\rethink-40-online-examples.kb");
Sleep(2000);
WinActivate("Load KB");
ControlClick("Load KB","","Button2");
;--Run->Start
Sleep(15000);
Send("!r");
Sleep(2000);
Send("s");
Sleep(120000);
;$testfinish=WinExists("Telewindows Client","Property");
;--Test finished,then Run->Pause
;--WinKill("Telewindows Client");
;--WinKill("G2 Server (development mode)");

;--ProcessClose("twng.exe");
;--ProcessClose("G2.exe");