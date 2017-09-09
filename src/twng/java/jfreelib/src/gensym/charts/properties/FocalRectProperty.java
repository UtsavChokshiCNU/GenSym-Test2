package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

import org.jfree.chart.JFreeChart;

/**
 * <b>focal-rect</b> int property class.
 * This property controls whether the control will have a focal rect or not.
 * A focal rect is a bounding rectangle surrounding the control to signify that
 * it owns the keyboard/mouse focus. This is similar to the bold effect around
 * standard Windows buttons.
 */
public class FocalRectProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public FocalRectProperty() {
        super(2632, "focal-rect");
    }

    /**
     * {@inheritDoc}
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        for (JFreeChart jchart : chart.getChart().getCharts()) {
            jchart.setBorderVisible(value != 0);
        }
    }
}
