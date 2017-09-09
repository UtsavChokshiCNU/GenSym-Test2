package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

/**
 * <b>null-data-value</b> double property class.
 * Sets Y axis null data value
 */
public class NullDataValueProperty extends PropValueBase<Double> {
    /**
     * Constructor
     */
    public NullDataValueProperty() {
        super(3268, "null-data-value");
    }

    /**
     * {@inheritDoc}
     * Sets Y axis null data value
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Double value) {
        chart.getChart().setNullDataValueY(value.doubleValue());
    }
}
