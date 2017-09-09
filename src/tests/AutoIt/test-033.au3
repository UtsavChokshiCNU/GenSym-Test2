;--If G2 server is running Then close it
if WinExists("Gensym G2 Real-Time Rule Engine - Server") Then
	WinKill("Gensym G2 Real-Time Rule Engine - Server");
EndIf
;--Start G2 server
Run("C:\G2\dst\g2\opt\g2.exe -ok C:\G2\license\g2sitev83.ok");
WinWait("Gensym G2 Real-Time Rule Engine - Server");
WinActivate("Gensym G2 Real-Time Rule Engine - Server");
WinWaitActive("Gensym G2 Real-Time Rule Engine - Server");
sleep(1000);
;--When G2 server started,start twng.exe
Run("C:\G2\dst\twng\opt\twng.exe localhost 1111 -log c:\log_twng_1111.log", "", @SW_MAXIMIZE);
WinWait("Telewindows Client from SBCL!");
WinActivate("Telewindows Client from SBCL!");
WinWaitActive("Telewindows Client from SBCL!");
;--Make sure that G2 Server is mapped on kbs\sources
Sleep(1000);
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
if WinExists("Telewindows Client from SBCL!","G2") Then
    ControlClick("G2","","Button1");
endif
Sleep(1000);
Send("{TAB}");
Sleep(1000);
if WinExists("Telewindows Client from SBCL!","G2") Then
    ControlClick("G2","","Button1");
endif
Sleep(1000);
Send("{TAB}");
Sleep(1000);
if WinExists("Telewindows Client from SBCL!","G2") Then
    ControlClick("G2","","Button1");
endif
Sleep(1000);
Send("{TAB}");
Sleep(1000);
if WinExists("Telewindows Client from SBCL!","G2") Then
    ControlClick("G2","","Button1");
endif
Sleep(1000);
Send("{TAB}");
Sleep(1000);
if WinExists("Telewindows Client from SBCL!","G2") Then
    ControlClick("G2","","Button1");
endif
Sleep(1000);
Send("{ENTER}");
Sleep(1000);
if WinExists("Telewindows Client from SBCL!","G2") Then
    ControlClick("G2","","Button1");
endif
Sleep(2000);
Send("{HOME}");
Sleep(1000);
ControlSetText("Telewindows Client from SBCL!","Text Editor for the module-search-path of SERVER-PARAMETERS","Scintilla1",'"C:\g2\src\gdanol\gda\kbs\", "C:\g2\src\gdanol\common\kbs\", "C:\g2\src\tests\","C:\g2\src\g2i\kbs\", "C:\g2\src\kbs\","C:\g2\src\g2db\kbs\","C:\g2\src\java\products\javalink\kbs\"');
Sleep(1000);
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
ControlSetText("Load KB","","Edit1","C:\G2\src\tests\error-on-start-v83r0.kb");
Sleep(1000);
WinActivate("Load KB");
ControlClick("Load KB","","Button2");

;--After load KB:error-on-start-v83r0.kb
WinActivate("Telewindows Client from SBCL!");
WinWaitActive("Telewindows Client from SBCL!");
$testws=WinExists("Telewindows Client from SBCL!","ERROR-ON-START-WKSP");
While $testws==0
	sleep(1000);
	$testws=WinExists("Telewindows Client from SBCL!","ERROR-ON-START-WKSP");
WEnd
Sleep(1000);
;--Run->Start
Send("!r");
Sleep(1000);
Send("s");

Sleep(4000);
$pos=WinGetPos("Telewindows Client from SBCL!");
MouseClick("left", ($pos[2]-345)*0.5-50,$pos[3]*0.6, 1);
Sleep(1000);
$Error=WinExists("Telewindows Client from SBCL!","Error Queue");
While $Error==0
	sleep(1000);
	$Error=WinExists("Telewindows Client from SBCL!","Error Queue");
WEnd
Sleep(2000);



