' CreateSampleDB.vbs : script help to create sample Microsoft Access database.
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

' Sample database file name
Const SampleDBName = "SampleDB.mdb"

Sub PopulateSampleDatabase(FileName)
Dim DS
Dim Con
Dim v

	' Datasource connection string
	DS = "Provider=Microsoft.Jet.OLEDB.4.0;" & _
     "Jet OLEDB:Engine Type=" & Format & _
    ";Data Source=" & FileName

	' Populate the sample tables
	Set Con = CreateObject("ADODB.Connection")
	Con.Open DS
	v = 1
	For i = 21 to 300000
		qry = "INSERT INTO [Table1] VALUES(" & CStr(i) & ",'Value" & CStr(v) & "','Value" & CStr(v + 1) & _
		"','Value" & CStr(v + 2) & "','Value" & CStr(v + 3) & "','Value" & CStr(v + 4) & "','Value" & CStr(v + 5) & "')"
		Con.Execute qry
		v = v + 6
	Next

	Con.Close
	Set Con = Nothing
End Sub

PopulateSampleDatabase SampleDBName
