package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;
import gensym.charts.ChartsCommon;
import java.awt.Color;

/**
 * Sets chart desk color
 * <b>desk-color</b> int property class.
 */
public class DeskColorProperty extends PropValueBase<Integer>{
    /**
     * Constructor
     */
    public DeskColorProperty() {
        super(2320, "desk-color");
    }
    
    /**
     * {@inheritDoc}
     * Sets desk color
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        chart.getStyle().setChartColor(new Color(ChartsCommon.convertBGRtoRGB(value)));
        chart.updateChartStyle();
    }
}
