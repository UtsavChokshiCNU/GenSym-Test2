#cs ----------------------------------------------------------------------------

 AutoIt Version: 3.3.6.1
 Author:  Sencom

 Script Function:
	Template AutoIt script.

#ce ----------------------------------------------------------------------------
; Make sure the screen is 1024*768
; Script Start - Add your code below here
#include <Process.au3>
Run("C:\G2\src\scripts\nt\StartServer.bat -kb C:\G2\src\tests\AutoIt\kbs\twng-tree-view-3.kb","C:\G2\src\scripts\nt")
Sleep(2000)
Run("C:\G2\dst\twng\opt\twng.exe","",@SW_MAXIMIZE)
Sleep(2000)
MouseClick("left",166,194)
Sleep(2000)
MouseWheel("up", 3)
Sleep(2000)
MouseClick("left",240,128)
Sleep(2000)
$var = PixelGetColor(64, 313)
If $var = 0xFFFFFF Then
MsgBox(4096, "Message", "The test is failed")
EndIf

ProcessClose("g2.exe")


	




