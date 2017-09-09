VERSION 5.00
Begin VB.Form TestListBoxForm 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "set at runtime"
   ClientHeight    =   3390
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   4710
   Icon            =   "Test2.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   3390
   ScaleWidth      =   4710
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton OK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   240
      TabIndex        =   1
      Top             =   2880
      Width           =   1455
   End
   Begin VB.ListBox List 
      Height          =   2595
      ItemData        =   "Test2.frx":000C
      Left            =   120
      List            =   "Test2.frx":000E
      TabIndex        =   0
      Top             =   120
      Width           =   4455
   End
End
Attribute VB_Name = "TestListBoxForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub OK_Click()
    Unload Me
End Sub
