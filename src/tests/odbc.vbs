Const HKEY_LOCAL_MACHINE = &H80000002

strComputer = "."
 
Set objReg=GetObject("winmgmts:{impersonationLevel=impersonate}!\\" & _ 
    strComputer & "\root\default:StdRegProv")
 
strKeyPath = "SOFTWARE\ODBC\ODBC.INI\ODBC Data Sources"
strValueName = "TestBridges"
strValue = "SQL Server"
objReg.SetStringValue HKEY_LOCAL_MACHINE,strKeyPath,strValueName,strValue
 
strKeyPath = "SOFTWARE\ODBC\ODBC.INI\TestBridges"

objReg.CreateKey HKEY_LOCAL_MACHINE,strKeyPath

strKeyPath = "SOFTWARE\ODBC\ODBC.INI\TestBridges"

strValueName = "Database"
strValue = "TestBridges"
objReg.SetStringValue HKEY_LOCAL_MACHINE,strKeyPath,strValueName,strValue
 
strValueName = "Driver"
strValue = "C:\WINDOWS\System32\SQLSRV32.dll"
objReg.SetStringValue HKEY_LOCAL_MACHINE,strKeyPath,strValueName,strValue

strValueName = "Server"
strValue = "(local)"
objReg.SetStringValue HKEY_LOCAL_MACHINE,strKeyPath,strValueName,strValue

strValueName = "Trusted_Connection"
strValue = "Yes"
objReg.SetStringValue HKEY_LOCAL_MACHINE,strKeyPath,strValueName,strValue