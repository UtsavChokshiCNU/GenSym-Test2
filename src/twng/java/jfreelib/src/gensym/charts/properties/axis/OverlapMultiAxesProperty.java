package gensym.charts.properties.axis;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>overlap-multi-axes</b> int property class.
 * Sets axes count for each axis set
 */
public class OverlapMultiAxesProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public OverlapMultiAxesProperty() {
        super(3059, "overlap-multi-axes");
    }

    /**
     * {@inheritDoc}
     * Sets axes count for each axis set
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getPlot().overlapAxes(i, value);
        }
    }
}
