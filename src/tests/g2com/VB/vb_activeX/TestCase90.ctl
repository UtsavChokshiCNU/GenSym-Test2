VERSION 5.00
Object = "{AC4C85D1-B16C-11D1-A718-006008C5F933}#2.0#0"; "G2Com.dll"
Begin VB.UserControl UserControl1 
   ClientHeight    =   495
   ClientLeft      =   0
   ClientTop       =   0
   ClientWidth     =   1905
   ScaleHeight     =   495
   ScaleWidth      =   1905
   Begin VB.Label Label1 
      Caption         =   "TESTCASE90"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1695
   End
   Begin GensymAxlCtl.G2Gateway G2Gateway1 
      Left            =   240
      OleObjectBlob   =   "TestCase90.ctx":0000
      Top             =   480
   End
End
Attribute VB_Name = "UserControl1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Public Function CallG2Method() As G2Item
Dim Item As G2Item
Set Item = G2Gateway1.Call("TESTCASE90")
Set CallG2Method = Item
End Function
