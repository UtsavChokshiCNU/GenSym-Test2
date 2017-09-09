#include-once
#include <GuiMenu.au3>
;#include <GuiToolbar.au3>
#include <WindowsConstants.au3>
#include <WinAPI.au3>
Opt("MustDeclareVars", 1)

Global $gaPopups[1][3] = [[0, 0]]
Global $winapi_gaWinList[2][2] = [[0, 0]]

Func _Lib_PopupGetHwnd($iIndex = 1)
    _Lib_PopupWait()
    Return $gaPopups[$iIndex][0]
EndFunc   ;==>_Lib_PopupGetHwnd

Func _Lib_PopupScan()
    Local $iI, $sClass, $hWnd, $hMenu
    ReDim $gaPopups[1][3]
    $gaPopups[0][0] = 0
    ReDim $winapi_gaWinList[64][2]
    $winapi_gaWinList[0][0] = 0
    $winapi_gaWinList[0][1] = 64
    _WinAPI_EnumWindowsPopup()
    For $iI = 1 To $winapi_gaWinList[0][0]
        $hWnd = $winapi_gaWinList[$iI][0]
        $sClass = $winapi_gaWinList[$iI][1]
        Select
            Case $sClass = "#32768"
                $hMenu = _SendMessage($hWnd, $MN_GETHMENU, 0, 0)
                _Lib_PopupAdd($hMenu, 1, $hWnd)
            Case $sClass = "ToolbarWindow32"
                _Lib_PopupAdd($hWnd, 2, _WinAPI_GetParent($hWnd))
            Case $sClass = "ToolTips_Class32"
                _Lib_PopupAdd($hWnd, 3, _WinAPI_GetParent($hWnd))
        EndSelect
    Next
EndFunc   ;==>_Lib_PopupScan

Func _Lib_PopupWait()
    Local $iLoop = 0
    While $iLoop < 50
        If $gaPopups[0][0] > 0 Then Return
        Sleep(100)
        _Lib_PopupScan()
        $iLoop += 1
    WEnd
    ConsoleWrite("Timeout waiting for popup window to appear" & @CRLF)
EndFunc   ;==>_Lib_PopupWait

Func _Lib_PopupAdd($hWnd, $iType, $hParent)
    Local $iCount
    $gaPopups[0][0] += 1
    $iCount = $gaPopups[0][0]
    ReDim $gaPopups[$iCount + 1][3]
    $gaPopups[$iCount][0] = $hWnd
    $gaPopups[$iCount][1] = $iType
    $gaPopups[$iCount][2] = $hParent
EndFunc   ;==>_Lib_PopupAdd

;--If G2 server is running Then close it
if WinExists("G2 Server (development mode)") Then
	WinKill("G2 Server (development mode)");
EndIf
;--Start G2 server
Run("C:\G2\src\scripts\nt\StartServer.bat");
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
Dim $loadkb
$loadkb=WinExists("Load KB");
While $loadkb==0
	sleep(2000);
	$loadkb=WinExists("Load KB");
WEnd
WinWait("Load KB");
WinActivate("Load KB");
WinWaitActive("Load KB");
Sleep(500);
ControlSetText("Load KB","","Edit1","C:\G2\src\tests\color-menu-test.kb");
Sleep(500);
WinActivate("Load KB");
ControlClick("Load KB","","Button2");
;--Run->Start
Sleep(500);
Send("!r");
Sleep(500);
Send("s");
Sleep(500);
;$testfinish=WinExists("Telewindows Client","Property");
;--Test finished,then Run->Pause
If not WinExists("KB Workspace") Then	
	WinActive("KB Workspace");
	MouseClick("right", 150, 150, 1);
	;MsgBox(0, "x, y", $size[0] & " " & $size[1] & " " & $size[2] & " " & $size[3]);
	Sleep(500);
	Dim $hMenu;
	$hMenu = _Lib_PopupGetHwnd(0);
	Sleep(500);
	Send("c");
	Sleep(500);
	Send("c");
	Sleep(500);
	Send("{ENTER}");
	Sleep(500);
	send("b");
	Sleep(500);

	MsgBox(0, "", "Success");

	Sleep(20000);
	;MsgBox(0, "", "Success")
Else
    MsgBox(0, "", "Failed")
EndIf