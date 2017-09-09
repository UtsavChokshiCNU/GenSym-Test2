package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

/**
 * <b>null-data-gaps</b> int property class.
 * Sets null data value gaps flag
 */
public class NullDataGapsProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public NullDataGapsProperty() {
        super(3066, "null-data-gaps");
    }

    /**
     * {@inheritDoc}
     * Sets null data value gaps flag
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        chart.getChart().setNullDataGaps(value != 0);
    }
}
