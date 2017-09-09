package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

/**
 * <b>subset-labels</b> string property class.
 * Sets subset (series) label
 */
public class SubsetLabelProperty extends PropValueBase<String> {
    /**
     * Constructor
     */
    public SubsetLabelProperty() {
        super(2125, "subset-labels");
    }

    /**
     * {@inheritDoc}
     * Sets subset (series) label
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, String value) {
        chart.getChart().setSeriesLabel(i, value);
    }
}
