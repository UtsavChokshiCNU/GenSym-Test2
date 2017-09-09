VERSION 5.00
Object = "{42B6C7E0-06C1-11D2-8698-00008618F471}#1.0#0"; "AXClient.dll"
Begin VB.Form FrmT2Workspace 
   Caption         =   "set at runtime"
   ClientHeight    =   4575
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6270
   Icon            =   "FrmT2Workspace.frx":0000
   LinkTopic       =   "Form1"
   MDIChild        =   -1  'True
   ScaleHeight     =   4575
   ScaleWidth      =   6270
   Begin GensymTw2Ctl.G2ItemHolder Holder 
      Left            =   5520
      OleObjectBlob   =   "FrmT2Workspace.frx":0442
      Top             =   3840
   End
   Begin GensymTw2Ctl.G2WorkspacePanel Panel 
      Height          =   4575
      Left            =   0
      OleObjectBlob   =   "FrmT2Workspace.frx":049C
      TabIndex        =   0
      Top             =   0
      Width           =   6255
   End
End
Attribute VB_Name = "FrmT2Workspace"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Resize()
    If Height > 400 Then Panel.Height = Height - 400
   
    If Width > 120 Then Panel.Width = Width - 120
End Sub

Private Sub Form_Unload(Cancel As Integer)
    MDIT2Window.RemoveWorkspaceWindow Me
End Sub

Private Sub Holder_ItemDeleted()
    Unload Me
End Sub

