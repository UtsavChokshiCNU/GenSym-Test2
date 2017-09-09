VERSION 5.00
Begin VB.Form frmRmvAxL 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "  Remove ActiveXLink from Registry"
   ClientHeight    =   4350
   ClientLeft      =   5160
   ClientTop       =   3945
   ClientWidth     =   6045
   Icon            =   "frmRmvAxL.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   4350
   ScaleWidth      =   6045
   StartUpPosition =   2  'CenterScreen
   Begin VB.CommandButton btnExit 
      Caption         =   "E&xit"
      Height          =   495
      Left            =   4680
      TabIndex        =   6
      Top             =   1320
      Width           =   1215
   End
   Begin VB.CommandButton btnClean 
      Caption         =   "&Clean"
      Height          =   495
      Left            =   4680
      TabIndex        =   5
      Top             =   720
      Width           =   1215
   End
   Begin VB.CommandButton btnAnalyze 
      Caption         =   "&Analyze"
      Height          =   495
      Left            =   4680
      TabIndex        =   4
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label lblPROGIDver 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   0
      Left            =   3480
      TabIndex        =   3
      Top             =   120
      Width           =   975
   End
   Begin VB.Label lblPROGID 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   0
      Left            =   2520
      TabIndex        =   2
      Top             =   120
      Width           =   975
   End
   Begin VB.Label lblUUID 
      Alignment       =   2  'Center
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H80000008&
      Height          =   255
      Index           =   0
      Left            =   1560
      TabIndex        =   1
      Top             =   120
      Width           =   975
   End
   Begin VB.Label lblObjName 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BackColor       =   &H00C0C0C0&
      BorderStyle     =   1  'Fixed Single
      ForeColor       =   &H00C00000&
      Height          =   255
      Index           =   0
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   1455
   End
End
Attribute VB_Name = "frmRmvAxL"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Const NrClasses = 15

Private Type AxLRegData
    PROGID      As String
    UUID        As String
    Vers        As Integer
End Type
Private AxLObjType(1 To NrClasses) As AxLRegData
' =========================================================
' If flgClean is false, report on which entries were found.
' If it is true, remove the found entries from the registry
' =========================================================
Private Sub scanner(flgClean As Boolean)
    Dim iX      As Integer
    Dim hKey    As Long         ' handle to the key
    Dim lRetVal As Long         ' return value from API
    Dim strX    As String
    Dim hives
    Dim hix     As Integer
    Dim hit     As Boolean
    Dim errFlag As Boolean
    Dim verct   As Integer
    Dim nxtVer  As Integer
    
    hives = Array("CLSID", "Interface", "TypeLib")
    
    For iX = 1 To NrClasses
    
        ' Look for the UUID
        ' ------------------
        If AxLObjType(iX).UUID > "" Then
            hit = False
            For hix = LBound(hives) To UBound(hives)
                strX = hives(hix) & "\" & AxLObjType(iX).UUID
                lRetVal = RegOpenKeyEx(HKEY_CLASSES_ROOT, strX, 0, KEY_ALL_ACCESS, hKey)
                RegCloseKey (hKey)
                
                ' Delete the UUID here
                ' --------------------
                If flgClean And lRetVal = 0 Then
                    Debug.Print strX
                    lRetVal = DeleteKey(HKEY_CLASSES_ROOT, strX)
                    lblUUID(iX).Caption = IIf(lRetVal = 0, "Deleted", "Failed")
                    hit = True
                    Exit For
                End If
                
                If lRetVal = 0 Then
                    lblUUID(iX).Caption = hives(hix)
                    hit = True
                    Exit For
                End If
            Next hix
            If Not hit Then lblUUID(iX).Caption = "Not Found"
        End If
        
        ' Process the PROGID
        ' ------------------
        If AxLObjType(iX).PROGID > "" Then
            strX = AxLObjType(iX).PROGID
            lRetVal = RegOpenKeyEx(HKEY_CLASSES_ROOT, strX, 0, KEY_ALL_ACCESS, hKey)
            RegCloseKey (hKey)
                
            ' Delete the PROGID here
            ' ----------------------
            If flgClean And lRetVal = 0 Then
                lRetVal = DeleteKey(HKEY_CLASSES_ROOT, strX)
                lblPROGID(iX).Caption = IIf(lRetVal = 0, "Deleted", "Failed")
            Else
                lblPROGID(iX).Caption = IIf(lRetVal = 0, "Found", "Not Found")
            End If
            
            ' Loop through the specific versions of the PROGIDs
            ' -------------------------------------------------
            If AxLObjType(iX).Vers > 0 Then
                nxtVer = 1
                verct = 0
                strX = strX & "."
                errFlag = False
           
                While nxtVer <= AxLObjType(iX).Vers
                    lRetVal = RegOpenKeyEx(HKEY_CLASSES_ROOT, strX & Trim(CStr(nxtVer)), 0, KEY_ALL_ACCESS, hKey)
                    RegCloseKey (hKey)
                    If lRetVal = 0 Then
                        verct = verct + 1
                        If flgClean Then
                            lRetVal = DeleteKey(HKEY_CLASSES_ROOT, strX & Trim(CStr(nxtVer)))
                            If lRetVal <> 0 Then errFlag = True
                        End If
                    End If
                    nxtVer = nxtVer + 1
                Wend
                                
                ' Report processing of specific PROGIDs
                ' -------------------------------------
                If verct = 0 Then
                    lblPROGIDver(iX).Caption = "Not Found"
                Else
                    If flgClean Then
                        If errFlag Then
                            lblPROGIDver(iX).Caption = "Error(s)"
                        ElseIf verct = 1 Then
                            lblPROGIDver(iX).Caption = "Deleted"
                        Else
                            lblPROGIDver(iX).Caption = Trim(CStr(verct)) & " deleted"
                        End If
                    Else
                        If verct = 1 Then
                            lblPROGIDver(iX).Caption = "Found"
                        Else
                            lblPROGIDver(iX).Caption = Trim(CStr(verct)) & " found"
                        End If
                    End If
                End If
            End If
        End If
            
    Next iX
        
End Sub
Private Sub btnAnalyze_Click()
On Error GoTo ScanFailed
    Call scanner(False)
    Exit Sub
ScanFailed:
    MsgBox Err.Description, vbOKOnly, "Processing Error"
End Sub

Private Sub btnClean_Click()
    Dim ans As Integer
    
    ans = MsgBox("You are about to completely remove ActiveXLink from the registry.  Are you sure?", vbQuestion Or vbYesNo, "Erase ActiveXLink from Registry?")
    If ans = vbYes Then
        scanner (True)
    End If
End Sub

Private Sub btnExit_Click()
    Unload Me
End Sub


' Load the Array, Create the Grid
' ===============================
Private Sub Form_Load()
    Dim ObjNames, PROGIDs, UUIDs, Versions
    Dim iX As Integer
    
    ObjNames = Array("G2Attribute", "G2ComObject", "G2Gateway", "G2Item", _
                     "G2ItemRef", "G2LAElement", "G2Law", "G2ListOrArray", _
                     "G2Structure", "G2StructureEntry", "GatewayProp", _
                     "G2Symbol", "G2Window", "G2Workspace", "TypeLib")
                    
    PROGIDs = Array("G2Com.G2Attribute", "", "G2Gateway.G2Gateway", _
                    "G2Com.G2Item", "G2Com.G2ItemRef", "G2Com.G2LAElement", _
                    "G2Com.G2Law", "G2Com.G2ListOrArray", "G2Gateway.G2Structure", _
                    "G2Gateway.G2StructureEntry", "GatewayProp.GatewayProp", _
                    "G2Com.G2Symbol", "G2Com.G2Window", "G2Com.G2Workspace", "")
    
    UUIDs = Array("{738B47FA-2D36-40D2-8DC3-47E97717E64B}", _
                   "{FCEB8041-EF78-4BE6-ADC8-51C173F65484}", _
                   "{AC4C85D0-B16C-11d1-A718-006008C5F933}", _
                   "{65DA1F96-DA11-47FE-B3EF-1CE21CDB0ED0}", _
                   "{15DD1D07-37FD-4D16-9ACB-BEBC4CE25438}", _
                   "{9BB94100-E344-415F-9976-D2BEB3DA4B29}", _
                   "", _
                   "{27F911C6-B864-4C85-A7FA-CE151B60F4BF}", _
                   "{CE90290F-2EAE-49EF-8B5A-D5FF6AAE8CE0}", _
                   "{15FC7CCC-C179-49BA-A68B-13C20C580DC0}", _
                   "{8AEF2DA3-471A-11D1-8AB5-00609703E60F}", _
                   "{3137F3E2-9860-4335-907B-3F0A4DE31C62}", _
                   "{4E1A836D-1FEA-4E83-8F2F-A21204406222}", _
                   "{4F6FF39F-793B-4BC5-8413-657F7BA99F57}", _
                   "{AC4C85D1-B16C-11D1-A718-006008C5F933}")
                   
    Versions = Array(1, 0, 6, 3, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 0)

    For iX = 0 To NrClasses - 1
        AxLObjType(iX + 1).PROGID = PROGIDs(iX)
        AxLObjType(iX + 1).UUID = UUIDs(iX)
        AxLObjType(iX + 1).Vers = Versions(iX)
    Next iX
        
    For iX = 1 To NrClasses
        Load lblObjName(iX)
        lblObjName(iX).Top = lblObjName(0).Top + iX * lblObjName(0).Height
        lblObjName(iX).Caption = ObjNames(iX - 1) & " "
        lblObjName(iX).Visible = True
           
        Load lblUUID(iX)
        lblUUID(iX).Top = lblUUID(0).Top + iX * lblUUID(0).Height
        If AxLObjType(iX).UUID = "" Then
            lblUUID(iX).BackColor = 0
        End If
        lblUUID(iX).Visible = True
        
        Load lblPROGID(iX)
        lblPROGID(iX).Top = lblPROGID(0).Top + iX * lblPROGID(0).Height
        If AxLObjType(iX).PROGID = "" Then
            lblPROGID(iX).BackColor = 0
        End If
        lblPROGID(iX).Visible = True
         
        Load lblPROGIDver(iX)
        lblPROGIDver(iX).Top = lblPROGIDver(0).Top + iX * lblPROGIDver(0).Height
        If AxLObjType(iX).Vers <= 0 Then
            lblPROGIDver(iX).BackColor = 0
        End If
        lblPROGIDver(iX).Visible = True
    Next iX
    
    ' Fill in the headings
    ' --------------------
    lblUUID(0).BackColor = lblObjName(0).BackColor
    lblUUID(0).Caption = "UUID"
    lblPROGID(0).BackColor = lblObjName(0).BackColor
    lblPROGID(0).Caption = "PROGID"
    lblPROGIDver(0).BackColor = lblObjName(0).BackColor
    lblPROGIDver(0).Caption = "PROGID.#"

End Sub
