VERSION 5.00
Object = "{42B6C7E0-06C1-11D2-8698-00008618F471}#2.0#0"; "AXClient.dll"
Begin VB.Form ItemHolderTestForm 
   Caption         =   "Form1"
   ClientHeight    =   2610
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   2415
   LinkTopic       =   "Form1"
   ScaleHeight     =   2610
   ScaleWidth      =   2415
   StartUpPosition =   3  'Windows Default
   Begin GensymTw2Ctl.G2ItemHolder G2ItemHolder1 
      Left            =   840
      OleObjectBlob   =   "ItemHolderTest.frx":0000
      Top             =   0
   End
   Begin GensymTw2Ctl.G2UiGateway G2UiGateway1 
      Left            =   240
      OleObjectBlob   =   "ItemHolderTest.frx":0078
      Top             =   0
   End
   Begin GensymTw2Ctl.G2ItemHolder G2ItemHolder2 
      Left            =   1440
      OleObjectBlob   =   "ItemHolderTest.frx":0158
      Top             =   0
   End
   Begin VB.Frame Frame1 
      Caption         =   "ItemHolder of MY-OBJECT"
      Height          =   1215
      Left            =   120
      TabIndex        =   1
      Top             =   480
      Width           =   2175
      Begin VB.CheckBox AutoDownload 
         Caption         =   "AutoDownload"
         Height          =   375
         Left            =   240
         TabIndex        =   3
         Top             =   720
         Width           =   1575
      End
      Begin VB.CheckBox AutoUpload 
         Caption         =   "AutoUpload"
         Height          =   375
         Left            =   240
         TabIndex        =   2
         Top             =   240
         Width           =   1575
      End
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Start"
      Height          =   735
      Left            =   120
      TabIndex        =   0
      Top             =   1800
      Width           =   2175
   End
End
Attribute VB_Name = "ItemHolderTestForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub AutoDownload_Click()
    If AutoDownload.Value = 0 Then
        G2ItemHolder1.AutoDownload = False
    Else
        G2ItemHolder1.AutoDownload = True
    End If
End Sub

Private Sub AutoUpload_Click()
    If AutoUpload.Value = 0 Then
        G2ItemHolder1.AutoUpload = False
    Else
        G2ItemHolder1.AutoUpload = True
    End If
End Sub

Private Sub Command1_Click()
    Dim X As Variant
    Dim struct As New G2Structure
    Dim symbol As New G2Symbol
    Dim sequence(1) As Variant
    
    
    struct.Member("float-member") = 5.5
    struct.Member("integer-member") = 5
    symbol.Value = "mem-ber"
    struct.Member("symbol-member") = symbol
    struct.Member("text-member") = "mem ber"
    struct.Member("empty-text-member") = ""
    struct.Member("truth-value-member") = True
    MsgBox "struct = " & struct.String
    X = struct.MemberNames
    
    If Not G2UiGateway1.IsConnected Then G2UiGateway1.Connect
    
    X = G2UiGateway1.CallG2Procedure("my-procedure", 9, "VB", False)
    MsgBox "MY-PROCEDURE() = " & X
    
    G2ItemHolder1.ReleaseItem
    G2ItemHolder1.Item = G2UiGateway1.GetNamedItem("MY-OBJECT")
    
    X = G2ItemHolder1.CallMethod("my-method")
    MsgBox "MY-OBJECT.MY-METHOD() = " & X
    
    G2ItemHolder2.Item = G2UiGateway1.GetNamedItem("MY-G2LIST")
    MsgBox "G2ItemHolder2.ElementType = " & G2ItemHolder2.ElementType
    MsgBox "G2ItemHolder2.ElementCount = " & G2ItemHolder2.ElementCount
    
    X = G2ItemHolder1.Attribute("attr-float")
    MsgBox "Attribute attr-float = " & X
    G2ItemHolder2.Element(0) = X
    X = 9.9
    G2ItemHolder1.Attribute("attr-float") = X
    
    X = G2ItemHolder1.Attribute("attr-integer")
    MsgBox "Attribute attr-integer = " & X
    G2ItemHolder2.Element(1) = X
    X = 22
    G2ItemHolder1.Attribute("attr-integer") = X
    
    X = G2ItemHolder1.Attribute("attr-sequence")
    MsgBox "Attribute attr-sequence, first member = " & X(0)
    X = Array(1, 2, 3)
    G2ItemHolder1.Attribute("attr-sequence") = X
    
    X = G2ItemHolder1.Attribute("attr-structure")
    MsgBox "Attribute attr-structure, member-text = " & X.Member("member-text")
    X = struct
    G2ItemHolder1.Attribute("attr-structure") = X
    
    X = G2ItemHolder1.Attribute("attr-symbol")
    MsgBox "Attribute attr-symbol = " & X.Value
    G2ItemHolder2.Element(2) = X
    X.Value = "new-symbol"
    G2ItemHolder1.Attribute("attr-symbol") = X
    
    X = G2ItemHolder1.Attribute("attr-text")
    MsgBox "Attribute attr-text = " & X
    G2ItemHolder2.Element(3) = X
    X = "new text"
    G2ItemHolder1.Attribute("attr-text") = X
    
    X = G2ItemHolder1.Attribute("attr-truth-value")
    MsgBox "Attribute attr-truth-value = " & X
    G2ItemHolder2.Element(4) = X
    X = True
    G2ItemHolder1.Attribute("attr-truth-value") = X
    
    G2ItemHolder2.Element(5) = G2ItemHolder1.Item
    
    G2ItemHolder2.Element(6) = struct
    
    If Not G2ItemHolder1.AutoUpload Then G2ItemHolder1.Upload
    If Not G2ItemHolder1.AutoDownload Then G2ItemHolder1.Download
    
    G2ItemHolder2.Item = G2UiGateway1.GetNamedItem("MY-G2ARRAY")
    MsgBox "G2ItemHolder2.ElementType = " & G2ItemHolder2.ElementType
    MsgBox "G2ItemHolder2.ElementCount = " & G2ItemHolder2.ElementCount
    
    X = G2ItemHolder1.Attribute("attr-float")
    MsgBox "Attribute attr-float = " & X
    G2ItemHolder2.Element(0) = X
    X = 9.9
    
    X = G2ItemHolder1.Attribute("attr-integer")
    MsgBox "Attribute attr-integer = " & X
    G2ItemHolder2.Element(1) = X
    X = 22
    
    X = G2ItemHolder1.Attribute("attr-symbol")
    MsgBox "Attribute attr-symbol = " & X.Value
    G2ItemHolder2.Element(2) = X
    
    X = G2ItemHolder1.Attribute("attr-text")
    MsgBox "Attribute attr-text = " & X
    G2ItemHolder2.Element(3) = X
    X = "new text"
    G2ItemHolder1.Attribute("attr-text") = X
    
    X = G2ItemHolder1.Attribute("attr-truth-value")
    MsgBox "Attribute attr-truth-value = " & X
    G2ItemHolder2.Element(4) = X
    X = True
    
    G2ItemHolder2.Element(5) = G2ItemHolder1.Item
    
    G2ItemHolder2.Element(6) = struct
    
    MsgBox "Seting MY-OBJECT.ATTR-TEXT to an empty string."
    G2ItemHolder1.Attribute("attr-text") = ""
    If Not G2ItemHolder1.AutoUpload Then G2ItemHolder1.Upload
    
    MsgBox "Seting MY-ARRAY.ELEMENT(3) to an empty string."
    G2ItemHolder2.Element(3) = ""
End Sub

Private Sub Form_Load()
    If G2ItemHolder1.AutoUpload Then
        AutoUpload.Value = 1
    Else
        AutoUpload.Value = 0
    End If
    
    If G2ItemHolder1.AutoDownload Then
        AutoDownload.Value = 1
    Else
        AutoDownload.Value = 0
    End If
End Sub

Private Sub G2ItemHolder1_SubscribedAttributeChanged(ByVal AttributeName As String, NewValue As Variant)
    MsgBox AttributeName & " changed"
'    MsgBox "Attribute " & AttributeName & " has changed to: " & NewValue
End Sub
