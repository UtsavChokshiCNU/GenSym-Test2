VERSION 5.00
Object = "{42B6C7E0-06C1-11D2-8698-00008618F471}#1.0#0"; "AXClient.dll"
Begin VB.Form WSSelectionAPIForm 
   Caption         =   "Workspace Selection API Demo"
   ClientHeight    =   6975
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   7830
   LinkTopic       =   "Form1"
   ScaleHeight     =   6975
   ScaleWidth      =   7830
   StartUpPosition =   3  'Windows Default
   Begin GensymTw2Ctl.G2UiGateway G2UiGateway1 
      Left            =   360
      OleObjectBlob   =   "WSSelectionAPI.frx":0000
      Top             =   4560
   End
   Begin GensymTw2Ctl.G2WorkspacePanel G2WorkspacePanel1 
      Height          =   4335
      Left            =   240
      OleObjectBlob   =   "WSSelectionAPI.frx":00E0
      TabIndex        =   0
      Top             =   120
      Width           =   7335
   End
   Begin VB.CommandButton Command12 
      Caption         =   "v"
      Height          =   495
      Left            =   3600
      TabIndex        =   8
      Top             =   6360
      Width           =   495
   End
   Begin VB.CommandButton Command11 
      Caption         =   "<"
      Height          =   495
      Left            =   2640
      TabIndex        =   7
      Top             =   5760
      Width           =   495
   End
   Begin VB.CommandButton Command10 
      Caption         =   "^"
      Height          =   495
      Left            =   3600
      TabIndex        =   6
      Top             =   5160
      Width           =   495
   End
   Begin VB.CommandButton Command9 
      Caption         =   ">"
      Height          =   495
      Left            =   4560
      TabIndex        =   5
      Top             =   5760
      Width           =   495
   End
   Begin VB.CommandButton Command8 
      Caption         =   "Remove MY-OBJECT from WS selection"
      Height          =   615
      Left            =   5520
      TabIndex        =   4
      Top             =   6240
      Width           =   2055
   End
   Begin VB.CommandButton Command7 
      Caption         =   "Add MY-OBJECT to WS selection"
      Height          =   615
      Left            =   5520
      TabIndex        =   3
      Top             =   5160
      Width           =   2055
   End
   Begin VB.CommandButton Command6 
      Caption         =   "Get workspace selection"
      Height          =   615
      Left            =   240
      TabIndex        =   2
      Top             =   6240
      Width           =   1935
   End
   Begin VB.CommandButton Command3 
      Caption         =   "Get TEST-WKSP"
      Height          =   615
      Left            =   240
      TabIndex        =   1
      Top             =   5160
      Width           =   1935
   End
   Begin VB.Label Label2 
      Caption         =   "This project needs the WSSelectionAPI KB to be loaded in G2."
      Height          =   375
      Left            =   1320
      TabIndex        =   10
      Top             =   4560
      Width           =   4935
   End
   Begin VB.Label Label1 
      Caption         =   "Move Selection"
      Height          =   255
      Left            =   3240
      TabIndex        =   9
      Top             =   5880
      Width           =   1215
   End
End
Attribute VB_Name = "WSSelectionAPIForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command3_Click()
    Dim Item As IG2Item

    G2UiGateway1.Connect
    Set Item = G2UiGateway1.GetNamedItem("test-wksp")
    G2WorkspacePanel1.AddWorkspace Item
End Sub

Private Sub Command6_Click()
    Dim Selection As Variant
    Dim Item As IG2Item
    
    Selection = G2WorkspacePanel1.GetSelection
    If Not IsEmpty(Selection) Then
        If UBound(Selection) - LBound(Selection) + 1 > 0 Then
            Set Item = Selection(0)
            MsgBox "First item of selection: " & Item.String
        Else
            MsgBox "No items are selected."
        End If
    Else
        MsgBox "No items are selected."
    End If
End Sub

Private Sub Command7_Click()
    G2WorkspacePanel1.AddElementToSelection (G2UiGateway1.GetNamedItem("my-object"))
End Sub

Private Sub Command8_Click()
G2WorkspacePanel1.RemoveElementFromSelection (G2UiGateway1.GetNamedItem("my-object"))
End Sub

Private Sub Command9_Click()
    G2WorkspacePanel1.MoveSelection 40, 0, True
End Sub

Private Sub Command10_Click()
    G2WorkspacePanel1.MoveSelection 0, -40, True
End Sub
Private Sub Command11_Click()
    G2WorkspacePanel1.MoveSelection -40, 0, True
End Sub
Private Sub Command12_Click()
    G2WorkspacePanel1.MoveSelection 0, 40, True
End Sub

