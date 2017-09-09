package gensym.charts.properties.axis;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>start-time</b> double property class.
 * Sets start time
 */
public class StartTimeProperty extends PropValueBase<Double> {
    /**
     * Constructor
     */
    public StartTimeProperty() {
        super(3098, "start-time");
    }

    /**
     * {@inheritDoc}
     * Sets start time
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Double value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.setStartTime(value);
        }
    }
}
