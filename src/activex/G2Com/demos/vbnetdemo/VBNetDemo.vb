' ==============================================================================
' 
'        A demonstration of using ActiveXLink with Visual Basic .NET
' 
' ==============================================================================
Option Strict Off
Option Explicit On 
Friend Class VBNetDemoForm
    Inherits System.Windows.Forms.Form

    Dim TheTrafficLight As New TrafficLight(Me)

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
    Public WithEvents CycleLights As System.Windows.Forms.Button
    Public WithEvents MaxVal As System.Windows.Forms.TextBox
    Public WithEvents MsgToPost As System.Windows.Forms.TextBox
    Public WithEvents CallRPC As System.Windows.Forms.Button
    Public WithEvents PostMsgBtn As System.Windows.Forms.Button
    Public WithEvents Label5 As System.Windows.Forms.Label
    Public WithEvents Frame1 As System.Windows.Forms.GroupBox
    Public WithEvents Label4 As System.Windows.Forms.Label
    Public WithEvents Label3 As System.Windows.Forms.Label
    Public WithEvents Frame2 As System.Windows.Forms.GroupBox
    Public WithEvents G2Gateway1 As AxGensymAxl.AxG2Gateway
    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.
    'Do not modify it using the code editor.
    Public WithEvents tbRetVal As System.Windows.Forms.TextBox
    <System.Diagnostics.DebuggerStepThrough()> Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.Resources.ResourceManager = New System.Resources.ResourceManager(GetType(VBNetDemoForm))
        Me.ToolTip1 = New System.Windows.Forms.ToolTip(Me.components)
        Me.CycleLights = New System.Windows.Forms.Button()
        Me.tbRetVal = New System.Windows.Forms.TextBox()
        Me.MaxVal = New System.Windows.Forms.TextBox()
        Me.MsgToPost = New System.Windows.Forms.TextBox()
        Me.CallRPC = New System.Windows.Forms.Button()
        Me.PostMsgBtn = New System.Windows.Forms.Button()
        Me.Frame1 = New System.Windows.Forms.GroupBox()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.Frame2 = New System.Windows.Forms.GroupBox()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.G2Gateway1 = New AxGensymAxl.AxG2Gateway()
        Me.Frame1.SuspendLayout()
        Me.Frame2.SuspendLayout()
        CType(Me.G2Gateway1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'CycleLights
        '
        Me.CycleLights.BackColor = System.Drawing.SystemColors.Control
        Me.CycleLights.Cursor = System.Windows.Forms.Cursors.Default
        Me.CycleLights.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.CycleLights.ForeColor = System.Drawing.SystemColors.ControlText
        Me.CycleLights.Location = New System.Drawing.Point(177, 201)
        Me.CycleLights.Name = "CycleLights"
        Me.CycleLights.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.CycleLights.Size = New System.Drawing.Size(81, 33)
        Me.CycleLights.TabIndex = 6
        Me.CycleLights.Text = "Cycle Lights"
        '
        'tbRetVal
        '
        Me.tbRetVal.AcceptsReturn = True
        Me.tbRetVal.AutoSize = False
        Me.tbRetVal.BackColor = System.Drawing.SystemColors.Window
        Me.tbRetVal.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.tbRetVal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.tbRetVal.ForeColor = System.Drawing.SystemColors.InactiveCaption
        Me.tbRetVal.Location = New System.Drawing.Point(238, 106)
        Me.tbRetVal.MaxLength = 0
        Me.tbRetVal.Name = "tbRetVal"
        Me.tbRetVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.tbRetVal.Size = New System.Drawing.Size(65, 19)
        Me.tbRetVal.TabIndex = 4
        Me.tbRetVal.TabStop = False
        Me.tbRetVal.Text = ""
        '
        'MaxVal
        '
        Me.MaxVal.AcceptsReturn = True
        Me.MaxVal.AutoSize = False
        Me.MaxVal.BackColor = System.Drawing.SystemColors.Window
        Me.MaxVal.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.MaxVal.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.MaxVal.ForeColor = System.Drawing.SystemColors.WindowText
        Me.MaxVal.Location = New System.Drawing.Point(238, 77)
        Me.MaxVal.MaxLength = 0
        Me.MaxVal.Name = "MaxVal"
        Me.MaxVal.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.MaxVal.Size = New System.Drawing.Size(65, 19)
        Me.MaxVal.TabIndex = 3
        Me.MaxVal.Text = "100"
        '
        'MsgToPost
        '
        Me.MsgToPost.AcceptsReturn = True
        Me.MsgToPost.AutoSize = False
        Me.MsgToPost.BackColor = System.Drawing.SystemColors.Window
        Me.MsgToPost.Cursor = System.Windows.Forms.Cursors.IBeam
        Me.MsgToPost.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.MsgToPost.ForeColor = System.Drawing.SystemColors.WindowText
        Me.MsgToPost.Location = New System.Drawing.Point(23, 104)
        Me.MsgToPost.MaxLength = 0
        Me.MsgToPost.Name = "MsgToPost"
        Me.MsgToPost.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.MsgToPost.Size = New System.Drawing.Size(129, 19)
        Me.MsgToPost.TabIndex = 2
        Me.MsgToPost.Text = "Hello G2!"
        '
        'CallRPC
        '
        Me.CallRPC.BackColor = System.Drawing.SystemColors.Control
        Me.CallRPC.Cursor = System.Windows.Forms.Cursors.Default
        Me.CallRPC.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.CallRPC.ForeColor = System.Drawing.SystemColors.ControlText
        Me.CallRPC.Location = New System.Drawing.Point(208, 28)
        Me.CallRPC.Name = "CallRPC"
        Me.CallRPC.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.CallRPC.Size = New System.Drawing.Size(81, 33)
        Me.CallRPC.TabIndex = 1
        Me.CallRPC.Text = "Call"
        '
        'PostMsgBtn
        '
        Me.PostMsgBtn.BackColor = System.Drawing.SystemColors.Control
        Me.PostMsgBtn.Cursor = System.Windows.Forms.Cursors.Default
        Me.PostMsgBtn.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.PostMsgBtn.ForeColor = System.Drawing.SystemColors.ControlText
        Me.PostMsgBtn.Location = New System.Drawing.Point(44, 28)
        Me.PostMsgBtn.Name = "PostMsgBtn"
        Me.PostMsgBtn.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.PostMsgBtn.Size = New System.Drawing.Size(81, 33)
        Me.PostMsgBtn.TabIndex = 0
        Me.PostMsgBtn.Text = "Post Message"
        '
        'Frame1
        '
        Me.Frame1.BackColor = System.Drawing.SystemColors.Control
        Me.Frame1.Controls.AddRange(New System.Windows.Forms.Control() {Me.Label5})
        Me.Frame1.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Frame1.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Frame1.Location = New System.Drawing.Point(8, 8)
        Me.Frame1.Name = "Frame1"
        Me.Frame1.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Frame1.Size = New System.Drawing.Size(153, 129)
        Me.Frame1.TabIndex = 5
        Me.Frame1.TabStop = False
        Me.Frame1.Text = "Display Data In G2"
        '
        'Label5
        '
        Me.Label5.BackColor = System.Drawing.SystemColors.Control
        Me.Label5.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label5.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label5.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label5.Location = New System.Drawing.Point(18, 68)
        Me.Label5.Name = "Label5"
        Me.Label5.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label5.Size = New System.Drawing.Size(124, 26)
        Me.Label5.TabIndex = 10
        Me.Label5.Text = "Enter Message to Display on G2 Message Board"
        '
        'Frame2
        '
        Me.Frame2.BackColor = System.Drawing.SystemColors.Control
        Me.Frame2.Controls.AddRange(New System.Windows.Forms.Control() {Me.Label4, Me.Label3})
        Me.Frame2.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Frame2.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Frame2.Location = New System.Drawing.Point(176, 8)
        Me.Frame2.Name = "Frame2"
        Me.Frame2.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Frame2.Size = New System.Drawing.Size(153, 129)
        Me.Frame2.TabIndex = 7
        Me.Frame2.TabStop = False
        Me.Frame2.Text = "Call G2 Procedure"
        '
        'Label4
        '
        Me.Label4.BackColor = System.Drawing.SystemColors.Control
        Me.Label4.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label4.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label4.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label4.Location = New System.Drawing.Point(21, 100)
        Me.Label4.Name = "Label4"
        Me.Label4.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label4.Size = New System.Drawing.Size(36, 15)
        Me.Label4.TabIndex = 9
        Me.Label4.Text = "Result:"
        '
        'Label3
        '
        Me.Label3.BackColor = System.Drawing.SystemColors.Control
        Me.Label3.Cursor = System.Windows.Forms.Cursors.Default
        Me.Label3.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Label3.ForeColor = System.Drawing.SystemColors.ControlText
        Me.Label3.Location = New System.Drawing.Point(28, 71)
        Me.Label3.Name = "Label3"
        Me.Label3.RightToLeft = System.Windows.Forms.RightToLeft.No
        Me.Label3.Size = New System.Drawing.Size(33, 14)
        Me.Label3.TabIndex = 8
        Me.Label3.Text = "Input:"
        '
        'G2Gateway1
        '
        Me.G2Gateway1.Enabled = True
        Me.G2Gateway1.Location = New System.Drawing.Point(40, 192)
        Me.G2Gateway1.Name = "G2Gateway1"
        Me.G2Gateway1.OcxState = CType(resources.GetObject("G2Gateway1.OcxState"), System.Windows.Forms.AxHost.State)
        Me.G2Gateway1.Size = New System.Drawing.Size(72, 56)
        Me.G2Gateway1.TabIndex = 8
        '
        'VBNetDemoForm
        '
        Me.AutoScaleBaseSize = New System.Drawing.Size(5, 13)
        Me.ClientSize = New System.Drawing.Size(343, 310)
        Me.Controls.AddRange(New System.Windows.Forms.Control() {Me.CycleLights, Me.tbRetVal, Me.MaxVal, Me.MsgToPost, Me.CallRPC, Me.PostMsgBtn, Me.Frame1, Me.Frame2, Me.G2Gateway1})
        Me.Font = New System.Drawing.Font("Arial", 8.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.Location = New System.Drawing.Point(4, 23)
        Me.Name = "VBNetDemoForm"
        Me.Text = "VB.NET / G2 - ActiveXLink Demo"
        Me.Frame1.ResumeLayout(False)
        Me.Frame2.ResumeLayout(False)
        CType(Me.G2Gateway1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)

    End Sub
#End Region
#Region "Upgrade Support "
    Private Shared m_vb6FormDefInstance As VBNetDemoForm
    Private Shared m_InitializingDefInstance As Boolean
    Public Shared Property DefInstance() As VBNetDemoForm
        Get
            If m_vb6FormDefInstance Is Nothing OrElse m_vb6FormDefInstance.IsDisposed Then
                m_InitializingDefInstance = True
                m_vb6FormDefInstance = New VBNetDemoForm()
                m_InitializingDefInstance = False
            End If
            DefInstance = m_vb6FormDefInstance
        End Get
        Set(ByVal Value As VBNetDemoForm)
            m_vb6FormDefInstance = Value
        End Set
    End Property
#End Region
    ' ---------------------------------------------------------------------------
    '                Demonstration of use of the Call method.
    '   Pass a positive number to the G2 procedure G2RandomGenerator.  It should
    '   return a random number less than the number you specified.  Display the
    '   result by putting it in the tbRetVal text box.
    ' ---------------------------------------------------------------------------
    Private Sub CallRPC_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles CallRPC.Click
        Dim InArgs(0) As Object
        Dim retVal As Double

        InArgs(0) = Val(MaxVal.Text)
        Try
            retVal = G2Gateway1.Call("G2RANDOMGENERATOR", InArgs)
        Catch ex As Exception
            MsgBox(ex.ToString)
        End Try

        tbRetVal.Text = CStr(retVal)
    End Sub


    ' ---------------------------------------------------------------------------
    '    The VB.NET graphic system is significantly different from that of VB 6
    '  In particular, you are responsible for redisplaying graphic objects when
    '  a Paint event is fired.  This is the Paint event handler for our demo.    
    ' ---------------------------------------------------------------------------
    Private Sub form_Paint(ByVal sender As Object, ByVal e As System.Windows.Forms.PaintEventArgs) Handles MyBase.Paint
        ' Create a local version of the graphics object for the PictureBox.
        Dim g As Graphics = e.Graphics

        TheTrafficLight.DrawMeTo(g, 60, 170)
    End Sub

    ' --------------------------------------------------------------------------
    '           When G2 returns an error message to this program,
    '                        display it in a message box.
    ' --------------------------------------------------------------------------
    Private Sub G2Gateway1_Error(ByVal eventSender As System.Object, ByVal eventArgs As AxGensymAxl._G2Events_ErrorEvent) Handles G2Gateway1.Error
        MsgBox(eventArgs.errorMessage)
    End Sub


    ' --------------------------------------------------------------------------
    ' G2 uses G2Com-Start or G2Com-Start-over-interface to execute this event 
    ' handler.  In our demo, the specified procedure name should be CYCLELIGHTS
    ' and the only input argument should be a text string that specifies the 
    ' desired state of the traffic light.
    ' --------------------------------------------------------------------------
    Private Sub G2Gateway1_RpcStarted(ByVal eventSender As System.Object, ByVal eventArgs As AxGensymAxl._G2Events_RpcStartedEvent) Handles G2Gateway1.RpcStarted
        Dim strLightState As String
        If eventArgs.procedureName = "CYCLELIGHTS" Then
            strLightState = eventArgs.inputArguments
            If strLightState = "STOP" Then
                TheTrafficLight.currentState = TrafficLight.LightState.Halt
            ElseIf strLightState = "SLOW" Then
                TheTrafficLight.currentState = TrafficLight.LightState.Slow
            Else
                TheTrafficLight.currentState = TrafficLight.LightState.Go
            End If
        End If
    End Sub

    ' --------------------------------------------------------------------------
    ' Demonstrate the PostMessage method.  This causes the message that you
    ' entered in the MsgToPost text box to be displayed on the G2 Message Board.
    ' --------------------------------------------------------------------------
    Private Sub PostMsgBtn_Click(ByVal eventSender As System.Object, ByVal eventArgs As System.EventArgs) Handles PostMsgBtn.Click
        G2Gateway1.PostMessage(MsgToPost.Text)
    End Sub


    ' --------------------------------------------------------------------------
    ' Demonstrate the Start method.  Get the current state of the traffic light,
    ' set it to the next state, and then Start the G2 procedure change-signal
    ' passing it a text string representing the new trafficlight state.
    ' --------------------------------------------------------------------------
    Private Sub CycleLights_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles CycleLights.Click
        Dim currentLightState As TrafficLight.LightState
        Dim msg4G2 As String

        currentLightState = TheTrafficLight.currentState
        If currentLightState = TrafficLight.LightState.Halt Then
            TheTrafficLight.currentState = TrafficLight.LightState.Slow
            msg4G2 = "slow"
        ElseIf currentLightState = TrafficLight.LightState.Slow Then
            TheTrafficLight.currentState = TrafficLight.LightState.Go
            msg4G2 = "go"
        Else
            TheTrafficLight.currentState = TrafficLight.LightState.Halt
            msg4G2 = "stop"
        End If

        Dim Arg4G2(0) As Object
        Arg4G2(0) = msg4G2
        Try
            G2Gateway1.Start("change-signal", Arg4G2)
        Catch ex As Exception
            MsgBox(ex.ToString)
        End Try
    End Sub
End Class