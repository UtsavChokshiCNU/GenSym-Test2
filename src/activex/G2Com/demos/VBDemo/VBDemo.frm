VERSION 5.00
Object = "{AC4C85D1-B16C-11D1-A718-006008C5F933}#2.0#0"; "G2Com.dll"
Begin VB.Form Form1 
   Caption         =   "VB / G2 - ActiveXLink Demo"
   ClientHeight    =   4650
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5145
   LinkTopic       =   "Form1"
   ScaleHeight     =   4650
   ScaleWidth      =   5145
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton CycleLights 
      Caption         =   "Cycle Lights"
      Height          =   495
      Left            =   2655
      TabIndex        =   6
      Top             =   3015
      Width           =   1215
   End
   Begin VB.TextBox CallItemRetVal 
      ForeColor       =   &H80000003&
      Height          =   285
      Left            =   3570
      TabIndex        =   4
      TabStop         =   0   'False
      Top             =   1590
      Width           =   975
   End
   Begin VB.TextBox CallItem 
      Height          =   285
      Left            =   3570
      TabIndex        =   3
      Text            =   "100"
      Top             =   1155
      Width           =   975
   End
   Begin VB.TextBox StartItem 
      Height          =   285
      Left            =   345
      TabIndex        =   2
      Text            =   "Hello G2!"
      Top             =   1605
      Width           =   1935
   End
   Begin VB.CommandButton CallRPC 
      Caption         =   "Call"
      Height          =   495
      Left            =   3120
      TabIndex        =   1
      Top             =   420
      Width           =   1215
   End
   Begin VB.CommandButton StartRPC 
      Caption         =   "Post Message"
      Height          =   495
      Left            =   660
      TabIndex        =   0
      Top             =   420
      Width           =   1215
   End
   Begin VB.Frame Frame1 
      Caption         =   "Display Data In G2"
      Height          =   1935
      Left            =   120
      TabIndex        =   5
      Top             =   120
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
      Left            =   2640
      TabIndex        =   7
      Top             =   120
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
   Begin GensymAxlCtl.G2Gateway G2Gateway1 
      Left            =   480
      OleObjectBlob   =   "VBDemo.frx":0000
      Top             =   2880
   End
   Begin VB.Shape Greenlight 
      FillColor       =   &H00004000&
      FillStyle       =   0  'Solid
      Height          =   495
      Left            =   1575
      Shape           =   3  'Circle
      Top             =   3465
      Width           =   495
   End
   Begin VB.Shape Yellowlight 
      FillColor       =   &H00004040&
      FillStyle       =   0  'Solid
      Height          =   495
      Left            =   1575
      Shape           =   3  'Circle
      Top             =   2985
      Width           =   495
   End
   Begin VB.Shape Redlight 
      FillColor       =   &H00000040&
      FillStyle       =   0  'Solid
      Height          =   495
      Left            =   1575
      Shape           =   3  'Circle
      Top             =   2505
      Width           =   495
   End
   Begin VB.Shape Shape4 
      FillColor       =   &H0080FFFF&
      FillStyle       =   0  'Solid
      Height          =   1695
      Left            =   1455
      Top             =   2385
      Width           =   735
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False


Dim NextMode As String
Dim RedOn, RedOff, YellowOn, YellowOff, GreenOn, GreenOff As Long

Private Sub CallRPC_Click()
  rannum = G2Gateway1.Call("G2RANDOMGENERATOR", Val(CallItem.Text))
  CallItemRetVal = str(rannum)
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

