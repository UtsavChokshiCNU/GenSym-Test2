;--If G2 server is running Then close it
if WinExists("Gensym G2 Real-Time Rule Engine - Server") Then
	WinKill("Gensym G2 Real-Time Rule Engine - Server");
EndIf
Dim $srcbox, $dstbox, $g2_dir, $g2_exe_path, $license, $module_search_path;

EnvSet("SRCBOX", "C:\g2\src\");
EnvSet("DSTBOX", "C:\g2\dst");

;--Obtaining SRCBOX and DSTBOX
$srcbox = EnvGet("SRCBOX");
$dstbox = EnvGet("DSTBOX");
$license = " -ok " & $dstbox & "\..\license\g2sitev83.ok";
$module_search_path = " -module-search-path ""'" & $srcbox & "\kbs\' '" & $srcbox & "\tests\'""";
$g2_dir = $dstbox & "\g2\opt\";
$g2_exe_path = $g2_dir & "g2.exe";
$twng_path = $dstbox & "\twng\opt\twng.exe localhost 1111";

If FileExists($g2_dir & "error_report.txt") Then
	FileDelete ($g2_dir & "error_report.txt");
EndIf

;-- Copy error-sender to g2 directory
FileCopy ($srcbox & "tests\AutoIt\error_sender.exe", $g2_dir & "error_sender.exe", 9);

;--Start G2 server
Run($g2_exe_path & $license & $module_search_path, $g2_dir);
WinWait("Gensym G2 Real-Time Rule Engine - Server");
WinActivate("Gensym G2 Real-Time Rule Engine - Server");
WinWaitActive("Gensym G2 Real-Time Rule Engine - Server");
sleep(1000);

;--When G2 server started,start twng.exe
Run($twng_path);
WinWait("Telewindows Client from SBCL!");
WinActivate("Telewindows Client from SBCL!");
WinWaitActive("Telewindows Client from SBCL!");

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
ControlSetText("Load KB","","Edit1", $srcbox & "tests\AutoIt\kbs\abort.kb");
Sleep(1000);
WinActivate("Load KB");
ControlClick("Load KB","","Button2");
;--After load KB
WinActivate("Telewindows Client from SBCL!");
WinWaitActive("Telewindows Client from SBCL!");

$abort=WinExists("G2");
While $abort==0
	sleep(1000);
	$abort=WinExists("G2");
WEnd

;-- Click on the Send report button
sleep(5000);
ControlClick("G2","" ,"Button2");
sleep(3000);

;--Check if error report exists
If FileExists($g2_dir & "error_report.txt") Then
    MsgBox(4096, "error_report.txt", "error_report.txt Exists");
Else
    MsgBox(4096,"error_report.txt", "error_report.txt Does NOT exists")
EndIf

;-- Clean up
If ProcessExists ("error_sender.exe") Then
	ProcessWaitClose ("error_sender.exe")
EndIf	

FileDelete ($g2_dir & "error_sender.exe");
FileDelete ($g2_dir & "error_report.txt");
if WinExists("Gensym G2 Real-Time Rule Engine - Server") Then
	WinKill("Gensym G2 Real-Time Rule Engine - Server");
EndIf