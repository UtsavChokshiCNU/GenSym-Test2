' PopulateSampleDB.vbs : script help to create sample Microsoft Access database.
'
' This file is a part of the samples of XTREME MFC class library.
' (c)1998-2011 Codejock Software, All Rights Reserved.
'
' THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
' RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
' CONSENT OF CODEJOCK SOFTWARE.
'
' THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
' IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
' YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
' SINGLE COMPUTER.
'
' CONTACT INFORMATION:
' support@codejock.com
' http://www.codejock.com
'--------------------------------------------------------------------------

' Constants for using ADOX database creation

Const Jet10 = 1
Const Jet11 = 2
Const Jet20 = 3
Const Jet3x = 4
Const Jet4x = 5

' Constants for using  DAO database creation

Const dbVersion10 = 1
Const dbVersion11 = 8
Const dbVersion20 = 16
Const dbVersion30 = 32
Const dbVersion40 = 64

' Sample database file name
Const SampleDBName = "SampleDB.mdb"

' Create a new Microsoft Access database using ADOX

Sub CreateSampleDatabase_ADOX(FileName, Format)
  Dim Catalog
  Dim Table1, Table2
  Dim Con
  Dim DS
  Dim i
  Dim v
  Dim qry
  Dim objWMIService
  Dim colSoftware
  Dim objSoftware
  Dim RS

	' Datasource connection string
	DS = "Provider=Microsoft.Jet.OLEDB.4.0;" & _
     "Jet OLEDB:Engine Type=" & Format & _
    ";Data Source=" & FileName

	' Create new database file
  Set Catalog = CreateObject("ADOX.Catalog")
  Catalog.Create DS

	' Create the sample table1
	Set Table1 = CreateObject("ADOX.Table")
	Table1.Name = "Table1"
	Table1.Columns.Append "Id", 3
	For i = 0 to 5
		Table1.Columns.Append "Field" & CStr(i), 202, 30
	Next
	Table1.Keys.Append "PK", 1, "Id"
	Catalog.Tables.Append Table1

	' Create the sample table, gethering installed software
	Set Table2 = CreateObject("ADOX.Table")
	Table2.Name = "SoftwareInventory"
	Table2.Columns.Append "Caption", 202, 250
	Table2.Columns.Append "Vendor", 202, 250
	Table2.Columns.Append "Version", 202, 250
	Table2.Columns.Append "PackageCache", 202, 250
	Table2.Columns.Append "Description", 202, 250
	Catalog.Tables.Append Table2

	Set Catalog = Nothing

	' Populate the sample tables
	Set Con = CreateObject("ADODB.Connection")
	Con.Open DS
	v = 1
	For i = 0 to 20
		qry = "INSERT INTO [Table1] VALUES(" & CStr(i) & ",'Value" & CStr(v) & "','Value" & CStr(v + 1) & _
		"','Value" & CStr(v + 2) & "','Value" & CStr(v + 3) & "','Value" & CStr(v + 4) & "','Value" & CStr(v + 5) & "')"
		Con.Execute qry
		v = v + 6
	Next

	' Use Microsoft WMI data provider
	Set objWMIService = GetObject("winmgmts:{impersonationLevel=impersonate}!\\.\root\cimv2")
	Set colSoftware = objWMIService.ExecQuery("Select * from Win32_Product")
	Set RS = CreateObject("ADODB.Recordset")
	RS.CursorType = 3
	RS.LockType = 3
	RS.Open "SoftwareInventory", Con
	RS.AddNew
		RS.Fields("Caption").Value = "TEST STRING WITH" & vbCrLf & "NEW LINE CHARACTERS"
		RS.Fields("Description").Value =  "TEST STRING WITH" & vbCrLf & "NEW LINE CHARACTERS"
		RS.Fields("PackageCache").Value =  "TEST STRING WITH" & vbCrLf & "NEW LINE CHARACTERS"
		RS.Fields("Vendor").Value =  "TEST STRING WITH" & vbCrLf & "NEW LINE CHARACTERS"
		RS.Fields("Version").Value =  "TEST STRING WITH" & vbCrLf & "NEW LINE CHARACTERS"
	For Each objSoftware in colSoftware
		RS.AddNew
		RS.Fields("Caption").Value = objSoftware.Caption
		RS.Fields("Description").Value =  objSoftware.Description
		RS.Fields("PackageCache").Value =  objSoftware.PackageCache
		RS.Fields("Vendor").Value =  objSoftware.Vendor
		RS.Fields("Version").Value =  objSoftware.Version
	Next
	RS.Update
	RS.Close
	Con.Close
	Set Con = Nothing
End Sub

' Create a new Microsoft Access database using DAO

Sub CreateNewMDB_DAO(FileName, Format)
  Dim Engine 
  Set Engine = CreateObject("DAO.DBEngine.36")
  Engine.CreateDatabase FileName, ";LANGID=0x0409;CP=1252;COUNTRY=0", Format
End Sub

' Create Microsoft Access sample database using DAO
' CreateNewMDB_DAO SampleDBName, dbVersion40

' Create Microsoft Access sample database using ADOX
CreateSampleDatabase_ADOX SampleDBName, Jet4x
