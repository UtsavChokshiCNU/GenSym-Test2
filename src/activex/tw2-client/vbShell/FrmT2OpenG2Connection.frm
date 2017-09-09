VERSION 5.00
Begin VB.Form FrmT2OpenG2Connection 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Open Connection"
   ClientHeight    =   2280
   ClientLeft      =   3120
   ClientTop       =   2970
   ClientWidth     =   3135
   Icon            =   "FrmT2OpenG2Connection.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2280
   ScaleWidth      =   3135
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox UserMode 
      Height          =   285
      Left            =   1320
      TabIndex        =   6
      Text            =   "set at runtime"
      Top             =   1200
      Width           =   1575
   End
   Begin VB.TextBox PortNumber 
      Height          =   285
      Left            =   1320
      TabIndex        =   3
      Text            =   "1111"
      Top             =   720
      Width           =   1575
   End
   Begin VB.TextBox HostName 
      Height          =   285
      Left            =   1320
      TabIndex        =   2
      Text            =   "localhost"
      Top             =   240
      Width           =   1575
   End
   Begin VB.CommandButton CancelButton 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   1680
      TabIndex        =   1
      Top             =   1680
      Width           =   1215
   End
   Begin VB.CommandButton ConnectButton 
      Caption         =   "Open"
      Default         =   -1  'True
      Height          =   375
      Left            =   240
      TabIndex        =   0
      Top             =   1680
      Width           =   1215
   End
   Begin VB.Label UserModeLabel 
      Alignment       =   1  'Right Justify
      Caption         =   "User Mode:"
      Height          =   255
      Left            =   240
      TabIndex        =   7
      Top             =   1200
      Width           =   975
   End
   Begin VB.Label PortNumberLabel 
      Alignment       =   1  'Right Justify
      Caption         =   "Port Number:"
      Height          =   255
      Left            =   240
      TabIndex        =   5
      Top             =   720
      Width           =   975
   End
   Begin VB.Label HostNameLabel 
      Alignment       =   1  'Right Justify
      Caption         =   "Host Name:"
      Height          =   255
      Left            =   240
      TabIndex        =   4
      Top             =   240
      Width           =   975
   End
End
Attribute VB_Name = "FrmT2OpenG2Connection"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub CancelButton_Click()
    Unload Me
End Sub

Private Sub ConnectButton_Click()
    On Error GoTo ErrorHandler
        MDIT2Window.G2UiGateway1.G2Location = HostName.Text & ":" & PortNumber.Text
        MDIT2Window.G2UiGateway1.UserMode = UserMode.Text
        MDIT2Window.G2UiGateway1.Connect
        Unload Me
        Exit Sub
ErrorHandler:
    MsgBox "While attempting to connect to " & HostName.Text & ":" _
      & PortNumber.Text & ", the following error occured." & vbCrLf & _
      vbCrLf & Err.Description, , "Connection Error"
End Sub

Private Sub Form_Load()
    UserMode.Text = LCase(MDIT2Window.G2UiGateway1.UserMode)
End Sub
