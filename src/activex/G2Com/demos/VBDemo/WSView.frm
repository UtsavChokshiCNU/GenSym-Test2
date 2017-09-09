VERSION 5.00
Object = "{AC4C85D1-B16C-11D1-A718-006008C5F933}#1.6#0"; "G2Com.dll"
Object = "{D03BCBA5-8C30-4FD6-A02E-9F7BE412FA3F}#1.0#0"; "WorkspaceView.ocx"
Begin VB.Form WSViewForm 
   Caption         =   "VB / G2 / TW - ActiveXLink Demo"
   ClientHeight    =   7785
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   12840
   LinkTopic       =   "Form1"
   ScaleHeight     =   7785
   ScaleWidth      =   12840
   StartUpPosition =   3  'Windows Default
   Begin WSVLib.WorkspaceView WorkspaceView2 
      Height          =   6495
      Left            =   7800
      TabIndex        =   19
      Top             =   1200
      Width           =   4935
      _Version        =   65536
      _ExtentX        =   8705
      _ExtentY        =   11456
      _StockProps     =   0
   End
   Begin WSVLib.WorkspaceView WorkspaceView1 
      Height          =   6495
      Left            =   2640
      TabIndex        =   18
      Top             =   1200
      Width           =   4935
      _Version        =   65536
      _ExtentX        =   8705
      _ExtentY        =   11456
      _StockProps     =   0
   End
   Begin VB.ComboBox PreferUUID2 
      Height          =   315
      ItemData        =   "WSView.frx":0000
      Left            =   9840
      List            =   "WSView.frx":000A
      TabIndex        =   17
      Text            =   "Name"
      Top             =   720
      Width           =   1095
   End
   Begin VB.ComboBox PreferUUID1 
      Height          =   315
      ItemData        =   "WSView.frx":001A
      Left            =   4440
      List            =   "WSView.frx":0024
      TabIndex        =   16
      Text            =   "Name"
      Top             =   720
      Width           =   1095
   End
   Begin VB.TextBox WSNameBox2 
      Height          =   375
      Left            =   8880
      TabIndex        =   14
      Text            =   "THE-USER-WS"
      Top             =   120
      Width           =   3855
   End
   Begin VB.CommandButton ConnectWS1 
      Caption         =   "Show Workspace"
      Height          =   495
      Left            =   2640
      TabIndex        =   13
      Top             =   600
      Width           =   1695
   End
   Begin VB.TextBox WSNameBox1 
      Height          =   375
      Left            =   3720
      TabIndex        =   11
      Text            =   "ACTIVEX-DEMO-WS"
      Top             =   120
      Width           =   3855
   End
   Begin VB.TextBox HostTextBox 
      Height          =   375
      Left            =   720
      TabIndex        =   7
      Text            =   "localhost"
      Top             =   120
      Width           =   1695
   End
   Begin VB.TextBox PortTextBox 
      Height          =   375
      Left            =   720
      TabIndex        =   6
      Text            =   "1112"
      Top             =   600
      Width           =   1695
   End
   Begin VB.CommandButton CycleLights 
      Caption         =   "Cycle Lights"
      Height          =   495
      Left            =   120
      TabIndex        =   3
      Top             =   5040
      Width           =   2295
   End
   Begin VB.TextBox MessageToPost 
      Height          =   285
      Left            =   345
      TabIndex        =   1
      Text            =   "Hello G2!"
      Top             =   2685
      Width           =   1935
   End
   Begin VB.CommandButton PostMessageBtn 
      Caption         =   "Post Message"
      Height          =   495
      Left            =   660
      TabIndex        =   0
      Top             =   1500
      Width           =   1215
   End
   Begin VB.Frame Frame1 
      Caption         =   "Display Data In G2"
      Height          =   1935
      Left            =   120
      TabIndex        =   2
      Top             =   1200
      Width           =   2295
      Begin VB.Label Label5 
         Caption         =   "Enter Message to Display on G2 Message Board"
         Height          =   390
         Left            =   270
         TabIndex        =   4
         Top             =   1020
         Width           =   1860
      End
   End
   Begin VB.TextBox GatewayConnection 
      Alignment       =   2  'Center
      Enabled         =   0   'False
      Height          =   375
      Left            =   5880
      TabIndex        =   12
      Text            =   "the G2 connection in use by the G2 Gateway"
      Top             =   600
      Width           =   3495
   End
   Begin VB.CommandButton ConnectWS2 
      Caption         =   "Show Workspace"
      Default         =   -1  'True
      Height          =   495
      Left            =   11040
      TabIndex        =   5
      Top             =   600
      Width           =   1695
   End
   Begin VB.Label Label8 
      Caption         =   "Workspace:"
      Height          =   375
      Left            =   7800
      TabIndex        =   15
      Top             =   120
      Width           =   975
   End
   Begin VB.Label Label7 
      Caption         =   "Workspace:"
      Height          =   375
      Left            =   2640
      TabIndex        =   10
      Top             =   120
      Width           =   975
   End
   Begin VB.Label Label6 
      Caption         =   "Host:"
      Height          =   375
      Left            =   120
      TabIndex        =   9
      Top             =   120
      Width           =   615
   End
   Begin VB.Label Label2 
      Caption         =   "Port:"
      Height          =   375
      Left            =   120
      TabIndex        =   8
      Top             =   600
      Width           =   375
   End
   Begin VB.Shape Greenlight 
      FillColor       =   &H00004000&
      FillStyle       =   0  'Solid
      Height          =   495
      Left            =   975
      Shape           =   3  'Circle
      Top             =   4305
      Width           =   495
   End
   Begin VB.Shape Yellowlight 
      FillColor       =   &H00004040&
      FillStyle       =   0  'Solid
      Height          =   495
      Left            =   975
      Shape           =   3  'Circle
      Top             =   3825
      Width           =   495
   End
   Begin VB.Shape Redlight 
      FillColor       =   &H00000040&
      FillStyle       =   0  'Solid
      Height          =   495
      Left            =   975
      Shape           =   3  'Circle
      Top             =   3345
      Width           =   495
   End
   Begin VB.Shape Shape4 
      FillColor       =   &H0080FFFF&
      FillStyle       =   0  'Solid
      Height          =   1695
      Left            =   855
      Top             =   3225
      Width           =   735
   End
   Begin GensymAxlCtl.G2Gateway G2Gateway1 
      Left            =   1560
      OleObjectBlob   =   "WSView.frx":0034
      Top             =   3720
   End
End
Attribute VB_Name = "WSViewForm"
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

  GatewayConnection.Text = HostTextBox.Text + ":" + PortTextBox.Text
  G2Gateway1.G2Location = GatewayConnection.Text
  WorkspaceView1.WorkspaceName = WSNameBox1.Text
  WorkspaceView2.WorkspaceName = WSNameBox2.Text
  WorkspaceView1.G2Gateway = G2Gateway1
  WorkspaceView2.G2Gateway = G2Gateway1
  NextMode = "slow"
  Redlight.FillColor = RedOn
  Yellowlight.FillColor = YellowOff
  Greenlight.FillColor = GreenOff
  CycleLights_Click
End Sub
Private Sub Form_Resize()
   Dim NewWidth As Integer
   
   NewWidth = (WSViewForm.Width - 3090) / 2
   If NewWidth > 10 Then
     WorkspaceView1.Width = NewWidth
     WorkspaceView2.Width = NewWidth
     WorkspaceView2.Left = NewWidth + 2865
   
     WorkspaceView1.Height = WSViewForm.Height - 1935
     WorkspaceView2.Height = WorkspaceView1.Height
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
Private Sub PostMessageBtn_Click()
  G2Gateway1.PostMessage MessageToPost.Text
End Sub
Private Sub ConnectWS1_Click()
  If PreferUUID1.Text = "UUID" Then
     WorkspaceView1.ShowWorkspaceWithUUID WSNameBox1.Text
  Else
     WorkspaceView1.ShowWorkspaceWithName WSNameBox1.Text
  End If
End Sub
Private Sub ConnectWS2_Click()
  If PreferUUID2.Text = "UUID" Then
     WorkspaceView2.ShowWorkspaceWithUUID WSNameBox2.Text
  Else
     WorkspaceView2.ShowWorkspaceWithName WSNameBox2.Text
  End If
End Sub
Private Sub WSNameBox1_Change()
  If PreferUUID1.Text = "UUID" Then
    WorkspaceView1.WorkspaceUUID = WSNameBox1.Text
  Else
    WorkspaceView1.WorkspaceName = WSNameBox1.Text
  End If
  ConnectWS1.Default = True
End Sub
Private Sub WSNameBox2_Change()
  If PreferUUID2.Text = "UUID" Then
    WorkspaceView2.WorkspaceUUID = WSNameBox2.Text
  Else
    WorkspaceView2.WorkspaceName = WSNameBox2.Text
  End If
  ConnectWS2.Default = True
End Sub
Private Sub HostTextBox_Change()
  GatewayConnection.Text = HostTextBox.Text + ":" + PortTextBox.Text
  G2Gateway1.G2Location = GatewayConnection.Text
End Sub
Private Sub PortTextBox_Change()
  GatewayConnection.Text = HostTextBox.Text + ":" + PortTextBox.Text
  G2Gateway1.G2Location = GatewayConnection.Text
End Sub
Private Sub G2Gateway1_Error(ByVal ErrorMessage As String, ByVal ErrorCode As Long, DeferredCallIdentifier As Variant)
  MsgBox ErrorMessage
End Sub
Private Sub G2Gateway1_RpcStarted(ByVal Name As String, InArgs As Variant)
  Dim str As String
  str = InArgs
  If Name = "CYCLELIGHTS" Then Call Update_Light(str)
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
