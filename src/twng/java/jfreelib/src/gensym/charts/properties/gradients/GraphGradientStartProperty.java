package gensym.charts.properties.gradients;

import gensym.charts.properties.PropValueBase;
import gensym.charts.JFreeChartHolder;
import gensym.charts.ChartsCommon;
import java.awt.Color;

/**
 * Sets chart gradient start-color
 * <b>graph-gradient-start</b> int property class.
 */
public class GraphGradientStartProperty extends PropValueBase<Integer>{
    /**
     * Constructor
     */
    public GraphGradientStartProperty() {
        super(2692, "graph-gradient-start");
    }

    /**
     * {@inheritDoc}
     * Sets start gradient color
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        Color color = new Color(ChartsCommon.convertBGRtoRGB(value));
        chart.getStyle().getGradients().setGraphGradientStart(color);
        
        chart.updateChartStyle();
    }
}
