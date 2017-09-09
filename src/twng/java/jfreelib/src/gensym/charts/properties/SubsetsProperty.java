package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

/**
 * <b>subsets</b> int property class.
 * Sets charts subsets (series) count
 */
public class SubsetsProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public SubsetsProperty() {
        super(2115, "subsets");
    }

    /**
     * {@inheritDoc}
     * Sets charts subsets (series) count
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        chart.getChart().setSeriesCount(value);
    }
}
