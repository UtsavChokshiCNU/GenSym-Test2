VERSION 5.00
Object = "{AC4C85D1-B16C-11D1-A718-006008C5F933}#1.3#0"; "G2Com.dll"
Object = "{F0F0CC75-38F6-443A-839E-FD43283C2B4B}#8.0#0"; "TwControl.ocx"
Begin VB.Form G2TWForm 
   Caption         =   "VB / G2 / TW - ActiveXLink Demo"
   ClientHeight    =   8025
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   10080
   LinkTopic       =   "Form1"
   ScaleHeight     =   8025
   ScaleWidth      =   10080
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox WorkspaceTextBox 
      Enabled         =   0   'False
      Height          =   375
      Left            =   3720
      TabIndex        =   19
      Text            =   "activex-demo-ws"
      Top             =   720
      Width           =   6135
   End
   Begin VB.TextBox HostTextBox 
      Height          =   375
      Left            =   3480
      TabIndex        =   14
      Text            =   "localhost"
      Top             =   120
      Width           =   2655
   End
   Begin VB.TextBox PortTextBox 
      Height          =   375
      Left            =   7560
      TabIndex        =   13
      Text            =   "1111"
      Top             =   120
      Width           =   2295
   End
   Begin VB.CommandButton ConnectButton 
      Caption         =   "Reconnect to G2"
      Default         =   -1  'True
      Height          =   495
      Left            =   360
      TabIndex        =   12
      Top             =   7320
      Width           =   1695
   End
   Begin TWLib.TwControl TwControl1 
      Height          =   6495
      Left            =   2640
      TabIndex        =   11
      Top             =   1320
      Width           =   7215
      _Version        =   524288
      _ExtentX        =   12726
      _ExtentY        =   11456
      _StockProps     =   0
   End
   Begin VB.CommandButton CycleLights 
      Caption         =   "Cycle Lights"
      Height          =   495
      Left            =   360
      TabIndex        =   6
      Top             =   6120
      Width           =   1695
   End
   Begin VB.TextBox CallItemRetVal 
      ForeColor       =   &H80000003&
      Height          =   285
      Left            =   1050
      TabIndex        =   4
      TabStop         =   0   'False
      Top             =   3750
      Width           =   975
   End
   Begin VB.TextBox CallItem 
      Height          =   285
      Left            =   1050
      TabIndex        =   3
      Text            =   "100"
      Top             =   3315
      Width           =   975
   End
   Begin VB.TextBox StartItem 
      Height          =   285
      Left            =   345
      TabIndex        =   2
      Text            =   "Hello G2!"
      Top             =   1725
      Width           =   1935
   End
   Begin VB.CommandButton CallRPC 
      Caption         =   "Call"
      Height          =   495
      Left            =   600
      TabIndex        =   1
      Top             =   2580
      Width           =   1215
   End
   Begin VB.CommandButton StartRPC 
      Caption         =   "Post Message"
      Height          =   495
      Left            =   660
      TabIndex        =   0
      Top             =   540
      Width           =   1215
   End
   Begin VB.Frame Frame1 
      Caption         =   "Display Data In G2"
      Height          =   1935
      Left            =   120
      TabIndex        =   5
      Top             =   240
      Width           =   2295
      Begin VB.Label Label5 
         Caption         =   "Enter Message to Display on G2 Message Board"
         Height          =   390
         Left            =   270
         TabIndex        =   10
         Top             =   1020
         Width           =   1860
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "Call G2 Procedure"
      Height          =   1935
      Left            =   120
      TabIndex        =   7
      Top             =   2280
      Width           =   2295
      Begin VB.Label Label4 
         Caption         =   "Result:"
         Height          =   225
         Left            =   315
         TabIndex        =   9
         Top             =   1500
         Width           =   540
      End
      Begin VB.Label Label3 
         Caption         =   "Input:"
         Height          =   210
         Left            =   420
         TabIndex        =   8
         Top             =   1065
         Width           =   495
      End
   End
   Begin VB.TextBox GatewayConnection 
      Enabled         =   0   'False
      Height          =   375
      Left            =   120
      TabIndex        =   20
      Text            =   "the G2 connection in use by the G2 Gateway"
      Top             =   6720
      Width           =   2415
   End
   Begin VB.Label Label7 
      Caption         =   "Workspace:"
      Height          =   375
      Left            =   2640
      TabIndex        =   18
      Top             =   720
      Width           =   975
   End
   Begin VB.Label Label6 
      Caption         =   "Host:"
      Height          =   375
      Left            =   2640
      TabIndex        =   17
      Top             =   120
      Width           =   735
   End
   Begin VB.Label Label2 
      Caption         =   "Port:"
      Height          =   375
      Left            =   6480
      TabIndex        =   16
      Top             =   120
      Width           =   735
   End
   Begin VB.Label Label1 
      Caption         =   "UI Mode:"
      Height          =   375
      Left            =   1680
      TabIndex        =   15
      Top             =   2400
      Width           =   855
   End
   Begin GensymAxlCtl.G2Gateway G2Gateway1 
      Left            =   360
      OleObjectBlob   =   "G2TW.frx":0000
      Top             =   4920
   End
   Begin VB.Shape Greenlight 
      FillColor       =   &H00004000&
      FillStyle       =   0  'Solid
      Height          =   495
      Left            =   975
      Shape           =   3  'Circle
      Top             =   5385
      Width           =   495
   End
   Begin VB.Shape Yellowlight 
      FillColor       =   &H00004040&
      FillStyle       =   0  'Solid
      Height          =   495
      Left            =   975
      Shape           =   3  'Circle
      Top             =   4905
      Width           =   495
   End
   Begin VB.Shape Redlight 
      FillColor       =   &H00000040&
      FillStyle       =   0  'Solid
      Height          =   495
      Left            =   975
      Shape           =   3  'Circle
      Top             =   4425
      Width           =   495
   End
   Begin VB.Shape Shape4 
      FillColor       =   &H0080FFFF&
      FillStyle       =   0  'Solid
      Height          =   1695
      Left            =   855
      Top             =   4305
      Width           =   735
   End
End
Attribute VB_Name = "G2TWForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim NextMode As String

Dim RedOn, RedOff, YellowOn, YellowOff, GreenOn, GreenOff As Long
Private Sub Form_Load()
  RedOn = &HFF&
  RedOff = &H40&
  YellowOn = &HFFFF&
  YellowOff = &H4040&
  GreenOn = &HFF00&
  GreenOff = &H4000&

  NextMode = "slow"
  Redlight.FillColor = RedOn
  Yellowlight.FillColor = YellowOff
  Greenlight.FillColor = GreenOff
  GatewayConnection.Text = G2Gateway1.G2Location
  TwControl1.LaunchUI = "verbose"
  TwControl1.ConnectToG2
End Sub
Private Sub Form_Resize()
   TwControl1.Height = G2TWForm.Height - 1935
   TwControl1.Width = G2TWForm.Width - 2985
End Sub
Private Sub Update_Light(Mode As String)
  If Mode = "PROCEED" Then
    Redlight.FillColor = RedOff
    Yellowlight.FillColor = YellowOff
    Greenlight.FillColor = GreenOn
  ElseIf Mode = "STOP" Then
    Redlight.FillColor = RedOn
    Yellowlight.FillColor = YellowOff
    Greenlight.FillColor = GreenOff
  Else
    Redlight.FillColor = RedOff
    Yellowlight.FillColor = YellowOn
    Greenlight.FillColor = GreenOff
  End If
End Sub
Private Sub CycleLights_Click()
  Call G2Gateway1.Start("CHANGE-SIGNAL", NextMode)
  If NextMode = "stop" Then
    NextMode = "slow"
  ElseIf NextMode = "slow" Then
    NextMode = "proceed"
  Else
    NextMode = "stop"
  End If
End Sub
Private Sub G2Gateway1_Error(ByVal ErrorMessage As String, ByVal ErrorCode As Long, DeferredCallIdentifier As Variant)
  MsgBox ErrorMessage
End Sub
Private Sub G2Gateway1_RpcStarted(ByVal Name As String, InArgs As Variant)
  Dim str As String
  str = InArgs
  If Name = "CYCLELIGHTS" Then Call Update_Light(str)
End Sub
Private Sub StartRPC_Click()
  G2Gateway1.PostMessage StartItem.Text
End Sub
Private Sub CallRPC_Click()
  rannum = G2Gateway1.Call("G2RANDOMGENERATOR", Val(CallItem.Text))
  CallItemRetVal = str(rannum)
End Sub
Private Sub ConnectButton_Click()
   GatewayConnection.Text = G2Gateway1.G2Location
   TwControl1.ConnectToG2
End Sub
Private Sub HostTextBox_Change()
  TwControl1.LaunchHost = HostTextBox.Text
  Text1.Text = HostTextBox.Text + ":" + PortTextBox.Text
End Sub
Private Sub PortTextBox_Change()
  TwControl1.LaunchPort = PortTextBox.Text
  Text1.Text = HostTextBox.Text + ":" + PortTextBox.Text
End Sub
Private Sub WorkspaceTextBox_Change()
  TwControl1.LaunchWorkspace = WorkspaceTextBox.Text
End Sub
