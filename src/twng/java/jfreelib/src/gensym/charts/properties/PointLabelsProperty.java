package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

/**
 * <b>point-labels</b> string property class.
 * Sets points labels
 */
public class PointLabelsProperty extends PropValueBase<String> {
    /**
     * Constructor
     */
    public PointLabelsProperty() {
        super(2130, "point-labels");
    }

    /**
     * {@inheritDoc}
     * Sets chart title
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, String value) {
        chart.getChart().setPointLabel(i, value);
    }
}
