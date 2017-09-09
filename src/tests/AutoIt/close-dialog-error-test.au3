;--After load KB:NIL-TEST.kb
WinActivate("Telewindows Client");
WinWaitActive("Telewindows Client");
$testws=WinExists("Example Dialog");
While $testws==0
	sleep(1000);
	$testws=WinExists("Example Dialog");
WEnd
Sleep(1000);

$winsize = WinGetPos("Example Dialog")


$editsize = ControlGetPos("Example Dialog","","Edit1")


;MsgBox(0, "Active window stats (x,y,width,height):", $editsize[0] & " " & $editsize[1] & " " & $editsize[2] & " " & $editsize[3])


MouseClick("left", $winsize[0] + $editsize[0] + 10, $winsize[1] + $editsize[1]+50, 2)

Sleep(20);

MouseClick("left", $winsize[0]+$winsize[2]-5, $winsize[1]+5, 2)







