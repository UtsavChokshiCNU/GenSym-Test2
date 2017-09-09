VERSION 5.00
Object = "{F0F0CC75-38F6-443A-839E-FD43283C2B4B}#7.1#0"; "TwControl.ocx"
Begin VB.Form TWForm 
   Caption         =   "Telewindows"
   ClientHeight    =   8115
   ClientLeft      =   1755
   ClientTop       =   1590
   ClientWidth     =   9435
   LinkTopic       =   "Form1"
   ScaleHeight     =   8115
   ScaleWidth      =   9435
   Begin VB.ComboBox UiComboBox 
      Height          =   315
      ItemData        =   "twform.frx":0000
      Left            =   5280
      List            =   "twform.frx":000A
      TabIndex        =   2
      Text            =   "standard"
      Top             =   480
      Width           =   1215
   End
   Begin TWLib.TwControl TwControl1 
      Height          =   6495
      Left            =   120
      TabIndex        =   4
      TabStop         =   0   'False
      Top             =   1440
      Width           =   9135
      _Version        =   458753
      _ExtentX        =   16113
      _ExtentY        =   11456
      _StockProps     =   0
   End
   Begin VB.CommandButton ConnectButton 
      Caption         =   "Connect to G2"
      Default         =   -1  'True
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   7080
      TabIndex        =   3
      Top             =   480
      Width           =   1695
   End
   Begin VB.TextBox PortTextBox 
      Height          =   375
      Left            =   840
      TabIndex        =   1
      Text            =   "1111"
      Top             =   720
      Width           =   3255
   End
   Begin VB.TextBox HostTextBox 
      Height          =   375
      Left            =   840
      TabIndex        =   0
      Text            =   "localhost"
      Top             =   240
      Width           =   3255
   End
   Begin VB.Label Label3 
      Caption         =   "UI Mode:"
      Height          =   375
      Left            =   4320
      TabIndex        =   7
      Top             =   480
      Width           =   855
   End
   Begin VB.Label Label2 
      Caption         =   "Port:"
      Height          =   375
      Left            =   120
      TabIndex        =   6
      Top             =   720
      Width           =   615
   End
   Begin VB.Label Label1 
      Caption         =   "Host:"
      Height          =   375
      Left            =   120
      TabIndex        =   5
      Top             =   240
      Width           =   615
   End
End
Attribute VB_Name = "TWForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub ConnectButton_Click()
  TwControl1.LaunchUI = UiComboBox.Text
  TwControl1.ConnectToG2
End Sub
Private Sub Form_Resize()
   TwControl1.Height = TWForm.Height - 2025
   TwControl1.Width = TWForm.Width - 420
End Sub

Private Sub HostTextBox_Change()
  TwControl1.LaunchHost = HostTextBox
End Sub

Private Sub PortTextBox_Change()
  TwControl1.LaunchPort = PortTextBox
End Sub
