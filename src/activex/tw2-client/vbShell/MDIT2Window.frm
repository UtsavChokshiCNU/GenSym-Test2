VERSION 5.00
Object = "{42B6C7E0-06C1-11D2-8698-00008618F471}#2.0#0"; "AXClient.dll"
Begin VB.MDIForm MDIT2Window 
   AutoShowChildren=   0   'False
   BackColor       =   &H8000000C&
   Caption         =   "set at runtime"
   ClientHeight    =   7560
   ClientLeft      =   165
   ClientTop       =   735
   ClientWidth     =   9885
   Icon            =   "MDIT2Window.frx":0000
   LinkTopic       =   "MDIForm1"
   NegotiateToolbars=   0   'False
   StartUpPosition =   3  'Windows Default
   Begin GensymTw2Ctl.G2UiGateway G2UiGateway1 
      Left            =   5160
      OleObjectBlob   =   "MDIT2Window.frx":0442
      Top             =   480
   End
   Begin VB.PictureBox Picture1 
      Align           =   2  'Align Bottom
      Height          =   255
      Left            =   0
      ScaleHeight     =   195
      ScaleWidth      =   9825
      TabIndex        =   0
      Top             =   7305
      Width           =   9885
      Begin VB.Label TW2Status 
         Alignment       =   1  'Right Justify
         Caption         =   "No Connection"
         Height          =   255
         Left            =   240
         TabIndex        =   1
         Top             =   0
         Width           =   9375
      End
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuFileExit 
         Caption         =   "E&xit"
      End
   End
   Begin VB.Menu mnuWorkspaces 
      Caption         =   "&Workspaces"
      Visible         =   0   'False
      Begin VB.Menu mnuWorkspacesGet 
         Caption         =   "&Get Workspace..."
         Enabled         =   0   'False
      End
   End
   Begin VB.Menu mnuObject 
      Caption         =   "&Object"
      Visible         =   0   'False
      Begin VB.Menu mnuObjectGetItem 
         Caption         =   "Get Item..."
      End
   End
   Begin VB.Menu mnuG2 
      Caption         =   "&G2"
      Begin VB.Menu mnuG2OpenConnection 
         Caption         =   "&Open  Connection..."
      End
      Begin VB.Menu mnuG2CloseConnection 
         Caption         =   "&Close  Connection"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuUserMode 
         Caption         =   "Change &User Mode..."
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuG2Separator 
         Caption         =   "-"
      End
      Begin VB.Menu mnuG2Pause 
         Caption         =   "&Pause"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuG2Start 
         Caption         =   "&Start"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuG2Reset 
         Caption         =   "&Reset"
         Enabled         =   0   'False
      End
      Begin VB.Menu mnuG2Restart 
         Caption         =   "R&estart"
         Enabled         =   0   'False
      End
   End
   Begin VB.Menu mnuWindow 
      Caption         =   "&Window"
      Visible         =   0   'False
      WindowList      =   -1  'True
      Begin VB.Menu mnuWindowCascade 
         Caption         =   "&Cascade"
      End
      Begin VB.Menu mnuWindowVTile 
         Caption         =   "&Tile Vertically"
      End
      Begin VB.Menu mnuWindowHTile 
         Caption         =   "&Tile Horizontally"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuHelpAbout 
         Caption         =   "&About Telewindows2"
      End
   End
End
Attribute VB_Name = "MDIT2Window"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private bShouldBeConnected As Boolean
Private WorkspaceWindowList As New Collection
Private ItemWindowList As New Collection

Private Sub G2UiGateway1_Error(ByVal Message As String)
    MsgBox Message, , "G2UiGateway Error"
End Sub

Private Sub G2UiGateway1_G2Connected()
    ' This event procedure will get called on a sucessful connection
    
    '  Update the display at the window bottom
    TW2Status.Caption = G2UiGateway1.G2Location & "  " & _
                        LCase(G2UiGateway1.UserMode)
    
    ' Now change all of the menus
    mnuWorkspacesGet.Enabled = True
    mnuWorkspaces.Visible = True
    mnuG2OpenConnection.Enabled = False
    mnuG2CloseConnection.Enabled = True
    mnuUserMode.Enabled = True
    mnuObject.Visible = True
    G2UiGateway1_G2StateChange G2UiGateway1.G2State
    bShouldBeConnected = True
End Sub

Private Sub G2UiGateway1_G2Disconnected()
    ' This event procedure will get called when the connection breaks
    
    Dim Workspace As WorkspaceWindowRecord
    Dim item As ItemWindowRecord
    
    If bShouldBeConnected Then
        MsgBox "The G2 server has terminated the connection.", , _
            "Connection Error"
    End If
    
    bShouldBeConnected = False
    TW2Status.Caption = "No Connection"
    mnuWorkspacesGet.Enabled = False
    mnuWorkspaces.Visible = False
    mnuG2OpenConnection.Enabled = True
    mnuG2CloseConnection.Enabled = False
    mnuUserMode.Enabled = False
    mnuObject.Visible = False
    mnuG2Pause.Enabled = False
    mnuG2Start.Enabled = False
    mnuG2Reset.Enabled = False
    mnuG2Restart.Enabled = False
    
    ' unload all of the workspace and item windows, the windows will
    '   remove themselves from the window list
    For Each Workspace In WorkspaceWindowList
        Unload Workspace.FormObj
    Next

    For Each item In ItemWindowList
        Unload item.FormObj
    Next

    AdjustWindowMenu
End Sub

Private Sub G2UiGateway1_G2StateChange(ByVal NewState As GensymTw2Ctl.G2States)
    ' This event procedure will get called when the state of the connected
    '   G2 server changes
    
    mnuG2Pause.Enabled = True
    mnuG2Start.Enabled = True
    mnuG2Reset.Enabled = True
    mnuG2Restart.Enabled = True
    
    If NewState = g2Paused Then
        mnuG2Pause.Enabled = False
    End If
    
    If NewState = g2Reset Then
        mnuG2Pause.Enabled = False
        mnuG2Reset.Enabled = False
        mnuG2Restart.Enabled = False
    End If
    
    If NewState = g2Resumed Then
        mnuG2Start.Enabled = False
    End If
    
    If NewState = g2Running Then
        mnuG2Start.Enabled = False
    End If
End Sub

Private Sub G2UiGateway1_HideWorkspace(ByVal Workspace As GensymTw2Ctl.G2Item2, ByVal WorkspaceShowingEvent As Object)
    ' This event procedure will get called when the G2 server wants a
    '   workspace to be hidden. (such as the clicking of a UIL hide button)

    Dim WorkspaceRec As WorkspaceWindowRecord

    For Each WorkspaceRec In WorkspaceWindowList
        ' Since 2 objects could reference the same G2 Item, use Equals
        '   method on G2Item2 instead of the IS operator
        If Workspace.Equals(WorkspaceRec.WorkspaceObj) Then
            Unload WorkspaceRec.FormObj
            Exit Sub
        End If
    Next
End Sub

Private Sub G2UiGateway1_ShowWorkspace(ByVal Workspace As GensymTw2Ctl.G2Item2, ByVal Particulars As GensymTw2Ctl.IG2Structure, ByVal WorkspaceShowingEvent As Object)
    ' This event procedure will get called when the G2 server wants a
    '   workspace to be shown. (such as the clicking of a goto workspace
    '   button)

    AddWorkspaceWindow Workspace
End Sub

Private Sub G2UiGateway1_UserModeChanged(ByVal NewUserMode As String)
    ' This event procedure will get called when the user mode of the
    '   connection changes

    TW2Status.Caption = G2UiGateway1.G2Location & "  " & LCase(NewUserMode)
End Sub

Private Sub MDIForm_Load()
    bShouldBeConnected = False
    Me.Caption = App.Title
End Sub

Private Sub mnuFileExit_Click()
    Unload Me
End Sub

Private Sub mnuG2CloseConnection_Click()
    bShouldBeConnected = False
    MDIT2Window.G2UiGateway1.Disconnect
End Sub

Private Sub mnuG2OpenConnection_Click()
    FrmT2OpenG2Connection.Show vbModal, Me
End Sub

Private Sub mnuG2Start_Click()
    MDIT2Window.G2UiGateway1.G2State = g2Running
End Sub

Private Sub mnuG2Reset_Click()
    MDIT2Window.G2UiGateway1.G2State = g2Reset
End Sub

Private Sub mnuG2Restart_Click()
    MDIT2Window.G2UiGateway1.G2State = g2Reset
    MDIT2Window.G2UiGateway1.G2State = g2Running
End Sub
Private Sub mnuG2Pause_Click()
    MDIT2Window.G2UiGateway1.G2State = g2Paused
End Sub

Private Sub mnuHelpAbout_Click()
    FrmT2About.Show vbModal, Me
End Sub

Private Sub mnuObjectGetItem_Click()
    FrmT2SpecifyItemName.Show vbModal, Me
End Sub


Private Sub MDIForm_Resize()
    On Error Resume Next
    TW2Status.Width = MDIT2Window.Width - 600
End Sub

Private Sub mnuUserMode_Click()
    FrmT2SpecifyUserMode.Show vbModal, Me
End Sub

Private Sub mnuWindowCascade_Click()
    MDIT2Window.Arrange vbCascade
End Sub

Private Sub mnuWindowHTile_Click()
    MDIT2Window.Arrange vbTileHorizontal
End Sub

Private Sub mnuWindowVTile_Click()
    MDIT2Window.Arrange vbTileVertical
End Sub

Private Sub mnuWorkspacesGet_Click()
    FrmT2SpecifyWorkspace.Show vbModal, Me
End Sub

Public Sub AddWorkspaceWindow(G2Workspace As G2Item2)
    Dim WorkspaceRec As WorkspaceWindowRecord
    Dim NewWorkspaceWindow As FrmT2Workspace
    Dim name As Variant
    
    'Show the workspace if it already exists
    For Each WorkspaceRec In WorkspaceWindowList
        ' Since 2 objects could reference the same G2 Item, use Equals
        '   method on G2Item2 instead of the IS operator
        If G2Workspace.Equals(WorkspaceRec.WorkspaceObj) Then
            WorkspaceRec.FormObj.SetFocus
            If WorkspaceRec.FormObj.WindowState = vbMinimized Then
                WorkspaceRec.FormObj.WindowState = vbNormal
            End If
            
            Exit Sub
        End If
    Next
    
    ' Get the name of the new workspace
    name = G2Workspace.Attribute("names")
    
    If IsArray(name) Then name = name(0)
    
    If IsObject(name) Then name = name.Value
    
    If IsNull(name) Or IsEmpty(name) Or name = "" Then name = "<UNNAMED>"
    
    ' Now create and intialize the a new workspace window
    Set NewWorkspaceWindow = New FrmT2Workspace
    NewWorkspaceWindow.Caption = name
    
    ' Put the new workspace window in the main window's list of workspaces
    Set WorkspaceRec = New WorkspaceWindowRecord
    Set WorkspaceRec.FormObj = NewWorkspaceWindow
    Set WorkspaceRec.WorkspaceObj = G2Workspace
    WorkspaceWindowList.Add WorkspaceRec
    
    ' We need to put the workspace in an item holder to know when the
    ' workspace is deleted, so we can unload the form.
    NewWorkspaceWindow.Holder.item = WorkspaceRec.WorkspaceObj
    
    'Put the workspace in the panel of the new window
    NewWorkspaceWindow.Panel.AddWorkspace WorkspaceRec.WorkspaceObj, False
    
    NewWorkspaceWindow.Show vbModeless
    mnuWindow.Visible = True
End Sub

Public Sub AddItemWindow(FormObj As Form)
    Dim ItemRec As ItemWindowRecord
    
    ' Put the new workspace window in the main window's list of workspaces
    Set ItemRec = New ItemWindowRecord
    Set ItemRec.FormObj = FormObj
    ItemWindowList.Add ItemRec
     
    FormObj.Show vbModeless
    mnuWindow.Visible = True
End Sub

Public Sub RemoveWorkspaceWindow(WindowToRemove As Form)
    Dim i As Integer
    Dim count As Integer
    Dim WorkspaceRec As WorkspaceWindowRecord
  
    count = WorkspaceWindowList.count
    For i = 1 To count
        Set WorkspaceRec = WorkspaceWindowList.item(i)
        If WorkspaceRec.FormObj Is WindowToRemove Then
            WorkspaceWindowList.Remove i
            AdjustWindowMenu
            Exit Sub
        End If
    Next
End Sub

Public Sub RemoveItemWindow(WindowToRemove As Form)
    Dim i As Integer
    Dim count As Integer
    Dim ItemRec As ItemWindowRecord
  
    count = ItemWindowList.count
    For i = 1 To count
        Set ItemRec = ItemWindowList.item(i)
        If ItemRec.FormObj Is WindowToRemove Then
            ItemWindowList.Remove i
            AdjustWindowMenu
            Exit Sub
        End If
    Next
End Sub

Private Sub AdjustWindowMenu()
    If ItemWindowList.count = 0 And WorkspaceWindowList.count = 0 Then
        mnuWindow.Visible = False
    End If
End Sub

