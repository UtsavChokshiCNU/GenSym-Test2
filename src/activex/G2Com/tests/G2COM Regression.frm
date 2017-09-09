VERSION 5.00
Object = "{A71ACD03-3B6E-11D1-8AB3-00609703E60F}#1.0#0"; "G2Com.dll"
Begin VB.Form Form1 
   Caption         =   "G2COM Regression Test"
   ClientHeight    =   3240
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6075
   LinkTopic       =   "Form1"
   ScaleHeight     =   3240
   ScaleWidth      =   6075
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton CallButton 
      Caption         =   "Call"
      Height          =   495
      Left            =   3120
      TabIndex        =   6
      Top             =   2640
      Width           =   1935
   End
   Begin VB.CommandButton StartButton 
      Caption         =   "Start"
      Height          =   495
      Left            =   960
      TabIndex        =   5
      Top             =   2640
      Width           =   1935
   End
   Begin VB.CommandButton Connect 
      Caption         =   "Connect"
      Height          =   495
      Left            =   960
      TabIndex        =   4
      Top             =   1920
      Width           =   1935
   End
   Begin VB.CommandButton Disconnect 
      Caption         =   "Disconnect"
      Height          =   495
      Left            =   3120
      TabIndex        =   2
      Top             =   1920
      Width           =   1935
   End
   Begin VB.TextBox Host 
      Height          =   285
      Left            =   3120
      TabIndex        =   1
      Text            =   "localhost:1111"
      Top             =   1320
      Width           =   2055
   End
   Begin VB.CommandButton Regression 
      Caption         =   "Run Regression Tests"
      Height          =   495
      Left            =   960
      TabIndex        =   0
      Top             =   1200
      Width           =   1935
   End
   Begin G2COMLibCtl.G2Gateway myCtl 
      Left            =   5400
      OleObjectBlob   =   "G2COMR~1.frx":0000
      Top             =   2160
   End
   Begin VB.Label Label1 
      Caption         =   $"G2COMR~1.frx":007A
      Height          =   495
      Left            =   600
      TabIndex        =   3
      Top             =   240
      Width           =   4815
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim bConnected As Boolean
Dim i, j, k As Long
Dim CallIndex1, CallIndex2 As Long

Private Sub CallButton_Click()
  Print #1, Now(); "method-CALLing G2RANDOMGENERATOR with 1 arg returning 1 . . . "
  myVal = myCtl.Call("g2randomgenerator", 30)
  Print #1, Now(); ". . . G2RANDOMGENERATOR returned "; Str(myVal)

'DoEvents
End Sub

Private Sub Connect_Click()
  Print #1, Now(); "method-Blocking connection attempt to "; myCtl.G2Location
  myCtl.Connect True
End Sub

Private Sub Disconnect_Click()
  Print #1, Now(); "method-Disconnection attempt from "; myCtl.G2Location
  myCtl.Disconnect
End Sub

Private Sub Form_Load()
  Open "G2COM.LOG" For Output As #1 Len = 5
  Print #1, Now(); "Log created . . ."

  'Try to manipulate a property programmatically.
  myCtl.G2Location = Host.Text

End Sub

Private Sub Form_Unload(Cancel As Integer)
  Print #1, Now(); ". . . Log closed."
  Close #1
End Sub

Private Sub myCtl_Called(ByVal Name As String, InArgs As Variant, OutArgs As Variant)
  Print #1, Now(); "event-CALLED received"
  Select Case Name
    Case "SQR"
        OutArgs = InArgs + 1
    Case Else
        ' Handle other situations here...
        Print #1, Now(); "Unknown local procedure called "; Name
  End Select

End Sub

Private Sub myCtl_Connected()
  Print #1, Now(); "event-CONNECTED to "; myCtl.G2Location
  bConnected = True
End Sub

Private Sub myCtl_Disconnected()
  Print #1, Now(); "event-DISCONNECTED received from "; myCtl.G2Location
End Sub

Private Sub myCtl_Error(ByVal ErrorMessage As String, ByVal ErrorCode As Long)
  Print #1, Now(); "event-ERROR received: "; ErrorMessage
End Sub

Private Sub myCtl_Returned(ByVal Name As String, RetArgs As Variant, ByVal CallIndex As Long)

  If CallIndex = CallIndex1 Then
    Print #1, Now(); ". . . event-"; Name; " returned "; Str(RetArgs)
  ElseIf CallIndex = CallIndex2 Then
    lb = LBound(RetArgs)
    ub = UBound(RetArgs)
    If ub = 0 Then nRet = 0 Else: nRet = ub - lb + 1
      Print #1, Now(); ". . . event-"; Name; " returned "; Str(nRet); " arguments:"
      For k = lb To ub
        If IsNumeric(RetArgs(k)) Then MYTEXT = Str(RetArgs(k)) Else: MYTEXT = RetArgs(k)
        Print #1, "    RetArgs("; Str(k); " ) = "; Str(RetArgs(k))
      Next
    Else
      Print #1, Now(); Name; " returned with call index of "; CallIndex
  End If
End Sub

Private Sub myCtl_Started(ByVal Name As String, InArgs As Variant)
  Print #1, Now(); "event-STARTED received"
  Select Case Name
    Case "LOOPBACK0"
        Call LoopBack0(Name)
    Case "LOOPBACK1"
        Call LoopBack1(Name, InArgs)
    Case "LOOPBACK2"
    Case "LOOPBACKN"
        Call LoopBack2(Name, InArgs)
    Case Else
        ' Handle other situations here...
        Print #1, Now(); "Unknown local procedure started "; Name
  End Select
End Sub

Private Sub Regression_Click()
  'On Error GoTo ErrorHandler  ' Enable error-handling routine.

  'blocking connect
  Print #1, Now(); "method-Attempting blocking connection to "; myCtl.G2Location
  myCtl.Connect True
  DoEvents

  Print #1, Now(); "method-Attempting disconnection from "; myCtl.G2Location
  myCtl.Disconnect
  DoEvents

  'Perform Contention Tests
  Print #1, "CONTENTION TESTS"
  Do_Contention_Tests
  DoEvents

  'Perform START INTO tests
  Print #1, "STARTS-INTO TESTS"
  Do_StartInto 8, 250
  DoEvents

  'Perform various CALL DEFERRED invocations
  Print #1, "CALL DEFERRED TESTS"
  Do_CallDeferred
  DoEvents

  'Perform various START invocations
  Print #1, "START TESTS"
  Do_Starts
  DoEvents

  'Perform various CALL invocations
  Print #1, "CALL TESTS"
  Do_Calls
  DoEvents

  'Perform various stress tests
  Print #1, "STRESS TESTS"
  Do_Stress 250
  DoEvents

  'Wait for outstanding requests to return.
  j = 0
  Do While j < 100000#
    DoEvents    ' Yield to other processes.
    j = j + 1
  Loop

  Print #1, Now(); "method-Disconnecting from "; myCtl.G2Location
  myCtl.Disconnect
  Exit Sub        ' Exit to avoid handler.

ErrorHandler:     ' Error-handling routine.
  Select Case Err.Number  ' Evaluate error number.
        Case 0 ' No error.
            Resume    ' Continue with line that caused error.
        Case Else
            ' Handle other situations here...
            Print #1, Now(); Str(Err.Number); " "; Err.Description

  End Select
  Print #1, Now(); "method-Explicitly disconnecting after error"
  myCtl.Disconnect
End Sub

Private Sub Do_Contention_Tests()

  Print #1, Now(); "method-STARTing LOOPBACK0 with no arguments . . . "
  myCtl.Start "LOOPBACK0"

  DoEvents

  Print #1, Now(); "method-CALLing G2RANDOMGENERATOR with 1 arg returning 1 . . . "
  myVal = myCtl.Call("g2randomgenerator", 30)
  Print #1, Now(); ". . . G2RANDOMGENERATOR returned "; Str(myVal)

  DoEvents
End Sub

Private Sub Do_StartInto(nArgCount As Long, nIterations As Long)
  Print #1, Now(); "method-STARTing STARTINTO with no arguments . . . "
  myCtl.Start "STARTINTO", nArgCount, nIterations
End Sub

Private Sub Do_Starts()

  Print #1, Now(); "method-STARTing LOOPBACK0 with no arguments . . . "
  myCtl.Start "LOOPBACK0"

  Print #1, Now(); "method-STARTing LOOPBACK1 with 1 argument . . . "
  Dim MYTEXT As String
  MYTEXT = Now()
  myCtl.Start "LOOPBACK1", MYTEXT

  Print #1, Now(); "method-STARTing LOOPBACK2 with 2 arguments . . . "
  myCtl.Start "LOOPBACK2", "Frank", 100.75

  Print #1, Now(); "method-STARTing LOOPBACKn with 8 arguments . . . "
  myCtl.Start "LOOPBACKn", "Sputnik", -1E-40, 1E+21, 5.75, 65535, -20032, False, -9493.3

' Print #1, Now(); "method-STARTing LOOPBACKn with 3 arguments . . . "
' myCtl.Start "LOOPBACKn", True, "G2 smells terrific!!", 250000
End Sub

Private Sub Do_Calls()
  'Print #1, Now(); "method-CALLing LOOPBACK0 with 0 args returning 0 . . . "
  'myCtl.Call "LOOPBACK0"

  Print #1, Now(); "method-CALLing G2RANDOMGENERATOR with 1 arg returning 1 . . . "
  myVal = myCtl.Call("g2randomgenerator", 30)
  Print #1, Now(); ". . . G2RANDOMGENERATOR returned "; Str(myVal)

  Print #1, Now(); "method-CALLing G2CHARTGENERATOR with 1 arg returning 5 . . . "
  Dim RetVals As Variant
  RetVals = myCtl.Call("G2CHARTGENERATOR", 100)
  lb = LBound(RetVals)
  ub = UBound(RetVals)
  If ub = 0 Then nRet = 0 Else: nRet = ub - lb + 1
  Print #1, Now(); ". . . G2CHARTGENERATOR returned "; Str(nRet); " arguments:"
  For k = lb To ub
    If IsNumeric(RetVals(k)) Then MYTEXT = Str(RetVals(k)) Else: MYTEXT = RetVals(k)
    Print #1, "    RetVals("; Str(k); " ) = "; Str(RetVals(k))
  Next
  'Print #1, Now(); "method-CALLing LOOPBACK2 with 2 arguments . . . "
End Sub

Private Sub Do_CallDeferred()
  'Print #1, Now(); "method-CALLing LOOPBACK0 with 0 args returning 0 . . . "
  'myCtl.Call "LOOPBACK0"

  Print #1, Now(); "method-CALL DEFERRED to G2RANDOMGENERATOR with 1 arg returning 1 . . . "
  CallIndex1 = myCtl.CallDeferred("g2randomgenerator", 30)

  Print #1, Now(); "method-CALL DEFERRED to G2CHARTGENERATOR with 1 arg returning 5 . . . "
  CallIndex2 = myCtl.CallDeferred("G2CHARTGENERATOR", 100)

  'Print #1, Now(); "method-CALLing LOOPBACK2 with 2 arguments . . . "
End Sub

Private Sub Do_Stress(lIterations As Long)
  For i = 0 To lIterations
    Print #1, Str(i)
    myCtl.Start "postmessage", "Yo" + Str(i)
    DoEvents 'Allow other processing
    Do_Starts
    DoEvents 'Allow other processing
    Do_Calls
    DoEvents 'Allow other processing
  Next

  Do_CallDeferred
End Sub

Private Sub LoopBack0(Name As String)
  Print #1, Now(); Name; " started in G2 with no args."
End Sub

Private Sub LoopBack1(Name As String, RetVals As Variant)
  Print #1, Now(); Name; " started in G2 with arg: "; RetVals
End Sub

Private Sub LoopBack2(Name As String, RetVals As Variant)
'Print #1, Now(); Name; " started in G2 at "; RetVals
  lb = LBound(RetVals)
  ub = UBound(RetVals)
  If ub = 0 Then nRet = 0 Else: nRet = ub - lb + 1
  Print #1, Now(); ". . . "; Name; " returned "; Str(nRet); " arguments:"
  For i = lb To ub
    If IsNumeric(RetVals(i)) Then MYTEXT = Str(RetVals(i)) Else: MYTEXT = RetVals(i)
    Print #1, "    RetVals("; Str(i); " ) = "; MYTEXT
  Next
End Sub

Private Sub StartButton_Click()
  Print #1, Now(); "method-STARTing LOOPBACK0 with no arguments . . . "
  myCtl.Start "LOOPBACK0"

  'DoEvents
End Sub

' The following user-defined function returns the square root of the
' argument passed to it.
Function CalculateSquareRoot(NumberArg As Double) As Double
    If NumberArg < 0 Then   ' Evaluate argument.
        Exit Function   ' Exit to calling procedure.
    Else
        CalculateSquareRoot = Sqr(NumberArg)    ' Return square root.
    End If
End Function


