VERSION 5.00
Object = "{AC4C85D1-B16C-11D1-A718-006008C5F933}#2.0#0"; "G2Com.dll"
Begin VB.Form TC9Form 
   Caption         =   "Test Case 9:  Connecting with G2 on Startup (Using G2 ActiveXLink with Microsoft Visual Basic)"
   ClientHeight    =   3195
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form2"
   ScaleHeight     =   3195
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.Timer Timer1 
      Interval        =   10
      Left            =   360
      Top             =   2520
   End
   Begin VB.Label TC9FormStatus 
      Caption         =   "Status:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   735
      Left            =   240
      TabIndex        =   0
      Top             =   360
      Width           =   3255
   End
   Begin GensymAxlCtl.G2Gateway TC9G2Gateway 
      Left            =   1080
      OleObjectBlob   =   "TC9Form.frx":0000
      Top             =   1320
   End
End
Attribute VB_Name = "TC9Form"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public G2Location As String
Public Wait As Boolean
Public IsConnected As Boolean

Private Sub Form_Load()
  TC9G2Gateway.Disconnect
  TC9FormStatus.Caption = "Status: Wait Connection"
  TC9G2Gateway.G2Location = G2Location
  IsConnected = False
  TC9G2Gateway.Connect (Wait)

End Sub





Private Sub TC9G2Gateway_G2Connected()
  IsConnected = True
  
End Sub

Private Sub Timer1_Timer()
If IsConnected = True Then
   TC9FormStatus.Caption = "Status: Connected"
Else
   TC9FormStatus.Caption = "Status: Wait Connection"
   End If
End Sub
