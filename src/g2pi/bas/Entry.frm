VERSION 5.00
Begin VB.Form frmEntry 
   Caption         =   "Add Server Information"
   ClientHeight    =   2175
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   8850
   Icon            =   "Entry.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   2175
   ScaleWidth      =   8850
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton btnCancel 
      Cancel          =   -1  'True
      Caption         =   "&Cancel"
      Height          =   495
      Left            =   7440
      TabIndex        =   7
      Top             =   840
      Width           =   1215
   End
   Begin VB.CommandButton btnOK 
      Caption         =   "&OK"
      Default         =   -1  'True
      Height          =   495
      Left            =   7440
      TabIndex        =   6
      Top             =   240
      Width           =   1215
   End
   Begin VB.TextBox txtPW 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   420
      IMEMode         =   3  'DISABLE
      Left            =   1680
      PasswordChar    =   "*"
      TabIndex        =   5
      Top             =   1400
      Width           =   5535
   End
   Begin VB.TextBox txtUserName 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   420
      Left            =   1680
      TabIndex        =   4
      Top             =   800
      Width           =   5535
   End
   Begin VB.TextBox txtServer 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   420
      Left            =   1680
      TabIndex        =   3
      Top             =   200
      Width           =   5535
   End
   Begin VB.Label Label6 
      Alignment       =   1  'Right Justify
      Caption         =   "&Password:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   0
      TabIndex        =   2
      Top             =   1440
      Width           =   1500
   End
   Begin VB.Label Label5 
      Alignment       =   1  'Right Justify
      Caption         =   "&User Name:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   0
      TabIndex        =   1
      Top             =   840
      Width           =   1500
   End
   Begin VB.Label Label4 
      Alignment       =   1  'Right Justify
      Caption         =   "&Server:"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   0
      TabIndex        =   0
      Top             =   240
      Width           =   1500
   End
End
Attribute VB_Name = "frmEntry"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Declare Sub CopyMem Lib "kernel32" Alias "RtlMoveMemory" (pDest As Any, pSrc As Any, ByVal dwLen As Long)
Private Declare Function LocalAlloc Lib "kernel32" (ByVal uFlags As Long, ByVal uBytes As Long) As Long
Private Declare Function LocalFree Lib "kernel32" (ByVal hMem As Long) As Long
Private Const LPTR = (&H0 Or &H40)

' =========================================================== '
'                                                             '
'           Turn a password into an encrypted string          '
'                                                             '
' =========================================================== '
'
Private Function Encode(PWIn As String, PWOut) As Boolean

    Dim iLen       As Integer
    Dim iRPos      As Integer
    Dim iRLen      As Integer
    Dim iHLen      As Integer
    Dim i          As Integer
    Dim iX         As Integer
    Dim strRndSrc  As String
    Dim encPW      As String * 81
    Dim lenDigs(3) As String
    Dim fSuccess   As Boolean
    
    Dim nd0        As String
    Dim nd1        As String
    Dim nd2        As String
    Dim magicNr    As Integer
    Dim iRandLen   As Integer
    Dim iPWLen     As Integer
    Dim decPW      As String * 81
    Dim strKey     As String * 18
    Dim strHlp     As String
    Dim strX       As String
    Dim strErase   As String
    Dim lSize      As Long
    Dim lpd        As Long
    Dim lps        As Long
    Dim ct         As Long
    Dim b(1 To 38) As Byte
    
    strRndSrc = "kS*3!QSX2WdC$rFvBGt%6yHnMjU7*iK,>/:p)))-{{{`{'}}="
    
    Encode = False
    iLen = Len(PWIn)
    If iLen > 80 Then Exit Function
    strHlp = "vi2  9083"
    iRPos = (iLen + 11) Mod 22
    iRLen = 3 * iLen Mod 17 + 1
    iHLen = 18 * iLen + iRLen
    
    ' Construct key (832769041-viervoor)
    ' ----------------------------------
    strKey = " 3 76  41-  er  or"
    strX = "                  "
    strErase = "                  "
    lps = StrPtr(strKey)
    lpd = StrPtr(strX)
    CopyMem ByVal lpd, ByVal lps, LenB(strX)
    lps = StrPtr(strHlp)
    lpd = StrPtr(strX)
    CopyMem ByVal lpd + 4, ByVal lps + 4, 2
    lps = StrPtr(strHlp)
    lpd = StrPtr(strX)
    CopyMem ByVal lpd + 20, ByVal lps, 4
    lps = StrPtr(strHlp)
    lpd = StrPtr(strX)
    CopyMem ByVal lpd, ByVal lps + 14, 2
    lps = StrPtr(strHlp)
    lpd = StrPtr(strX)
    CopyMem ByVal lpd + 30, ByVal lpd + 32, 2
    lps = StrPtr(strHlp)
    lpd = StrPtr(strX)
    CopyMem ByVal lpd + 10, ByVal lps + 10, 4
    lps = StrPtr(strHlp)
    lpd = StrPtr(strX)
    CopyMem ByVal lpd + 28, ByVal lpd + 20, 2
    
    fSuccess = Encrypter(PWIn, strX, encPW)
    
    lps = StrPtr(strErase)
    lpd = StrPtr(strX)
    CopyMem ByVal lpd, ByVal lps, LenB(strX)
    
    If Not fSuccess Then Exit Function
    For i = 0 To 2
        iX = iHLen Mod 23
        lenDigs(i) = IIf(iX <= 9, Chr$(iX + 33), Chr$(iX - 10 + Asc("A")))
        Debug.Print i, iX
        iHLen = (iHLen - iX) / 23
    Next i
    
    PWOut = lenDigs(0) & lenDigs(2) & Chr(4 + iLen + iRLen + 32) & Mid(strRndSrc, iRPos, iRLen) & Trim(encPW) & lenDigs(1)
    Encode = True
    
    ' Model for decoding - remove later
    ' ---------------------------------
    nd0 = Asc(Left(PWOut, 1))
    nd2 = Asc(Mid(PWOut, 2, 1))
    nd1 = Asc(Right(PWOut, 1))
    
    magicNr = nd2 - IIf(nd2 >= Asc("A"), Asc("A"), 33)
    magicNr = 23 * magicNr + nd1 - IIf(nd1 >= Asc("A"), Asc("A") - 10, 33)
    magicNr = 23 * magicNr + nd0 - IIf(nd0 >= Asc("A"), Asc("A") - 10, 33)
    
    iRandLen = magicNr Mod 18
    iPWLen = (magicNr - iRandLen) / 18
    
    fSuccess = Decrypt(Mid(PWOut, iRandLen + 4, iPWLen), "832769041-viervoor", decPW)
End Function
' =================================================
' Cancel the addition of a new server record or the
' modification of an existing record
' =================================================
Private Sub btnCancel_Click()
    efOK = False
    Unload Me
End Sub
' ========================================================
' The user is done adding a new server record or modifying
' an existing record.  There must be a server name.
' ========================================================
Private Sub btnOK_Click()
    Dim encPW    As String * 162
    Dim pw       As String * 120
    Dim fSuccess As Boolean
    Dim llen     As Long
    Dim i        As Integer
    
    
    If Trim(txtServer) = "" Then
        Beep
    Else
        efOK = True
        efServer.ServerName = Trim(txtServer)
        efServer.userName = IIf(Trim(txtUserName) = "", "", Trim(txtUserName))
        If efModPW Then
            If txtPW = "" Then
                efServer.password = ""
            Else
                If Not Encode(txtPW, efServer.password) Then
                    MsgBox "Password storage failure.", vbCritical, "Not Processed"
                    efOK = False
                End If
            End If
        End If
        Unload Me
    End If
End Sub



Private Sub txtPW_Change()
    efMod = True
    efModPW = True
End Sub

Private Sub txtPW_GotFocus()
    Dim iLen As Integer
    
    iLen = Len(txtPW)
    If iLen > 0 Then
        txtPW.SelStart = 0
        txtPW.SelLength = iLen
    End If

End Sub

Private Sub txtServer_Change()
    efMod = True
End Sub
' Select the entire field
' =======================
Private Sub txtServer_GotFocus()
    Dim iLen As Integer
    
    iLen = Len(txtServer)
    If iLen > 0 Then
        txtServer.SelStart = 0
        txtServer.SelLength = iLen
    End If
End Sub
' Commas and spaces are not permitted in server name
' =================================================
Private Sub txtServer_KeyPress(KeyAscii As Integer)
    If KeyAscii = Asc(",") Or KeyAscii = Asc(" ") Then
        Beep
        KeyAscii = 0
    End If
End Sub
Private Sub txtUserName_Change()
    efMod = True
End Sub
' Select the entire field
' =======================
Private Sub txtUserName_GotFocus()
    Dim iLen As Integer
    
    iLen = Len(txtUserName)
    If iLen > 0 Then
        txtUserName.SelStart = 0
        txtUserName.SelLength = iLen
    End If

End Sub

' Commas are not permitted in user name
' =====================================
Private Sub txtUserName_KeyPress(KeyAscii As Integer)
    If KeyAscii = Asc(",") Then
        Beep
        KeyAscii = 0
    End If
End Sub
