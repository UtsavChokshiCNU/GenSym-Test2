VERSION 5.00
Object = "{42B6C7E0-06C1-11D2-8698-00008618F471}#2.0#0"; "AXClient.dll"
Begin VB.Form WorkspacePanelForm 
   Caption         =   "PanelTest"
   ClientHeight    =   6705
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8760
   LinkTopic       =   "Form1"
   ScaleHeight     =   6705
   ScaleWidth      =   8760
   StartUpPosition =   3  'Windows Default
   Begin GensymTw2Ctl.G2UiGateway G2UiGateway1 
      Left            =   360
      OleObjectBlob   =   "AutoLoadWSTest.frx":0000
      Top             =   6120
   End
   Begin GensymTw2Ctl.G2WorkspacePanel G2WorkspacePanel1 
      Height          =   5655
      Left            =   360
      OleObjectBlob   =   "AutoLoadWSTest.frx":00E0
      TabIndex        =   0
      Top             =   240
      Width           =   8175
   End
End
Attribute VB_Name = "WorkspacePanelForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub G2WorkspacePanel1_SelectionChanged()
    MsgBox "The workspace panel selection has changed"
End Sub
