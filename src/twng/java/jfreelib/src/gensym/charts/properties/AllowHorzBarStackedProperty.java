package gensym.charts.properties;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;

/**
 * <b>allow-horz-bar-stacked</b> int property class.
 * Allows horizontal bar stacking
 */
public class AllowHorzBarStackedProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public AllowHorzBarStackedProperty() {
        super(3419, "allow-horz-bar-stacked");
    }

    /**
     * {@inheritDoc}
     *  Allows horizontal bar stacking
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.setHorzBarStackedAllowed(value != 0);
        }
    }
}
