package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

/**
 * <b>xdata</b> double property class.
 * Sets X points value.
 */
public class XDataSimpleProperty extends PropValueBase<Double> {

    /**
     * Constructor
     */
    public XDataSimpleProperty() {
        super(2135, "xdata");
    }

    /**
     * {@inheritDoc}
     * Sets X points value.
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Double value) {
        chart.getChart().setValueX(i, j, value);
        chart.updateChartData();
    }
}
