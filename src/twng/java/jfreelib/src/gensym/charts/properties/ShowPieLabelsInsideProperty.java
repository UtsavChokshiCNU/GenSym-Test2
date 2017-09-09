package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;
import gensym.charts.PieChart;

/**
 * <b>show-pie-labels-inside</b> int property class.
 * Show labels inside or outside of Pie Charts
 */
public class ShowPieLabelsInsideProperty extends PropValueBase<Integer> {
    /**
     * Show labels outside of Pie charts
     */
    public static final int SHOW_LABELS_OUTSIDE = 0;

    /**
     * Constructor
     */
    public ShowPieLabelsInsideProperty() {
        super(10001, "show-pie-labels-inside");
    }

    /**
     * {@inheritDoc}
     * Sets showing labels inside of pie chart flag
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
    	((PieChart) chart.getChart()).setShowLabelsInsideOfChart(value != SHOW_LABELS_OUTSIDE);
    }
}
