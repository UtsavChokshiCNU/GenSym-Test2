VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Begin VB.Form frmMain 
   Caption         =   "PI Servers"
   ClientHeight    =   2700
   ClientLeft      =   165
   ClientTop       =   555
   ClientWidth     =   11235
   Icon            =   "Main.frx":0000
   KeyPreview      =   -1  'True
   LinkTopic       =   "Form1"
   ScaleHeight     =   2700
   ScaleWidth      =   11235
   StartUpPosition =   2  'CenterScreen
   Begin MSComDlg.CommonDialog dlgCo 
      Left            =   120
      Top             =   2160
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin VB.VScrollBar vs1 
      Height          =   1815
      LargeChange     =   4
      Left            =   10680
      TabIndex        =   18
      Top             =   480
      Visible         =   0   'False
      Width           =   255
   End
   Begin VB.Label lblNothing 
      Caption         =   "There are no entries in the table.  Press [Insert] to add a PI server to the list."
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000C0&
      Height          =   375
      Left            =   1440
      TabIndex        =   19
      Top             =   1000
      Visible         =   0   'False
      Width           =   8295
   End
   Begin VB.Label lblSrvName 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "123456789x123456789x123456789x12"
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   4
      Left            =   240
      TabIndex        =   17
      Top             =   1920
      Visible         =   0   'False
      Width           =   4455
   End
   Begin VB.Label lblUser 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "123456789x123456789x123456789x12"
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   4
      Left            =   4680
      TabIndex        =   16
      Top             =   1920
      Visible         =   0   'False
      Width           =   4455
   End
   Begin VB.Label lblPW 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "default"
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   4
      Left            =   9120
      TabIndex        =   15
      Top             =   1920
      Visible         =   0   'False
      Width           =   1545
   End
   Begin VB.Label lblSrvName 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "123456789x123456789x123456789x12"
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   3
      Left            =   240
      TabIndex        =   14
      Top             =   1560
      Visible         =   0   'False
      Width           =   4455
   End
   Begin VB.Label lblUser 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "123456789x123456789x123456789x12"
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   3
      Left            =   4680
      TabIndex        =   13
      Top             =   1560
      Visible         =   0   'False
      Width           =   4455
   End
   Begin VB.Label lblPW 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "default"
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   3
      Left            =   9120
      TabIndex        =   12
      Top             =   1560
      Visible         =   0   'False
      Width           =   1545
   End
   Begin VB.Label lblSrvName 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "123456789x123456789x123456789x12"
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   2
      Left            =   240
      TabIndex        =   11
      Top             =   1200
      Visible         =   0   'False
      Width           =   4455
   End
   Begin VB.Label lblUser 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "123456789x123456789x123456789x12"
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   2
      Left            =   4680
      TabIndex        =   10
      Top             =   1200
      Visible         =   0   'False
      Width           =   4455
   End
   Begin VB.Label lblPW 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "default"
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   2
      Left            =   9120
      TabIndex        =   9
      Top             =   1200
      Visible         =   0   'False
      Width           =   1545
   End
   Begin VB.Label lblSrvName 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "123456789x123456789x123456789x12"
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   1
      Left            =   240
      TabIndex        =   8
      Top             =   840
      Visible         =   0   'False
      Width           =   4455
   End
   Begin VB.Label lblUser 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "123456789x123456789x123456789x12"
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   1
      Left            =   4680
      TabIndex        =   7
      Top             =   840
      Visible         =   0   'False
      Width           =   4455
   End
   Begin VB.Label lblPW 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "default"
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   1
      Left            =   9120
      TabIndex        =   6
      Top             =   840
      Visible         =   0   'False
      Width           =   1545
   End
   Begin VB.Label lblPassword 
      Caption         =   "Password"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   9240
      TabIndex        =   5
      Top             =   195
      Width           =   1215
   End
   Begin VB.Label lblUserName 
      Caption         =   "User Name"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   4800
      TabIndex        =   4
      Top             =   195
      Width           =   1215
   End
   Begin VB.Label lblServer 
      Caption         =   "Server"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   360
      TabIndex        =   3
      Top             =   195
      Width           =   1215
   End
   Begin VB.Label lblPW 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "default"
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   0
      Left            =   9120
      TabIndex        =   2
      Top             =   480
      Visible         =   0   'False
      Width           =   1545
   End
   Begin VB.Label lblUser 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "123456789x123456789x123456789x12"
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   0
      Left            =   4680
      TabIndex        =   1
      Top             =   480
      Visible         =   0   'False
      Width           =   4455
   End
   Begin VB.Label lblSrvName 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "123456789x123456789x123456789x12"
      BeginProperty Font 
         Name            =   "Courier"
         Size            =   15
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   375
      Index           =   0
      Left            =   240
      TabIndex        =   0
      Top             =   480
      Visible         =   0   'False
      Width           =   4455
   End
   Begin VB.Menu mnuFile 
      Caption         =   "&File"
      Begin VB.Menu mnuFileNew 
         Caption         =   "&New"
         Shortcut        =   ^N
      End
      Begin VB.Menu mnuFileOpen 
         Caption         =   "&Open"
         Shortcut        =   ^O
      End
      Begin VB.Menu mnuFileLine 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileSave 
         Caption         =   "&Save"
         Shortcut        =   ^S
      End
      Begin VB.Menu mnuFileSaveAs 
         Caption         =   "Save &As"
         Shortcut        =   {F2}
      End
      Begin VB.Menu mnuFileLine2 
         Caption         =   "-"
      End
      Begin VB.Menu mnuFileExit 
         Caption         =   "E&xit"
         Shortcut        =   ^X
      End
   End
   Begin VB.Menu mnuEdit 
      Caption         =   "&Edit"
      Begin VB.Menu mnuEditUndo 
         Caption         =   "&Undo"
         Enabled         =   0   'False
         Shortcut        =   ^Z
      End
      Begin VB.Menu mnuEditLine1 
         Caption         =   "-"
      End
      Begin VB.Menu mnuEditApp 
         Caption         =   "&Append Server Data"
      End
      Begin VB.Menu mnuEditIns 
         Caption         =   "&Insert Server Data"
      End
      Begin VB.Menu mnuEditEdit 
         Caption         =   "&Edit Server Data"
      End
      Begin VB.Menu mnuEditDelete 
         Caption         =   "&Delete Server Data"
      End
   End
   Begin VB.Menu mnuHelp 
      Caption         =   "&Help"
      Begin VB.Menu mnuHelpAbout 
         Caption         =   "&About"
      End
   End
   Begin VB.Menu mnrX 
      Caption         =   "Right Menu"
      Visible         =   0   'False
      Begin VB.Menu mnrUndo 
         Caption         =   "&Undo"
      End
      Begin VB.Menu mnrLine 
         Caption         =   "-"
      End
      Begin VB.Menu mnrInsert 
         Caption         =   "&Insert"
      End
      Begin VB.Menu mnrAppend 
         Caption         =   "&Append"
      End
      Begin VB.Menu mnrEdit 
         Caption         =   "&Edit"
      End
      Begin VB.Menu mnrDelete 
         Caption         =   "&Delete"
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private fEffect       As Boolean

Private Type UndoInfo
    action     As Integer
    pos        As Integer
    ServerName As String
    userName   As String
    password   As String
    fModified  As Boolean
    top        As Integer
    cursor     As Integer
End Type

Const maxUndos = 10
Const UD_ADD = 1
Const UD_MOD = 0
Const UD_DEL = -1

Private UndoTable(maxUndos - 1) As UndoInfo
Private UndoX               As UndoInfo
Private nNextUndo           As Integer
Private nrUndos             As Integer

Const NR_LINES = 5
' ========================================================== '
'                                                            '
' Depending upon the setting of fApp, insert a new server    '
' information record at the current cursor position or       '
' immediately after it.                                      '
'                                                            '
' ========================================================== '
Private Sub AppendOrInsert(fApp As Boolean)
    Dim i    As Integer
    Dim iYN  As Integer
    Dim iSrv As Integer
    Dim iLoc As Integer
    
    efTitle = IIf(fApp, "Append a PI Server to the List", "Insert a PI Server into the List")
    efMode = EF_ADD
    efDone = False
    frmEntry.Show 1
    
    ' See if the new server exists
    ' ----------------------------
    If efOK Then
        For i = 0 To nNrServers - 1
            If UCase(efServer.ServerName) = UCase(Server(i).ServerName) Then
                iYN = MsgBox(efServer.ServerName & " is already in the server table.  Update its user name/password?", vbYesNo + vbQuestion + vbDefaultButton2, "Server already known")
                If iYN = vbYes Then
                    Call SaveUndoInfo(UD_MOD, i)
                    Server(i).userName = efServer.userName
                    Server(i).password = efServer.password
                    FileModified (True)
                    DisplayTable
                End If
                Exit Sub
            End If
        Next i
    
    ' It doesn't.  Remember it.
    ' -------------------------
        updateNrServers (nNrServers + 1)
        If nNrServers = 1 Then
            ReDim Server(1)
            i = 0
            UpdateCursor (0)
        Else
            ReDim Preserve Server(nNrServers)
            iSrv = nTop + nCursor
            iLoc = IIf(fApp, iSrv + 1, iSrv)
            For i = nNrServers - 1 To iLoc Step -1
                Server(i + 1) = Server(i)
            Next i
            i = iLoc
        End If
        Call SaveUndoInfo(UD_ADD, i)
        FileModified (True)
        Server(i).ServerName = efServer.ServerName
        Server(i).userName = efServer.userName
        Server(i).password = efServer.password
        If fApp Then
            If nCursor = NR_LINES - 1 Then
                nTop = nTop + 1
                fEffect = True
                vs1.Value = nTop + nCursor
                fEffect = False
            Else
                UpdateCursor (nCursor + 1)
            End If
        End If
        DisplayTable
    End If

End Sub

' ========================================================== '
'                                                            '
'     Remove all information for all servers from memory.    '
'                                                            '
' ========================================================== '
Private Sub CleanUp()
    If nNrServers > 1 Then ReDim Server(1)
    updateNrServers (0)
    nTop = 0
    nCursor = 0
    fNamed = False
    FileModified (False)
    resetUndo
    DisplayTable
End Sub
' ========================================================== '
'                                                            '
' Display the data for up to NR_LINES servers, starting with '
' the server in the nTop position of the server table.  We   '
' call this function any time we may of changed the set of   '
' servers to be shown.                                       '
'                                                            '
' ========================================================== '
Private Sub DisplayTable()

    Dim iSrc        As Integer
    Dim iDisp       As Integer
    Dim fgcor       As Long
    Dim bgcor       As Long
    
    ' Any time we need to redisplay the screen, it is likely
    ' that the scroll bar setting will have changed.
    ' ------------------------------------------------------
    SetScrollBar
    
    ' Display nTop to lesser of nTop + NR_LINES - 1 or nNrServers-1
    ' -------------------------------------------------------------
    iDisp = 0
    For iSrc = nTop To IIf(nNrServers < nTop + NR_LINES, nNrServers - 1, nTop + NR_LINES - 1)
        setColors (iDisp)
        lblSrvName(iDisp).Caption = Server(iSrc).ServerName
        lblSrvName(iDisp).Visible = True
        lblUser(iDisp).Caption = Server(iSrc).userName
        lblUser(iDisp).Visible = True
        lblPW(iDisp).Caption = IIf(Server(iSrc).password = "", "Default", "*******")
        lblPW(iDisp).Visible = True
        iDisp = iDisp + 1
    Next iSrc
    While iDisp < NR_LINES
        lblSrvName(iDisp).Visible = False
        lblUser(iDisp).Visible = False
        lblPW(iDisp).Visible = False
        iDisp = iDisp + 1
    Wend
    
    ' Display or hide message about what to do when there
    ' are not any servers.
    ' ---------------------------------------------------
    lblNothing.Visible = (nNrServers = 0)

End Sub
' ========================================================== '
'                                                            '
' Remember whether or not there has been a change.  If so,   '
' put * in the form caption.                                 '
'                                                            '
' ========================================================== '
Private Sub FileModified(fMod As Boolean)
    Dim strTitle As String
    
    fModified = fMod
    strTitle = "PI Servers " & IIf(fNamed, strDestFile, "") & IIf(fModified, " *", "")
    If strTitle <> Me.Caption Then Me.Caption = strTitle

End Sub
' Load the information about the PI servers in
' fileName into the Server array
' ---------------------------------------------
Function LoadList(fileName As String) As Boolean
On Error GoTo NotLoaded

    Dim iStep      As Integer
    Dim iLen       As Integer
    Dim iComma     As Integer
    Dim iPW        As Integer
    Dim i          As Integer
    Dim Buffer     As String
    Dim ServerName As String
    Dim User       As String
    Dim pw         As String
    Dim strErrMsg  As String
    Dim fFormatErr As Boolean
    Dim fNewSrvr   As Boolean
    
    fFormatErr = False
    iStep = 1
    Open fileName For Input As #1
    CleanUp
    iStep = 2
    While Not EOF(1)
    
        ' Read the next line
        ' ------------------
        Line Input #1, Buffer
        Buffer = Trim(Buffer)
        
        ' Prepare to extract the 3 parts.  Assume
        ' the user name and password are missing.
        ' ---------------------------------------
        fNewSrvr = True
        iLen = Len(Buffer)
        User = ""
        iPW = iLen + 1
        pw = ""
        If (iLen > 0) Then
        
            ' Extract the Server Name
            ' -----------------------
            iComma = InStr(Buffer, ",")
            If iComma > 0 Then
                If iComma = 1 Then
                    fFormatErr = True
                    strErrMsg = "server name is required"
                    GoTo NotLoaded
                Else
                    ServerName = Left(Buffer, iComma - 1)
                    If iComma = iLen Then GoTo LoadArray
                    Buffer = Right(Buffer, iLen - iComma)
                End If
            Else
                ServerName = Buffer
                GoTo LoadArray
            End If
            
            ' Extract the User Name & Encrypted Password
            ' ------------------------------------------
            iLen = Len(Buffer)
            If iLen = 0 Then GoTo LoadArray
            iComma = InStr(Buffer, ",")
            If iComma = 0 Then
                User = Buffer
                GoTo LoadArray
            Else
                If iComma > 1 Then User = Left(Buffer, iComma - 1)
                If iComma < iLen Then pw = Right(Buffer, iLen - iComma)
            End If

            ' If this server is already in the table,
            ' overwrite its user and password info
            ' ---------------------------------------
LoadArray:
            For i = 0 To nNrServers - 1
                If UCase(ServerName) = UCase(Server(i).ServerName) Then
                    MsgBox "Warning: information for " & ServerName & " overwritten", vbExclamation, "More than one entry for this server"
                    fNewSrvr = False
                    Exit For
                End If
            Next i
            
            ' Create a new entry for this server
            ' ----------------------------------
            If fNewSrvr Then
                i = nNrServers
                updateNrServers (nNrServers + 1)
                If nNrServers = 1 Then
                    ReDim Server(nNrServers)
                Else
                    ReDim Preserve Server(nNrServers)
                End If
                Server(i).ServerName = ServerName
            End If
        
            ' Save the user name and encrypted password
            ' -----------------------------------------
            Server(i).userName = User
            Server(i).password = pw
        End If
    Wend
    nTop = 0
    nCursor = 0
    DisplayTable
    
    ' Success
    ' -------
    Close #1
    LoadList = True
    Exit Function

    ' Failed to load server table
    ' ---------------------------
NotLoaded:
    If iStep > 1 Then Close #1
    If fFormatErr Then
        MsgBox "Unable to load server information from """ & fileName & """: " & strErrMsg, , "Load Error"
    Else
        MsgBox "Unable to load server information from """ & fileName & """: " & Err.Description, , "Load Error"
    End If
    nNrServers = 0
    LoadList = False
    Exit Function
End Function
' ================================================
' Give the user a chance to save the file or abort
' the operation if the server data has changed.
' ================================================
Private Function OKtoThrowOut() As Boolean

    Dim iYN    As Integer
    Dim strMsg As String

    ' Nothing to do if there have not been any modifications
    ' ------------------------------------------------------
    OKtoThrowOut = True
    If Not fModified Then Exit Function
    
    ' Save it, throw it out, or abort action
    ' --------------------------------------
    strMsg = "Save the changes" & IIf(fNamed, " to " & strDestFile, "") & "?"
    iYN = MsgBox(strMsg, vbQuestion + vbYesNoCancel + vbDefaultButton3, "There are Unsaved Changes")
    If Not iYN = vbYes Then
        OKtoThrowOut = (iYN = vbNo)
        Exit Function
    End If
    
    ' We need to save the changes before continuing
    ' ---------------------------------------------
    OKtoThrowOut = SaveChanges(False)

End Function
' ========================================================== '
'                                                            '
'  Determine whether or not the information for the server   '
'  in the specified line of the server table is currently    '
'  being displayed.                                          '
'                                                            '
' ========================================================== '
Private Function OnPage(absLine As Integer) As Boolean

    OnPage = absLine >= nTop And absLine < nTop + NR_LINES
    
End Function
' ========================================================== '
'                                                            '
'                   Restart Undo recording                   '
'                                                            '
' ========================================================== '
Private Sub resetUndo()
    nrUndos = 0
    nNextUndo = 0
    mnuEditUndo.Enabled = False
    mnrUndo.Enabled = False
End Sub
' ========================================================== '
'                                                            '
'     Write the changes in the server table to a file.       '
'                                                            '
' ========================================================== '
Private Function SaveChanges(fSaveAs As Boolean) As Boolean
On Error GoTo SaveError

    Dim iYN     As Integer
    Dim i       As Integer
    Dim strX    As String
    
    SaveChanges = False
        
    ' if not "Save As", save it without a dialog
    ' ------------------------------------------
    dlgCo.fileName = IIf(fNamed, strDestFile, "PISRVRS.dat")
    dlgCo.Filter = "PI Server Data (*.dat)|*.dat|All (*.*)|*.*"
    If Not fSaveAs And fNamed Then GoTo SaveFile
    
    ' Get the file name and directory
    ' -------------------------------
    dlgCo.DefaultExt = ".dat"
    dlgCo.CancelError = True
    dlgCo.ShowSave
    
    ' Determine if we are trying overwrite a file
    ' other than the originally opened file.
    ' -------------------------------------------
    If fNamed Then
        If UCase(dlgCo.fileName) = UCase(strDestFile) Then GoTo SaveFile
    End If
    strX = Dir(dlgCo.fileName)
    If strX > "" Then
        If Dir(dlgCo.fileName, vbNormal) > "" Then
            iYN = MsgBox("Overwrite " & dlgCo.fileName & "?", vbQuestion + vbYesNo + vbDefaultButton2, "File Exists")
            If iYN = vbNo Then Exit Function
        Else
            MsgBox dlgCo.fileName & " cannot be overwritten", vbExclamation + vbOKOnly, "Not a Writeable File"
            Exit Function
        End If
    End If
    
    ' Write the data to the file
    ' --------------------------
SaveFile:
    Open dlgCo.fileName For Output As #1
    For i = 0 To nNrServers - 1
        Print #1, Server(i).ServerName & "," & Server(i).userName & "," & Server(i).password
    Next i
    Close #1
    
    fNamed = True
    strDestFile = dlgCo.fileName
    FileModified (False)
    
    SaveChanges = True
    Exit Function
SaveError:
    SaveChanges = False
    If Err.Number = cdlCancel Then Exit Function
    MsgBox "Error writing to " & dlgCo.fileName & ":" & Err.Description, vbExclamation + vbOKOnly, "Unable to Save"
End Function
' ========================================================== '
'                                                            '
'    Any time we do something that we might want to undo,    '
'    we save the information to undo it here.                '
'                                                            '
' ========================================================== '
Private Sub SaveUndoInfo(action As Integer, pos As Integer)
    UndoX.action = action
    UndoX.fModified = fModified
    UndoX.pos = pos
    If action <> UD_ADD Then
        UndoX.ServerName = Server(pos).ServerName
        UndoX.userName = Server(pos).userName
        UndoX.password = Server(pos).password
    End If
    UndoX.top = nTop
    UndoX.cursor = nCursor
    UndoTable(nNextUndo) = UndoX
    mnuEditUndo.Enabled = True
    mnrUndo.Enabled = True
    If nrUndos < maxUndos Then nrUndos = nrUndos + 1
    nNextUndo = nNextUndo + 1
    If nNextUndo >= maxUndos Then nNextUndo = 0
End Sub
' ========================================================== '
'                                                            '
' Set the colors for the specified line to show whether or   '
' not it is the cursor line.                                 '
'                                                            '
' ========================================================== '
Sub setColors(nLine As Integer)
    Dim bgcor As Long
    Dim fgcor As Long
    
    bgcor = IIf(nLine = nCursor, vbBlue, vbWhite)
    fgcor = IIf(nLine = nCursor, vbYellow, vbBlack)
    lblSrvName(nLine).BackColor = bgcor
    lblSrvName(nLine).ForeColor = fgcor
    lblUser(nLine).BackColor = bgcor
    lblUser(nLine).ForeColor = fgcor
    lblPW(nLine).BackColor = bgcor
    lblPW(nLine).ForeColor = fgcor
End Sub
' =============================================================== '
'                                                                 '
' Based upon the number of servers in the server table and the    '
' current cursor setting, set and show the scroll bar or hide it. '
'                                                                 '
' =============================================================== '
Private Sub SetScrollBar()
    fEffect = True
    If nNrServers > NR_LINES Then
        vs1.Min = 0
        vs1.Max = nNrServers - 1
        vs1.Value = nCursor + nTop
        vs1.Visible = True
    Else
        vs1.Visible = False
    End If
    fEffect = False
End Sub
' =========================================================== '
'                                                             '
'    Adjust the scroll bar at the same time we change the     '
'    cursor postion.                                          '
'                                                             '
' =========================================================== '
Private Sub UpdateCursor(newCursor As Integer)
    nCursor = newCursor
    If nNrServers > NR_LINES Then
        fEffect = True
        vs1.Value = nTop + nCursor
        fEffect = False
    End If
End Sub
' =========================================================== '
'                                                             '
'  Disable several menus any time there are not any servers   '
'  in the server info table.  Show or hide the scroll bar     '
'  any time the number of servers in the server table         '
'  changes.                                                   '
'                                                             '
' =========================================================== '
Private Sub updateNrServers(newCt As Integer)
    nNrServers = newCt
    
    mnuFileSave.Enabled = newCt > 0
    mnuFileSaveAs.Enabled = mnuFileSave.Enabled
    mnuEditEdit.Enabled = mnuFileSave.Enabled
    mnrEdit.Enabled = mnuFileSave.Enabled
    mnuEditDelete.Enabled = mnuFileSave.Enabled
    mnrDelete.Enabled = mnuFileSave.Enabled
    If nNrServers > 5 Then
        fEffect = True
        vs1.Max = nNrServers - 1
        vs1.Value = nCursor + nTop
        vs1.Visible = True
        fEffect = False
    Else
        vs1.Visible = False
    End If
End Sub
' =========================================================== '
'                                                             '
' All keyboard commands are processed here, at the form level '
'                                                             '
' =========================================================== '
Private Sub Form_KeyDown(KeyCode As Integer, Shift As Integer)
    Dim nLastScrLine As Integer
    Dim nAbsLine     As Integer
    
    nLastScrLine = IIf(NR_LINES < nNrServers, NR_LINES, nNrServers) - 1
    
    ' Down arrow
    ' ----------
    If KeyCode = vbKeyDown Then
        If nCursor < nLastScrLine Then
            UpdateCursor (nCursor + 1)
            setColors (nCursor - 1)
            setColors (nCursor)
        ElseIf nCursor + nTop = nNrServers - 1 Then
            AppendOrInsert (True)
        Else
            nTop = nTop + 1
            DisplayTable
        End If
        
    ' Up arrow
    ' --------
    ElseIf KeyCode = vbKeyUp Then
        If nCursor > 0 Then
            UpdateCursor (nCursor - 1)
            setColors (nCursor + 1)
            setColors (nCursor)
        ElseIf nTop > 0 Then
            nTop = nTop - 1
            fEffect = True
            vs1.Value = nTop + nCursor
            fEffect = False
            DisplayTable
        End If
        
    ' Insert key
    ' ----------
    ElseIf KeyCode = vbKeyInsert Then
        Call mnuEditIns_Click
        
    ' Delete key
    ' ----------
    ElseIf KeyCode = vbKeyDelete Then
        Call mnuEditDelete_Click
        
    ' Enter key - modify current record
    ' ---------------------------------
    ElseIf KeyCode = vbKeyReturn Then
        If nNrServers > 0 Then
            Call mnuEditEdit_Click
        End If
        
    ' Page up (not ctrl-PageUp)
    ' -------------------------
    ElseIf KeyCode = vbKeyPageUp And ((Shift And vbCtrlMask) = 0) Then
        nAbsLine = nTop + nCursor - NR_LINES + 1
        If nAbsLine < 0 Then nAbsLine = 0
        If Not OnPage(nAbsLine) Then
            nTop = nAbsLine - nCursor
            If nTop < 0 Then nTop = 0
        End If
        nCursor = nAbsLine - nTop
        DisplayTable
                
    ' Page down (not ctrl-PageDown)
    ' -----------------------------
    ElseIf KeyCode = vbKeyPageDown And ((Shift And vbCtrlMask) = 0) Then
        nAbsLine = nTop + nCursor + NR_LINES - 1
        If nAbsLine >= nNrServers Then nAbsLine = nNrServers - 1
        If Not OnPage(nAbsLine) Then
            nTop = nTop + NR_LINES - 1
            If nTop + NR_LINES >= nNrServers Then nTop = nNrServers - NR_LINES
        End If
        nCursor = nAbsLine - nTop
        DisplayTable
        
    ' Home or ctrl-PageUp
    ' -------------------
    ElseIf KeyCode = vbKeyHome Or KeyCode = vbKeyPageUp Then
        nTop = 0
        nCursor = 0
        DisplayTable
        
    ' End or ctrl-PageDown
    ' --------------------
    ElseIf KeyCode = vbKeyEnd Or KeyCode = vbKeyPageDown Then
        nTop = nNrServers - NR_LINES
        If nTop < 0 Then nTop = 0
        nCursor = nNrServers - 1 - nTop
        DisplayTable
        
    ' Alt-F4 exits program
    ' --------------------
    ElseIf KeyCode = vbKeyF4 And (Shift And vbAltMask) Then
        Call mnuFileExit_Click
    End If
    
    KeyCode = 0
        
End Sub
' =========================================================== '
'                                                             '
'    We are loading the main form.  Initialize the display.   '
'                                                             '
' =========================================================== '
Private Sub Form_Load()
    Dim i          As Integer
    Dim strSrvList As String * 129
    Dim strX       As String
    Dim iLen       As Integer
    Dim iYN        As Integer
    
    ' Initialization
    ' --------------
    fNamed = False
    fModified = False
    
    ' Look for existing PI Servers file
    ' 1. check environment variable G2PSL
    ' -----------------------------------
    iLen = GetEnvironmentVariable("G2PSL", strSrvList, 128)
    If iLen > 0 Then
        strDestFile = Left(strSrvList, iLen)
        If LoadList(strDestFile) Then
            fNamed = True
            GoTo StartMain
        End If
    End If

    ' 2. if not found look for PISRVRS.dat in current directory
    ' ---------------------------------------------------------
    strX = CurDir & IIf(Right$(CurDir, 1) = "\", "pisrvrs.dat", "\pisrvrs.dat")
    If Dir(strX) > "" Then
        If LoadList(strX) Then
            fNamed = True
            strDestFile = strX
            GoTo StartMain
        End If
    End If
    
    ' 3. if not found, give user option of creating new or browsing
    ' -------------------------------------------------------------
    iYN = MsgBox("Would you like to search for the server data file?", vbYesNo + vbQuestion, "Server Data File not Found")
    If iYN = vbYes Then
        dlgCo.InitDir = CurDir
        mnuFileOpen_Click
    End If
    
    
    ' Open main form which will display loaded information
    ' ----------------------------------------------------
StartMain:
    ' Start with a clean slate
    ' ------------------------
    updateNrServers (nNrServers)
    FileModified (False)
    resetUndo
  
    ' If there are no servers in the server table,
    ' display the entry form so the user can add one.
    ' -----------------------------------------------
    If nNrServers = 0 Then
        Call mnuEditIns_Click
    End If
            
    ' If a scroll bar is needed, initialize it.
    ' -----------------------------------------
    If nNrServers > NR_LINES Then
        fEffect = True
        vs1.Visible = True
        vs1.Max = nNrServers - NR_LINES
        vs1.LargeChange = NR_LINES - 1
        vs1.Value = 0
        fEffect = False
    End If
    
        
    ' Initialization: Enable or disable menus, we are
    ' in an unmodified state, there is nothing to undo.
    ' -------------------------------------------------
    
    ' Show the start of the table
    ' ---------------------------
    nTop = 0
    nCursor = 0
    DisplayTable
    
    ' Display this form
    ' -----------------
    Me.Show
End Sub
' =========================================================== '
'                                                             '
'        Give the user a chance to save any changes           '
'        before closing this form                             '
'                                                             '
' =========================================================== '
Private Sub Form_Unload(Cancel As Integer)
    Cancel = Not OKtoThrowOut
End Sub
' =========================================================== '
'                                                             '
'       Give the user a chance to insert a record from a      '
'       right-click menu.                                     '
'                                                             '
' =========================================================== '
Private Sub lblNothing_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single)
    If Button = vbRightButton Then PopupMenu mnrX
End Sub
' =========================================================== '
'                                                             '
'              Select the line that was clicked               '
'                                                             '
' =========================================================== '
Private Sub lblPW_Click(Index As Integer)
    UpdateCursor (Index)
    DisplayTable
End Sub
' =========================================================== '
'                                                             '
'           Edit the line that was double-clicked             '
'                                                             '
' =========================================================== '
Private Sub lblPW_DblClick(Index As Integer)
    Call lblPW_Click(Index)
    Call mnuEditEdit_Click
End Sub
' =========================================================== '
'                                                             '
' Display the right menu for the line that was right-clicked  '
'                                                             '
' =========================================================== '
Private Sub lblPW_MouseDown(Index As Integer, Button As Integer, Shift As Integer, X As Single, Y As Single)
    If Button = vbRightButton Then
        Call lblPW_Click(Index)
        PopupMenu mnrX
    End If
End Sub
' =========================================================== '
'                                                             '
'              Select the line that was clicked               '
'                                                             '
' =========================================================== '
Private Sub lblSrvName_Click(Index As Integer)
    UpdateCursor (Index)
    DisplayTable
End Sub
' =========================================================== '
'                                                             '
'           Edit the line that was double-clicked             '
'                                                             '
' =========================================================== '
Private Sub lblSrvName_DblClick(Index As Integer)
    Call lblSrvName_Click(Index)
    Call mnuEditEdit_Click
End Sub
' =========================================================== '
'                                                             '
' Display the right menu for the line that was right-clicked  '
'                                                             '
' =========================================================== '
Private Sub lblSrvName_MouseDown(Index As Integer, Button As Integer, Shift As Integer, X As Single, Y As Single)
    If Button = vbRightButton Then
        Call lblSrvName_Click(Index)
        PopupMenu mnrX
    End If
End Sub
' =========================================================== '
'                                                             '
'              Select the line that was clicked               '
'                                                             '
' =========================================================== '
Private Sub lblUser_Click(Index As Integer)
    UpdateCursor (Index)
    DisplayTable
End Sub
' =========================================================== '
'                                                             '
'           Edit the line that was double-clicked             '
'                                                             '
' =========================================================== '
Private Sub lblUser_DblClick(Index As Integer)
    Call lblUser_Click(Index)
    Call mnuEditEdit_Click
End Sub
' =========================================================== '
'                                                             '
' Display the right menu for the line that was right-clicked  '
'                                                             '
' =========================================================== '
Private Sub lblUser_MouseDown(Index As Integer, Button As Integer, Shift As Integer, X As Single, Y As Single)
    If Button = vbRightButton Then
        Call lblUser_Click(Index)
        PopupMenu mnrX
    End If
End Sub
' =========================================================== '
'                                                             '
'  Insert a record into the table after the current record.   '
'                                                             '
' =========================================================== '
Private Sub mnrAppend_Click()
    Call mnuEditApp_Click
End Sub
Private Sub mnrDelete_Click()
    Call mnuEditDelete_Click
End Sub
Private Sub mnrEdit_Click()
    Call mnuEditEdit_Click
End Sub
' =========================================================== '
'                                                             '
'  Insert a record into the table before the current record.  '
'                                                             '
' =========================================================== '
Private Sub mnrInsert_Click()
    Call mnuEditIns_Click
End Sub
Private Sub mnrUndo_Click()
    Call mnuEditUndo_Click
End Sub
' =========================================================== '
'                                                             '
'  Insert a record into the table after the current record.   '
'                                                             '
' =========================================================== '
Private Sub mnuEditApp_Click()
    AppendOrInsert (True)
End Sub
' =========================================================== '
'                                                             '
'                 Delete the current record.                  '
'                                                             '
' =========================================================== '
Private Sub mnuEditDelete_Click()
    Dim iSrv As Integer
    Dim iYN  As Integer
    Dim i    As Integer
    
    iSrv = nTop + nCursor
    iYN = MsgBox("Are you sure you wish to delete " & Server(iSrv).ServerName, vbQuestion + vbYesNo + vbDefaultButton2, "Remove Server?")
    If iYN = vbYes Then
        Call SaveUndoInfo(UD_DEL, iSrv)
        FileModified (True)
        For i = iSrv To nNrServers - 2
            Server(i) = Server(i + 1)
        Next i
        If OnPage(nNrServers - 1) Then
            If nTop > 0 Then
                nTop = nTop - 1
            ElseIf nTop + nCursor = nNrServers - 1 Then
                nCursor = nCursor - 1
            End If
        End If
        updateNrServers (nNrServers - 1)
        If nNrServers > 0 Then ReDim Preserve Server(nNrServers)
        DisplayTable
    End If
End Sub
' =========================================================== '
'                                                             '
'                   Modify the current record.                '
'                                                             '
' =========================================================== '
Private Sub mnuEditEdit_Click()
    Dim iSrv As Integer
    
    efMode = EF_EDIT
    efTitle = "Edit PI Server Information"
    efDone = False
    iSrv = nTop + nCursor
    efServer = Server(iSrv)
    Load frmEntry
    frmEntry.Caption = efTitle
    efOK = False
    efMod = False
    efModPW = False
    If efMode = EF_EDIT Then
        frmEntry!txtServer = efServer.ServerName
        frmEntry!txtUserName = efServer.userName
        frmEntry!txtPW = IIf(efServer.password = "", "", "****")
    End If
    frmEntry.Show (1)
    If efOK Then
        If efMod Then
            Call SaveUndoInfo(UD_MOD, iSrv)
            Server(iSrv) = efServer
            FileModified (True)
            DisplayTable
        End If
    End If
        
End Sub
' =========================================================== '
'                                                             '
'  Insert a record into the table before the current record.  '
'                                                             '
' =========================================================== '
Private Sub mnuEditIns_Click()
    AppendOrInsert (False)
End Sub
' =========================================================== '
'                                                             '
'       Undo the last modification to the server table.       '
'                                                             '
' =========================================================== '
Private Sub mnuEditUndo_Click()
    Dim action As Integer
    Dim i      As Integer
    Dim p      As Integer
    Dim sri    As ServerInfo
    
    
    ' Back up and point to the command to be undone
    ' ---------------------------------------------
    nNextUndo = nNextUndo - 1
    If nNextUndo < 0 Then nNextUndo = maxUndos - 1
    p = UndoTable(nNextUndo).pos
    action = UndoTable(nNextUndo).action
    
    ' The action we are undoing is an append/insert.
    ' Delete the new server record.
    ' -----------------------------------------------
    If action = UD_ADD Then
           
        ' Delete server record
        ' --------------------
        For i = p To nNrServers - 1
            Server(i) = Server(i + 1)
        Next i
        updateNrServers (nNrServers - 1)
        If nNrServers > 0 Then ReDim Preserve Server(nNrServers)
        
    ' We are undoing a modification to an existing record.
    ' Save the new information, then restore the original info.
    ' ---------------------------------------------------------
    ElseIf action = UD_MOD Then
            
        ' Restore the original info
        ' -------------------------
        Server(p).ServerName = UndoTable(nNextUndo).ServerName
        Server(p).userName = UndoTable(nNextUndo).userName
        Server(p).password = UndoTable(nNextUndo).password
                
                
    ' We are undoing a delete.  Put back the original record.
    ' -------------------------------------------------------
    Else
    
        ' Make room for the new record
        ' ----------------------------
        nNrServers = nNrServers + 1
        ReDim Preserve Server(nNrServers)
        
        ' Open a slot for the new record
        ' ------------------------------
        For i = nNrServers To p + 1 Step -1
            Server(i) = Server(i - 1)
        Next i
        
        ' Add the new record to the server info table
        ' -------------------------------------------
        Server(p).ServerName = UndoTable(nNextUndo).ServerName
        Server(p).userName = UndoTable(nNextUndo).userName
        Server(p).password = UndoTable(nNextUndo).password
    End If
    
    ' Display the corrected table
    ' ---------------------------
    nTop = UndoTable(nNextUndo).top
    nCursor = UndoTable(nNextUndo).cursor
    DisplayTable
    FileModified (UndoTable(nNextUndo).fModified)
    
    ' Disable the undo command if we have processed all undo.s
    ' --------------------------------------------------------
    nrUndos = nrUndos - 1
    If nrUndos <= 0 Then
        mnuEditUndo.Enabled = False
        mnrUndo.Enabled = False
    End If
End Sub
' =========================================================== '
'                                                             '
'      Exit the program.  The form's unload function will     '
'      give the user a chance to save any changes before      '
'      the program terminates.                                '
'                                                             '
' =========================================================== '
Private Sub mnuFileExit_Click()
    Unload Me
End Sub
' =========================================================== '
'                                                             '
'      After giving the user a chance to save any changes,    '
'      start a new PI server data file.                       '
'                                                             '
' =========================================================== '
Private Sub mnuFileNew_Click()
    If OKtoThrowOut Then
        CleanUp
    End If
End Sub
' =========================================================== '
'                                                             '
'  After giving the user a chance to save any changes,        '
'  load a new server information table.  If the load fails,   '
'  use a blank table since prior information may have been    '
'  overwritten before the load failed.                        '
'                                                             '
' =========================================================== '
Private Sub mnuFileOpen_Click()
    If OKtoThrowOut Then
        dlgCo.fileName = IIf(fNamed, strDestFile, "PISRVRS.dat")
        dlgCo.Filter = "PI Server Data (*.dat)|*.dat|All (*.*)|*.*"
        dlgCo.Flags = cdlOFNHideReadOnly
        dlgCo.ShowOpen
    End If
    
    If LoadList(dlgCo.fileName) Then
        fNamed = True
        strDestFile = dlgCo.fileName
        FileModified (False)
        resetUndo
    Else
        CleanUp
    End If
OpenFailed:
    If Err.Number = cdlCancel Then Exit Sub
End Sub
' =========================================================== '
'                                                             '
'  Save the current server table to the file from which       '
'  it was loaded.                                             '
'                                                             '
' =========================================================== '
Private Sub mnuFileSave_Click()
    If fModified Then SaveChanges (False)
End Sub
' =========================================================== '
'                                                             '
'    Save the current server table, possibly to a new file.   '
'                                                             '
' =========================================================== '
Private Sub mnuFileSaveAs_Click()
    SaveChanges (True)
End Sub
' =========================================================== '
'                                                             '
'               Display the "About" Screen                    '
'                                                             '
' =========================================================== '
Private Sub mnuHelpAbout_Click()
    Load frmAbout
End Sub
' =========================================================== '
'                                                             '
'  Modify the cursor position when the scroll bar is clicked. '
'                                                             '
' =========================================================== '
Private Sub vs1_Change()
Dim nDesired

    If fEffect Then Exit Sub
    If vs1.Value >= nTop And vs1.Value < nTop + NR_LINES Then
        nCursor = vs1.Value - nTop
    ElseIf vs1.Value < nCursor Then
        nTop = vs1.Value
        nCursor = 0
    Else
        nDesired = vs1.Value - 2
        nTop = IIf(nDesired < 0, 0, nDesired)
        If nTop + NR_LINES > nNrServers Then nTop = nNrServers - NR_LINES
        nCursor = vs1.Value - nTop
    End If
    DisplayTable
End Sub
