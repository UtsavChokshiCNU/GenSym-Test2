VERSION 5.00
Object = "{42B6C7E0-06C1-11D2-8698-00008618F471}#2.0#0"; "AXClient.dll"
Begin VB.Form MainForm 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "VB Demo"
   ClientHeight    =   6600
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   7590
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   6600
   ScaleWidth      =   7590
   StartUpPosition =   3  'Windows Default
   Begin GensymTw2Ctl.G2WorkspacePanel G2WorkspacePanel1 
      Height          =   4215
      Left            =   240
      OleObjectBlob   =   "MainForm.frx":0000
      TabIndex        =   3
      Top             =   1440
      Width           =   7095
   End
   Begin GensymTw2Ctl.G2UiGateway G2UiGateway1 
      Left            =   6480
      OleObjectBlob   =   "MainForm.frx":0066
      Top             =   840
   End
   Begin GensymTw2Ctl.G2ItemHolder G2ItemHolder1 
      Left            =   2880
      OleObjectBlob   =   "MainForm.frx":013E
      Top             =   840
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Fetch Total Parts Processed"
      Height          =   495
      Left            =   960
      TabIndex        =   1
      Top             =   840
      Width           =   1575
   End
   Begin VB.Label Label2 
      Caption         =   $"MainForm.frx":01C0
      Height          =   615
      Left            =   600
      TabIndex        =   2
      Top             =   5760
      Width           =   6615
   End
   Begin VB.Label Label1 
      Caption         =   $"MainForm.frx":027C
      Height          =   375
      Left            =   240
      TabIndex        =   0
      Top             =   240
      Width           =   7095
   End
End
Attribute VB_Name = "MainForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
  MsgBox G2ItemHolder1.Attribute("total-part-processed")
End Sub
