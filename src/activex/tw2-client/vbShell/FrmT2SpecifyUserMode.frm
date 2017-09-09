VERSION 5.00
Begin VB.Form FrmT2SpecifyUserMode 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Change User Mode"
   ClientHeight    =   1305
   ClientLeft      =   2760
   ClientTop       =   3750
   ClientWidth     =   3150
   Icon            =   "FrmT2SpecifyUserMode.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1305
   ScaleWidth      =   3150
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.TextBox UserMode 
      Height          =   285
      Left            =   1200
      TabIndex        =   2
      Text            =   "set at runtime"
      Top             =   240
      Width           =   1695
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   1680
      TabIndex        =   1
      Top             =   720
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "Change"
      Default         =   -1  'True
      Height          =   375
      Left            =   240
      TabIndex        =   0
      Top             =   720
      Width           =   1215
   End
   Begin VB.Label UserModeLabel 
      Alignment       =   1  'Right Justify
      Caption         =   "User Mode:"
      Height          =   255
      Left            =   240
      TabIndex        =   3
      Top             =   240
      Width           =   855
   End
End
Attribute VB_Name = "FrmT2SpecifyUserMode"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub CancelButton_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    UserMode.Text = LCase(MDIT2Window.G2UiGateway1.UserMode)
End Sub

Private Sub OKButton_Click()
    On Error GoTo ErrorHandler
        MDIT2Window.G2UiGateway1.UserMode = UserMode.Text
        Unload Me
        Exit Sub
ErrorHandler:
    MsgBox "While attempting to change the user mode to " & UserMode.Text _
        & ", the following error occured." & vbCrLf & _
        vbCrLf & Err.Description, , "User Mode Error"
End Sub
