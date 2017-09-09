package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

import java.util.List;

/**
 * <b>xdata</b> double array property class.
 * Sets X points value.
 */
public class XDataProperty extends PropValueBase<List<Double>> {

    /**
     * Constructor
     */
    public XDataProperty() {
        super(2135, "xdata");
    }

    /**
     * {@inheritDoc}
     * Sets X points value.
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, List<Double> value) {
        chart.getChart().setValuesX(value);
        chart.updateChartData();
    }
}
