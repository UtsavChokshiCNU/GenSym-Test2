Public Class TrafficLight

    Public Enum LightState
        Halt
        Slow
        Go
    End Enum

    ' Constructor
    ' ===========
    Public Sub New(ByVal containingForm As Form)
        m_Form = containingForm

        m_Bitmap = New Bitmap(50, 114, Drawing.Imaging.PixelFormat.Format24bppRgb)
        m_Graphics = Graphics.FromImage(m_Bitmap)
        m_Graphics.DrawRectangle(System.Drawing.Pens.Black, 0, 0, 50, 114)
        m_Graphics.FillRectangle(System.Drawing.Brushes.DarkOrange, 1, 1, 48, 112)

        currentState = LightState.Halt
    End Sub

    ' State Accessor & Mutator Methods
    ' ================================
    Public Property currentState() As LightState
        Get
            Return m_LightState
        End Get
        Set(ByVal newLightState As LightState)
            m_LightState = newLightState

            Dim currentBrush As System.Drawing.Brush
            currentBrush = IIf(newLightState = LightState.Halt, System.Drawing.Brushes.Red, System.Drawing.Brushes.Black)
            m_Graphics.FillEllipse(currentBrush, 10, 10, 30, 30)
            currentBrush = IIf(newLightState = LightState.Slow, System.Drawing.Brushes.Yellow, System.Drawing.Brushes.Black)
            m_Graphics.FillEllipse(currentBrush, 10, 42, 30, 30)
            currentBrush = IIf(newLightState = LightState.Go, System.Drawing.Brushes.GreenYellow, System.Drawing.Brushes.Black)
            m_Graphics.FillEllipse(currentBrush, 10, 74, 30, 30)

            ' Request a Paint event which is necessary to update the display.
            ' The event handler should contain a call to this object's DrawMeTo method.
            ' -------------------------------------------------------------------------
            m_Form.Invalidate()
        End Set
    End Property

    ' Routine Used by Paint to Display this Traffic Light
    ' ===================================================
    Public Sub DrawMeTo(ByVal g As Graphics, ByVal x As Short, ByVal y As Short)
        g.DrawImage(m_Bitmap, x, y, 49, 113)
    End Sub


    Private m_LightState As LightState
    Private m_Bitmap As Bitmap
    Private m_Graphics As Graphics
    Private m_Form As Form

End Class
