VERSION 5.00
Begin VB.Form FrmT2SpecifyWorkspace 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Get Workspace"
   ClientHeight    =   3465
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   5085
   Icon            =   "FrmT2SpecifyWorkspace.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3465
   ScaleWidth      =   5085
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton Command2 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   3480
      TabIndex        =   2
      Top             =   2880
      Width           =   1335
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Get"
      Default         =   -1  'True
      Enabled         =   0   'False
      Height          =   375
      Left            =   240
      TabIndex        =   1
      Top             =   2880
      Width           =   1335
   End
   Begin VB.ListBox List1 
      Height          =   2400
      ItemData        =   "FrmT2SpecifyWorkspace.frx":0442
      Left            =   240
      List            =   "FrmT2SpecifyWorkspace.frx":0444
      Sorted          =   -1  'True
      TabIndex        =   0
      Top             =   240
      Width           =   4575
   End
End
Attribute VB_Name = "FrmT2SpecifyWorkspace"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Command1_Click()
    Dim WorkspaceName As String
    Dim Workspace As G2Item2
  
    WorkspaceName = List1.Text
    Unload Me

    ' Get the workspace and put it in the panel
    Set Workspace = MDIT2Window.G2UiGateway1.GetNamedItem(WorkspaceName, _
        "kb-workspace")
    MDIT2Window.AddWorkspaceWindow Workspace
End Sub

Private Sub showWorkspace(name As String)
End Sub

Private Sub Command2_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    Dim Names As Variant
    Dim i As Integer
  
    List1.Clear
    Names = MDIT2Window.G2UiGateway1.GetNamedWorkspaces
    For i = 0 To UBound(Names)
        List1.AddItem Names(i)
    Next i
End Sub

Private Sub List1_Click()
    Command1.Enabled = True
End Sub

Private Sub List1_DblClick()
    Command1_Click
End Sub
