package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;
import gensym.charts.SeriesGraph;

/**
 * <b>mark-data-points</b> int property class.
 * This property controls whether data-points are marked with a small circle.
 * HotSpotSize controls size of these marks.
 */
public class MarkDataPointsProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public MarkDataPointsProperty() {
        super(3215, "mark-data-points");
    }

    /**
     * {@inheritDoc}
     *  Do mark or unmark points
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof SeriesGraph) {
            SeriesGraph graph = (SeriesGraph) chart.getChart();
            graph.setMarkDataPoints(value != 0);
        }
    }
}
