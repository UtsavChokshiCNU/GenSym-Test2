package gensym.charts.properties.gradients;

import gensym.charts.properties.PropValueBase;
import gensym.charts.JFreeChartHolder;
import gensym.charts.ChartsCommon;
import java.awt.Color;

/**
 * Sets chart gradient end-color
 * <b>graph-gradient-end</b> int property class.
 */
public class GraphGradientEndProperty extends PropValueBase<Integer>{
    /**
     * Constructor
     */
    public GraphGradientEndProperty() {
        super(2693, "graph-gradient-end");
    }

    /**
     * {@inheritDoc}
     * Sets chart gradient end-color
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        Color color = new Color(ChartsCommon.convertBGRtoRGB(value));
        chart.getStyle().getGradients().setGraphGradientEnd(color);
        
        chart.updateChartStyle();
    }
}
