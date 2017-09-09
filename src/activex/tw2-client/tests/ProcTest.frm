VERSION 5.00
Object = "{42B6C7E0-06C1-11D2-8698-00008618F471}#2.0#0"; "AXClient.dll"
Begin VB.Form ProcTestForm 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Procedure Test"
   ClientHeight    =   1935
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   6750
   Icon            =   "ProcTest.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   1935
   ScaleWidth      =   6750
   StartUpPosition =   3  'Windows Default
   Begin GensymTw2Ctl.G2UiGateway G2UiGateway1 
      Left            =   120
      OleObjectBlob   =   "ProcTest.frx":000C
      Top             =   120
   End
   Begin VB.CommandButton StartMyMethodBtn 
      Caption         =   "Start my-object.my-method"
      Height          =   495
      Left            =   3840
      TabIndex        =   5
      Top             =   1320
      Width           =   2775
   End
   Begin VB.CommandButton StartMyProc2Btn 
      Caption         =   "Start my-procedure2"
      Height          =   495
      Left            =   2040
      TabIndex        =   4
      Top             =   1320
      Width           =   1695
   End
   Begin VB.CommandButton StartMyProcBtn 
      Caption         =   "Start my-procedure"
      Height          =   495
      Left            =   120
      TabIndex        =   3
      Top             =   1320
      Width           =   1815
   End
   Begin VB.CommandButton CallMyMethodBtn 
      Caption         =   "Call my-object.my-method"
      Height          =   495
      Left            =   3840
      TabIndex        =   2
      Top             =   720
      Width           =   2775
   End
   Begin VB.CommandButton CallMyProc2Btn 
      Caption         =   "Call my-procedure2"
      Height          =   495
      Left            =   2040
      TabIndex        =   0
      Top             =   720
      Width           =   1695
   End
   Begin VB.CommandButton CallMyProcBtn 
      Caption         =   "Call my-procedure"
      Height          =   495
      Left            =   120
      TabIndex        =   1
      Top             =   720
      Width           =   1815
   End
End
Attribute VB_Name = "ProcTestForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub CallMyProcBtn_Click()
    G2UiGateway1.Connect
    MsgBox "my-procedure() = " & G2UiGateway1.CallG2Procedure("my-procedure", 45, "", False)
End Sub

Private Sub CallMyProc2Btn_Click()
    Dim sequence(0 To 2) As Variant

    sequence(0) = 1
    sequence(1) = ""
    sequence(2) = True
    G2UiGateway1.Connect
    MsgBox "my-procedure2() = " & G2UiGateway1.CallG2Procedure("my-procedure2", sequence)
End Sub

Private Sub CallMyMethodBtn_Click()
    G2UiGateway1.Connect
    MsgBox "my-object.my-method = " & G2UiGateway1.GetNamedItem("my-object").CallMethod("my-method")
End Sub

Private Sub StartMyProcBtn_Click()
    G2UiGateway1.Connect
    G2UiGateway1.StartG2Procedure "my-procedure", 145, "", False
    MsgBox "Started my-procedure"
End Sub

Private Sub StartMyProc2Btn_Click()
    Dim sequence(0 To 2) As Variant

    sequence(0) = 1
    sequence(1) = ""
    sequence(2) = True
    G2UiGateway1.Connect
    G2UiGateway1.StartG2Procedure "my-procedure2", sequence
    MsgBox "Started my-procedure2"
End Sub

Private Sub StartMyMethodBtn_Click()
    G2UiGateway1.Connect
    G2UiGateway1.GetNamedItem("my-object").StartMethod ("my-method")
    MsgBox "Started my-object.my-method"
End Sub

