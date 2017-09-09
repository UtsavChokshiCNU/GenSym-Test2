VERSION 5.00
Object = "{AC4C85D1-B16C-11D1-A718-006008C5F933}#1.2#0"; "G2Com.dll"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   4335
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   6450
   LinkTopic       =   "Form1"
   ScaleHeight     =   4335
   ScaleWidth      =   6450
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton PostMessage 
      Caption         =   "Post Message"
      Height          =   495
      Left            =   600
      TabIndex        =   7
      Top             =   3480
      Width           =   1455
   End
   Begin VB.CommandButton ErrorTest 
      Caption         =   "Error"
      Height          =   495
      Left            =   600
      TabIndex        =   6
      Top             =   2880
      Width           =   1455
   End
   Begin VB.CommandButton CallDeferredTests 
      Caption         =   "Call Deferred Tests"
      Height          =   495
      Left            =   600
      TabIndex        =   5
      Top             =   1560
      Width           =   1455
   End
   Begin VB.CommandButton Disconnect 
      Caption         =   "Disconnect"
      Height          =   495
      Left            =   4440
      TabIndex        =   4
      Top             =   1560
      Width           =   1455
   End
   Begin VB.CommandButton NonBlockingConnect 
      Caption         =   "Non Blocking Connect"
      Height          =   495
      Left            =   4440
      TabIndex        =   3
      Top             =   960
      Width           =   1455
   End
   Begin VB.CommandButton BlockingConnect 
      Caption         =   "Blocking Connect"
      Height          =   495
      Left            =   4440
      TabIndex        =   2
      Top             =   360
      Width           =   1455
   End
   Begin VB.CommandButton Calls 
      Caption         =   "Call Tests"
      Height          =   495
      Left            =   600
      TabIndex        =   1
      Top             =   960
      Width           =   1455
   End
   Begin VB.CommandButton Starts 
      Caption         =   "Start Tests"
      Height          =   495
      Left            =   600
      TabIndex        =   0
      Top             =   360
      Width           =   1455
   End
   Begin GensymAxlCtl.G2Gateway G2Gateway1 
      Left            =   2640
      OleObjectBlob   =   "Axl Tests.frx":0000
      Top             =   240
   End
   Begin VB.Label CallZeroDisplay 
      Caption         =   "0"
      Height          =   255
      Left            =   5400
      TabIndex        =   20
      Top             =   3360
      Width           =   615
   End
   Begin VB.Label StartZeroDisplay 
      Caption         =   "0"
      Height          =   255
      Left            =   4080
      TabIndex        =   19
      Top             =   3360
      Width           =   735
   End
   Begin VB.Label CallManyDisplay 
      Caption         =   "0"
      Height          =   255
      Left            =   5400
      TabIndex        =   18
      Top             =   3120
      Width           =   735
   End
   Begin VB.Label Call1Display 
      Caption         =   "0"
      Height          =   255
      Left            =   5400
      TabIndex        =   17
      Top             =   2880
      Width           =   615
   End
   Begin VB.Label Label4 
      Caption         =   "Call Counts:"
      Height          =   255
      Left            =   5160
      TabIndex        =   16
      Top             =   2520
      Width           =   975
   End
   Begin VB.Label StartManyDisplay 
      Caption         =   "0"
      Height          =   255
      Left            =   4080
      TabIndex        =   15
      Top             =   3120
      Width           =   735
   End
   Begin VB.Label Start1Display 
      Caption         =   "0"
      Height          =   255
      Left            =   4080
      TabIndex        =   14
      Top             =   2880
      Width           =   615
   End
   Begin VB.Label Label3 
      Caption         =   "Start Counts:"
      Height          =   255
      Left            =   3840
      TabIndex        =   13
      Top             =   2520
      Width           =   975
   End
   Begin VB.Label PostManyDisplay 
      Caption         =   "0"
      Height          =   255
      Left            =   2880
      TabIndex        =   12
      Top             =   3360
      Width           =   615
   End
   Begin VB.Label ReturnManyDisplay 
      Caption         =   "0"
      Height          =   255
      Left            =   2880
      TabIndex        =   11
      Top             =   3120
      Width           =   735
   End
   Begin VB.Label ReturnItDisplay 
      Caption         =   "0"
      Height          =   255
      Left            =   2880
      TabIndex        =   10
      Top             =   2880
      Width           =   615
   End
   Begin VB.Label Label2 
      Caption         =   "Return Counts:"
      Height          =   255
      Left            =   2400
      TabIndex        =   9
      Top             =   2520
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Connection Status"
      Height          =   255
      Left            =   2520
      TabIndex        =   8
      Top             =   1680
      Width           =   1335
   End
   Begin VB.Shape ConnectedStatus 
      BorderColor     =   &H00000000&
      FillColor       =   &H80000004&
      FillStyle       =   0  'Solid
      Height          =   495
      Left            =   2880
      Shape           =   3  'Circle
      Top             =   1080
      Width           =   495
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Dim CallReturnItCount As Long
Dim CallReturnManyCount As Long
Dim CallPostManyCount As Long
Dim Start1Count As Long
Dim StartManyCount As Long
Dim StartZeroCount As Long
Dim Call1Count As Long
Dim CallManyCount As Long
Dim CallZeroCount As Long


Private Sub BlockingConnect_Click()
  Call G2Gateway1.Connect(True)
  ConnectedStatus.FillColor = 0
End Sub

Private Sub CallDeferredTests_Click()

  CallReturnItCount = 0
  CallReturnManyCount = 0
  CallPostManyCount = 0
  
  For i = 1 To 1000
  
    ' Test call cases
    ' There is no need to explicitly cover all types
    ' since this is covered in the other call tests
    Call G2Gateway1.CallDeferred("call-return-it", 1, "Hello from VB")
    Call G2Gateway1.CallDeferred("call-return-many", 2)
    Call G2Gateway1.CallDeferred("post-many", 3, 123, 3.1415, "Hello G2")
    DoEvents
  Next i
  
  ' make sure that the handle matches
  Call G2Gateway1.CallDeferred("postmessage", "my id", "Test it")
End Sub



Private Sub Form_Unload(Cancel As Integer)
  G2Gateway1.Disconnect
End Sub

Private Sub G2Gateway1_Error(ByVal ErrorMessage As String, ByVal ErrorCode As Long, DeferredCallIdentifier As Variant)
  MsgBox ErrorMessage
End Sub

Private Sub G2Gateway1_GotMessage(ByVal Message As String)
  MsgBox Message
End Sub


' Call tests
Private Sub Calls_Click()
  For i = 1 To 1000
  
    ' Test single values, passing data both ways
    ret = G2Gateway1.Call("call-return-it", True)
    If ret <> True Then Error 50000
    ret = G2Gateway1.Call("Call-Return-It", 123)
    If ret <> 123 Then Error 50000
    ret = G2Gateway1.Call("CALL-RETURN-IT", 3.1415)
    If ret <> 3.1415 Then Error 50000
    ret = G2Gateway1.Call("call-return-it", "Hi There")
    If ret <> "Hi There" Then Error 50000
    Dim val As Variant
    val = Now()
   ret = G2Gateway1.Call("call-return-it", val)
    If ret <> val Then Error 50000
   
    ' Test Passing a array
    Dim arr(5) As Variant
    arr(1) = "Hi"
    arr(2) = 123
    arr(3) = 3.13455
    arr(4) = Now()
    arr(5) = False
    Call G2Gateway1.Call("postmessage", arr)
    
    Dim arrr(1 To 3, 4 To 5) As Variant
    arrr(1, 4) = 14
    arrr(2, 4) = True
    arrr(3, 4) = "Hello, this is a array"
    arrr(1, 5) = 3.234
    arrr(2, 5) = 25
    arrr(3, 5) = 35
    retarr = G2Gateway1.Call("call-return-it", arrr)
    'Error 50000
    ' Return a array of values
    ret = G2Gateway1.Call("call-return1")
    If ret(0) <> True Then Error 50000
    If ret(1) <> 123 Then Error 50000
    If ret(2) <> 3.1415 Then Error 50000
    If ret(3) <> "Foobar" Then Error 50000
    
    ' Return many values
    ret = G2Gateway1.Call("call-return-many")
    If ret(1) <> True Then Error 50000
    If ret(2) <> 123 Then Error 50000
    If ret(3) <> 3.1415 Then Error 50000
    If ret(4) <> "Foobar" Then Error 50000
   
    ' Send many arguments
    Call G2Gateway1.Call("post-many", 123, 3.1415, "Hello G2")
    DoEvents
  Next i
  MsgBox "Processing complete"
End Sub

Private Sub Disconnect_Click()
  Call G2Gateway1.Disconnect
End Sub

Private Sub ErrorTest_Click()
  Call G2Gateway1.Call("Thisdoesnotexist")
End Sub

Private Sub G2Gateway1_G2Connected()
    ConnectedStatus.FillColor = &HFF00& ' green
End Sub

Private Sub G2Gateway1_G2Disconnected()
    ConnectedStatus.FillColor = &HFF& ' red
End Sub


Private Sub G2Gateway1_G2Paused()
  MsgBox "Paused"
End Sub

Private Sub G2Gateway1_G2Resumed()
  MsgBox "Resumed"
End Sub

Private Sub G2Gateway1_RpcReturned(ByVal ProcedureName As String, ReturnArguments As Variant, DeferredCallIdentifier As Variant)
Select Case ProcedureName
  Case "call-return-it"
    If DeferredCallIdentifier <> 1 Then Error 50000
    If ReturnArguments <> "Hello from VB" Then Error 50000
    CallReturnItCount = CallReturnItCount + 1
    ReturnItDisplay.Caption = Str(CallReturnItCount)
  Case "call-return-many"
    If DeferredCallIdentifier <> 2 Then Error 50000
    If ReturnArguments(1) <> True Then Error 50000
    If ReturnArguments(2) <> 123 Then Error 50000
    If ReturnArguments(3) <> 3.1415 Then Error 50000
    If ReturnArguments(4) <> "Foobar" Then Error 50000
    CallReturnManyCount = CallReturnManyCount + 1
    ReturnManyDisplay.Caption = Str(CallReturnManyCount)
  Case "post-many"
    If DeferredCallIdentifier <> 3 Then Error 50000
    CallPostManyCount = CallPostManyCount + 1
    PostManyDisplay.Caption = Str(CallPostManyCount)
  Case "postmessage"
    If DeferredCallIdentifier <> "my id" Then Error 50000
    MsgBox "Processing Complete"
  Case Else
    MsgBox ProcedureName
  End Select
  
End Sub

Private Sub G2Gateway1_RpcStarted(ByVal ProcedureName As String, InputArguments As Variant)
  Select Case ProcedureName
  Case "start-many":
    If InputArguments(1) <> True Then Error 50000
    If InputArguments(2) <> 123 Then Error 50000
    If InputArguments(3) <> 3.1415 Then Error 50000
    If InputArguments(4) <> "Hi" Then Error 50000
    StartManyCount = StartManyCount + 1
    StartManyDisplay.Caption = Str(StartManyCount)
  Case "start-one":
    If InputArguments <> "Hello" Then Error 50000
    Start1Count = Start1Count + 1
    Start1Display.Caption = Str(Start1Count)
  Case "start-zero":
    StartZeroCount = StartZeroCount + 1
    StartZeroDisplay.Caption = Str(StartZeroCount)
  Case "inspect"
    Error 50000
  Case Else
    MsgBox ProcedureName
  End Select
End Sub

Private Sub G2Gateway1_RpcCalled(ByVal ProcedureName As String, InputArguments As Variant, ReturnArguments As Variant)
  Select Case ProcedureName
  Case "call-many":
    If InputArguments(1) <> True Then Error 50000
    If InputArguments(2) <> 123 Then Error 50000
    If InputArguments(3) <> 3.1415 Then Error 50000
    If InputArguments(4) <> "Hi" Then Error 50000
    CallManyCount = CallManyCount + 1
    CallManyDisplay.Caption = Str(CallManyCount)
    ReDim ReturnArguments(2) As Variant
    ReturnArguments(1) = "Hello"
    ReturnArguments(2) = 123
  Case "call-one":
    If InputArguments <> "Hello" Then Error 50000
    Call1Count = Call1Count + 1
    Call1Display.Caption = Str(Call1Count)
    ' Do a blocking call while in a event
    Call G2Gateway1.Call("postmessage", "Hi")
    ReturnArguments = True
  Case "call-zero":
    CallZeroCount = CallZeroCount + 1
    CallZeroDisplay.Caption = Str(CallZeroCount)
  Case Else
    MsgBox ProcedureName
  End Select
End Sub



Private Sub NonBlockingConnect_Click()
  Call G2Gateway1.Connect(False)
  ConnectedStatus.FillColor = 0
End Sub

Private Sub PostMessage_Click()
  Call G2Gateway1.PostMessage("I dont love you because you ate my dog")
End Sub

' Test procedure starts
Private Sub Starts_Click()
  For i = 1 To 1000
    ' Test argument mapping
    Call G2Gateway1.Start("PostMessage", True)
    Call G2Gateway1.Start("PostMessage", 123)
    Call G2Gateway1.Start("PostMessage", 3.145)
    Call G2Gateway1.Start("PostMessage", "Hi There")
    Call G2Gateway1.Start("POSTMESSAGE", #8/3/66 10:53:00 AM#)
    
    ' multi dim array
    Dim arrr(1 To 3, 4 To 5) As Variant
    arrr(1, 4) = 14
    arrr(2, 4) = True
    arrr(3, 4) = "Hello, this is a array"
    arrr(1, 5) = 3.234
    arrr(2, 5) = 25
    arrr(3, 5) = 35
    Call G2Gateway1.Start("PostMessage", arrr)
    
    ' Send many arguments
    Call G2Gateway1.Start("post-many", 123, 3.1415, "Hello G2")
    
    ' No arguments
    Call G2Gateway1.Start("call-return-many")
    
    ' Send array
    Dim arr(5) As Variant
    arr(0) = "Hi"
    arr(1) = 123
    arr(2) = 3.13455
    arr(3) = Now()
    arr(4) = False
    Call G2Gateway1.Start("postmessage", arr)
    DoEvents
  Next i
  MsgBox "Processing complete"
End Sub

