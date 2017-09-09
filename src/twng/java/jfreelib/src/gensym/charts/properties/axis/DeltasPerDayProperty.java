package gensym.charts.properties.axis;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>deltas-per-day</b> int property class.
 * Sets delta X value
 */
public class DeltasPerDayProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public DeltasPerDayProperty() {
        super(3097, "deltas-per-day");
    }

    /**
     * {@inheritDoc}
     * Sets delta X value
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.setDeltasPerDay(value);
        }
    }
}
