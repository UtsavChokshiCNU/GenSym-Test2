package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

/**
 * <b>allow-zooming</b> int property class.
 * Sets zooming flag
 */
public class AllowZoomingProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public AllowZoomingProperty() {
        super(3282, "allow-zooming");
    }

    /**
     * {@inheritDoc}
     * Sets zooming flag
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        chart.setZoomable(value != 0);
    }
}
