VERSION 5.00
Object = "{AC4C85D1-B16C-11D1-A718-006008C5F933}#2.0#0"; "G2Com.dll"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command1 
      Caption         =   "Command1"
      Height          =   375
      Left            =   2040
      TabIndex        =   1
      Top             =   120
      Width           =   1095
   End
   Begin VB.TextBox StartItem 
      Height          =   375
      Left            =   120
      TabIndex        =   0
      Text            =   "Text1"
      Top             =   120
      Width           =   1695
   End
   Begin GensymAxlCtl.G2Gateway G2Gateway1 
      Left            =   1680
      OleObjectBlob   =   "Form1.frx":0000
      Top             =   1680
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Form_Load()
G2Gateway1.G2Location = "pc1:1122"

End Sub

