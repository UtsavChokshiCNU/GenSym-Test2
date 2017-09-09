VERSION 5.00
Object = "{42B6C7E0-06C1-11D2-8698-00008618F471}#2.0#0"; "AXClient.dll"
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Begin VB.Form ItemHolderForm 
   Caption         =   "Auto Load MY-OBJECT@g2-1"
   ClientHeight    =   7275
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8070
   LinkTopic       =   "Form1"
   ScaleHeight     =   7275
   ScaleWidth      =   8070
   StartUpPosition =   3  'Windows Default
   Begin GensymTw2Ctl.G2UiGateway G2UiGateway1 
      Left            =   600
      OleObjectBlob   =   "AutoLoadItemTest.frx":0000
      Top             =   6480
   End
   Begin GensymTw2Ctl.G2ItemHolder G2ItemHolder1 
      Left            =   3000
      OleObjectBlob   =   "AutoLoadItemTest.frx":00D8
      Top             =   6480
   End
   Begin MSFlexGridLib.MSFlexGrid MSFlexGrid1 
      Height          =   6255
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   7815
      _ExtentX        =   13785
      _ExtentY        =   11033
      _Version        =   327680
      AllowUserResizing=   1
   End
End
Attribute VB_Name = "ItemHolderForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Load()
    Dim AttributeNames As Variant
    Dim AttributeValue As Variant
    Dim CurrentRow As Integer
    Dim N As Integer
    Dim i As Integer
  
    If Not G2UiGateway1.IsConnected Then
        MsgBox "Test Failed: the gateway did not connect."
        Exit Sub
    End If
    
    ' now that we have the item, create the form to show it on
    ' and set up the display
   
    MSFlexGrid1.TextMatrix(0, 0) = "Attribute Name"
    MSFlexGrid1.TextMatrix(0, 1) = "Attribute Value"
    MSFlexGrid1.ColWidth(0) = 3000
    MSFlexGrid1.ColWidth(1) = 4500
    MSFlexGrid1.ColAlignment(0) = 6 ' right
    MSFlexGrid1.ColAlignment(1) = 0 ' left
    
    ' Now walk the list attributes and get each value
    AttributeNames = G2ItemHolder1.AttributeNames
    N = UBound(AttributeNames)  ' how many are there?
    CurrentRow = 0
    For i = LBound(AttributeNames) To N
        MSFlexGrid1.Rows = CurrentRow + 2
        MSFlexGrid1.TextMatrix(CurrentRow + 1, 0) = AttributeNames(i)
        AttributeValue = G2ItemHolder1.Attribute(AttributeNames(i))
        If IsArray(AttributeValue) Then
            If UBound(AttributeValue) - LBound(AttributeValue) > 0 Then
                AttributeValue = AttributeValue(LBound(AttributeValue))
            Else
                AttributeValue = ""
            End If
        End If
        
        If IsObject(AttributeValue) Then AttributeValue = AttributeValue.String
        
        If IsNull(AttributeValue) Then AttributeValue = ""
        
        MSFlexGrid1.TextMatrix(CurrentRow + 1, 1) = AttributeValue
        CurrentRow = CurrentRow + 1
    Next i
End Sub
