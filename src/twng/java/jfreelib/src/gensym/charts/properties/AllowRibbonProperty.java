package gensym.charts.properties;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;

/**
 * <b>allow-ribbon</b> int property class.
 * Allows Ribbon plotting method
 */
public class AllowRibbonProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public AllowRibbonProperty() {
        super(3091, "allow-ribbon");
    }

    /**
     * {@inheritDoc}
     *  Allows Ribbon plotting method
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.setRibbonAllowed(value != 0);
        }
    }
}
