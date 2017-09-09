VERSION 5.00
Object = "{6B7E6392-850A-101B-AFC0-4210102A8DA7}#1.1#0"; "COMCTL32.OCX"
Begin VB.Form FrmT2DisplayItemAttributes 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "set at runtime"
   ClientHeight    =   3630
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   6495
   Icon            =   "FrmT2DisplayItemAttributes.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MDIChild        =   -1  'True
   ScaleHeight     =   3630
   ScaleWidth      =   6495
   Begin VB.CommandButton CommandOK 
      Caption         =   "OK"
      Default         =   -1  'True
      Height          =   375
      Left            =   2640
      TabIndex        =   0
      Top             =   3000
      Width           =   1215
   End
   Begin ComctlLib.ListView ListView1 
      Height          =   2535
      Left            =   240
      TabIndex        =   1
      Top             =   240
      Width           =   6015
      _ExtentX        =   10610
      _ExtentY        =   4471
      View            =   3
      LabelWrap       =   -1  'True
      HideSelection   =   -1  'True
      _Version        =   327680
      ForeColor       =   -2147483640
      BackColor       =   -2147483643
      BorderStyle     =   1
      Appearance      =   1
      MouseIcon       =   "FrmT2DisplayItemAttributes.frx":0442
      NumItems        =   0
   End
End
Attribute VB_Name = "FrmT2DisplayItemAttributes"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub ListView1_ColumnClick(ByVal ColumnHeader As ColumnHeader)
    Dim newSortOrder As Integer
    
    ' When a ColumnHeader object is clicked, the ListView control is
    ' sorted by the subitems of that column, unless the it is already
    ' the sort column, then we reverse the sort order.
    
    newSortOrder = lvwAscending
    
    ' The SortKey is 0 based and the Index of the ColumnHeader is 1 based
    ' the view starts out not sorted
    If ListView1.SortKey = ColumnHeader.Index - 1 Then
        If ListView1.SortOrder = lvwDescending Or Not ListView1.Sorted Then
            newSortOrder = lvwAscending
        Else
            newSortOrder = lvwDescending
        End If
    End If
    
    ListView1.Sorted = True
    ListView1.SortOrder = newSortOrder
    ListView1.SortKey = ColumnHeader.Index - 1
End Sub

Private Sub CommandOK_Click()
    Unload Me
End Sub

Private Sub Form_Unload(Cancel As Integer)
    MDIT2Window.RemoveItemWindow Me
End Sub

