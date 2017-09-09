package gensym.charts.properties;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;

/**
 * <b>allow-step</b> int property class.
 * Allows Step plotting method
 */
public class AllowStepProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public AllowStepProperty() {
        super(3067, "allow-step");
    }

    /**
     * {@inheritDoc}
     *  Allows Step plotting method
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.setStepAllowed(value != 0);
        }
    }
}
