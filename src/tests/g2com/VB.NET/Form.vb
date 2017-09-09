Option Strict Off
Option Explicit On
Imports VB = Microsoft.VisualBasic
Friend Class Form1
	Inherits System.Windows.Forms.Form
#Region "Windows Form Designer generated code "
	Public Sub New()
		MyBase.New()
		If m_vb6FormDefInstance Is Nothing Then
			If m_InitializingDefInstance Then
				m_vb6FormDefInstance = Me
			Else
				Try 
					'For the start-up form, the first instance created is the default instance.
					If System.Reflection.Assembly.GetExecutingAssembly.EntryPoint.DeclaringType Is Me.GetType Then
						m_vb6FormDefInstance = Me
					End If
				Catch
				End Try
			End If
		End If
		'This call is required by the Windows Form Designer.
		InitializeComponent()
	End Sub
	'Form overrides dispose to clean up the component list.
	Protected Overloads Overrides Sub Dispose(ByVal Disposing As Boolean)
		If Disposing Then
			If Not components Is Nothing Then
				components.Dispose()
			End If
		End If
		MyBase.Dispose(Disposing)
	End Sub
	'Required by the Windows Form Designer
	Private components As System.ComponentModel.IContainer
	Public ToolTip1 As System.Windows.Forms.ToolTip
    Public WithEvents Label2 As Microsoft.VisualBasic.Compatibility.VB6.LabelArray
	Public WithEvents Label3 As Microsoft.VisualBasic.Compatibility.VB6.LabelArray
	Public WithEvents TC4Command As Microsoft.VisualBasic.Compatibility.VB6.ButtonArray
	Public WithEvents TC4Param As Microsoft.VisualBasic.Compatibility.VB6.TextBoxArray
	Public WithEvents TCInput As Microsoft.VisualBasic.Compatibility.VB6.LabelArray
	'NOTE: The following procedure is required by the Windows Form Designer
	'It can be modified using the Windows Form Designer.
	'Do not modify it using the code editor.
    Public WithEvents _TestTabTabular_TabPage0 As System.Windows.Forms.TabPage
    Public WithEvents TestTab1 As System.Windows.Forms.TabControl
    Public WithEvents _TestTab1_TabPage6 As System.Windows.Forms.TabPage
    Public WithEvents TC11Caption As System.Windows.Forms.Label
    Public WithEvents TC11Frame2 As System.Windows.Forms.GroupBox
    Public WithEvents TC11CALL As System.Windows.Forms.Button
    Public WithEvents TC11Label5 As System.Windows.Forms.Label
    Public WithEvents _TestTab1_TabPage5 As System.Windows.Forms.TabPage
    Public WithEvents TC10Caption As System.Windows.Forms.Label
    Public WithEvents TC10Frame1 As System.Windows.Forms.GroupBox
    Public WithEvents TC10Post As System.Windows.Forms.Button
    Public WithEvents TC10Msg As System.Windows.Forms.TextBox
    Public WithEvents _TestTab1_TabPage10 As System.Windows.Forms.TabPage
    Public WithEvents Label6 As System.Windows.Forms.Label
    Public WithEvents _TestTab1_TabPage3 As System.Windows.Forms.TabPage
    Public WithEvents TC8Label1 As System.Windows.Forms.Label
    Public WithEvents TestTabTabular As System.Windows.Forms.TabControl
    Public WithEvents TCResult As System.Windows.Forms.TextBox
    Public WithEvents TC1Input As System.Windows.Forms.TextBox
    Public WithEvents TC3Input As System.Windows.Forms.TextBox
    Public WithEvents TC2Input As System.Windows.Forms.TextBox
    Public WithEvents Label1 As System.Windows.Forms.Label
    Public WithEvents Label4 As System.Windows.Forms.Label
    Public WithEvents Label5 As System.Windows.Forms.Label
    Public WithEvents Label7 As System.Windows.Forms.Label
    Public WithEvents Label8 As System.Windows.Forms.Label
    Public WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Public WithEvents Label9 As System.Windows.Forms.Label
    Public WithEvents Label11 As System.Windows.Forms.Label
    Public WithEvents Button2 As System.Windows.Forms.Button
    Public WithEvents MaxVal As System.Windows.Forms.TextBox
    Public WithEvents CallItemRetVal As System.Windows.Forms.TextBox
    Public WithEvents TC12Command As System.Windows.Forms.Button
    Public WithEvents TC12Green As System.Windows.Forms.Label
    Public WithEvents TC12Yel As System.Windows.Forms.Label
    Public WithEvents TC12Red As System.Windows.Forms.Label
    Public WithEvents TC12Shape4 As System.Windows.Forms.Label
    Friend WithEvents AxG2GatewayTC13 As AxGensymAxl.AxG2Gateway
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(Form1))
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.Label2 = New Microsoft.VisualBasic.Compatibility.VB6.LabelArray(Me.components)
        Me.Label3 = New Microsoft.VisualBasic.Compatibility.VB6.LabelArray(Me.components)
        Me.TC4Command = New Microsoft.VisualBasic.Compatibility.VB6.ButtonArray(Me.components)
        Me.TC4Param = New Microsoft.VisualBasic.Compatibility.VB6.TextBoxArray(Me.components)
        Me.TCInput = New Microsoft.VisualBasic.Compatibility.VB6.LabelArray(Me.components)
        Me._TestTabTabular_TabPage0 = New System.Windows.Forms.TabPage
        Me.TestTab1 = New System.Windows.Forms.TabControl
        Me._TestTab1_TabPage6 = New System.Windows.Forms.TabPage
        Me.AxG2GatewayTC13 = New AxGensymAxl.AxG2Gateway
        Me.TC11Caption = New System.Windows.Forms.Label
        Me.TC11Frame2 = New System.Windows.Forms.GroupBox
        Me.Label8 = New System.Windows.Forms.Label
        Me.Label7 = New System.Windows.Forms.Label
        Me.Label5 = New System.Windows.Forms.Label
        Me.Label4 = New System.Windows.Forms.Label
        Me.Label1 = New System.Windows.Forms.Label
        Me.TC2Input = New System.Windows.Forms.TextBox
        Me.TC3Input = New System.Windows.Forms.TextBox
        Me.TCResult = New System.Windows.Forms.TextBox
        Me.TC1Input = New System.Windows.Forms.TextBox
        Me.TC11CALL = New System.Windows.Forms.Button
        Me.TC11Label5 = New System.Windows.Forms.Label
        Me._TestTab1_TabPage5 = New System.Windows.Forms.TabPage
        Me.TC10Caption = New System.Windows.Forms.Label
        Me.TC10Frame1 = New System.Windows.Forms.GroupBox
        Me.TC10Post = New System.Windows.Forms.Button
        Me.TC10Msg = New System.Windows.Forms.TextBox
        Me._TestTab1_TabPage10 = New System.Windows.Forms.TabPage
        Me.GroupBox1 = New System.Windows.Forms.GroupBox
        Me.Label9 = New System.Windows.Forms.Label
        Me.Label11 = New System.Windows.Forms.Label
        Me.MaxVal = New System.Windows.Forms.TextBox
        Me.CallItemRetVal = New System.Windows.Forms.TextBox
        Me.Button2 = New System.Windows.Forms.Button
        Me.Label6 = New System.Windows.Forms.Label
        Me._TestTab1_TabPage3 = New System.Windows.Forms.TabPage
        Me.TC12Command = New System.Windows.Forms.Button
        Me.TC12Green = New System.Windows.Forms.Label
        Me.TC12Yel = New System.Windows.Forms.Label
        Me.TC12Red = New System.Windows.Forms.Label
        Me.TC12Shape4 = New System.Windows.Forms.Label
        Me.TC8Label1 = New System.Windows.Forms.Label
        Me.TestTabTabular = New System.Windows.Forms.TabControl
        CType(Me.Label2, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.Label3, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.TC4Command, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.TC4Param, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.TCInput, System.ComponentModel.ISupportInitialize).BeginInit()
        Me._TestTabTabular_TabPage0.SuspendLayout()
        Me.TestTab1.SuspendLayout()
        Me._TestTab1_TabPage6.SuspendLayout()
        CType(Me.AxG2GatewayTC13, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.TC11Frame2.SuspendLayout()
        Me._TestTab1_TabPage5.SuspendLayout()
        Me.TC10Frame1.SuspendLayout()
        Me._TestTab1_TabPage10.SuspendLayout()
        Me.GroupBox1.SuspendLayout()
        Me._TestTab1_TabPage3.SuspendLayout()
        Me.TestTabTabular.SuspendLayout()
        Me.SuspendLayout()
        '
        '_TestTabTabular_TabPage0
        '
        Me._TestTabTabular_TabPage0.Controls.Add(Me.TestTab1)
        Me._TestTabTabular_TabPage0.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._TestTabTabular_TabPage0.Location = New System.Drawing.Point(4, 22)
        Me._TestTabTabular_TabPage0.Name = "_TestTabTabular_TabPage0"
        Me._TestTabTabular_TabPage0.Size = New System.Drawing.Size(672, 390)
        Me._TestTabTabular_TabPage0.TabIndex = 0
        Me._TestTabTabular_TabPage0.Text = "Linking G2 Server with COM-compliant application"
        '
        'TestTab1
        '
        Me.TestTab1.Controls.Add(Me._TestTab1_TabPage6)
        Me.TestTab1.Controls.Add(Me._TestTab1_TabPage5)
        Me.TestTab1.Controls.Add(Me._TestTab1_TabPage10)
        Me.TestTab1.Controls.Add(Me._TestTab1_TabPage3)
        Me.TestTab1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TestTab1.ItemSize = New System.Drawing.Size(42, 18)
        Me.TestTab1.Location = New System.Drawing.Point(16, 16)
        Me.TestTab1.Name = "TestTab1"
        Me.TestTab1.SelectedIndex = 10
        Me.TestTab1.Size = New System.Drawing.Size(640, 360)
        Me.TestTab1.TabIndex = 1
        '
        '_TestTab1_TabPage6
        '
        Me._TestTab1_TabPage6.Controls.Add(Me.AxG2GatewayTC13)
        Me._TestTab1_TabPage6.Controls.Add(Me.TC11Caption)
        Me._TestTab1_TabPage6.Controls.Add(Me.TC11Frame2)
        Me._TestTab1_TabPage6.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._TestTab1_TabPage6.Location = New System.Drawing.Point(4, 22)
        Me._TestTab1_TabPage6.Name = "_TestTab1_TabPage6"
        Me._TestTab1_TabPage6.Size = New System.Drawing.Size(632, 334)
        Me._TestTab1_TabPage6.TabIndex = 6
        Me._TestTab1_TabPage6.Text = "Test Case 14"
        '
        'AxG2GatewayTC13
        '
        Me.AxG2GatewayTC13.ContainingControl = Me
        Me.AxG2GatewayTC13.Enabled = True
        Me.AxG2GatewayTC13.Location = New System.Drawing.Point(568, 72)
        Me.AxG2GatewayTC13.Name = "AxG2GatewayTC13"
        Me.AxG2GatewayTC13.OcxState = CType(resources.GetObject("AxG2GatewayTC13.OcxState"), System.Windows.Forms.AxHost.State)
        Me.AxG2GatewayTC13.Size = New System.Drawing.Size(50, 50)
        Me.AxG2GatewayTC13.TabIndex = 50
        '
        'TC11Caption
        '
        Me.TC11Caption.BackColor = System.Drawing.SystemColors.Control
        Me.TC11Caption.Cursor = System.Windows.Forms.Cursors.Default
        Me.TC11Caption.Font = New System.Drawing.Font("Arial", 12.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TC11Caption.ForeColor = System.Drawing.SystemColors.ControlText
        Me.TC11Caption.Location = New System.Drawing.Point(0, 16)
        Me.TC11Caption.Name = "TC11Caption"
        Me.TC11Caption.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.TC11Caption.Size = New System.Drawing.Size(656, 41)
        Me.TC11Caption.TabIndex = 42
        Me.TC11Caption.Text = "Programs that use AxG2Gateways (Using G2 ActiveXLink with Visual Basic .NET)"
        '
        'TC11Frame2
        '
        Me.TC11Frame2.BackColor = System.Drawing.SystemColors.Control
        Me.TC11Frame2.Controls.Add(Me.Label8)
        Me.TC11Frame2.Controls.Add(Me.Label7)
        Me.TC11Frame2.Controls.Add(Me.Label5)
        Me.TC11Frame2.Controls.Add(Me.Label4)
        Me.TC11Frame2.Controls.Add(Me.Label1)
        Me.TC11Frame2.Controls.Add(Me.TC2Input)
        Me.TC11Frame2.Controls.Add(Me.TC3Input)
        Me.TC11Frame2.Controls.Add(Me.TCResult)
        Me.TC11Frame2.Controls.Add(Me.TC1Input)
        Me.TC11Frame2.Controls.Add(Me.TC11CALL)
        Me.TC11Frame2.Controls.Add(Me.TC11Label5)
        Me.TC11Frame2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TC11Frame2.ForeColor = System.Drawing.SystemColors.ControlText
        Me.TC11Frame2.Location = New System.Drawing.Point(40, 72)
        Me.TC11Frame2.Name = "TC11Frame2"
        Me.TC11Frame2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.TC11Frame2.Size = New System.Drawing.Size(144, 216)
        Me.TC11Frame2.TabIndex = 49
        Me.TC11Frame2.TabStop = False
        Me.TC11Frame2.Text = "Call G2 Procedure"
        '
        'Label8
        '
        Me.Label8.BackColor = System.Drawing.SystemColors.Control
        Me.Label8.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label8.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label8.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label8.Location = New System.Drawing.Point(16, 192)
        Me.Label8.Name = "Label8"
        Me.Label8.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label8.Size = New System.Drawing.Size(40, 17)
        Me.Label8.TabIndex = 61
        Me.Label8.Text = "Integer"
        '
        'Label7
        '
        Me.Label7.BackColor = System.Drawing.SystemColors.Control
        Me.Label7.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label7.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label7.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label7.Location = New System.Drawing.Point(48, 160)
        Me.Label7.Name = "Label7"
        Me.Label7.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label7.Size = New System.Drawing.Size(48, 17)
        Me.Label7.TabIndex = 60
        Me.Label7.Text = "Result"
        '
        'Label5
        '
        Me.Label5.BackColor = System.Drawing.SystemColors.Control
        Me.Label5.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label5.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label5.Location = New System.Drawing.Point(16, 104)
        Me.Label5.Name = "Label5"
        Me.Label5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label5.Size = New System.Drawing.Size(32, 17)
        Me.Label5.TabIndex = 59
        Me.Label5.Text = "Float"
        '
        'Label4
        '
        Me.Label4.BackColor = System.Drawing.SystemColors.Control
        Me.Label4.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label4.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label4.Location = New System.Drawing.Point(16, 80)
        Me.Label4.Name = "Label4"
        Me.Label4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label4.Size = New System.Drawing.Size(40, 17)
        Me.Label4.TabIndex = 58
        Me.Label4.Text = "Integer"
        '
        'Label1
        '
        Me.Label1.BackColor = System.Drawing.SystemColors.Control
        Me.Label1.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label1.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label1.Location = New System.Drawing.Point(16, 56)
        Me.Label1.Name = "Label1"
        Me.Label1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label1.Size = New System.Drawing.Size(40, 17)
        Me.Label1.TabIndex = 57
        Me.Label1.Text = "String"
        '
        'TC2Input
        '
        Me.TC2Input.AcceptsReturn = True
        Me.TC2Input.AutoSize = False
        Me.TC2Input.BackColor = System.Drawing.SystemColors.Window
        Me.TC2Input.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.TC2Input.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TC2Input.ForeColor = System.Drawing.SystemColors.WindowText
        Me.TC2Input.Location = New System.Drawing.Point(64, 72)
        Me.TC2Input.MaxLength = 0
        Me.TC2Input.Name = "TC2Input"
        Me.TC2Input.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.TC2Input.Size = New System.Drawing.Size(65, 24)
        Me.TC2Input.TabIndex = 56
        Me.TC2Input.Text = "3"
        '
        'TC3Input
        '
        Me.TC3Input.AcceptsReturn = True
        Me.TC3Input.AutoSize = False
        Me.TC3Input.BackColor = System.Drawing.SystemColors.Window
        Me.TC3Input.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.TC3Input.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TC3Input.ForeColor = System.Drawing.SystemColors.WindowText
        Me.TC3Input.Location = New System.Drawing.Point(64, 96)
        Me.TC3Input.MaxLength = 0
        Me.TC3Input.Name = "TC3Input"
        Me.TC3Input.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.TC3Input.Size = New System.Drawing.Size(65, 24)
        Me.TC3Input.TabIndex = 55
        Me.TC3Input.Text = "3.34"
        '
        'TCResult
        '
        Me.TCResult.AcceptsReturn = True
        Me.TCResult.AutoSize = False
        Me.TCResult.BackColor = System.Drawing.SystemColors.Window
        Me.TCResult.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.TCResult.Enabled = False
        Me.TCResult.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TCResult.ForeColor = System.Drawing.SystemColors.WindowText
        Me.TCResult.Location = New System.Drawing.Point(64, 184)
        Me.TCResult.MaxLength = 0
        Me.TCResult.Name = "TCResult"
        Me.TCResult.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.TCResult.Size = New System.Drawing.Size(65, 24)
        Me.TCResult.TabIndex = 54
        Me.TCResult.Text = ""
        '
        'TC1Input
        '
        Me.TC1Input.AcceptsReturn = True
        Me.TC1Input.AutoSize = False
        Me.TC1Input.BackColor = System.Drawing.SystemColors.Window
        Me.TC1Input.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.TC1Input.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TC1Input.ForeColor = System.Drawing.SystemColors.WindowText
        Me.TC1Input.Location = New System.Drawing.Point(64, 48)
        Me.TC1Input.MaxLength = 0
        Me.TC1Input.Name = "TC1Input"
        Me.TC1Input.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.TC1Input.Size = New System.Drawing.Size(65, 24)
        Me.TC1Input.TabIndex = 52
        Me.TC1Input.Text = "XYZ"
        '
        'TC11CALL
        '
        Me.TC11CALL.BackColor = System.Drawing.SystemColors.Control
        Me.TC11CALL.Cursor = System.Windows.Forms.Cursors.Default
        Me.TC11CALL.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TC11CALL.ForeColor = System.Drawing.SystemColors.ControlText
        Me.TC11CALL.Location = New System.Drawing.Point(16, 128)
        Me.TC11CALL.Name = "TC11CALL"
        Me.TC11CALL.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.TC11CALL.Size = New System.Drawing.Size(112, 24)
        Me.TC11CALL.TabIndex = 50
        Me.TC11CALL.Text = "Call Procedure "
        '
        'TC11Label5
        '
        Me.TC11Label5.BackColor = System.Drawing.SystemColors.Control
        Me.TC11Label5.Cursor = System.Windows.Forms.Cursors.Default
        Me.TC11Label5.Font = New System.Drawing.Font("Arial", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TC11Label5.ForeColor = System.Drawing.SystemColors.ControlText
        Me.TC11Label5.Location = New System.Drawing.Point(56, 24)
        Me.TC11Label5.Name = "TC11Label5"
        Me.TC11Label5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.TC11Label5.Size = New System.Drawing.Size(48, 17)
        Me.TC11Label5.TabIndex = 51
        Me.TC11Label5.Text = "Input"
        '
        '_TestTab1_TabPage5
        '
        Me._TestTab1_TabPage5.Controls.Add(Me.TC10Caption)
        Me._TestTab1_TabPage5.Controls.Add(Me.TC10Frame1)
        Me._TestTab1_TabPage5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._TestTab1_TabPage5.Location = New System.Drawing.Point(4, 22)
        Me._TestTab1_TabPage5.Name = "_TestTab1_TabPage5"
        Me._TestTab1_TabPage5.Size = New System.Drawing.Size(632, 334)
        Me._TestTab1_TabPage5.TabIndex = 5
        Me._TestTab1_TabPage5.Text = "Test Case 15"
        '
        'TC10Caption
        '
        Me.TC10Caption.BackColor = System.Drawing.SystemColors.Control
        Me.TC10Caption.Cursor = System.Windows.Forms.Cursors.Default
        Me.TC10Caption.Font = New System.Drawing.Font("Arial", 12.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TC10Caption.ForeColor = System.Drawing.SystemColors.ControlText
        Me.TC10Caption.Location = New System.Drawing.Point(16, 16)
        Me.TC10Caption.Name = "TC10Caption"
        Me.TC10Caption.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.TC10Caption.Size = New System.Drawing.Size(617, 49)
        Me.TC10Caption.TabIndex = 36
        Me.TC10Caption.Text = "Test Case 15:  The PostMessage Demo (Using G2 ActiveXLink with Visual Basic .NET)" & _
        ""
        '
        'TC10Frame1
        '
        Me.TC10Frame1.BackColor = System.Drawing.SystemColors.Control
        Me.TC10Frame1.Controls.Add(Me.TC10Post)
        Me.TC10Frame1.Controls.Add(Me.TC10Msg)
        Me.TC10Frame1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TC10Frame1.ForeColor = System.Drawing.SystemColors.ControlText
        Me.TC10Frame1.Location = New System.Drawing.Point(40, 80)
        Me.TC10Frame1.Name = "TC10Frame1"
        Me.TC10Frame1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.TC10Frame1.Size = New System.Drawing.Size(280, 73)
        Me.TC10Frame1.TabIndex = 39
        Me.TC10Frame1.TabStop = False
        Me.TC10Frame1.Text = "Post Message"
        '
        'TC10Post
        '
        Me.TC10Post.BackColor = System.Drawing.SystemColors.Control
        Me.TC10Post.Cursor = System.Windows.Forms.Cursors.Default
        Me.TC10Post.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TC10Post.ForeColor = System.Drawing.SystemColors.ControlText
        Me.TC10Post.Location = New System.Drawing.Point(200, 24)
        Me.TC10Post.Name = "TC10Post"
        Me.TC10Post.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.TC10Post.Size = New System.Drawing.Size(73, 25)
        Me.TC10Post.TabIndex = 41
        Me.TC10Post.Text = "Post"
        '
        'TC10Msg
        '
        Me.TC10Msg.AcceptsReturn = True
        Me.TC10Msg.AutoSize = False
        Me.TC10Msg.BackColor = System.Drawing.SystemColors.Window
        Me.TC10Msg.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.TC10Msg.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TC10Msg.ForeColor = System.Drawing.SystemColors.WindowText
        Me.TC10Msg.Location = New System.Drawing.Point(8, 24)
        Me.TC10Msg.MaxLength = 0
        Me.TC10Msg.Name = "TC10Msg"
        Me.TC10Msg.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.TC10Msg.Size = New System.Drawing.Size(185, 25)
        Me.TC10Msg.TabIndex = 40
        Me.TC10Msg.Text = "Test Message"
        '
        '_TestTab1_TabPage10
        '
        Me._TestTab1_TabPage10.Controls.Add(Me.GroupBox1)
        Me._TestTab1_TabPage10.Controls.Add(Me.Label6)
        Me._TestTab1_TabPage10.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._TestTab1_TabPage10.Location = New System.Drawing.Point(4, 22)
        Me._TestTab1_TabPage10.Name = "_TestTab1_TabPage10"
        Me._TestTab1_TabPage10.Size = New System.Drawing.Size(632, 334)
        Me._TestTab1_TabPage10.TabIndex = 10
        Me._TestTab1_TabPage10.Text = "Test Case 16"
        '
        'GroupBox1
        '
        Me.GroupBox1.BackColor = System.Drawing.SystemColors.Control
        Me.GroupBox1.Controls.Add(Me.Label9)
        Me.GroupBox1.Controls.Add(Me.Label11)
        Me.GroupBox1.Controls.Add(Me.MaxVal)
        Me.GroupBox1.Controls.Add(Me.CallItemRetVal)
        Me.GroupBox1.Controls.Add(Me.Button2)
        Me.GroupBox1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.GroupBox1.ForeColor = System.Drawing.SystemColors.ControlText
        Me.GroupBox1.Location = New System.Drawing.Point(40, 64)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.GroupBox1.Size = New System.Drawing.Size(144, 144)
        Me.GroupBox1.TabIndex = 70
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "Call G2 Procedure"
        '
        'Label9
        '
        Me.Label9.BackColor = System.Drawing.SystemColors.Control
        Me.Label9.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label9.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label9.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label9.Location = New System.Drawing.Point(16, 112)
        Me.Label9.Name = "Label9"
        Me.Label9.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label9.Size = New System.Drawing.Size(40, 17)
        Me.Label9.TabIndex = 61
        Me.Label9.Text = "Result"
        '
        'Label11
        '
        Me.Label11.BackColor = System.Drawing.SystemColors.Control
        Me.Label11.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label11.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label11.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label11.Location = New System.Drawing.Point(24, 80)
        Me.Label11.Name = "Label11"
        Me.Label11.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label11.Size = New System.Drawing.Size(32, 17)
        Me.Label11.TabIndex = 59
        Me.Label11.Text = "Input"
        '
        'MaxVal
        '
        Me.MaxVal.AcceptsReturn = True
        Me.MaxVal.AutoSize = False
        Me.MaxVal.BackColor = System.Drawing.SystemColors.Window
        Me.MaxVal.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.MaxVal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.MaxVal.ForeColor = System.Drawing.SystemColors.WindowText
        Me.MaxVal.Location = New System.Drawing.Point(64, 72)
        Me.MaxVal.MaxLength = 0
        Me.MaxVal.Name = "MaxVal"
        Me.MaxVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.MaxVal.Size = New System.Drawing.Size(65, 24)
        Me.MaxVal.TabIndex = 55
        Me.MaxVal.Text = "100"
        '
        'CallItemRetVal
        '
        Me.CallItemRetVal.AcceptsReturn = True
        Me.CallItemRetVal.AutoSize = False
        Me.CallItemRetVal.BackColor = System.Drawing.SystemColors.Window
        Me.CallItemRetVal.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.CallItemRetVal.Enabled = False
        Me.CallItemRetVal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.CallItemRetVal.ForeColor = System.Drawing.SystemColors.WindowText
        Me.CallItemRetVal.Location = New System.Drawing.Point(64, 104)
        Me.CallItemRetVal.MaxLength = 0
        Me.CallItemRetVal.Name = "CallItemRetVal"
        Me.CallItemRetVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.CallItemRetVal.Size = New System.Drawing.Size(65, 24)
        Me.CallItemRetVal.TabIndex = 54
        Me.CallItemRetVal.Text = ""
        '
        'Button2
        '
        Me.Button2.BackColor = System.Drawing.SystemColors.Control
        Me.Button2.Cursor = System.Windows.Forms.Cursors.Default
        Me.Button2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Button2.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Button2.Location = New System.Drawing.Point(40, 24)
        Me.Button2.Name = "Button2"
        Me.Button2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Button2.Size = New System.Drawing.Size(64, 32)
        Me.Button2.TabIndex = 50
        Me.Button2.Text = "Call"
        '
        'Label6
        '
        Me.Label6.BackColor = System.Drawing.SystemColors.Control
        Me.Label6.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label6.Font = New System.Drawing.Font("Arial", 12.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label6.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label6.Location = New System.Drawing.Point(16, 16)
        Me.Label6.Name = "Label6"
        Me.Label6.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label6.Size = New System.Drawing.Size(608, 41)
        Me.Label6.TabIndex = 67
        Me.Label6.Text = "Test Case 16:  The Call Demo (Using G2 ActiveXLink with Visual Basic .NET)"
        '
        '_TestTab1_TabPage3
        '
        Me._TestTab1_TabPage3.Controls.Add(Me.TC12Command)
        Me._TestTab1_TabPage3.Controls.Add(Me.TC12Green)
        Me._TestTab1_TabPage3.Controls.Add(Me.TC12Yel)
        Me._TestTab1_TabPage3.Controls.Add(Me.TC12Red)
        Me._TestTab1_TabPage3.Controls.Add(Me.TC12Shape4)
        Me._TestTab1_TabPage3.Controls.Add(Me.TC8Label1)
        Me._TestTab1_TabPage3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me._TestTab1_TabPage3.Location = New System.Drawing.Point(4, 22)
        Me._TestTab1_TabPage3.Name = "_TestTab1_TabPage3"
        Me._TestTab1_TabPage3.Size = New System.Drawing.Size(632, 334)
        Me._TestTab1_TabPage3.TabIndex = 3
        Me._TestTab1_TabPage3.Text = "Test Case 17"
        '
        'TC12Command
        '
        Me.TC12Command.BackColor = System.Drawing.SystemColors.Control
        Me.TC12Command.Cursor = System.Windows.Forms.Cursors.Default
        Me.TC12Command.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TC12Command.ForeColor = System.Drawing.SystemColors.ControlText
        Me.TC12Command.Location = New System.Drawing.Point(128, 120)
        Me.TC12Command.Name = "TC12Command"
        Me.TC12Command.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.TC12Command.Size = New System.Drawing.Size(81, 33)
        Me.TC12Command.TabIndex = 66
        Me.TC12Command.Text = "Cycle Lights"
        '
        'TC12Green
        '
        Me.TC12Green.BackColor = System.Drawing.Color.Red
        Me.TC12Green.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.TC12Green.ForeColor = System.Drawing.Color.Black
        Me.TC12Green.Location = New System.Drawing.Point(64, 160)
        Me.TC12Green.Name = "TC12Green"
        Me.TC12Green.Size = New System.Drawing.Size(33, 33)
        Me.TC12Green.TabIndex = 67
        '
        'TC12Yel
        '
        Me.TC12Yel.BackColor = System.Drawing.Color.Red
        Me.TC12Yel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.TC12Yel.ForeColor = System.Drawing.Color.Black
        Me.TC12Yel.Location = New System.Drawing.Point(64, 120)
        Me.TC12Yel.Name = "TC12Yel"
        Me.TC12Yel.Size = New System.Drawing.Size(33, 33)
        Me.TC12Yel.TabIndex = 68
        '
        'TC12Red
        '
        Me.TC12Red.BackColor = System.Drawing.Color.Red
        Me.TC12Red.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.TC12Red.ForeColor = System.Drawing.Color.Black
        Me.TC12Red.Location = New System.Drawing.Point(64, 80)
        Me.TC12Red.Name = "TC12Red"
        Me.TC12Red.Size = New System.Drawing.Size(33, 33)
        Me.TC12Red.TabIndex = 69
        '
        'TC12Shape4
        '
        Me.TC12Shape4.BackColor = System.Drawing.Color.FromArgb(CType(64, Byte), CType(64, Byte), CType(64, Byte))
        Me.TC12Shape4.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle
        Me.TC12Shape4.Location = New System.Drawing.Point(56, 72)
        Me.TC12Shape4.Name = "TC12Shape4"
        Me.TC12Shape4.Size = New System.Drawing.Size(49, 129)
        Me.TC12Shape4.TabIndex = 70
        '
        'TC8Label1
        '
        Me.TC8Label1.BackColor = System.Drawing.SystemColors.Control
        Me.TC8Label1.Cursor = System.Windows.Forms.Cursors.Default
        Me.TC8Label1.Font = New System.Drawing.Font("Arial", 12.0!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TC8Label1.ForeColor = System.Drawing.SystemColors.ControlText
        Me.TC8Label1.Location = New System.Drawing.Point(16, 16)
        Me.TC8Label1.Name = "TC8Label1"
        Me.TC8Label1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.TC8Label1.Size = New System.Drawing.Size(641, 41)
        Me.TC8Label1.TabIndex = 25
        Me.TC8Label1.Text = "Test Case 17:  The Traffic Light Demo(Using G2 ActiveXLink with Visual Basic .NET" & _
        ")"
        '
        'TestTabTabular
        '
        Me.TestTabTabular.Appearance = System.Windows.Forms.TabAppearance.FlatButtons
        Me.TestTabTabular.Controls.Add(Me._TestTabTabular_TabPage0)
        Me.TestTabTabular.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.TestTabTabular.ItemSize = New System.Drawing.Size(42, 18)
        Me.TestTabTabular.Location = New System.Drawing.Point(0, 0)
        Me.TestTabTabular.Name = "TestTabTabular"
        Me.TestTabTabular.SelectedIndex = 1
        Me.TestTabTabular.Size = New System.Drawing.Size(680, 416)
        Me.TestTabTabular.TabIndex = 0
        '
        'Form1
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.BackColor = System.Drawing.SystemColors.Control
        Me.ClientSize = New System.Drawing.Size(680, 413)
        Me.Controls.Add(Me.TestTabTabular)
        Me.Cursor = System.Windows.Forms.Cursors.Default
        Me.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Location = New System.Drawing.Point(4, 23)
        Me.Name = "Form1"
        Me.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.StartPosition = System.Windows.Forms.FormStartPosition.Manual
        Me.Text = "Test Cases"
        CType(Me.Label2, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.Label3, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.TC4Command, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.TC4Param, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.TCInput, System.ComponentModel.ISupportInitialize).EndInit()
        Me._TestTabTabular_TabPage0.ResumeLayout(False)
        Me.TestTab1.ResumeLayout(False)
        Me._TestTab1_TabPage6.ResumeLayout(False)
        CType(Me.AxG2GatewayTC13, System.ComponentModel.ISupportInitialize).EndInit()
        Me.TC11Frame2.ResumeLayout(False)
        Me._TestTab1_TabPage5.ResumeLayout(False)
        Me.TC10Frame1.ResumeLayout(False)
        Me._TestTab1_TabPage10.ResumeLayout(False)
        Me.GroupBox1.ResumeLayout(False)
        Me._TestTab1_TabPage3.ResumeLayout(False)
        Me.TestTabTabular.ResumeLayout(False)
        Me.ResumeLayout(False)

    End Sub
#End Region 
#Region "Upgrade Support "
	Private Shared m_vb6FormDefInstance As Form1
	Private Shared m_InitializingDefInstance As Boolean
	Public Shared Property DefInstance() As Form1
		Get
			If m_vb6FormDefInstance Is Nothing OrElse m_vb6FormDefInstance.IsDisposed Then
				m_InitializingDefInstance = True
				m_vb6FormDefInstance = New Form1()
				m_InitializingDefInstance = False
			End If
			DefInstance = m_vb6FormDefInstance
		End Get
		Set
			m_vb6FormDefInstance = Value
		End Set
	End Property
#End Region 
    Public TC12NextMode As String
    Public TC12Mode As String
	
	Private Structure SECURITY_ATTRIBUTES
		Dim nLength As Integer
		Dim lpSecurityDescriptor As Integer
		Dim bInheritHandle As Integer
	End Structure
	
	Private Structure STARTUPINFO
		Dim cb As Integer
		Dim lpReserved As Integer
		Dim lpDesktop As Integer
		Dim lpTitle As Integer
		Dim dwX As Integer
		Dim dwY As Integer
		Dim dwXSize As Integer
		Dim dwYSize As Integer
		Dim dwXCountChars As Integer
		Dim dwYCountChars As Integer
		Dim dwFillAttribute As Integer
		Dim dwFlags As Integer
		Dim wShowWindow As Short
		Dim cbReserved2 As Short
		Dim lpReserved2 As Integer
		Dim hStdInput As Integer
		Dim hStdOutput As Integer
		Dim hStdError As Integer
	End Structure
	
	Private Structure PROCESS_INFORMATION
		Dim hProcess As Integer
		Dim hThread As Integer
		Dim dwProcessID As Integer
		Dim dwThreadID As Integer
	End Structure

    Private Sub TC10Post_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles TC10Post.Click
        AxG2GatewayTC13.PostMessage(TC10Msg.Text)
    End Sub

    Private Sub Form1_Load(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles MyBase.Load
        TC12NextMode = "slow"
    End Sub

   
    Private Sub Update_Light(ByRef Mode As String)
        If Mode = "PROCEED" Then
            TC12Red.BackColor = Color.White
            TC12Yel.BackColor = Color.White
            TC12Green.BackColor = Color.Green
        ElseIf Mode = "STOP" Then
            TC12Red.BackColor = Color.Red
            TC12Yel.BackColor = Color.White
            TC12Green.BackColor = Color.White
        Else
            TC12Red.BackColor = Color.White
            TC12Yel.BackColor = Color.Yellow
            TC12Green.BackColor = Color.White
        End If
    End Sub
    Private Sub AxG2GatewayTC13_RpcStarted(ByVal eventSender As System.Object, ByVal eventArgs As AxGensymAxl._G2Events_RpcStartedEvent) Handles AxG2GatewayTC13.RpcStarted
        TC12Mode = UCase(eventArgs.inputArguments)
        If eventArgs.procedureName = "CYCLELIGHTS" Then Call Update_Light(TC12Mode)
    End Sub

    Private Sub TC11CALL_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TC11CALL.Click

        Dim X As Integer
        Dim ParamOut(2) As Object
        ParamOut(0) = TC1Input.Text
        ParamOut(1) = Int32.Parse(TC2Input.Text)
        ParamOut(2) = Double.Parse(TC3Input.Text)
        X = AxG2GatewayTC13.Call("TESTCASE14", ParamOut)

        TCResult.Text = X.ToString

    End Sub


    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        Dim InArgs(0) As Object
        Dim rannum As Double
        InArgs(0) = Val(MaxVal.Text)
        rannum = AxG2GatewayTC13.Call("G2RANDOMGENERATOR", InArgs)
        CallItemRetVal.Text = CStr(rannum)
    End Sub


    Private Sub TC12Command_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TC12Command.Click
        Dim rannu As Object
        Dim InArgs(0) As Object
        InArgs(0) = TC12NextMode
        rannu = AxG2GatewayTC13.Call("CHANGE-SIGNAL", InArgs)
        If TC12NextMode = "stop" Then
            TC12NextMode = "slow"
        ElseIf TC12NextMode = "slow" Then
            TC12NextMode = "proceed"
        Else
            TC12NextMode = "stop"
        End If
    End Sub

    
End Class