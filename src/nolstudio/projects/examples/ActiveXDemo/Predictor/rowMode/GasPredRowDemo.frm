VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{CDE0EF53-4E9A-11D4-B8A0-0000861E0389}#1.0#0"; "NolOnline.dll"
Begin VB.Form GasPredRowDemo 
   Caption         =   "GasPredRowDemo"
   ClientHeight    =   5925
   ClientLeft      =   45
   ClientTop       =   270
   ClientWidth     =   5715
   LinkTopic       =   "GasOptTest"
   ScaleHeight     =   5925
   ScaleWidth      =   5715
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton retraind 
      Caption         =   "Retrain D"
      Height          =   375
      Left            =   4440
      TabIndex        =   17
      Top             =   2760
      Width           =   1095
   End
   Begin VB.CommandButton RetrainF 
      Caption         =   "Retrain F"
      Height          =   375
      Left            =   4440
      TabIndex        =   16
      Top             =   2280
      Width           =   1095
   End
   Begin VB.CheckBox Check1 
      Caption         =   "Display Console"
      Height          =   375
      Left            =   4440
      TabIndex        =   15
      Top             =   3240
      Value           =   1  'Checked
      Width           =   975
   End
   Begin VB.CommandButton ModelStat 
      Caption         =   "ModelStat"
      Height          =   375
      Left            =   4440
      TabIndex        =   14
      Top             =   3720
      Width           =   1095
   End
   Begin VB.CommandButton retrain 
      Caption         =   "Retrain M"
      Height          =   375
      Left            =   4440
      TabIndex        =   13
      Top             =   1800
      Width           =   1095
   End
   Begin VB.OptionButton varNames 
      Caption         =   "Input Tags"
      Height          =   372
      Index           =   3
      Left            =   2280
      TabIndex        =   12
      Top             =   1320
      Width           =   1212
   End
   Begin VB.TextBox CalCount 
      Height          =   288
      Left            =   4560
      TabIndex        =   11
      Text            =   "Text1"
      Top             =   4680
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
      Left            =   4800
      Top             =   5400
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
      Height          =   3960
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
      Height          =   4935
      Left            =   120
      TabIndex        =   9
      Top             =   840
      Width           =   4212
   End
   Begin NOLONLINELibCtl.NolPredictor gasplant 
      Left            =   4680
      OleObjectBlob   =   "GasPredRowDemo.frx":0000
      Top             =   4920
   End
   Begin VB.Label Label2 
      Caption         =   "Calculated:"
      Height          =   255
      Left            =   4560
      TabIndex        =   10
      Top             =   4320
      Width           =   975
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
Attribute VB_Name = "GasPredRowDemo"
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
Dim isloaded As Boolean
Dim inputs As Variant
Dim outputs As Variant
Dim xlbook As Excel.Workbook

Private Sub CalcOutputs()
Dim outputCell As String
    outputCell = "R" & Index
    outputs = gasplant.calculateOutputsForRow
    xlsheet.Range(outputCell).Value = outputs(0)
End Sub

Private Sub Browse_Click()
    GasPredRowDemo.cdlgload.ShowOpen
    file = GasPredRowDemo.cdlgload.FileTitle
    path = Left(GasPredRowDemo.cdlgload.FileName, _
        Len(GasPredRowDemo.cdlgload.FileName) - Len(file))

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
    
    If (isloaded = True) Then
        total = gasplant.getNumberOfInputs() - 1
        ReDim localinputs(0 To total) As Double
    
        For Index = 3 To 22
            cell1 = "A" & Index
            For counter = 0 To total
                localinputs(counter) = xlsheet.Range(cell1).Value
                cell1 = Chr(65 + counter + 1) & Index
                gasplant.setInputForRowByIndex counter, localinputs(counter)
            Next counter
            Call CalcOutputs
            CalCount.Text = (Index - 3)
        Next Index
        
        For Index = 23 To 42
            cell1 = "A" & Index
            For counter = 0 To total
                localinputs(counter) = xlsheet.Range(cell1).Value
                cell1 = Chr(65 + counter + 1) & Index
                gasplant.setInputForRowByName gasplant.inputNames(counter), localinputs(counter)
            Next counter
            Call CalcOutputs
            CalCount.Text = (Index - 3)
        Next Index
        
        For Index = 43 To 199
            cell1 = "A" & Index
            For counter = 0 To total
                localinputs(counter) = xlsheet.Range(cell1).Value
                cell1 = Chr(65 + counter + 1) & Index
            Next counter
            inputs = localinputs
            gasplant.setInputsForRow inputs
            Call CalcOutputs
            CalCount.Text = (Index - 3)
        Next Index
    
    
    End If

End Sub

Private Sub Form_Load()

    Set xlapp = CreateObject("Excel.Application")
    xlapp.Workbooks.Open App.path & "\GasplantRow.xls"
    xlapp.Visible = True
    Set xlbook = xlapp.Workbooks(1)
    Set xlsheet = xlbook.Worksheets(1)
    isloaded = False
    GasPredRowDemo.Show
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

Private Sub ModelStat_Click()
    Dim modelrate As Double
    Dim numberofOutput As Integer
    Dim testrmse As Variant
    Dim trainrmse As Variant
    Dim testcorr As Variant
    Dim traincorr As Variant
    
    numberofOutput = gasplant.getNumberOfOutputs()
    modelrate = gasplant.getModelRate()
    MsgBox (modelrate)
    
    testrmse = gasplant.getTestRmse()
    MsgBox ("testrmse")
    MsgBox (testrmse(0))
    
    trainrmse = gasplant.getTrainingRmse()
    MsgBox ("trainrmse")
    MsgBox (trainrmse(0))
    
    testcorr = gasplant.getTestCorr()
    MsgBox ("testcorr")
    MsgBox (testcorr(0))
    
    traincorr = gasplant.getTrainingCorr()
    MsgBox ("traincorr")
    MsgBox (traincorr(0))
    
End Sub

Private Sub retrain_Click()
    Dim i As Integer
    Dim j As Integer
    Dim autoStop As Boolean
    Dim newtraining As Boolean
    Dim display As Boolean
    autoStop = True
    newtraining = True
    display = Check1.Value
    Dim total As Integer
    Dim counter As Integer
    Dim cell1 As String
       MsgBox display
    
    total = gasplant.getNumberOfInputs() - 1
    ReDim xm(600, total + 1) As Double
    ReDim ym(600, 1) As Double
Rem Pretend to read data
    For Index = 3 To 603
        cell1 = "A" & Index
        For counter = 0 To total
            xm(Index - 3, counter) = xlsheet.Range(cell1).Value
            cell1 = Chr(65 + counter + 1) & Index
        Next counter
        cell1 = Chr(65 + total + 1) & Index
        ym(Index - 3, 0) = xlsheet.Range(cell1).Value
    Next Index
    gasplant.trainModel xm, ym, 1.01, autoStop, newtraining, display
End Sub

Private Sub retraind_Click()
    Dim autoStop As Boolean
    Dim newtraining As Boolean
    Dim display As Boolean
    autoStop = True
    newtraining = True
    display = True
    Dim dfs(1) As String
    dfs(0) = "GasplantRow.ds"
    gasplant.trainModelFromFiles dfs, 1.01, autoStop, newtraining, display
End Sub

Private Sub RetrainF_Click()
    Dim autoStop As Boolean
    Dim newtraining As Boolean
    Dim display As Boolean
    autoStop = True
    newtraining = True
    display = True
    Dim dfs(2) As String
    dfs(0) = "GasplantRowInput.csv"
    dfs(1) = "GasplantRowOutput.csv"
    gasplant.trainModelFromFile dfs(0), dfs(1), 1.01, autoStop, newtraining, display
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
