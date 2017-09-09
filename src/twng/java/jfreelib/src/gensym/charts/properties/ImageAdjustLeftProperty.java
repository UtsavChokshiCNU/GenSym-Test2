package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

import org.jfree.ui.RectangleInsets;

/**
 * <b>image-adjust-left</b> int property class.
 * Adjusts chart left
 */
public class ImageAdjustLeftProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public ImageAdjustLeftProperty() {
        super(2982, "image-adjust-left");
    }

    /**
     * {@inheritDoc}
     * Adjusts chart left
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        RectangleInsets padding = chart.getPadding();
        if (padding == null) {
            chart.setPadding(new RectangleInsets(0, value, 0, 0));
        } else {
            chart.setPadding(new RectangleInsets(padding.getTop(), value, padding.getBottom(), padding.getRight()));
        }
    }
}
