package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

/**
 * <b>subset-line-types</b> int property class.
 * Sets chart line type
 */
public class SubsetLineTypesProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public SubsetLineTypesProperty() {
        super(3271, "subset-line-types");
    }

    /**
     * {@inheritDoc}
     * Sets chart line type
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        chart.getChart().setSeriesLineType(i, value);
    }
}
