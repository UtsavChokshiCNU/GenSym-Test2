VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{CDE0EF53-4E9A-11D4-B8A0-0000861E0389}#1.0#0"; "NolOnline.dll"
Begin VB.Form GasPredTimeDemo 
   Caption         =   "GasPredTimeDemo"
   ClientHeight    =   4905
   ClientLeft      =   45
   ClientTop       =   270
   ClientWidth     =   5625
   LinkTopic       =   "GasOptTest"
   ScaleHeight     =   4905
   ScaleWidth      =   5625
   StartUpPosition =   3  'Windows Default
   Begin VB.OptionButton varNames 
      Caption         =   "Input Tags"
      Height          =   372
      Index           =   3
      Left            =   2280
      TabIndex        =   12
      Top             =   1320
      Width           =   1452
   End
   Begin VB.TextBox CalCount 
      Height          =   288
      Left            =   4560
      TabIndex        =   11
      Text            =   "Text1"
      Top             =   2640
      Width           =   852
   End
   Begin VB.CommandButton Load 
      Caption         =   "Load"
      Height          =   372
      Left            =   4440
      TabIndex        =   7
      Top             =   840
      Width           =   1092
   End
   Begin MSComDlg.CommonDialog cdlgload 
      Left            =   4680
      Top             =   4080
      _ExtentX        =   688
      _ExtentY        =   688
      _Version        =   393216
      DialogTitle     =   "Load Optimization"
      FileName        =   "*.mod"
      Filter          =   "*.mod"
   End
   Begin VB.OptionButton varNames 
      Caption         =   "Input Names"
      Height          =   252
      Index           =   2
      Left            =   240
      TabIndex        =   6
      Top             =   1320
      Width           =   1932
   End
   Begin VB.OptionButton varNames 
      Caption         =   "Output Tags"
      Height          =   252
      Index           =   1
      Left            =   2280
      TabIndex        =   5
      Top             =   1080
      Width           =   1932
   End
   Begin VB.OptionButton varNames 
      Caption         =   "Output Names"
      Height          =   252
      Index           =   0
      Left            =   240
      TabIndex        =   4
      Top             =   1080
      Width           =   1572
   End
   Begin VB.CommandButton Browse 
      Caption         =   "Browse..."
      Height          =   372
      Left            =   4440
      TabIndex        =   3
      Top             =   360
      Width           =   1092
   End
   Begin VB.TextBox PathName 
      Height          =   372
      Left            =   240
      TabIndex        =   2
      Top             =   360
      Width           =   4092
   End
   Begin VB.ListBox VariableList 
      Height          =   2790
      Left            =   240
      TabIndex        =   1
      Top             =   1680
      Width           =   3972
   End
   Begin VB.CommandButton Calculate 
      Caption         =   "Calculate"
      Height          =   372
      Left            =   4440
      TabIndex        =   0
      Top             =   1320
      Width           =   1092
   End
   Begin VB.Frame Frame1 
      Caption         =   "Variables:"
      Height          =   3972
      Left            =   120
      TabIndex        =   9
      Top             =   840
      Width           =   4212
   End
   Begin NOLONLINELibCtl.NolPredictor gasplant 
      Left            =   4560
      OleObjectBlob   =   "GasPredTimeDemo.frx":0000
      Top             =   3480
   End
   Begin VB.Label Label2 
      Caption         =   "Calculated:"
      Height          =   252
      Left            =   4560
      TabIndex        =   10
      Top             =   2400
      Width           =   972
   End
   Begin VB.Label Label1 
      Caption         =   "Model File Location:"
      Height          =   372
      Left            =   240
      TabIndex        =   8
      Top             =   120
      Width           =   2052
   End
End
Attribute VB_Name = "GasPredTimeDemo"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim xlapp As Excel.Application
Dim xlsheet As Excel.Worksheet
Dim Index As Long
Dim file As String
Dim path As String
Dim timeString As String
Dim isloaded As Boolean
Dim inputs As Variant
Dim outputs As Variant
Dim xlbook As Excel.Workbook

Private Sub CalcOutputs()
Dim outputCell As String
    outputCell = "J" & Index
    outputs = gasplant.calculateOutputsAtTime(timeString)
    xlsheet.Range(outputCell).Value = outputs(0)
End Sub

Private Sub Browse_Click()
    GasPredTimeDemo.cdlgload.ShowOpen
    file = GasPredTimeDemo.cdlgload.FileTitle
    path = Left(GasPredTimeDemo.cdlgload.FileName, _
        Len(GasPredTimeDemo.cdlgload.FileName) - Len(file))

    If PathName.Text = "" Then
        If (file = "") Then
            path = gasplant.PathName
            file = gasplant.FileName
        End If
        PathName.Text = path & file
    End If
End Sub

Private Sub Calculate_Click()
    Dim counter As Integer
    Dim cell1 As String
    Dim total As Integer
    Dim timeFormat As String
    
    timeFormat = "M/d/y H:m"
    gasplant.setTimeFormat timeFormat
    
    If (isloaded = True) Then
        total = gasplant.getNumberOfInputs() - 1
        ReDim localinputs(0 To total) As Double
    
        For Index = 3 To 22
            cell1 = "A" & Index
            timeString = xlsheet.Range(cell1).Text
            cell1 = "B" & Index
            For counter = 0 To total
                localinputs(counter) = xlsheet.Range(cell1).Value
                cell1 = Chr(65 + counter + 2) & Index
                gasplant.setInputAtTimeByIndex counter, localinputs(counter), timeString
            Next counter
            Call CalcOutputs
            CalCount.Text = (Index - 3)
        Next Index
        
        For Index = 23 To 42
            cell1 = "A" & Index
            timeString = xlsheet.Range(cell1).Text
            cell1 = "B" & Index
            For counter = 0 To total
                localinputs(counter) = xlsheet.Range(cell1).Value
                cell1 = Chr(65 + counter + 2) & Index
                gasplant.setInputAtTimeByName gasplant.inputNames(counter), localinputs(counter), timeString
            Next counter
            Call CalcOutputs
            CalCount.Text = (Index - 3)
        Next Index
        
        For Index = 43 To 200
            cell1 = "A" & Index
            timeString = xlsheet.Range(cell1).Text
            cell1 = "B" & Index
            For counter = 0 To total
                localinputs(counter) = xlsheet.Range(cell1).Value
                cell1 = Chr(65 + counter + 2) & Index
            Next counter
            inputs = localinputs
            gasplant.setInputsAtTime inputs, timeString
            Call CalcOutputs
            CalCount.Text = (Index - 3)
        Next Index
    
    
    End If
End Sub

Private Sub Form_Load()

    Set xlapp = CreateObject("Excel.Application")
    xlapp.Workbooks.Open App.path & "\GasplantTime.xls"
    xlapp.Visible = True
    Set xlbook = xlapp.Workbooks(1)
    Set xlsheet = xlbook.Worksheets(1)
    isloaded = False
    GasPredTimeDemo.Show
End Sub

Private Sub Load_Click()
Dim counter As Integer
Dim numberOfVariables As Integer
    If (file <> "") Then
        gasplant.loadModel file, path
        isloaded = True
        varNames.Item(0).Value = True
        VariableList.Clear
        numberOfVariables = gasplant.getNumberOfOutputs()
        For counter = 0 To numberOfVariables
            VariableList.AddItem gasplant.outputNames(counter)
        Next counter
     End If
End Sub

Private Sub varNames_Click(Index As Integer)
Dim counter As Integer
Dim numberOfVariables As Integer

    VariableList.Clear
    If (isloaded = True) Then
        Select Case Index
            Case 0
                numberOfVariables = gasplant.getNumberOfOutputs()
                For counter = 0 To numberOfVariables
                    VariableList.AddItem gasplant.outputNames(counter)
                Next counter
           Case 1
                numberOfVariables = gasplant.getNumberOfOutputs()
                For counter = 0 To numberOfVariables
                    VariableList.AddItem gasplant.outputTags(counter)
                Next counter
            Case 2
                numberOfVariables = gasplant.getNumberOfInputs()
                For counter = 0 To numberOfVariables
                    VariableList.AddItem gasplant.inputNames(counter)
                Next counter
            Case 3
                numberOfVariables = gasplant.getNumberOfInputs()
                For counter = 0 To numberOfVariables
                    VariableList.AddItem gasplant.inputTags(counter)
                Next counter
        End Select
   Else
        VariableList.AddItem "No model is loaded"
   End If
    
End Sub
