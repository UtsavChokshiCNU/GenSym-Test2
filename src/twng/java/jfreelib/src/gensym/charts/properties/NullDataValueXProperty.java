package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

/**
 * <b>null-data-value-x</b> double property class.
 * Sets X axis null data value
 */
public class NullDataValueXProperty extends PropValueBase<Double> {
    /**
     * Constructor
     */
    public NullDataValueXProperty() {
        super(3656, "null-data-value-x");
    }

    /**
     * {@inheritDoc}
     * Sets X axis null data value
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Double value) {
        chart.getChart().setNullDataValueX(value.doubleValue());
    }
}
