package gensym.charts.properties.gradients;

import gensym.charts.properties.PropValueBase;
import gensym.charts.JFreeChartHolder;

/**
 * Sets chart gradient style
 * <b>graph-gradient-style</b> int property class.
 */
public class GraphGradientStyleProperty extends PropValueBase<Integer>{
    /**
     * Constructor
     */
    public GraphGradientStyleProperty() {
        super(2694, "graph-gradient-style");
    }

    /**
     * {@inheritDoc}
     * Sets chart gradient style
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        chart.getStyle().getGradients().setGraphGradientStyle(value);
        chart.updateChartStyle();
    }
}
