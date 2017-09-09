package gensym.charts.properties.axis;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>multi-axes-subsets</b> int property class.
 * Sets series count for each axis
 */
public class MultiAxesSubsetsProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public MultiAxesSubsetsProperty() {
        super(3001, "multi-axes-subsets");
    }

    /**
     * {@inheritDoc}
     * Sets series count for each axis
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getPlot().setPlotSeries(i, value);
        }
    }
}
