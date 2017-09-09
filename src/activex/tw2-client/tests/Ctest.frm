VERSION 5.00
Object = "{42B6C7E0-06C1-11D2-8698-00008618F471}#2.0#0"; "AXClient.dll"
Begin VB.Form Ctestform 
   Caption         =   "Connection Test"
   ClientHeight    =   3375
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4830
   LinkTopic       =   "Form1"
   ScaleHeight     =   3375
   ScaleWidth      =   4830
   StartUpPosition =   3  'Windows Default
   Begin GensymTw2Ctl.G2UiGateway G2UiGateway2 
      Left            =   3360
      OleObjectBlob   =   "Ctest.frx":0000
      Top             =   480
   End
   Begin GensymTw2Ctl.G2UiGateway G2UiGateway1 
      Left            =   960
      OleObjectBlob   =   "Ctest.frx":00D8
      Top             =   480
   End
   Begin VB.CommandButton Disconnect2 
      Caption         =   "Disconnect"
      Height          =   495
      Left            =   2760
      TabIndex        =   3
      Top             =   1920
      Width           =   1695
   End
   Begin VB.CommandButton Connect2 
      Caption         =   "Connect"
      Height          =   495
      Left            =   2760
      TabIndex        =   2
      Top             =   1200
      Width           =   1695
   End
   Begin VB.CommandButton Disconnect1 
      Caption         =   "Disconnect"
      Height          =   495
      Left            =   360
      TabIndex        =   1
      Top             =   1920
      Width           =   1695
   End
   Begin VB.CommandButton Connect1 
      Caption         =   "Connect"
      Height          =   495
      Left            =   360
      TabIndex        =   0
      Top             =   1200
      Width           =   1695
   End
   Begin VB.Frame Frame1 
      Caption         =   "set at  runtime"
      Height          =   3015
      Left            =   120
      TabIndex        =   4
      Top             =   120
      Width           =   2175
      Begin VB.Label Label1 
         Alignment       =   2  'Center
         Caption         =   "set at runtime"
         Height          =   255
         Left            =   240
         TabIndex        =   6
         Top             =   2520
         Width           =   1695
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "set at runtime"
      Height          =   3015
      Left            =   2520
      TabIndex        =   5
      Top             =   120
      Width           =   2175
      Begin VB.Label Label2 
         Alignment       =   2  'Center
         Caption         =   "set at runtime"
         Height          =   255
         Left            =   240
         TabIndex        =   7
         Top             =   2520
         Width           =   1695
      End
   End
End
Attribute VB_Name = "Ctestform"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()
    Frame1.Caption = G2UiGateway1.G2Location
    Frame2.Caption = G2UiGateway2.G2Location
     
    If Not G2UiGateway1.IsConnected Then
        Label1.Caption = "Not Connected"
    Else
        Label1.Caption = "Connected"
    End If
     
   If Not G2UiGateway2.IsConnected Then
        Label2.Caption = "Not Connected"
    Else
        Label2.Caption = "Connected"
    End If
End Sub

Private Sub Connect1_Click()
    G2UiGateway1.Connect
End Sub

Private Sub Disconnect1_Click()
    G2UiGateway1.Disconnect
End Sub

Private Sub G2UiGateway1_G2Connected()
    Label1.Caption = "Connected"
End Sub

Private Sub G2UiGateway1_G2Disconnected()
    Label1.Caption = "Not Connected"
End Sub

Private Sub Connect2_Click()
    G2UiGateway2.Connect
End Sub

Private Sub Disconnect2_Click()
    G2UiGateway2.Disconnect
End Sub

Private Sub G2UiGateway2_G2Connected()
    Label2.Caption = "Connected"
End Sub

Private Sub G2UiGateway2_G2Disconnected()
    Label2.Caption = "Not Connected"
End Sub

