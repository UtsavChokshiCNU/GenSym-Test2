package gensym.charts.properties;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;

/**
 * <b>scrolling-subsets</b> int property class.
 * Sets count of scrolling subsets.
 */
public class ScrolingSubsetsProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public ScrolingSubsetsProperty() {
        super(3070, "scrolling-subsets");
    }

    /**
     * {@inheritDoc}
     * Sets count of scrolling subsets.
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getSeriesScrolling().setScrollingItems(value, false);
            chart.updateScrolls();
        }
    }
}
