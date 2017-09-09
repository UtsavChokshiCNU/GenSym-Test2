package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

import java.util.List;

/**
 * <b>ydata</b> double array property class.
 * Sets Y points value.
 */
public class YDataProperty extends PropValueBase<List<Double>> {

    /**
     * Constructor
     */
    public YDataProperty() {
        super(2140, "ydata");
    }

    /**
     * {@inheritDoc}
     * Sets Y points value.
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, List<Double> value) {
        chart.getChart().setValuesY(value);
        chart.updateChartData();
    }
}
