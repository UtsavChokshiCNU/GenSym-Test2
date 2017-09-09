VERSION 5.00
Object = "{AC4C85D1-B16C-11D1-A718-006008C5F933}#1.6#0"; "G2Com.dll"
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form frmItemRef 
   Caption         =   "ReadItem"
   ClientHeight    =   9600
   ClientLeft      =   4545
   ClientTop       =   1830
   ClientWidth     =   8130
   LinkTopic       =   "Form1"
   ScaleHeight     =   9600
   ScaleWidth      =   8130
   StartUpPosition =   1  'CenterOwner
   Begin VB.Frame frm03 
      Height          =   1095
      Left            =   6720
      TabIndex        =   48
      Top             =   0
      Width           =   1335
      Begin VB.CheckBox chkRename 
         Caption         =   "Rename"
         Height          =   195
         Left            =   240
         TabIndex        =   50
         Top             =   840
         Width           =   975
      End
      Begin VB.CommandButton btnCreate 
         Caption         =   "Create"
         Height          =   495
         Left            =   120
         TabIndex        =   49
         Top             =   240
         Width           =   1095
      End
   End
   Begin TabDlg.SSTab SSTab2 
      Height          =   2775
      Left            =   120
      TabIndex        =   19
      Top             =   720
      Width           =   4095
      _ExtentX        =   7223
      _ExtentY        =   4895
      _Version        =   393216
      TabOrientation  =   3
      TabHeight       =   520
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Batang"
         Size            =   8.25
         Charset         =   204
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      TabCaption(0)   =   "Comm"
      TabPicture(0)   =   "Conn.frx":0000
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "btnDiscon"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "cmdDisCon"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).Control(2)=   "btnConn"
      Tab(0).Control(2).Enabled=   0   'False
      Tab(0).Control(3)=   "btnRdWin"
      Tab(0).Control(3).Enabled=   0   'False
      Tab(0).Control(4)=   "btnRdItem"
      Tab(0).Control(4).Enabled=   0   'False
      Tab(0).Control(5)=   "btnGetWkspc"
      Tab(0).Control(5).Enabled=   0   'False
      Tab(0).Control(6)=   "btnSendItem"
      Tab(0).Control(6).Enabled=   0   'False
      Tab(0).Control(7)=   "btnSendText"
      Tab(0).Control(7).Enabled=   0   'False
      Tab(0).Control(8)=   "btnSendWin"
      Tab(0).Control(8).Enabled=   0   'False
      Tab(0).Control(9)=   "txtHost"
      Tab(0).Control(9).Enabled=   0   'False
      Tab(0).Control(10)=   "btnSendRef"
      Tab(0).Control(10).Enabled=   0   'False
      Tab(0).Control(11)=   "btnStudyH"
      Tab(0).Control(11).Enabled=   0   'False
      Tab(0).ControlCount=   12
      TabCaption(1)   =   "Edit"
      TabPicture(1)   =   "Conn.frx":001C
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "lblCN"
      Tab(1).Control(1)=   "lblName"
      Tab(1).Control(2)=   "lblVal"
      Tab(1).Control(3)=   "Label2"
      Tab(1).Control(4)=   "Label1"
      Tab(1).Control(5)=   "btnUnlink"
      Tab(1).Control(6)=   "btnDelLocal"
      Tab(1).Control(7)=   "btnModLocal"
      Tab(1).Control(8)=   "txtCN"
      Tab(1).Control(9)=   "txtName"
      Tab(1).Control(10)=   "txtVal"
      Tab(1).Control(11)=   "txtTXTAT"
      Tab(1).Control(12)=   "txtINTAT"
      Tab(1).ControlCount=   13
      TabCaption(2)   =   "-"
      TabPicture(2)   =   "Conn.frx":0038
      Tab(2).ControlEnabled=   0   'False
      Tab(2).Control(0)=   "btnBogus1"
      Tab(2).Control(1)=   "cmdBogus2"
      Tab(2).ControlCount=   2
      Begin VB.CommandButton btnStudyH 
         Caption         =   "Send Handle"
         Height          =   495
         Left            =   120
         TabIndex        =   54
         Top             =   2040
         Width           =   1095
      End
      Begin VB.CommandButton btnSendRef 
         Caption         =   "Send Ref"
         Height          =   495
         Left            =   2520
         TabIndex        =   53
         Top             =   2040
         Width           =   1095
      End
      Begin VB.TextBox txtHost 
         Height          =   375
         Left            =   1320
         TabIndex        =   52
         Top             =   2040
         Width           =   1095
      End
      Begin VB.CommandButton btnSendWin 
         Caption         =   "Send Window"
         Height          =   495
         Left            =   2520
         TabIndex        =   51
         Top             =   1440
         Width           =   1095
      End
      Begin VB.TextBox txtINTAT 
         Height          =   285
         Left            =   -73920
         TabIndex        =   43
         Top             =   1560
         Width           =   2415
      End
      Begin VB.TextBox txtTXTAT 
         Height          =   285
         Left            =   -73920
         TabIndex        =   42
         Top             =   1200
         Width           =   2415
      End
      Begin VB.TextBox txtVal 
         Height          =   285
         Left            =   -73920
         TabIndex        =   41
         Top             =   840
         Width           =   2415
      End
      Begin VB.TextBox txtName 
         Height          =   285
         Left            =   -73920
         TabIndex        =   40
         Top             =   480
         Width           =   2415
      End
      Begin VB.TextBox txtCN 
         Height          =   285
         Left            =   -73920
         TabIndex        =   39
         Top             =   120
         Width           =   2415
      End
      Begin VB.CommandButton btnModLocal 
         Caption         =   "Local Mod"
         Height          =   495
         Left            =   -72480
         TabIndex        =   38
         Top             =   2040
         Width           =   1095
      End
      Begin VB.CommandButton btnDelLocal 
         Caption         =   "Delete Local"
         Height          =   495
         Left            =   -73680
         TabIndex        =   37
         Top             =   2040
         Width           =   1095
      End
      Begin VB.CommandButton btnUnlink 
         Caption         =   "Unlink"
         Height          =   495
         Left            =   -74880
         TabIndex        =   36
         Top             =   2040
         Width           =   1095
      End
      Begin VB.CommandButton btnBogus1 
         Caption         =   "Bogus Attr"
         Height          =   495
         Left            =   -73560
         TabIndex        =   35
         Top             =   1440
         Width           =   1095
      End
      Begin VB.CommandButton cmdBogus2 
         Caption         =   "Bogus Type"
         Height          =   495
         Left            =   -73560
         TabIndex        =   34
         Top             =   720
         Width           =   1095
      End
      Begin VB.CommandButton btnSendText 
         Caption         =   "Send Text"
         Height          =   495
         Left            =   2520
         TabIndex        =   27
         Top             =   240
         Width           =   1095
      End
      Begin VB.CommandButton btnSendItem 
         Caption         =   "SendItem"
         Height          =   495
         Left            =   2520
         TabIndex        =   26
         Top             =   840
         Width           =   1095
      End
      Begin VB.CommandButton btnGetWkspc 
         Caption         =   "Read Wkspc"
         Height          =   495
         Left            =   1320
         TabIndex        =   25
         Top             =   840
         Width           =   1095
      End
      Begin VB.CommandButton btnRdItem 
         Caption         =   "Read Item"
         Height          =   495
         Left            =   1320
         TabIndex        =   24
         Top             =   240
         Width           =   1095
      End
      Begin VB.CommandButton btnRdWin 
         Caption         =   "Read Window"
         Height          =   495
         Left            =   1320
         TabIndex        =   23
         Top             =   1440
         Width           =   1095
      End
      Begin VB.CommandButton btnConn 
         Caption         =   "Connect"
         Height          =   495
         Left            =   120
         TabIndex        =   22
         Top             =   240
         Width           =   1095
      End
      Begin VB.CommandButton cmdDisCon 
         Caption         =   "Discon/Conn"
         Height          =   495
         Left            =   120
         TabIndex        =   21
         Top             =   1440
         Width           =   1095
      End
      Begin VB.CommandButton btnDiscon 
         Caption         =   "Disconnect"
         Height          =   495
         Left            =   120
         TabIndex        =   20
         Top             =   840
         Width           =   1095
      End
      Begin VB.Label Label1 
         Alignment       =   1  'Right Justify
         Caption         =   "TXTAT:"
         Height          =   255
         Left            =   -74880
         TabIndex        =   32
         Top             =   1240
         Width           =   900
      End
      Begin VB.Label Label2 
         Alignment       =   1  'Right Justify
         Caption         =   "INTAT:"
         Height          =   255
         Left            =   -74880
         TabIndex        =   31
         Top             =   1600
         Width           =   900
      End
      Begin VB.Label lblVal 
         Alignment       =   1  'Right Justify
         Caption         =   "Value:"
         Height          =   255
         Left            =   -74880
         TabIndex        =   30
         Top             =   880
         Width           =   900
      End
      Begin VB.Label lblName 
         Alignment       =   1  'Right Justify
         Caption         =   "Name:"
         Height          =   255
         Left            =   -74880
         TabIndex        =   29
         Top             =   520
         Width           =   900
      End
      Begin VB.Label lblCN 
         Alignment       =   1  'Right Justify
         Caption         =   "ClassName:"
         Height          =   255
         Left            =   -74880
         TabIndex        =   28
         Top             =   160
         Width           =   900
      End
   End
   Begin VB.CommandButton cmdRefresh 
      Caption         =   "Refresh"
      Height          =   495
      Left            =   6840
      TabIndex        =   8
      Top             =   1800
      Width           =   1095
   End
   Begin VB.CommandButton cmdDelete 
      Caption         =   "Delete"
      Height          =   495
      Left            =   6840
      TabIndex        =   7
      Top             =   2400
      Width           =   1095
   End
   Begin VB.CommandButton btnUpdate 
      Caption         =   "Update"
      Height          =   495
      Left            =   6840
      TabIndex        =   6
      Top             =   1200
      Width           =   1095
   End
   Begin TabDlg.SSTab tab02 
      Height          =   4100
      Left            =   4440
      TabIndex        =   5
      Top             =   120
      Width           =   2175
      _ExtentX        =   3836
      _ExtentY        =   7223
      _Version        =   393216
      TabOrientation  =   3
      Tabs            =   2
      TabsPerRow      =   2
      TabHeight       =   520
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Futura Md BT"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      TabCaption(0)   =   "Items"
      TabPicture(0)   =   "Conn.frx":0054
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "frm01"
      Tab(0).Control(0).Enabled=   0   'False
      Tab(0).Control(1)=   "chkBogus"
      Tab(0).Control(1).Enabled=   0   'False
      Tab(0).Control(2)=   "chkTxtat"
      Tab(0).Control(2).Enabled=   0   'False
      Tab(0).Control(3)=   "chkIntat"
      Tab(0).Control(3).Enabled=   0   'False
      Tab(0).Control(4)=   "chkValue"
      Tab(0).Control(4).Enabled=   0   'False
      Tab(0).Control(5)=   "chkAll"
      Tab(0).Control(5).Enabled=   0   'False
      Tab(0).Control(6)=   "txtCustom"
      Tab(0).Control(6).Enabled=   0   'False
      Tab(0).ControlCount=   7
      TabCaption(1)   =   "Workspaces"
      TabPicture(1)   =   "Conn.frx":0070
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "frm02"
      Tab(1).Control(1)=   "Image1"
      Tab(1).ControlCount=   2
      Begin VB.Frame frm02 
         Caption         =   "Notify On"
         Height          =   1575
         Left            =   -74880
         TabIndex        =   45
         Top             =   240
         Width           =   1575
         Begin VB.OptionButton optWID 
            Caption         =   "Item Removed"
            Height          =   255
            Left            =   120
            TabIndex        =   47
            Top             =   960
            Width           =   1350
         End
         Begin VB.OptionButton optWIA 
            Caption         =   "Item Added"
            Height          =   375
            Left            =   120
            TabIndex        =   46
            Top             =   480
            Width           =   1335
         End
      End
      Begin VB.TextBox txtCustom 
         BeginProperty Font 
            Name            =   "Arial"
            Size            =   8.25
            Charset         =   204
            Weight          =   700
            Underline       =   0   'False
            Italic          =   0   'False
            Strikethrough   =   0   'False
         EndProperty
         Height          =   285
         Left            =   480
         TabIndex        =   44
         Text            =   "AXL"
         Top             =   2160
         Visible         =   0   'False
         Width           =   975
      End
      Begin VB.CheckBox chkAll 
         Caption         =   "All"
         Height          =   255
         Left            =   480
         TabIndex        =   18
         Top             =   2280
         Width           =   975
      End
      Begin VB.CheckBox chkValue 
         Caption         =   "Value"
         Height          =   255
         Left            =   480
         TabIndex        =   17
         Top             =   2640
         Width           =   855
      End
      Begin VB.CheckBox chkIntat 
         Caption         =   "Intat"
         Height          =   255
         Left            =   480
         TabIndex        =   16
         Top             =   3000
         Width           =   855
      End
      Begin VB.CheckBox chkTxtat 
         Caption         =   "Txtat"
         Height          =   255
         Left            =   480
         TabIndex        =   15
         Top             =   3360
         Width           =   735
      End
      Begin VB.CheckBox chkBogus 
         Caption         =   "Bogus"
         Height          =   255
         Left            =   480
         TabIndex        =   14
         Top             =   3720
         Width           =   975
      End
      Begin VB.Frame frm01 
         Caption         =   "Subscribe"
         Height          =   1875
         Left            =   360
         TabIndex        =   9
         Top             =   120
         Width           =   1215
         Begin VB.OptionButton optSelect 
            Caption         =   "Selection"
            Height          =   255
            Left            =   120
            TabIndex        =   56
            Top             =   1540
            Width           =   975
         End
         Begin VB.OptionButton optVal 
            Caption         =   "Value"
            Height          =   255
            Left            =   120
            TabIndex        =   55
            Top             =   1280
            Width           =   855
         End
         Begin VB.OptionButton optDelete 
            Caption         =   "Delete"
            Height          =   255
            Left            =   120
            TabIndex        =   13
            Top             =   240
            Width           =   855
         End
         Begin VB.OptionButton optModify 
            Caption         =   "Modify"
            Height          =   255
            Left            =   120
            TabIndex        =   12
            Top             =   500
            Width           =   975
         End
         Begin VB.OptionButton optColor 
            Caption         =   "Color Chg"
            Height          =   255
            Left            =   120
            TabIndex        =   11
            Top             =   760
            Width           =   1050
         End
         Begin VB.OptionButton optCustom 
            Caption         =   "Custom"
            Height          =   255
            Left            =   120
            TabIndex        =   10
            Top             =   1020
            Width           =   855
         End
      End
      Begin VB.Image Image1 
         Height          =   2055
         Left            =   -74880
         Picture         =   "Conn.frx":008C
         Stretch         =   -1  'True
         Top             =   1920
         Width           =   1575
      End
   End
   Begin VB.TextBox txtRpt 
      Height          =   5175
      Left            =   120
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   4
      Top             =   4320
      Width           =   7695
   End
   Begin VB.CommandButton btnUnsubscribe 
      Caption         =   "Unsubscribe"
      Height          =   495
      Left            =   6840
      TabIndex        =   3
      Top             =   3600
      Width           =   1095
   End
   Begin VB.CommandButton btnSubscribe 
      Caption         =   "Subscribe"
      Height          =   495
      Left            =   6840
      TabIndex        =   2
      Top             =   3000
      Width           =   1095
   End
   Begin VB.CommandButton btnClear 
      Caption         =   "Clear Rpt"
      Height          =   495
      Left            =   2640
      TabIndex        =   1
      Top             =   3600
      Width           =   1095
   End
   Begin VB.CommandButton btnReport 
      Caption         =   "Report"
      Height          =   495
      Left            =   240
      TabIndex        =   0
      Top             =   3600
      Width           =   1095
   End
   Begin VB.Label lblType 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      Caption         =   "None"
      BeginProperty Font 
         Name            =   "Batang"
         Size            =   18
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   720
      TabIndex        =   33
      Top             =   120
      Width           =   2655
   End
   Begin GensymAxlCtl.G2Gateway AXL2 
      Left            =   7440
      OleObjectBlob   =   "Conn.frx":6CE3
      Top             =   3720
   End
   Begin GensymAxlCtl.G2Gateway AXL 
      Left            =   6840
      OleObjectBlob   =   "Conn.frx":6D65
      Top             =   3720
   End
   Begin VB.Line Line1 
      BorderWidth     =   2
      X1              =   4305
      X2              =   4305
      Y1              =   120
      Y2              =   4320
   End
End
Attribute VB_Name = "frmItemRef"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
    Dim nWSCt As Integer
    Dim git   As G2Item
    Dim gitd  As G2Item
    Dim crNr  As Integer
    Dim lHndl As Long
    Dim ws(0 To 1) As Integer
    
Private Sub App2Rpt(msg As String)
    If txtRpt.Text = "" Then
        txtRpt.Text = msg
    Else
        txtRpt.Text = txtRpt.Text & Chr(13) & Chr(10) & msg
    End If
End Sub
Private Sub Classify()
    If git Is Nothing Then
        lblType = "None"
    ElseIf TypeName(git) = "IG2Workspace" Then
        lblType = "Workspace"
    ElseIf TypeName(git) = "IG2Item2" Then
        lblType = "Item"
    ElseIf TypeName(git) = "IG2Window" Then
        lblType = "Window"
    Else
        lblType = "Unknown"
    End If
End Sub
Private Function CountChks() As Integer
Dim n As Integer

    If chkAll Then
        CountChks = 0
        Exit Function
    End If
    n = 0
    If chkValue Then n = n + 1
    If chkIntat Then n = n + 1
    If chkTxtat Then n = n + 1
    If chkBogus Then n = n + 1
    If n = 0 Then
        CountChks = -1
    Else
        CountChks = n
    End If
End Function
Private Sub AXL_G2Connected()
    App2Rpt ("Connected")
End Sub

Private Sub AXL_CustomEvent(localItem As GensymAxlCtl.G2Item, ByVal EventName As String, ByVal newValue As Variant, ByVal subscriptionHndl As Long, ByVal userData As Variant)
    App2Rpt ("Custom Event of type " & EventName & " triggered for item " & localItem.Name)
    App2Rpt ("New Value = " & CStr(newValue) & ".  Handle = " & CStr(subscriptionHndl))
End Sub

Private Sub AXL_G2Disconnected()
    App2Rpt ("Disconnected")
End Sub

Private Sub AXL_ItemDeleted(localItem As GensymAxlCtl.G2Item, ByVal subscriptionHndl As Long, ByVal userData As Variant)
    App2Rpt ("Item of type " & CStr(localItem.ClassName) & " deleted.  Sub handle:" & CStr(subscriptionHndl) & ".  User ID = " & userData)
End Sub

Private Sub AXL_AttributeModified(localItem As GensymAxlCtl.G2Item, ByVal attributeName As String, ByVal newValue As Variant, ByVal subscriptionHndl As Long, ByVal userData As Variant)
    App2Rpt ("Item of type " & CStr(localItem.ClassName) & " modified.")
    App2Rpt ("+ Attribute Name = " & attributeName & ".  New Value = " & CStr(newValue) & ".")
    App2Rpt ("+ Sub handle:" & CStr(subscriptionHndl) & ".  User ID = " & userData & ".")
End Sub

Private Sub AXL_IconColorChanged(localItem As GensymAxlCtl.G2Item, ByVal subscriptionHndl As Long, ByVal chgStruct As Object, ByVal userData As Variant)
    Dim stru As G2Structure
    Dim n As Integer, i As Integer
    Dim atNames As Variant, atVals As Variant
    
    App2Rpt ("Color of Icon Changed")
    App2Rpt (TypeName(chgStruct))
    Set stru = chgStruct
    n = stru.Count
    atNames = stru.Names
    atVals = stru.Values
    For i = 0 To n - 1
        App2Rpt atNames(i) & " : " & stru(i) & " : " & TypeName(stru(i))
    Next i
    
End Sub

Private Sub AXL_ItemAdded(localItem As GensymAxlCtl.G2Workspace, ByVal subscriptionHndl As Long, ByVal userData As Variant)
    Dim strDets    As String
    Dim wsAsIt     As G2Item
    
    Set wsAsIt = localItem
    If wsAsIt.Name > "" Then
        strDets = wsAsIt.Name
    Else
        strDets = "with UUID = " & wsAsIt.Reference.UUID
    End If
    App2Rpt ("Item Added to Workspace " & strDets & ".")
    App2Rpt ("+ User Data = " & CStr(userData))
End Sub


Private Sub AXL_ItemRemoved(localItem As GensymAxlCtl.G2Workspace, ByVal subscriptionHndl As Long, ByVal userData As Variant)
    Dim strDets    As String
    Dim wsAsIt     As G2Item
    
    Set wsAsIt = localItem
    If wsAsIt.Name > "" Then
        strDets = wsAsIt.Name
    Else
        strDets = "with UUID = " & wsAsIt.Reference.UUID
    End If
    App2Rpt ("Item Removed From Workspace " & strDets & ".")
    App2Rpt ("+ User Data = " & CStr(userData))
End Sub

Private Sub AXL_ItemSelected(localWindow As GensymAxlCtl.G2Window, ByVal subscriptionHandle As Long, ByVal userData As Variant)
    Dim g2li As G2Item
    
    Set g2li = localWindow
    App2Rpt ("Item selected in window with UUID " & g2li.Reference.UUID)
    App2Rpt ("+ handle = " & CStr(subscriptionHandle) & "   User Data = " & CStr(userData))
End Sub

Private Sub AXL_RpcCalled(ByVal ProcedureName As String, InputArguments As Variant, ReturnArguments As Variant)
    App2Rpt ("RPC Called")
    DoEvents
    If ProcedureName = "Nr1" Then
        txtRpt = txtRpt & Chr(13) & Chr(10) & "G2COM-Call " & ProcedureName & " : " & InputArguments
        ReturnArguments = git.Reference
    Else
        Set git = InputArguments
        ReturnArguments = "Ready to test linkage"
    End If
End Sub

Private Sub axlo_G2Connected(index As Integer)
    App2Rpt ("Axlo(1) connected")
End Sub

Private Sub axlo_G2Disconnected(index As Integer)
    App2Rpt ("Axlo(1) disconnected")
End Sub


Private Sub AXL_ValueChanged(localItem As GensymAxlCtl.G2Item, ByVal newValue As Variant, ByVal subscriptionHndl As Long, ByVal userData As Variant)
    App2Rpt ("Value of " & git.Name & " changed to " & CStr(newValue))
    App2Rpt ("+handle = " & CStr(subscriptionHndl) & ".  User Data = " & CStr(userData))
    
End Sub

Private Sub btnBogus1_Click()
    If git Is Nothing Then
        App2Rpt ("Item has not yet been read")
        Exit Sub
    End If
    Call git.Add("BogusAttr", "Fail")
    Call git.Symbolize("BogusAttr", True)
    App2Rpt ("Bogus Attribute Added to Item")
End Sub

Private Sub btnClear_Click()
    txtRpt = ""
End Sub

Private Sub btnConn_Click()
    AXL.Connect (True)
End Sub

Private Sub btnCreate_Click()
    If git Is Nothing Then
        App2Rpt ("Cannot Create.  Item has not yet been read or created locally")
        Exit Sub
    End If
    
On Error GoTo CreateErr
    If chkRename Then
        git.Name = "VBUDC" & CStr(crNr)
        crNr = crNr + 1
    End If
    git.Create AXL
    App2Rpt ("Create Succeeded")
    Exit Sub
CreateErr:
    txtRpt.Text = "Error Creating Item: " & CStr(Err.Number) & " : " & Err.Description
End Sub

Private Sub btnDelLocal_Click()
    Set git = Nothing
    txtRpt.Text = "Local copy of item deleted."
    Classify
End Sub

Private Sub btnDiscon_Click()
    AXL.Disconnect
End Sub

Private Sub btnDup_Click()
    On Error GoTo DupFailed
    If Not git Is Nothing Then
        Set gitd = git.Duplicate
        txtRpt.Text = "Duplication Succeeded"
    Else
        txtRpt.Text = "Nothing to duplicate"
    End If
    Exit Sub
DupFailed:
    txtRpt.Text = "Error Duplicating Item: " & CStr(Err.Number) & " : " & Err.Description
End Sub

Private Sub btnGetWkspc_Click()

    Dim vbMgc As G2Workspace
    
On Error GoTo GetErr
    Set git = AXL.Call("Send-Wkspc")
    txtRpt.Text = "Workspace Read"
    Classify
    Exit Sub
GetErr:
    txtRpt = txtRpt & Chr(13) & Chr(10) & "Error Getting Workspace: " & CStr(Err.Number) & " : " & Err.Description
End Sub

Private Sub btnModLocal_Click()
    Dim i As Integer
    Dim modified As Boolean
    
    If git Is Nothing Then
        Set git = New G2Item
        git.ClassName = "UDC"
        git.Name = "AUDC" & crNr
        crNr = crNr + 1
        git.Add "TXTAT", ""
        git.Add "INTAT", 0
    End If
    On Error GoTo nameNext
    If txtCN.Text > "" Then
        git.ClassName = txtCN.Text
        modified = True
    End If
nameNext:
    On Error GoTo valNext
    If txtName.Text > "" Then
        git.Name = txtName.Text
        modified = True
    End If
valNext:
    On Error GoTo intNext
    i = CInt(txtVal)
    git.Value = i
    modified = True
intNext:
    On Error GoTo textNext
    If txtINTAT.Text > "" Then
        i = CInt(txtINTAT)
        git("INTAT") = i
        modified = True
    End If
textNext:
    On Error GoTo 0
    If txtTXTAT <> "" Then
        git("TXTAT") = txtTXTAT.Text
        modified = True
    End If
    If modified Then txtRpt.Text = "Modified"
End Sub

Private Sub btnRdItem_Click()
    Dim atNames, atTypes, x
    Dim i As Integer
    
On Error GoTo GetErr
    Set git = AXL.Call("SendItem")
    txtRpt.Text = "Item Read"
    Classify
    Exit Sub
GetErr:
    txtRpt = txtRpt & Chr(13) & Chr(10) & "Error Getting Item: " & CStr(Err.Number) & " : " & Err.Description
End Sub

Private Sub btnRdWin_Click()
    Dim host As String
    
    On Error GoTo GetErr
    Set git = AXL.Call("Send-Window", txtHost.Text)
    txtRpt.Text = "Window Read"
    Classify
    Exit Sub
GetErr:
    txtRpt = txtRpt & Chr(13) & Chr(10) & "Error Getting Window: " & CStr(Err.Number) & " : " & Err.Description
End Sub

Private Sub btnReport_Click()
    Dim atNames, atTypes, x
    Dim i           As Integer, n As Integer
    Dim vx          As Variant
    Dim SubscrpLine As String
    
    If git Is Nothing Then
        txtRpt.Text = "Item has not been read or created"
        Exit Sub
    End If

    App2Rpt ("Item is of type " & TypeName(git))
    App2Rpt ("Class Name: " & git.ClassName)
    App2Rpt ("Name: " & git.Name)
On Error GoTo NoVal
    App2Rpt ("Value: " & CStr(git.Value))
    GoTo MergePaths
NoVal:
    App2Rpt ("No Value")
MergePaths:
    n = git.Count
    atNames = git.AttrNames
    atTypes = git.AttrTypes
    For i = 0 To n - 1
        If atTypes(i) <> 11 Then
            App2Rpt (CStr(i + 1) & ": " & atNames(i) & ": " & git(i))
        End If
    Next i
    
    If git.Linked Then
        App2Rpt ("Linked to an item in G2")
        App2Rpt ("UUID = " & git.Reference.UUID)
    Else
        App2Rpt ("Not linked to an item in G2")
    End If
    App2Rpt ("Subscriptions:")
    vx = git.Subscriptions()
    For i = LBound(vx) To UBound(vx)
        SubscrpLine = CStr(vx(i, 0))
        If vx(i, 1) = 1 Then
            SubscrpLine = SubscrpLine & " : Modify : " & vx(i, 2)
        ElseIf vx(i, 1) = 2 Then
            SubscrpLine = SubscrpLine & " : Delete"
        ElseIf vx(i, 1) = 3 Then
            SubscrpLine = SubscrpLine & " : Color Change"
        ElseIf vx(i, 1) = 4 Then
            SubscrpLine = SubscrpLine & " : Custom : " & vx(i, 2)
        ElseIf vx(i, 1) = 5 Then
            SubscrpLine = SubscrpLine & " : Value change"
        ElseIf vx(i, 1) = 6 Then
            SubscrpLine = SubscrpLine & " : Add Item to Workspace"
        ElseIf vx(i, 1) = 7 Then
            SubscrpLine = SubscrpLine & " : Delete Item From Workspace"
        Else
            SubscrpLine = SubscrpLine & " : Update this program"
        End If
        App2Rpt (SubscrpLine)
    Next i
    App2Rpt ("================================")
        
    Exit Sub

End Sub

Private Sub btnSendItem_Click()
    Dim gout As New G2Item
    
    gout.ClassName = "UDC"
    gout.Name = "Ted"
    gout.Value = 6
    gout.Add "intat", 3
    gout.Add "txtat", "Guten Abend· ‹Û¯Ú ¿ÍÛ„Ú‚"
    On Error GoTo SendErr
    AXL.Start "KeepItem", gout
    Exit Sub
SendErr:
    txtRpt = "Send of text message failed: " & CStr(Err.Number) & " : " & Err.Description
End Sub

Private Sub btnSendRef_Click()
    If git Is Nothing Then
        txtRpt.Text = "Item has not been read or initialized"
        Exit Sub
    ElseIf Not git.Linked Then
        txtRpt.Text = "Item is not linked.  Can't send reference"
        Exit Sub
    End If
    On Error GoTo SendRefError
    AXL.Start "TestTrans", git.Reference
    App2Rpt ("Sent Reference To G2.  Check Message Board")
    Exit Sub
SendRefError:
    txtRpt.Text = "Sending Reference Failed: " & CStr(Err.Number) & " : " & Err.Description
End Sub

Private Sub btnSendText_Click()
    AXL.Start "PostMsg", "Good Evening Ã. »ÌÚÂÌÚËÓÌ"
End Sub

Private Sub btnSendWin_Click()
    Dim winNr   As Integer
    Dim uruuid  As String
    Dim scratch As Long
    
    If git Is Nothing Then
        txtRpt.Text = "Item has not been read or initialized"
    ElseIf TypeName(git) <> "IG2Window" Then
        txtRpt.Text = "Item is not a G2-WINDOW"
    Else
        If git.Name = "Porangatu" Then
            winNr = 0
        Else
            winNr = 1
        End If
        ws(winNr) = IIf(ws(winNr) = 0, 1, 0)
        ' Call git.Reference.git(uruuid, scratch)
        Call AXL.Start("EXWS", git.Reference, ws(winNr))
    End If
End Sub

Private Sub btnStudyH_Click()
    AXL.Start "StudyH", git.Reference
End Sub

Private Sub btnSubscribe_Click()
    Dim toWhat     As String
    Dim vToWhat    As Variant
    Dim hndlOrList As Variant
    Dim n          As Integer
    Dim i          As Integer
    Dim atlist()   As String
    Dim evName     As String
    Dim tws        As G2Workspace
    Dim twin       As G2Window
    
    If git Is Nothing Then
        txtRpt.Text = "Cannot subscribe.  Item has not been read or initialized."
    ElseIf Not git.Linked Then
        txtRpt.Text = "Cannot subscribe.  Not linked to remote item."
    Else
        On Error GoTo SubscribeFailed
        If tab02.Tab = 0 Then
            If optDelete Then
                lHndl = git.SubscribeToDeletion("Tag for Delete Notification")
                txtRpt.Text = "Subscribed to delete"
                Exit Sub
            ElseIf optColor Then
                lHndl = git.SubscribeToIconColorChange(3)
                txtRpt.Text = "Subscribed to icon color change"
                Exit Sub
            ElseIf optCustom Then
                If txtCustom = "" Then
                    evName = "AXL"
                Else
                    evName = txtCustom.Text
                End If
                lHndl = git.SubscribeToCustomEvent(evName, 2.5)
                txtRpt.Text = "Subscribed to custom event """ & evName & """"
                Exit Sub
            ElseIf optVal Then
                lHndl = git.SubscribeToValueChange(True)
                txtRpt.Text = "Subscribed to value change "
                Exit Sub
            ElseIf optSelect Then
                If TypeName(git) = "IG2Window" Then
                    Set twin = git
                    lHndl = twin.SubscribeToSelection(47)
                    App2Rpt ("Subscribed to selection")
                    Exit Sub
                Else
                    txtRpt.Text = "Current item is not a G2 Window"
                    Exit Sub
                End If
            Else
                vToWhat = "ALL"
                n = CountChks()
                If n = -1 Then
                    txtRpt.Text = "Nothing to subscribe to"
                    Exit Sub
                ElseIf n = 1 Then
                    If chkValue Then
                        toWhat = "VALUE"
                    ElseIf chkIntat Then
                        toWhat = "INTAT"
                    ElseIf chkTxtat Then
                        toWhat = "TXTAT"
                    ElseIf chkBogus Then
                        toWhat = "BOGUS"
                    End If
                    vToWhat = toWhat
                ElseIf n > 1 Then
                    ReDim atlist(1 To n)
                    i = 1
                    If chkValue Then
                        toWhat = "VALUE"
                        atlist(i) = "VALUE"
                        i = i + 1
                    End If
                    If chkIntat Then
                        toWhat = "INTAT"
                        atlist(i) = "INTAT"
                        i = i + 1
                    End If
                    If chkTxtat Then
                        toWhat = "TXTAT"
                        atlist(i) = "TXTAT"
                        i = i + 1
                    End If
                    If chkBogus Then
                        toWhat = "BOGUS"
                        atlist(i) = "BOGUS"
                    End If
                    vToWhat = atlist
                End If
            End If
            hndlOrList = git.SubscribeToAttributeModification(vToWhat, "User-defined tag")
            txtRpt.Text = "Subscribed"
            If TypeName(hndlOrList) = "Long" Then
                lHndl = hndlOrList
            End If
        ElseIf tab02.Tab = 1 Then
            If TypeName(git) = "IG2Workspace" Then
                Set tws = git
                If optWIA Then
                    lHndl = tws.SubscribeToItemAddition("WIA")
                    App2Rpt ("Subscribed to ""Item added to WS"".  Handle = " & CStr(lHndl))
                ElseIf optWID Then
                    lHndl = tws.SubscribeToItemRemoval("WID")
                    App2Rpt ("Subscribed to ""Item removal from WS"".  Handle = " & CStr(lHndl))
                End If
            Else
                txtRpt = "Loaded item is not a workspace"
            End If
        End If
    End If
    Exit Sub
SubscribeFailed:
    txtRpt.Text = "Subscribe Failed: " & CStr(Err.Number) & " : " & Err.Description
End Sub

Private Sub btnUnlink_Click()
    If Not git Is Nothing Then
        git.Unlink
        txtRpt.Text = "Unlink Succeeded."
        Classify
    Else
        txtRpt.Text = "Item has not been read or initialized."
    End If
    Exit Sub
UnlinkError:
    txtRpt.Text = "Unlink Failed: " & CStr(Err.Number) & " : " & Err.Description
End Sub

Private Sub btnUnsubscribe_Click()
    Dim vFromWhat   As Variant
    Dim atlist()
    Dim i           As Integer
    Dim n           As Integer
    Dim wsa         As G2Workspace
    Dim wina        As G2Window

    ' Rule out the cases that fail for every subscription type
    ' --------------------------------------------------------
    If git Is Nothing Then
        txtRpt.Text = "Cannot unsubscribe.  Item has not been read or initialized."
    ElseIf Not git.Linked Then
        txtRpt.Text = "Cannot unsubscribe.  Not linked to remote item."
    Else
        On Error GoTo UnsubscribeFailed
        
        ' Process Unsubscribing to G2Item Events
        ' --------------------------------------
        If tab02.Tab = 0 Then
            If optDelete Then
                git.UnsubscribeFromDeletion
                App2Rpt ("Unsubscribed from delete")
                Exit Sub
            ElseIf optColor Then
                git.UnsubscribeFromIconColorChange
                App2Rpt ("Unsubscribed from color change")
                Exit Sub
            ElseIf optCustom Then
                If txtCustom.Text > "" Then
                    git.UnsubscribeFromCustomEvent (txtCustom.Text)
                    App2Rpt ("Unsubscribed from custom event " & txtCustom.Text)
                    Exit Sub
                Else
                    App2Rpt ("You must specify event name")
                End If
            ElseIf optVal Then
                git.UnsubscribeFromValueChange
                    App2Rpt ("Unsubscribed from value change.")
                    Exit Sub
            ElseIf optSelect Then
                If TypeName(git) = "IG2Window" Then
                    Set wina = git
                    wina.UnsubscribeFromSelection
                    App2Rpt ("Unsubscribed from Selection")
                    Exit Sub
                Else
                    App2Rpt ("Item is not a G2Window")
                End If
            Else
                n = CountChks()  ' Returns 0 if All is checked
                If n = 0 Then    ' Returns -1 is nothing is checked
                    git.UnsubscribeFromAll
                    App2Rpt ("Canceled ALL Subscriptions")
                    Exit Sub
                ElseIf n = 1 Then
                    If chkValue Then
                        vFromWhat = "VALUE"
                    ElseIf chkIntat Then
                        vFromWhat = "INTAT"
                    ElseIf chkTxtat Then
                        vFromWhat = "TXTAT"
                    ElseIf chkBogus Then
                        vFromWhat = "BOGUS"
                    End If
                ElseIf n > 1 Then
                    ReDim atlist(1 To n)
                    i = 1
                    If chkValue Then
                        atlist(i) = "VALUE"
                        i = i + 1
                    End If
                    If chkIntat Then
                        atlist(i) = "INTAT"
                        i = i + 1
                    End If
                    If chkTxtat Then
                        atlist(i) = "TXTAT"
                        i = i + 1
                    End If
                    If chkBogus Then
                        atlist(i) = "BOGUS"
                    End If
                    vFromWhat = atlist
                Else
                    App2Rpt ("Nothing was checked")
                End If
            End If
            git.UnsubscribeFromAttributeModification (vFromWhat)
            App2Rpt ("Unsubscribed")
        ElseIf tab02.Tab = 1 Then
            If TypeName(git) = "IG2Workspace" Then
                Set wsa = git
                If optWIA Then
                    wsa.UnsubscribeFromItemAddition
                    App2Rpt ("Unsubscribed From ""Item Added to Workspace"".")
                    Exit Sub
                ElseIf optWID Then
                    wsa.UnsubscribeFromItemRemoval
                    App2Rpt ("Unsubscribed From ""Item Deleted from Workspace"".")
                    Exit Sub
                End If
            Else
                txtRpt.Text = "Item is not a workspace"
            End If
        End If
    End If
    Exit Sub
UnsubscribeFailed:
    txtRpt.Text = "Unsubscribe Failed: " & CStr(Err.Number) & " : " & Err.Description
End Sub

Private Sub btnUpdate_Click()
    If git Is Nothing Then
        txtRpt.Text = "Item has not been read yet"
        Exit Sub
    End If
    On Error GoTo UpdateFailed
    git.Update
    txtRpt.Text = "Updated Succeeded"
    Exit Sub
UpdateFailed:
    txtRpt.Text = "Update Failed: " & CStr(Err.Number) & " : " & Err.Description
End Sub

Private Sub cmdBogus2_Click()
    If git Is Nothing Then
        txtRpt.Text = "Item has not been read yet"
        Exit Sub
    End If
    git.Remove ("INTAT")
    Call git.Add("INTAT", "Not an Integer")
    txtRpt.Text = "Intat Attibute changed to text"
End Sub

Private Sub cmdDelete_Click()
    If git Is Nothing Then
        txtRpt.Text = "Item has not been read yet"
        Exit Sub
    End If
On Error GoTo RptEr
    git.Delete
    txtRpt.Text = "Delete Succeeded"
    Exit Sub
RptEr:
    txtRpt.Text = "Delete Failed: " & CStr(Err.Number) & " : " & Err.Description
End Sub

Private Sub cmdDisCon_Click()
    AXL.Disconnect
    AXL.Connect (False)
End Sub

Private Sub cmdRefresh_Click()
On Error GoTo ErrMsg
    git.Refresh
    txtRpt.Text = "Item Refreshed"
    Exit Sub
ErrMsg:
    txtRpt.Text = "Refresh of Item Failed: " & CStr(Err.Number) & " : " & Err.Description
End Sub
Private Sub Command1_Click()
    Dim cron As New G2Item
    Dim svuid As String
    Dim itr As New G2ItemRef
    
    cron.ClassName = "UDC"
    cron.Name = "Second"
    Call cron.Add("txtat", "from axl")
    cron.Create AXL2
    svuid = cron.Reference.UUID
    itr.Gateway = AXL
    itr.UUID = svuid
    
    git.Unlink
    git.Link itr
    
    App2Rpt ("Linked to new item")
    
End Sub

Private Sub Command2_Click()

End Sub

Private Sub Form_Load()
    nWSCt = 1
    crNr = 1
    optModify.Value = True
    lHndl = -1
    
End Sub

Private Sub Label3_Click()

End Sub

Private Sub lblType_Change()
    If lblType.Caption = "None" Then
        btnSubscribe.Enabled = False
        btnUnsubscribe.Enabled = False
    ElseIf Caption = "Workspace" Then
        btnSubscribe.Enabled = True
        btnUnsubscribe.Enabled = True
    End If
End Sub

Private Sub optColor_Click()
    chkAll.Visible = False
    chkValue.Visible = False
    chkTxtat.Visible = False
    chkIntat.Visible = False
    chkBogus.Visible = False
    txtCustom.Visible = False
End Sub

Private Sub optCustom_Click()
    chkAll.Visible = False
    chkValue.Visible = False
    chkTxtat.Visible = False
    chkIntat.Visible = False
    chkBogus.Visible = False
    txtCustom.Visible = True
End Sub

Private Sub optDelete_Click()
    chkAll.Visible = False
    chkValue.Visible = False
    chkTxtat.Visible = False
    chkIntat.Visible = False
    chkBogus.Visible = False
    txtCustom.Visible = False
End Sub

Private Sub optModify_Click()
    chkAll.Visible = True
    chkValue.Visible = True
    chkTxtat.Visible = True
    chkIntat.Visible = True
    chkBogus.Visible = True
    txtCustom.Visible = False
End Sub

Private Sub optSelect_Click()
    chkAll.Visible = False
    chkValue.Visible = False
    chkTxtat.Visible = False
    chkIntat.Visible = False
    chkBogus.Visible = False
    txtCustom.Visible = False
End Sub
