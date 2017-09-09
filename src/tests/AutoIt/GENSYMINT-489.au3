#cs ----------------------------------------------------------------------------

 AutoIt Version: 3.3.6.1
 Author:         Sencom

 Script Function:
	Template AutoIt script.

#ce ----------------------------------------------------------------------------


;-- If G2 server is running Then close it
If ProcessExists ("g2.exe") Then
	ProcessClose ("g2.exe")
EndIf

Dim $srcbox, $dstbox, $g2_dir, $g2_exe_path, $license, $module_search_path

EnvSet("GENSYMDIR", "C:\G2")
$gensym_dir = EnvGet("GENSYMDIR")
EnvSet("SRCBOX", $gensym_dir & "\src")
EnvSet("DSTBOX", $gensym_dir & "\dst")

;-- Obtaining SRCBOX and DSTBOX
$srcbox = EnvGet("SRCBOX")
$dstbox = EnvGet("DSTBOX")
$g2_dir = $dstbox & "\g2\opt"
$g2_path = $srcbox & "\scripts\nt\StartServer.bat -kb " & $srcbox & "\tests\AutoIt\kbs\twng-grid-view-test.kb"
$twng_path = $dstbox & "\twng\opt\twng.exe"


;-- Start G2 server
Run($g2_path, $gensym_dir)
WinWait("G2 Server (development mode)")
WinActivate("G2 Server (development mode)")
WinWaitActive("G2 Server (development mode)")
sleep(1000)

;-- When G2 server started,start twng.exe
Run($twng_path)
WinWait("Telewindows Client")
WinActivate("Telewindows Client")
WinWaitActive("Telewindows Client")

;--Start kb
Send("!rs")

;-- Get control content
;-- Because the MFCGridCtrl is not an normal control,
;---- so the AutoIt haven't provid a function that can get gridctrl's
;---- content directly. We must use an ugly way to get it.
WinWait("Dialog Title")
WinActivate("Dialog Title")
WinWaitActive("Dialog Title")

;-- Clear clip
$column1 = "NULL"
$column2 = "NULL"
ClipPut($column1)

;-- Select center cell
ControlClick("Dialog Title", "", "[CLASS:MFCGridCtrl]")
;-- Get the first column, first row's content use copy methord
Send("{up}{up}{left}{left}^c")
Sleep(100)
$column1 = ClipGet()
;-- Get the second column, first row's content use copy methord
Send("{right}^c")
Sleep(100)
$column2 = ClipGet()

;-- If the two column have content, success, else, failed
If $column1 = "Mary" And $column2 = "Campione" Then
	MsgBox(0, "Result", "Success")
Else
	$result = "Failed, current col1 = [" & $column1 & "] and col2 = [" & $column2 & "]."
	MsgBox(0, "Result", $result)
EndIf


;-- Clean up
if WinExists("G2 Server (development mode)") Then
	WinKill("G2 Server (development mode)")
EndIf