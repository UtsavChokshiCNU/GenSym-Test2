VERSION 5.00
Begin VB.Form FrmT2SpecifyItemName 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Get Item"
   ClientHeight    =   1320
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   3390
   Icon            =   "FrmT2SpecifyItemName.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   1320
   ScaleWidth      =   3390
   ShowInTaskbar   =   0   'False
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton CommandCancel 
      Cancel          =   -1  'True
      Caption         =   "Cancel"
      Height          =   375
      Left            =   1800
      TabIndex        =   3
      Top             =   720
      Width           =   1335
   End
   Begin VB.CommandButton CommandDisplay 
      Caption         =   "Get"
      Default         =   -1  'True
      Height          =   375
      Left            =   240
      TabIndex        =   2
      Top             =   720
      Width           =   1335
   End
   Begin VB.TextBox ItemName 
      Height          =   285
      Left            =   1200
      TabIndex        =   0
      Top             =   240
      Width           =   1935
   End
   Begin VB.Label ItemNameLabel 
      Alignment       =   1  'Right Justify
      Caption         =   "Item Name:"
      Height          =   255
      Left            =   240
      TabIndex        =   1
      Top             =   240
      Width           =   855
   End
End
Attribute VB_Name = "FrmT2SpecifyItemName"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub CommandCancel_Click()
    Unload Me
End Sub

Private Sub CommandDisplay_Click()
    Dim G2Object As G2Item
    Dim NewForm As FrmT2DisplayItemAttributes
    Dim Names As Variant
    Dim InUserAttributes As Boolean
    Dim N As Integer
    Dim i As Integer
    Dim attrval As Variant
    Dim columns As Integer
    Dim ListViewItem As ListItem
    
    ' This will get a named object from G2 and display its
    ' attributes in a grid

    If ItemName.Text = "" Then
        MsgBox "Please enter a valid item name.", , "Entry Error"
        Exit Sub
    End If

    On Error GoTo ErrorHandler
        Set G2Object = MDIT2Window.G2UiGateway1.GetNamedItem(ItemName.Text)
         
        ' Now that we have the item, create the form to show it on
        ' and set up the display
        Set NewForm = New FrmT2DisplayItemAttributes
    
        ' Add ColumnHeaders. The width of the columns is
        ' the width of the control divided by the number of
        ' ColumnHeader objects.
        columns = 2
        NewForm.ListView1.ColumnHeaders.Add , , "Attribute Name", _
            NewForm.ListView1.Width / (columns + 1), lvwColumnLeft
        NewForm.ListView1.ColumnHeaders.Add , , "Attribute Value", _
            NewForm.ListView1.Width / columns * 4, lvwColumnLeft
    
        ' Now walk the list of each attribute, get its value and stuff it
        Names = G2Object.AttributeNames
        N = UBound(Names)  ' how many are there?
        InUserAttributes = False
        For i = 0 To N
            If InUserAttributes = True Then
                Set ListViewItem = NewForm.ListView1.ListItems.Add
        
                ' The first colunm is the ListItem text and the other columns
                ' are the SubItems, which are 1 based.
                ListViewItem.Text = Names(i)

                attrval = G2Object.Attribute(Names(i))
                If IsArray(attrval) Then attrval = attrval(0)
              
                If IsObject(attrval) Then attrval = attrval.String
              
                If IsNull(attrval) Then attrval = ""
              
                ListViewItem.SubItems(1) = attrval
            End If
            
            If Names(i) = "ITEM-X-POSITION" Then InUserAttributes = True
        Next i
          
        NewForm.Caption = "Display " & UCase(ItemName.Text) & " Attributes"
        Unload Me
        MDIT2Window.AddItemWindow NewForm
        Exit Sub
ErrorHandler:
    MsgBox "While attempting to obtain: " & ItemName.Text & _
      ", the following error occured." & vbCrLf & _
      vbCrLf & Err.Description, , "Error Obtaining Object"
End Sub

