package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

/**
 * <b>ydata</b> double property class.
 * Sets Y points value.
 */
public class YDataSimpleProperty extends PropValueBase<Double> {
    /**
     * Constructor
     */
    public YDataSimpleProperty() {
        super(2140, "ydata");
    }

    /**
     * {@inheritDoc}
     * Sets Y points value.
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Double value) {
        chart.getChart().setValueY(i, j, value);
        chart.updateChartData();
    }
}
