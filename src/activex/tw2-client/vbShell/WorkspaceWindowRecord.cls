VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "WorkspaceWindowRecord"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Attribute VB_Ext_KEY = "SavedWithClassBuilder6" ,"Yes"
Attribute VB_Ext_KEY = "Top_Level" ,"Yes"

Option Explicit

'local variable(s) to hold property value(s)
Private mvarFormObj As Form 'local copy
Private mvarWorkspaceObj As Object 'local copy
Public Property Set WorkspaceObj(ByVal vData As Object)
'used when assigning an Object to the property, on the left side of a Set statement.
'Syntax: Set x.WorkspaceObj = Form1
    Set mvarWorkspaceObj = vData
End Property


Public Property Get WorkspaceObj() As Object
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.WorkspaceObj
    Set WorkspaceObj = mvarWorkspaceObj
End Property



Public Property Set FormObj(ByVal vData As Form)
'used when assigning an Object to the property, on the left side of a Set statement.
'Syntax: Set x.FormObj = Form1
    Set mvarFormObj = vData
End Property


Public Property Get FormObj() As Form
'used when retrieving value of a property, on the right side of an assignment.
'Syntax: Debug.Print X.FormObj
    Set FormObj = mvarFormObj
End Property

