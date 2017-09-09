package gensym.charts.properties.axis;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>delta-x</b> int property class.
 * Sets delta X value
 */
public class DeltaXProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public DeltaXProperty() {
        super(3096, "delta-x");
    }

    /**
     * {@inheritDoc}
     * Sets delta X value
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.setDeltaX(value);
        }
    }
}
