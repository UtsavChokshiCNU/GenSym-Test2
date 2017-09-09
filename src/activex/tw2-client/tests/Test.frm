VERSION 5.00
Object = "{42B6C7E0-06C1-11D2-8698-00008618F471}#2.0#0"; "AXClient.dll"
Object = "{BDC217C8-ED16-11CD-956C-0000C04E4C0A}#1.1#0"; "TABCTL32.OCX"
Begin VB.Form TestForm 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Test"
   ClientHeight    =   10245
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   11520
   Icon            =   "Test.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   10245
   ScaleWidth      =   11520
   StartUpPosition =   3  'Windows Default
   Begin GensymTw2Ctl.G2ItemHolder G2ItemHolder1 
      Left            =   11040
      OleObjectBlob   =   "Test.frx":000C
      Top             =   2520
   End
   Begin GensymTw2Ctl.G2UiGateway G2UiGateway1 
      Left            =   11040
      OleObjectBlob   =   "Test.frx":0074
      Top             =   3120
   End
   Begin GensymTw2Ctl.G2WorkspacePanel G2WorkspacePanel1 
      Height          =   3495
      Left            =   120
      OleObjectBlob   =   "Test.frx":014C
      TabIndex        =   0
      Top             =   120
      Width           =   10935
   End
   Begin TabDlg.SSTab SSTab1 
      Height          =   6015
      Left            =   120
      TabIndex        =   1
      Top             =   4080
      Width           =   11295
      _ExtentX        =   19923
      _ExtentY        =   10610
      _Version        =   327680
      Tabs            =   8
      TabsPerRow      =   4
      TabHeight       =   520
      TabCaption(0)   =   "Start Here"
      TabPicture(0)   =   "Test.frx":017E
      Tab(0).ControlCount=   1
      Tab(0).ControlEnabled=   -1  'True
      Tab(0).Control(0)=   "ConnectBtn"
      Tab(0).Control(0).Enabled=   0   'False
      TabCaption(1)   =   "G2Symbol"
      TabPicture(1)   =   "Test.frx":019A
      Tab(1).ControlCount=   1
      Tab(1).ControlEnabled=   0   'False
      Tab(1).Control(0)=   "SymbolValueBtn"
      Tab(1).Control(0).Enabled=   -1  'True
      TabCaption(2)   =   "G2Structure"
      TabPicture(2)   =   "Test.frx":01B6
      Tab(2).ControlCount=   1
      Tab(2).ControlEnabled=   0   'False
      Tab(2).Control(0)=   "StructureBtn"
      Tab(2).Control(0).Enabled=   -1  'True
      TabCaption(3)   =   "G2ItemHolder"
      TabPicture(3)   =   "Test.frx":01D2
      Tab(3).ControlCount=   7
      Tab(3).ControlEnabled=   0   'False
      Tab(3).Control(0)=   "CloneBtn"
      Tab(3).Control(0).Enabled=   -1  'True
      Tab(3).Control(1)=   "GetMyObjectBtn"
      Tab(3).Control(1).Enabled=   -1  'True
      Tab(3).Control(2)=   "InHolderBtn"
      Tab(3).Control(2).Enabled=   -1  'True
      Tab(3).Control(3)=   "SubAttrFloatBtn"
      Tab(3).Control(3).Enabled=   -1  'True
      Tab(3).Control(4)=   "UnsubAttrFloatBtn"
      Tab(3).Control(4).Enabled=   -1  'True
      Tab(3).Control(5)=   "ReleaseItemBtn"
      Tab(3).Control(5).Enabled=   -1  'True
      Tab(3).Control(6)=   "AttrTextBtn"
      Tab(3).Control(6).Enabled=   -1  'True
      TabCaption(4)   =   "G2WorkspacePanel"
      TabPicture(4)   =   "Test.frx":01EE
      Tab(4).ControlCount=   24
      Tab(4).ControlEnabled=   0   'False
      Tab(4).Control(0)=   "RemoveAllWkspBtn"
      Tab(4).Control(0).Enabled=   -1  'True
      Tab(4).Control(1)=   "SelectAllBtn"
      Tab(4).Control(1).Enabled=   -1  'True
      Tab(4).Control(2)=   "ClearSelectionBtn"
      Tab(4).Control(2).Enabled=   -1  'True
      Tab(4).Control(3)=   "MoveSelectionDownBtn"
      Tab(4).Control(3).Enabled=   -1  'True
      Tab(4).Control(4)=   "MoveSelectionLeftBtn"
      Tab(4).Control(4).Enabled=   -1  'True
      Tab(4).Control(5)=   "MoveSelectionUpBtn"
      Tab(4).Control(5).Enabled=   -1  'True
      Tab(4).Control(6)=   "MoveSelectionRightBtn"
      Tab(4).Control(6).Enabled=   -1  'True
      Tab(4).Control(7)=   "UnselectMyObjectBtn"
      Tab(4).Control(7).Enabled=   -1  'True
      Tab(4).Control(8)=   "SelectMyObjectBtn"
      Tab(4).Control(8).Enabled=   -1  'True
      Tab(4).Control(9)=   "GetSelectionBtn"
      Tab(4).Control(9).Enabled=   -1  'True
      Tab(4).Control(10)=   "TransNewObjToWkspBtn"
      Tab(4).Control(10).Enabled=   -1  'True
      Tab(4).Control(11)=   "ScrollBtn"
      Tab(4).Control(11).Enabled=   -1  'True
      Tab(4).Control(12)=   "ShowTestWkspBtn"
      Tab(4).Control(12).Enabled=   -1  'True
      Tab(4).Control(13)=   "PrevWkspBtn"
      Tab(4).Control(13).Enabled=   -1  'True
      Tab(4).Control(14)=   "GetTestWksp2Btn"
      Tab(4).Control(14).Enabled=   -1  'True
      Tab(4).Control(15)=   "CreateNewObjBtn"
      Tab(4).Control(15).Enabled=   -1  'True
      Tab(4).Control(16)=   "GetTestWkspBtn"
      Tab(4).Control(16).Enabled=   -1  'True
      Tab(4).Control(17)=   "SelectNewObjBtn"
      Tab(4).Control(17).Enabled=   -1  'True
      Tab(4).Control(18)=   "RemoveWkspBtn"
      Tab(4).Control(18).Enabled=   -1  'True
      Tab(4).Control(19)=   "DeleteSelectionBtn"
      Tab(4).Control(19).Enabled=   -1  'True
      Tab(4).Control(20)=   "NextWkspBtn"
      Tab(4).Control(20).Enabled=   -1  'True
      Tab(4).Control(21)=   "ShowSubWorkspaceBtn"
      Tab(4).Control(21).Enabled=   -1  'True
      Tab(4).Control(22)=   "TransNewObjToAttrBtn"
      Tab(4).Control(22).Enabled=   -1  'True
      Tab(4).Control(23)=   "SelectBtnLabel"
      Tab(4).Control(23).Enabled=   0   'False
      TabCaption(5)   =   "G2Item"
      TabPicture(5)   =   "Test.frx":020A
      Tab(5).ControlCount=   17
      Tab(5).ControlEnabled=   0   'False
      Tab(5).Control(0)=   "ItemEqualsBtn"
      Tab(5).Control(0).Enabled=   -1  'True
      Tab(5).Control(1)=   "MakeTransientBtn"
      Tab(5).Control(1).Enabled=   -1  'True
      Tab(5).Control(2)=   "MakePermanentBtn"
      Tab(5).Control(2).Enabled=   -1  'True
      Tab(5).Control(3)=   "EnableItemBtn"
      Tab(5).Control(3).Enabled=   -1  'True
      Tab(5).Control(4)=   "DisableItemBtn"
      Tab(5).Control(4).Enabled=   -1  'True
      Tab(5).Control(5)=   "MoveByBtn"
      Tab(5).Control(5).Enabled=   -1  'True
      Tab(5).Control(6)=   "SetBoundsBtn"
      Tab(5).Control(6).Enabled=   -1  'True
      Tab(5).Control(7)=   "DropToBottomBtn"
      Tab(5).Control(7).Enabled=   -1  'True
      Tab(5).Control(8)=   "LiftToTopBtn"
      Tab(5).Control(8).Enabled=   -1  'True
      Tab(5).Control(9)=   "RestoreBtn"
      Tab(5).Control(9).Enabled=   -1  'True
      Tab(5).Control(10)=   "MyListElementsBtn"
      Tab(5).Control(10).Enabled=   -1  'True
      Tab(5).Control(11)=   "MyArrayElementsBtn"
      Tab(5).Control(11).Enabled=   -1  'True
      Tab(5).Control(12)=   "IsABtn"
      Tab(5).Control(12).Enabled=   -1  'True
      Tab(5).Control(13)=   "MoveBtn"
      Tab(5).Control(13).Enabled=   -1  'True
      Tab(5).Control(14)=   "TestWkspBtn"
      Tab(5).Control(14).Enabled=   -1  'True
      Tab(5).Control(15)=   "TransMyObjectOffBtn"
      Tab(5).Control(15).Enabled=   -1  'True
      Tab(5).Control(16)=   "TransMyObjectWkspBtn"
      Tab(5).Control(16).Enabled=   -1  'True
      TabCaption(6)   =   "G2UiGateway"
      TabPicture(6)   =   "Test.frx":0226
      Tab(6).ControlCount=   10
      Tab(6).ControlEnabled=   0   'False
      Tab(6).Control(0)=   "IsConnectedBtn"
      Tab(6).Control(0).Enabled=   -1  'True
      Tab(6).Control(1)=   "CallMyProcBtn"
      Tab(6).Control(1).Enabled=   -1  'True
      Tab(6).Control(2)=   "CallMyProc2Btn"
      Tab(6).Control(2).Enabled=   -1  'True
      Tab(6).Control(3)=   "CallMyMethodBtn"
      Tab(6).Control(3).Enabled=   -1  'True
      Tab(6).Control(4)=   "StartMyProcBtn"
      Tab(6).Control(4).Enabled=   -1  'True
      Tab(6).Control(5)=   "StartMyProc2Btn"
      Tab(6).Control(5).Enabled=   -1  'True
      Tab(6).Control(6)=   "StartMyMethodBtn"
      Tab(6).Control(6).Enabled=   -1  'True
      Tab(6).Control(7)=   "PostMessageBtn"
      Tab(6).Control(7).Enabled=   -1  'True
      Tab(6).Control(8)=   "DirectSubClassesBtn"
      Tab(6).Control(8).Enabled=   -1  'True
      Tab(6).Control(9)=   "InstOfClassBtn"
      Tab(6).Control(9).Enabled=   -1  'True
      TabCaption(7)   =   "Do this Last"
      TabPicture(7)   =   "Test.frx":0242
      Tab(7).ControlCount=   1
      Tab(7).ControlEnabled=   0   'False
      Tab(7).Control(0)=   "DisconnectBtn"
      Tab(7).Control(0).Enabled=   -1  'True
      Begin VB.CommandButton RemoveAllWkspBtn 
         Caption         =   "Remove all workspaces"
         Height          =   375
         Left            =   -70440
         TabIndex        =   63
         Top             =   5280
         Width           =   2055
      End
      Begin VB.CommandButton CloneBtn 
         Caption         =   "Clone MY-OBJECT"
         Height          =   495
         Left            =   -68160
         TabIndex        =   62
         Top             =   1320
         Width           =   2055
      End
      Begin VB.CommandButton IsConnectedBtn 
         Caption         =   "IsConnected()"
         Height          =   495
         Left            =   -74520
         TabIndex        =   61
         Top             =   3000
         Width           =   2055
      End
      Begin VB.CommandButton ItemEqualsBtn 
         Caption         =   "Test item.Equals"
         Height          =   495
         Left            =   -74880
         TabIndex        =   60
         Top             =   780
         Width           =   2055
      End
      Begin VB.CommandButton MakeTransientBtn 
         Caption         =   "Make MY-OBJECT transient"
         Height          =   495
         Left            =   -72720
         TabIndex        =   59
         Top             =   4380
         Width           =   2055
      End
      Begin VB.CommandButton MakePermanentBtn 
         Caption         =   "Make MY-OBJECT permanent"
         Height          =   495
         Left            =   -70560
         TabIndex        =   58
         Top             =   1380
         Width           =   2055
      End
      Begin VB.CommandButton EnableItemBtn 
         Caption         =   "Enable MY-OBJECT"
         Height          =   495
         Left            =   -74880
         TabIndex        =   57
         Top             =   2580
         Width           =   2055
      End
      Begin VB.CommandButton DisableItemBtn 
         Caption         =   "Disable MY-OBJECT"
         Height          =   495
         Left            =   -74880
         TabIndex        =   56
         Top             =   1980
         Width           =   2055
      End
      Begin VB.CommandButton MoveByBtn 
         Caption         =   "Move MY-OBJECT by 20, 20"
         Height          =   495
         Left            =   -72720
         TabIndex        =   55
         Top             =   3780
         Width           =   2055
      End
      Begin VB.CommandButton SetBoundsBtn 
         Caption         =   "MY-OBJECT.SetBounds()"
         Height          =   495
         Left            =   -72720
         TabIndex        =   54
         Top             =   1380
         Width           =   2055
      End
      Begin VB.CommandButton DropToBottomBtn 
         Caption         =   "Drop MY-OBJECT to bottom"
         Height          =   495
         Left            =   -72720
         TabIndex        =   53
         Top             =   2580
         Width           =   2055
      End
      Begin VB.CommandButton LiftToTopBtn 
         Caption         =   "Lift MY-OBJECT to top"
         Height          =   495
         Left            =   -72720
         TabIndex        =   52
         Top             =   1980
         Width           =   2055
      End
      Begin VB.CommandButton RestoreBtn 
         Caption         =   "Restore MY-OBJECT to normal size"
         Height          =   495
         Left            =   -72720
         TabIndex        =   51
         Top             =   3180
         Width           =   2055
      End
      Begin VB.CommandButton MyListElementsBtn 
         Caption         =   "MY-G2LIST.Elements"
         Height          =   495
         Left            =   -67920
         TabIndex        =   50
         Top             =   1500
         Width           =   2055
      End
      Begin VB.CommandButton MyArrayElementsBtn 
         Caption         =   "MY-G2ARRAY.Elements"
         Height          =   495
         Left            =   -67920
         TabIndex        =   49
         Top             =   960
         Width           =   2055
      End
      Begin VB.CommandButton IsABtn 
         Caption         =   "Item.IsInstanceOfClass"
         Height          =   495
         Left            =   -74880
         TabIndex        =   48
         Top             =   1380
         Width           =   2055
      End
      Begin VB.CommandButton MoveBtn 
         Caption         =   "Move MY-OBJECT"
         Height          =   495
         Left            =   -70560
         TabIndex        =   47
         Top             =   1980
         Width           =   2055
      End
      Begin VB.CommandButton TestWkspBtn 
         Caption         =   "Get TEST-WKSP"
         Height          =   495
         Left            =   -72720
         TabIndex        =   46
         Top             =   780
         Width           =   2055
      End
      Begin VB.CommandButton TransMyObjectOffBtn 
         Caption         =   "Transfer MY-OBJECT off of its workspace"
         Height          =   495
         Left            =   -72720
         TabIndex        =   45
         Top             =   4980
         Width           =   2055
      End
      Begin VB.CommandButton TransMyObjectWkspBtn 
         Caption         =   "Transfer MY-OBJECT to TEST-WKSP"
         Height          =   495
         Left            =   -70560
         TabIndex        =   44
         Top             =   780
         Width           =   2055
      End
      Begin VB.CommandButton SelectAllBtn 
         Caption         =   "Select All"
         Height          =   375
         Left            =   -70440
         TabIndex        =   42
         Top             =   3720
         Width           =   2055
      End
      Begin VB.CommandButton ClearSelectionBtn 
         Caption         =   "Clear WS selection"
         Height          =   375
         Left            =   -70440
         TabIndex        =   41
         Top             =   4800
         Width           =   2055
      End
      Begin VB.CommandButton MoveSelectionDownBtn 
         Caption         =   "v"
         Height          =   495
         Left            =   -69600
         TabIndex        =   40
         Top             =   3120
         Width           =   495
      End
      Begin VB.CommandButton MoveSelectionLeftBtn 
         Caption         =   "<"
         Height          =   495
         Left            =   -70440
         TabIndex        =   39
         Top             =   2520
         Width           =   495
      End
      Begin VB.CommandButton MoveSelectionUpBtn 
         Caption         =   "^"
         Height          =   495
         Left            =   -69600
         TabIndex        =   38
         Top             =   1920
         Width           =   495
      End
      Begin VB.CommandButton MoveSelectionRightBtn 
         Caption         =   ">"
         Height          =   495
         Left            =   -68880
         TabIndex        =   37
         Top             =   2520
         Width           =   495
      End
      Begin VB.CommandButton UnselectMyObjectBtn 
         Caption         =   "Remove MY-OBJECT from WS selection"
         Height          =   495
         Left            =   -70440
         TabIndex        =   36
         Top             =   4200
         Width           =   2055
      End
      Begin VB.CommandButton SelectMyObjectBtn 
         Caption         =   "Add MY-OBJECT to WS selection"
         Height          =   495
         Left            =   -70440
         TabIndex        =   35
         Top             =   840
         Width           =   2055
      End
      Begin VB.CommandButton GetSelectionBtn 
         Caption         =   "Get workspace selection"
         Height          =   375
         Left            =   -70440
         TabIndex        =   34
         Top             =   1440
         Width           =   2055
      End
      Begin VB.CommandButton TransNewObjToWkspBtn 
         Caption         =   "Transfer MY-NEW-OBJECT to TEST-WKSP2"
         Height          =   615
         Left            =   -74760
         TabIndex        =   33
         Top             =   4440
         Width           =   2055
      End
      Begin VB.CommandButton ScrollBtn 
         Caption         =   "Scroll to Location 0,0"
         Height          =   375
         Left            =   -74760
         TabIndex        =   32
         Top             =   2760
         Width           =   2055
      End
      Begin VB.CommandButton ShowTestWkspBtn 
         Caption         =   "Show TEST-WKSP"
         Height          =   375
         Left            =   -74760
         TabIndex        =   31
         Top             =   1800
         Width           =   2055
      End
      Begin VB.CommandButton PrevWkspBtn 
         Caption         =   "Previous Workspace"
         Height          =   375
         Left            =   -74760
         TabIndex        =   30
         Top             =   2280
         Width           =   2055
      End
      Begin VB.CommandButton GetTestWksp2Btn 
         Caption         =   "Get TEST-WKSP2"
         Height          =   375
         Left            =   -74760
         TabIndex        =   29
         Top             =   1320
         Width           =   2055
      End
      Begin VB.CommandButton CreateNewObjBtn 
         Caption         =   "Create MY-NEW-OBJECT"
         Height          =   375
         Left            =   -74760
         TabIndex        =   28
         Top             =   3240
         Width           =   2055
      End
      Begin VB.CommandButton GetTestWkspBtn 
         Caption         =   "Get TEST-WKSP"
         Height          =   375
         Left            =   -74760
         TabIndex        =   27
         Top             =   840
         Width           =   2055
      End
      Begin VB.CommandButton SelectNewObjBtn 
         Caption         =   "Add MY-NEW-OBJECT to WS selection"
         Height          =   495
         Left            =   -74760
         TabIndex        =   26
         Top             =   5160
         Width           =   2055
      End
      Begin VB.CommandButton RemoveWkspBtn 
         Caption         =   "Remove TEST-WKSP2"
         Height          =   375
         Left            =   -72600
         TabIndex        =   25
         Top             =   1320
         Width           =   2055
      End
      Begin VB.CommandButton DeleteSelectionBtn 
         Caption         =   "Delete WS Selection"
         Height          =   375
         Left            =   -72600
         TabIndex        =   24
         Top             =   840
         Width           =   2055
      End
      Begin VB.CommandButton NextWkspBtn 
         Caption         =   "Next Workspace"
         Height          =   375
         Left            =   -72600
         TabIndex        =   23
         Top             =   2400
         Width           =   2055
      End
      Begin VB.CommandButton ShowSubWorkspaceBtn 
         Caption         =   "Show the subworkspace of MY-OBJECT"
         Height          =   495
         Left            =   -72600
         TabIndex        =   22
         Top             =   1800
         Width           =   2055
      End
      Begin VB.CommandButton TransNewObjToAttrBtn 
         Caption         =   "Transfer MY-NEW-OBJECT to MY-OBJECT.attr-item"
         Height          =   615
         Left            =   -74760
         TabIndex        =   21
         Top             =   3720
         Width           =   2055
      End
      Begin VB.CommandButton CallMyProcBtn 
         Caption         =   "Call my-procedure"
         Height          =   495
         Left            =   -71280
         TabIndex        =   20
         Top             =   1200
         Width           =   2055
      End
      Begin VB.CommandButton CallMyProc2Btn 
         Caption         =   "Call my-procedure2"
         Height          =   495
         Left            =   -71280
         TabIndex        =   19
         Top             =   1800
         Width           =   2055
      End
      Begin VB.CommandButton CallMyMethodBtn 
         Caption         =   "Call my-object.my-method"
         Height          =   495
         Left            =   -71280
         TabIndex        =   18
         Top             =   2400
         Width           =   2055
      End
      Begin VB.CommandButton StartMyProcBtn 
         Caption         =   "Start my-procedure"
         Height          =   495
         Left            =   -68880
         TabIndex        =   17
         Top             =   1200
         Width           =   2055
      End
      Begin VB.CommandButton StartMyProc2Btn 
         Caption         =   "Start my-procedure2"
         Height          =   495
         Left            =   -68880
         TabIndex        =   16
         Top             =   1800
         Width           =   2055
      End
      Begin VB.CommandButton StartMyMethodBtn 
         Caption         =   "Start my-object.my-method"
         Height          =   495
         Left            =   -68880
         TabIndex        =   15
         Top             =   2400
         Width           =   2055
      End
      Begin VB.CommandButton GetMyObjectBtn 
         Caption         =   "Put MY-OBJECT in the Holder"
         Height          =   495
         Left            =   -70920
         TabIndex        =   14
         Top             =   1680
         Width           =   2055
      End
      Begin VB.CommandButton SymbolValueBtn 
         Caption         =   "Make a symbol"
         Height          =   495
         Left            =   -71040
         TabIndex        =   13
         Top             =   1680
         Width           =   2055
      End
      Begin VB.CommandButton InHolderBtn 
         Caption         =   "What's in the holder?"
         Height          =   495
         Left            =   -70920
         TabIndex        =   12
         Top             =   2280
         Width           =   2055
      End
      Begin VB.CommandButton SubAttrFloatBtn 
         Caption         =   "Subscribe to attr-float"
         Height          =   495
         Left            =   -70920
         TabIndex        =   11
         Top             =   1080
         Width           =   2055
      End
      Begin VB.CommandButton PostMessageBtn 
         Caption         =   "Send ""Hi from VB."" to G2"
         Height          =   495
         Left            =   -74520
         TabIndex        =   10
         Top             =   1200
         Width           =   2055
      End
      Begin VB.CommandButton DirectSubClassesBtn 
         Caption         =   "Direct Subclasses of OBJECT"
         Height          =   495
         Left            =   -74520
         TabIndex        =   9
         Top             =   1800
         Width           =   2055
      End
      Begin VB.CommandButton InstOfClassBtn 
         Caption         =   "Instances of MY-CLASS"
         Height          =   495
         Left            =   -74520
         TabIndex        =   8
         Top             =   2400
         Width           =   2055
      End
      Begin VB.CommandButton StructureBtn 
         Caption         =   "Make a structure"
         Height          =   495
         Left            =   -71040
         TabIndex        =   7
         Top             =   1800
         Width           =   2055
      End
      Begin VB.CommandButton ConnectBtn 
         Caption         =   "Connect"
         Height          =   495
         Left            =   3960
         TabIndex        =   6
         Top             =   1680
         Width           =   2055
      End
      Begin VB.CommandButton UnsubAttrFloatBtn 
         Caption         =   "Unsubscribe to attr-float"
         Height          =   495
         Left            =   -70920
         TabIndex        =   5
         Top             =   4080
         Width           =   2055
      End
      Begin VB.CommandButton ReleaseItemBtn 
         Caption         =   "Release the item in the holder"
         Height          =   495
         Left            =   -70920
         TabIndex        =   4
         Top             =   3480
         Width           =   2055
      End
      Begin VB.CommandButton AttrTextBtn 
         Caption         =   "Change attr-text to """""
         Height          =   495
         Left            =   -70920
         TabIndex        =   3
         Top             =   2880
         Width           =   2055
      End
      Begin VB.CommandButton DisconnectBtn 
         Caption         =   "Disconnect"
         Height          =   495
         Left            =   -71040
         TabIndex        =   2
         Top             =   1800
         Width           =   2055
      End
      Begin VB.Label SelectBtnLabel 
         Caption         =   "Move WS Selection"
         Height          =   375
         Left            =   -69720
         TabIndex        =   43
         Top             =   2520
         Width           =   855
      End
   End
   Begin VB.Label EventBoxLabel 
      Caption         =   "Last Event Received"
      Height          =   255
      Left            =   120
      TabIndex        =   65
      Top             =   3720
      Width           =   1575
   End
   Begin VB.Label EventBox 
      BorderStyle     =   1  'Fixed Single
      Height          =   255
      Left            =   1680
      TabIndex        =   64
      Top             =   3720
      Width           =   9735
      WordWrap        =   -1  'True
   End
End
Attribute VB_Name = "TestForm"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Form_Activate()
    If Not G2UiGateway1.IsConnected Then
        SSTab1.Tab = 0
    End If
End Sub

Private Sub G2ItemHolder1_ItemDeleted()
    MsgBox "The item in the holder has been deleted.", , "Event Received"
    EventBox.Caption = "ItemDeleted"
End Sub

Private Sub G2UiGateway1_Error(ByVal Message As String)
    MsgBox "Error: " & Message, , "Event Received"
    EventBox.Caption = "Error: " & Message
End Sub

Private Sub G2UiGateway1_G2StateChange(ByVal NewState As GensymTw2Ctl.G2States)
    EventBox.Caption = "G2StateChange: " & NewState
End Sub

Private Sub G2UiGateway1_UserLoggedIn()
    MsgBox "UserLoggedIn", , "Event Received"
    EventBox.Caption = "UserLoggedIn"
End Sub

Private Sub G2UiGateway1_UserLoggedOut()
    EventBox.Caption = "UserLoggedOut"
End Sub

Private Sub G2UiGateway1_UserModeChanged(ByVal NewUserMode As String)
    EventBox.Caption = "UserModeChanged: " & NewUserMode
End Sub

Private Sub IsConnectedBtn_Click()
    'Test the fact that the true value return is a -1 short not 1
    '  by using the Not operator
    If Not G2UiGateway1.IsConnected Then
        MsgBox "IsConnected() = False"
    Else
        MsgBox "IsConnected() = True"
    End If
End Sub

Private Sub RemoveAllWkspBtn_Click()
    G2WorkspacePanel1.RemoveAllWorkspaces
End Sub

Private Sub ShowSubWorkspaceBtn_Click()
    G2UiGateway1.CallG2Procedure "show-wksp"
End Sub

Private Sub ScrollBtn_Click()
    G2WorkspacePanel1.ScrollToLocation 0, 0
End Sub

Private Sub TransNewObjToWkspBtn_Click()
    G2UiGateway1.GetNamedItem("my-new-object").TransferToWorkspace G2UiGateway1.GetNamedItem("test-wksp2"), 0, -50
End Sub

Private Sub SelectNewObjBtn_Click()
    G2WorkspacePanel1.AddElementToSelection (G2UiGateway1.GetNamedItem("my-new-object"))
End Sub

Private Sub TransNewObjToAttrBtn_Click()
    Dim DestItem As G2Item
    Dim item As G2Item
    
    Set DestItem = G2UiGateway1.GetNamedItem("my-object")
    Set item = G2UiGateway1.GetNamedItem("my-new-object")
    item.TransferToItem DestItem, "attr-item"
    MsgBox DestItem.Attribute("attr-item").Attribute("names").Value
End Sub

Private Sub MoveByBtn_Click()
    Dim item As G2Item
    
    Set item = G2UiGateway1.GetNamedItem("my-object")
    item.MoveBy 20, 20, True
End Sub
Private Sub MoveBtn_Click()
    Dim item As G2Item
    
    Set item = G2UiGateway1.GetNamedItem("my-object")
    item.Move 105, 65, True
End Sub

Private Sub UnsubAttrFloatBtn_Click()
    G2ItemHolder1.UnsubscribeToAttribute "attr-float"
    MsgBox "Subscribed attributes : " & G2ItemHolder1.SubscribedAttributes
End Sub
Private Sub IsABtn_Click()
    Dim item As G2Item
    Dim isItemInstanceOfClass As Boolean
    
    Set item = G2UiGateway1.GetNamedItem("my-object")
    isItemInstanceOfClass = item.IsInstanceOfClass("my-class")
    MsgBox "my-object.IsInstanceOfClass(my-class) = " & isItemInstanceOfClass
    
    Set item = G2UiGateway1.GetNamedItem("my-object")
    isItemInstanceOfClass = item.IsInstanceOfClass("g2-list")
    MsgBox "my-object.IsInstanceOfClass(g2-list) = " & isItemInstanceOfClass
End Sub

Private Sub InstOfClassBtn_Click()
    Dim instances As Variant
    Dim firstInstance, lastInstance, i As Integer
    Dim names As Variant
    Dim NewForm As New TestListBoxForm
    
    instances = G2UiGateway1.ClassInstances("my-class")
    If Not IsArray(instances) Then
        MsgBox "ClassInstances did not return an array.", , "Error"
        Exit Sub
    End If
    
    firstInstance = LBound(instances)
    lastInstance = UBound(instances)
    
    For i = firstInstance To lastInstance
        names = instances(i).Attribute("names")
        If IsArray(names) Then
            If UBound(names) - LBound(names) > 0 Then
                names = names(LBound(names))
            Else
                names = ""
            End If
        End If
        
        If IsObject(names) Then names = names.String
        
        If IsNull(names) Then names = ""
        
        NewForm.List.AddItem names
    Next i

    NewForm.Caption = "Instances of MY-CLASS"
    NewForm.Show vbModal, Me
End Sub
Private Sub DirectSubClassesBtn_Click()
    Dim subclasses As Variant
    Dim firstSubclass, lastSubclass, i As Integer
    Dim classname As Variant
    Dim NewForm As New TestListBoxForm
    
    subclasses = G2UiGateway1.DirectSubclasses("object")
    If Not IsArray(subclasses) Then
        MsgBox "DirectSubclasses did not return an array.", , "Error"
        Exit Sub
    End If
    
    firstSubclass = LBound(subclasses)
    lastSubclass = UBound(subclasses)
    
    For i = firstSubclass To lastSubclass
        classname = subclasses(i)
        If IsArray(classname) Then
            If UBound(classname) - LBound(classname) > 0 Then
                classname = classname(LBound(classname))
            Else
                classname = ""
            End If
        End If
        
        If IsObject(classname) Then classname = classname.String
        
        If IsNull(classname) Then classname = ""
        
        NewForm.List.AddItem classname
    Next i

    NewForm.Caption = "Direct Subclasses of OBJECT"
    NewForm.Show vbModal, Me
End Sub

Private Sub MyArrayElementsBtn_Click()
    Dim G2Array As G2Item
    Dim numberOfElements, i As Integer
    Dim sequence() As Variant
    
    Set G2Array = G2UiGateway1.GetNamedItem("my-g2array")
    numberOfElements = G2Array.ElementCount
    ReDim sequence(numberOfElements)
    For i = 0 To numberOfElements - 1
        sequence(i) = i
    Next i
    
    G2Array.Elements = sequence
End Sub
Private Sub MyListElementsBtn_Click()
    Dim G2List As G2Item
    Dim i As Integer
    Dim sequence(10) As Variant
    
    Set G2List = G2UiGateway1.GetNamedItem("my-g2list")
    For i = 0 To 9
        sequence(i) = i
    Next i
    
    G2List.Elements = sequence
End Sub

Private Sub G2UiGateway1_GotMessage(ByVal Message As String)
    MsgBox "Message from G2: " & Message, , "Event Received"
    EventBox.Caption = "GotMessage: " & Message
End Sub

Private Sub G2UiGateway1_HideWorkspace(ByVal workspace As GensymTw2Ctl.G2Item2, ByVal WorkspaceShowingEvent As Object)
    EventBox.Caption = "HideWorkspace"
    G2WorkspacePanel1.ProcessHideWorkspaceEvent WorkspaceShowingEvent
End Sub

Private Sub G2UiGateway1_ShowWorkspace(ByVal workspace As GensymTw2Ctl.G2Item2, ByVal Particulars As GensymTw2Ctl.IG2Structure, ByVal WorkspaceShowingEvent As Object)
    EventBox.Caption = "ShowWorkspace"
    G2WorkspacePanel1.ProcessShowWorkspaceEvent WorkspaceShowingEvent
End Sub
Private Sub ConnectBtn_Click()
    G2UiGateway1.Connect
End Sub

Private Sub DeleteSelectionBtn_Click()
    G2WorkspacePanel1.DeleteSelection
End Sub

Private Sub CreateNewObjBtn_Click()
    Dim item As G2Item
    
    Set item = G2UiGateway1.CreateItem("my-class")
    item.Attribute("names") = G2UiGateway1.Symbol("my-new-object")
    MsgBox "MY-NEW-OBJECT.Transient = " & item.Transient
End Sub

Private Sub DisableItemBtn_Click()
    Dim item As G2Item
    
    Set item = G2UiGateway1.GetNamedItem("my-object")
    item.Disable
    MsgBox "MY-OBJECT.ManuallyDisabled " & item.ManuallyDisabled
End Sub

Private Sub EnableItemBtn_Click()
    Dim item As G2Item
    
    Set item = G2UiGateway1.GetNamedItem("my-object")
    item.Enable
    MsgBox "MY-OBJECT.ManuallyDisabled " & item.ManuallyDisabled
End Sub

Private Sub MakePermanentBtn_Click()
    Dim item As G2Item
    
    Set item = G2UiGateway1.GetNamedItem("my-object")
    item.MakePermanent
    MsgBox "MY-OBJECT.Transient " & item.Transient
End Sub

Private Sub MakeTransientBtn_Click()
    Dim item As G2Item
    
    Set item = G2UiGateway1.GetNamedItem("my-object")
    item.MakeTransient
    MsgBox "MY-OBJECT.Transient " & item.Transient
End Sub

Private Sub ClearSelectionBtn_Click()
    G2WorkspacePanel1.ClearSelection
End Sub

Private Sub DisconnectBtn_Click()
    G2UiGateway1.Disconnect
End Sub

Private Sub GetTestWksp2Btn_Click()
    G2WorkspacePanel1.AddWorkspace (G2UiGateway1.GetNamedItem("test-wksp2"))
End Sub

Private Sub NextWkspBtn_Click()
    G2WorkspacePanel1.NextWorkspace
End Sub

Private Sub PrevWkspBtn_Click()
    G2WorkspacePanel1.PreviousWorkspace
End Sub

Private Sub AttrTextBtn_Click()
    MsgBox "MY-OBJECT.attr-text = " & G2ItemHolder1.Attribute("attr-text")
    G2ItemHolder1.Attribute("attr-text") = ""
End Sub

Private Sub GetMyObjectBtn_Click()
    G2ItemHolder1.item = G2UiGateway1.GetNamedItem("my-object")
    MsgBox G2ItemHolder1.item.String & " has been put in the holder"
End Sub

Private Sub TransMyObjectOffBtn_Click()
    G2UiGateway1.GetNamedItem("my-object").TransferOff
End Sub

Private Sub RemoveWkspBtn_Click()
    G2WorkspacePanel1.RemoveWorkspace (G2UiGateway1.GetNamedItem("test-wksp2"))
End Sub

Private Sub SelectAllBtn_Click()
    G2WorkspacePanel1.SelectAll
End Sub

Private Sub ShowTestWkspBtn_Click()
    G2WorkspacePanel1.ShowWorkspace (G2UiGateway1.GetNamedItem("test-wksp"))
End Sub

Private Sub RestoreBtn_Click()
    G2UiGateway1.GetNamedItem("my-object").RestoreNormalSize
End Sub

Private Sub GetTestWkspBtn_Click()
    G2WorkspacePanel1.AddWorkspace (G2UiGateway1.GetNamedItem("test-wksp"))
End Sub

Private Sub LiftToTopBtn_Click()
    G2UiGateway1.GetNamedItem("my-object").LiftToTop
End Sub

Private Sub DropToBottomBtn_Click()
    G2UiGateway1.GetNamedItem("my-object").DropToBottom
End Sub

Private Sub PostMessageBtn_Click()
    G2UiGateway1.PostMessage "Hi from VB."
End Sub

Private Sub ItemEqualsBtn_Click()
    Dim item As G2Item2
    Dim isItemEqual As Boolean
    
    Set item = G2UiGateway1.GetNamedItem("my-object")
    isItemEqual = item.Equals(G2UiGateway1.GetNamedItem("my-object"))
    MsgBox "my-object.Equals(my-object) = " & isItemEqual
    
    isItemEqual = item.Equals(G2UiGateway1.GetNamedItem("my-g2list"))
    MsgBox "my-object.Equals(my-g2list) = " & isItemEqual
End Sub

Private Sub InHolderBtn_Click()
    If G2ItemHolder1.IsEmpty Then
        MsgBox "There is nothing in the holder."
    Else
        MsgBox G2ItemHolder1.item.Attribute("names").Value & " is in the holder."
    End If
End Sub

Private Sub ReleaseItemBtn_Click()
    G2ItemHolder1.ReleaseItem
End Sub

Private Sub CloneBtn_Click()
    Dim clone As G2Item
    
    Set clone = G2UiGateway1.GetNamedItem("my-object").G2Clone
    MsgBox "Clone.Transient = " & clone.Transient
    
    G2ItemHolder1.item = clone
    EventBox.Caption = ""
    MsgBox "A clone of my object has been put into the item holder."
    
    MsgBox "The clone will now be deleted."
    clone.Delete
End Sub

Private Sub SetBoundsBtn_Click()
    Dim myObject As G2Item
    Dim xpos As Integer
    Dim ypos As Integer
    
    Set myObject = G2UiGateway1.GetNamedItem("my-object")
    xpos = myObject.Attribute("ITEM-X-POSITION")
    ypos = myObject.Attribute("ITEM-Y-POSITION")
    myObject.SetBounds xpos + 100, ypos, xpos + 200, ypos - 100
End Sub

Private Sub StructureBtn_Click()
    Dim Structure As G2Structure
    Dim MemberName As Variant
    Dim i As Integer
    Dim memberCount As Integer
    Dim NewForm As New TestListBoxForm
    
    Set Structure = G2UiGateway1.Structure("float-member", "this is bad")
    Structure.Member("float-member") = 1.1
    Structure.Member("integer-member") = 1
    Structure.Member("symbol-member") = G2UiGateway1.Symbol("test-symbol")
    Structure.Member("text-member") = "test text"
    Structure.Member("empty-text-member") = ""
    Structure.Member("truth-value-member") = True

    MemberName = Structure.MemberNames
    If IsArray(MemberName) Then
        memberCount = UBound(MemberName)
        For i = LBound(MemberName) To memberCount
            NewForm.List.AddItem MemberName(i)
        Next i
    End If

    NewForm.Caption = "Structure Members"
    NewForm.Show vbModal, Me
    
    MsgBox Structure.String
    Structure.ClearMember "truth-value-member"
    MsgBox "Without truth-value-member " & Structure.String
End Sub

Private Sub GetSelectionBtn_Click()
    Dim Selection As Variant
    Dim item As G2Item
    
    Selection = G2WorkspacePanel1.GetSelection
    If Not IsEmpty(Selection) Then
        If UBound(Selection) - LBound(Selection) + 1 > 0 Then
            Set item = Selection(0)
            MsgBox "The first item selected is " & item.String
        Else
            MsgBox "There is nothing in the selection."
        End If
    Else
        MsgBox "There is no workspace selection."
    End If
End Sub

Private Sub SelectMyObjectBtn_Click()
    G2WorkspacePanel1.AddElementToSelection (G2UiGateway1.GetNamedItem("my-object"))
End Sub

Private Sub UnselectMyObjectBtn_Click()
    G2WorkspacePanel1.RemoveElementFromSelection (G2UiGateway1.GetNamedItem("my-object"))
End Sub

Private Sub MoveSelectionRightBtn_Click()
    G2WorkspacePanel1.MoveSelection 50, 0, True
End Sub

Private Sub G2UiGateway1_G2Connected()
    MsgBox "G2Connected", , "Event Received"
    EventBox.Caption = "G2Connected"
End Sub

Private Sub G2UiGateway1_G2Disconnected()
    MsgBox "G2Disconnected", , "Event Received"
    EventBox.Caption = "G2Disconnected"
End Sub
Private Sub SubAttrFloatBtn_Click()
    G2ItemHolder1.SubscribeToAttribute "attr-float"
    MsgBox "Subscribed attributes : " & G2ItemHolder1.SubscribedAttributes
End Sub

Private Sub G2ItemHolder1_SubscribedAttributeChanged(ByVal AttributeName As String, NewValue As Variant)
    EventBox.Caption = "SubscribedAttributeChanged: " & AttributeName
    
    If IsNumeric(NewValue) Or VarType(NewValue) = vbString Or _
      VarType(NewValue) = vbBoolean Then
        EventBox.Caption = EventBox.Caption & " = [" & NewValue & "]"
    End If
End Sub

Private Sub MoveSelectionUpBtn_Click()
    G2WorkspacePanel1.MoveSelection 0, -50, True
End Sub
Private Sub MoveSelectionLeftBtn_Click()
    G2WorkspacePanel1.MoveSelection -50, 0, True
End Sub
Private Sub MoveSelectionDownBtn_Click()
    G2WorkspacePanel1.MoveSelection 0, 50, True
End Sub

Private Sub G2WorkspacePanel1_SelectionChanged()
    If Not SSTab1.Tab = 3 Then
        MsgBox "The workspace panel selection has changed.", , "Event Received"
    End If
        
    EventBox.Caption = "SelectionChanged."
End Sub

Private Sub SymbolValueBtn_Click()
    Dim Symbol As G2Symbol

    Set Symbol = G2UiGateway1.Symbol("foo")
    Symbol.Value = "test-symbol"
    MsgBox "Value = " & Symbol.Value & ", String = " & Symbol.String
End Sub

Private Sub TestWkspBtn_Click()
    G2WorkspacePanel1.AddWorkspace (G2UiGateway1.GetNamedItem("test-wksp"))
End Sub

Private Sub TransMyObjectWkspBtn_Click()
    G2UiGateway1.GetNamedItem("my-object").TransferToWorkspace G2UiGateway1.GetNamedItem("test-wksp"), 0, -50
End Sub


Private Sub CallMyProcBtn_Click()
    MsgBox "my-procedure() = " & G2UiGateway1.CallG2Procedure("my-procedure", 45, "", False)
End Sub
Private Sub CallMyProc2Btn_Click()
    Dim sequence(0 To 2) As Variant

    sequence(0) = 1
    sequence(1) = ""
    sequence(2) = True
    MsgBox "my-procedure2() = " & G2UiGateway1.CallG2Procedure("my-procedure2", sequence)
End Sub

Private Sub CallMyMethodBtn_Click()
    MsgBox "my-object.my-method = " & G2UiGateway1.GetNamedItem("my-object").CallMethod("my-method")
End Sub

Private Sub StartMyProcBtn_Click()
    G2UiGateway1.StartG2Procedure "my-procedure", 145, "", False
End Sub

Private Sub StartMyProc2Btn_Click()
    Dim sequence(0 To 2) As Variant

    sequence(0) = 1
    sequence(1) = ""
    sequence(2) = True
    G2UiGateway1.StartG2Procedure "my-procedure2", sequence
End Sub

Private Sub StartMyMethodBtn_Click()
    G2UiGateway1.GetNamedItem("my-object").StartMethod ("my-method")
End Sub


