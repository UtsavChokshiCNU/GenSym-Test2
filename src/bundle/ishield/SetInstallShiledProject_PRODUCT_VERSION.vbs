'/////////////////////////////////////////////////////////////////////////////
'  
'  Update the PRODUCT_VERSION string in an InstallShield project
'
'  Usage:  To use the objects in this script, make sure you have the
'          following items in place on your system:
'          1. InstallShield must be installed so that
'             the end-user automation is available.
'          2. You must have Windows Scripting Host (Wscript.exe) installed.
'			  InstallShield only installs 32-bit COM components, so on 64 bit OS
'			  you need to run 32-bit wscript.exe from `syswow64`
'          3. The script expects the following command-line arguments, in order:
'             a. The fully qualified path to an existing .ism file.
'             b. The full string value to be set
'
'  Remark:  This could be rewritten in Java using jacob or jawin to avoid having
'  			another programming language.
'/////////////////////////////////////////////////////////////////////////////
  
If Wscript.Arguments.Count < 1 Then
    Wscript.Echo "InstallShield PRODUCT_VERSION string updated" & _
        vbNewLine & "1st argument is the full path to the .ism file" & _
        vbNewLine & "2nd argument is the full string to set for PRODUCT_VERSION"
    Wscript.Quit 1
End If
 
' Create the end-user automation object
Dim ISWIProject
' As InstallShield version go up, so does the number after `IswiAuto`.
' For IS2013 it's 20, for IS2014 it's 21, etc.
Set ISWIProject = CreateObject("IswiAuto20.ISWiProject"): CheckError
 
' Open the project specified at the command line
ISWIProject.OpenProject Wscript.Arguments(0): CheckError

' Change the product version string
' Here we assume that the first language would be the ony having PRODUCT_VERSION
' string, which should hold in general, but, this could be improveds
ISWIProject.ISWiLanguages.Item(1).ISWiStringEntries.Item("PRODUCT_VERSION").Value = Wscript.Arguments(1)
 
' Save and close the project
ISWIProject.SaveProject: CheckError
ISWIProject.CloseProject: CheckError
 

'/////////////////////////////////////////////////////////////////////////////
Sub CheckError()
    Dim message, errRec
    If Err = 0 Then Exit Sub
    message = Err.Source & " " & Hex(Err) & ": " & Err.Description
    Wscript.Echo message
    Wscript.Quit 2
End Sub