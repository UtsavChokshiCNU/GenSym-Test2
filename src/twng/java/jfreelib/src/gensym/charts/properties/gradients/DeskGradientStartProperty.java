package gensym.charts.properties.gradients;

import gensym.charts.properties.PropValueBase;
import gensym.charts.JFreeChartHolder;
import gensym.charts.ChartsCommon;
import java.awt.Color;

/**
 * Sets chart desk gradient start-color
 * <b>desk-gradient-start</b> int property class.
 */
public class DeskGradientStartProperty extends PropValueBase<Integer>{
    /**
     * Constructor
     */
    public DeskGradientStartProperty() {
        super(2687, "desk-gradient-start");
    }
    
    /**
     * {@inheritDoc}
     * Sets start gradient color
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        Color color = new Color(ChartsCommon.convertBGRtoRGB(value));
        chart.getStyle().getGradients().setDeskGradientStart(color);
        
        chart.updateChartStyle();
    }
}
