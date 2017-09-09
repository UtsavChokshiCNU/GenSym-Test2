VERSION 5.00
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "COMDLG32.OCX"
Object = "{CDE0EF53-4E9A-11D4-B8A0-0000861E0389}#1.0#0"; "NolOnline.dll"
Begin VB.Form GasOptTest 
   Caption         =   "GasOptTest"
   ClientHeight    =   4965
   ClientLeft      =   45
   ClientTop       =   270
   ClientWidth     =   5625
   LinkTopic       =   "GasOptTest"
   ScaleHeight     =   4965
   ScaleWidth      =   5625
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton TrainWhole 
      Caption         =   "Train Whole"
      Height          =   375
      Left            =   4440
      TabIndex        =   15
      Top             =   2760
      Width           =   1095
   End
   Begin VB.CommandButton trainstate 
      Caption         =   "Train State"
      Height          =   375
      Left            =   4440
      TabIndex        =   14
      Top             =   2280
      Width           =   1095
   End
   Begin VB.CommandButton trainoutput 
      Caption         =   "Train Output"
      Height          =   375
      Left            =   4440
      TabIndex        =   13
      Top             =   1800
      Width           =   1095
   End
   Begin MSComDlg.CommonDialog cdlgload 
      Left            =   4560
      Top             =   4200
      _ExtentX        =   688
      _ExtentY        =   688
      _Version        =   393216
      DialogTitle     =   "Load Optimization"
      FileName        =   "*.opt"
      Filter          =   "*.opt"
   End
   Begin VB.TextBox CalCount 
      Height          =   288
      Left            =   4560
      TabIndex        =   9
      Text            =   "Text1"
      Top             =   3720
      Width           =   852
   End
   Begin VB.CommandButton Load 
      Caption         =   "Load"
      Height          =   372
      Left            =   4440
      TabIndex        =   4
      Top             =   840
      Width           =   1092
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
      TabIndex        =   6
      Top             =   840
      Width           =   4212
      Begin VB.OptionButton varNames 
         Caption         =   "Manipulated Variables"
         Height          =   252
         Index           =   1
         Left            =   2160
         TabIndex        =   12
         Top             =   240
         Width           =   1932
      End
      Begin VB.OptionButton varNames 
         Caption         =   "Exogenous Variables"
         Height          =   252
         Index           =   2
         Left            =   240
         TabIndex        =   11
         Top             =   480
         Width           =   1932
      End
      Begin VB.OptionButton varNames 
         Caption         =   "Output Variables"
         Height          =   252
         Index           =   0
         Left            =   240
         TabIndex        =   10
         Top             =   240
         Width           =   1572
      End
      Begin VB.OptionButton varNames 
         Caption         =   "State Variables"
         Height          =   252
         Index           =   3
         Left            =   2160
         TabIndex        =   7
         Top             =   480
         Width           =   1452
      End
   End
   Begin NOLONLINELibCtl.NolOptimizer gasplant 
      Left            =   4440
      OleObjectBlob   =   "GasOptDemo.frx":0000
      Top             =   4440
   End
   Begin VB.Label Label2 
      Caption         =   "Calculated:"
      Height          =   255
      Left            =   4560
      TabIndex        =   8
      Top             =   3360
      Width           =   975
   End
   Begin VB.Label Label1 
      Caption         =   "Optimization File Location:"
      Height          =   372
      Left            =   240
      TabIndex        =   5
      Top             =   120
      Width           =   2052
   End
End
Attribute VB_Name = "GasOptTest"
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
Dim xlbook As Excel.Workbook

Private Sub CalcOutputs()
Dim outputCell As String
Dim value As Double
Dim numberOfVariables As Integer
Dim counter As Integer

    gasplant.Calculate
    outputCell = "H" & Index
    value = gasplant.getValueByName(gasplant.outputNames(0))
    xlsheet.Range(outputCell).value = value
    
    numberOfVariables = gasplant.getNumberOfVariables(1)
    For counter = 0 To numberOfVariables - 1
        outputCell = Chr(65 + counter + 8) & Index
        value = gasplant.getValueByTag(gasplant.manipulatedTags(counter))
        xlsheet.Range(outputCell).value = value
    Next counter
    
    numberOfVariables = gasplant.getNumberOfVariables(3)
    For counter = 0 To numberOfVariables - 1
        outputCell = Chr(65 + counter + 14) & Index
        value = gasplant.getValueByName(gasplant.stateNames(counter))
        xlsheet.Range(outputCell).value = value
    Next counter
    
    
End Sub

Private Sub Browse_Click()
    GasOptTest.cdlgload.ShowOpen
    file = GasOptTest.cdlgload.FileTitle
    path = Left(GasOptTest.cdlgload.FileName, _
        Len(GasOptTest.cdlgload.FileName) - Len(file))

    If PathName.Text = "" Then
        If (file = "") Then
            path = gasplant.PathName
            file = gasplant.FileName
        End If

        PathName.Text = path & file
    End If
End Sub

Private Sub Calculate_Click()
 Dim value As Variant
 Dim cell1 As String
 Dim bounds As Variant
  
    If (isloaded = True) Then
        For Index = 5 To 100
'        For Index = 5 To 1156
            cell1 = "A" & Index
            value = xlsheet.Range(cell1).value
            bounds = gasplant.getBoundsByName(gasplant.outputNames(0))
            bounds(2) = value
            gasplant.setBoundsByName gasplant.outputNames(0), bounds
            Call CalcOutputs
            CalCount.Text = (Index - 5)
        Next Index
    End If
End Sub

Private Sub cdlgload_Click()

End Sub

Private Sub Form_Load()

    Set xlapp = CreateObject("Excel.Application")
    xlapp.Workbooks.Open App.path & "\gasplantOpt.xls"
    xlapp.Visible = True
    Set xlbook = xlapp.Workbooks(1)
    Set xlsheet = xlbook.Worksheets(1)
    isloaded = False
    GasOptTest.Show
End Sub

Private Sub Load_Click()
Dim counter As Integer
Dim numberOfVariables As Integer
    If (file <> "") Then
        gasplant.loadOptimization file, path
        isloaded = True
        varNames.Item(0).value = True
        VariableList.Clear
        numberOfVariables = gasplant.getNumberOfVariables(0)
        For counter = 0 To numberOfVariables
            VariableList.AddItem gasplant.outputNames(counter)
        Next counter
 
    End If
End Sub

Private Sub trainoutput_Click()
    Dim autoStop As Boolean
    Dim newtraining As Boolean
    Dim display As Boolean
    autoStop = True
    newtraining = True
    display = True
        
    Dim dfs(2) As String
    dfs(0) = "Gasplant1input.csv"
    dfs(1) = "Gasplant1Output.csv"
    gasplant.trainOutputModelFromFile dfs(0), dfs(1), 1.01, autoStop, newtraining, display
End Sub

Private Sub trainstate_Click()
    Dim autoStop As Boolean
    Dim newtraining As Boolean
    Dim display As Boolean
    autoStop = True
    newtraining = True
    display = True
        
    Dim dfs(2) As String
    dfs(0) = "Gasplant1stateinput.csv"
    dfs(1) = "Gasplant1state.csv"
    gasplant.trainStateModelFromFile dfs(0), dfs(1), 1.01, autoStop, newtraining, display
End Sub

Private Sub TrainWhole_Click()
    Dim autoStop As Boolean
    Dim newtraining As Boolean
    Dim display As Boolean
    autoStop = True
    newtraining = True
    display = True
        
    Dim dfs(1) As String
    dfs(0) = "Gasplant1.ds"
    gasplant.trainModelFromFiles dfs, 1.01, autoStop, newtraining, display

End Sub

Private Sub varNames_Click(Index As Integer)
Dim counter As Integer
Dim numberOfVariables As Integer

    VariableList.Clear
    If (isloaded = True) Then
        Select Case Index
            Case 0
                numberOfVariables = gasplant.getNumberOfVariables(0)
                For counter = 0 To numberOfVariables
                    VariableList.AddItem gasplant.outputNames(counter)
                Next counter
           Case 1
                numberOfVariables = gasplant.getNumberOfVariables(1)
                For counter = 0 To numberOfVariables
                    VariableList.AddItem gasplant.manipulatedNames(counter)
                Next counter
            Case 2
                numberOfVariables = gasplant.getNumberOfVariables(2)
                For counter = 0 To numberOfVariables
                    VariableList.AddItem gasplant.exogenousNames(counter)
                Next counter
            Case 3
                numberOfVariables = gasplant.getNumberOfVariables(3)
                For counter = 0 To numberOfVariables
                    VariableList.AddItem gasplant.stateNames(counter)
                Next counter
        End Select
   Else
        VariableList.AddItem "No model is loaded"
   End If
    
End Sub
