package gensym.charts.properties.gradients;

import gensym.charts.properties.PropValueBase;
import gensym.charts.JFreeChartHolder;
import gensym.charts.ChartsCommon;
import java.awt.Color;

/**
 * Sets chart desk gradient end-color
 * <b>desk-gradient-end</b> int property class.
 */
public class DeskGradientEndProperty extends PropValueBase<Integer>{
    /**
     * Constructor
     */
    public DeskGradientEndProperty() {
        super(2688, "desk-gradient-end");
    }
    
    /**
     * {@inheritDoc}
     * Sets chart desk gradient end-color
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        Color color = new Color(ChartsCommon.convertBGRtoRGB(value));
        chart.getStyle().getGradients().setDeskGradientEnd(color);
        
        chart.updateChartStyle();
    }
}
