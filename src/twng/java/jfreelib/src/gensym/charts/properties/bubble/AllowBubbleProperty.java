package gensym.charts.properties.bubble;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>allow-bubble</b> int property class.
 * Allows Bubble plotting method
 */
public class AllowBubbleProperty extends PropValueBase<Integer> {

    /**
     * Constructor
     */
    public AllowBubbleProperty() {
        super(3640, "allow-bubble");
    }

    /**
     * {@inheritDoc}
     *  Allows bubble plotting method
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.setBubbleAllowed(value != 0);
        }
    }
}
