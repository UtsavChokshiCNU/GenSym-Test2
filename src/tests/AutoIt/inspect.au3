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
Run("C:\G2\dst\twng\opt\twng.exe localhost 1111", "", @SW_MAXIMIZE);
WinWait("Telewindows Client");
WinActivate("Telewindows Client");
WinWaitActive("Telewindows Client");

Send("!t");
$editmenu=WinExists("Tools");
While $editmenu==0
	sleep(50);
	$editmenu=WinExists("Tools");
WEnd
Sleep(1000);
Send("{ENTER}");
Sleep(2000);

$sizeBefore = ControlGetPos ("Telewindows Client", "Text Editor for Inspect Command", "Scintilla1");

Send("s");
Sleep(100);
Send("h");
Sleep(100);
Send("o");
Sleep(100);
Send("w");
Sleep(100);
Send("{SPACE}");
Sleep(100);
Send("o");
Send("n");
Send("{SPACE}");
Send("a");
Send("{SPACE}");
Send("w");
Send("o");
Send("r");
Send("k");
Send("s");
Send("p");
Send("a");
Send("c");
Send("e");
$sizeAfter = ControlGetPos ("Telewindows Client", "Text Editor for Inspect Command", "Scintilla1");
If $sizeAfter[2] <> $sizeBefore[2] OR $sizeAfter[3] <> $sizeBefore[3] Then
MsgBox(0, "Test result" ,"Failure");
Else
MsgBox(0, "Test result", "Pass");
EndIf
Sleep(2000);



