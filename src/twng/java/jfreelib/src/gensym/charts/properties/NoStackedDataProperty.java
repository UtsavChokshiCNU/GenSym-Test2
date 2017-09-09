package gensym.charts.properties;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;

/**
 * <b>no-stacked-data</b> int property class.
 * Disables bar stacking
 */
public class NoStackedDataProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public NoStackedDataProperty() {
        super(3305, "no-stacked-data");
    }

    /**
     * {@inheritDoc}
     *  Disables bar stacking
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.setStackedDataAllowed(value == 0);
        }
    }
}
