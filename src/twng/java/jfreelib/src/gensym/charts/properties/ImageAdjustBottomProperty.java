package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

import org.jfree.ui.RectangleInsets;

/**
 * <b>image-adjust-bottom</b> int property class.
 * Adjusts chart bottom
 */
public class ImageAdjustBottomProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public ImageAdjustBottomProperty() {
        super(2985, "image-adjust-bottom");
    }

    /**
     * {@inheritDoc}
     * Adjusts chart bottom
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        RectangleInsets padding = chart.getPadding();
        if (padding == null) {
            chart.setPadding(new RectangleInsets(0, 0, value, 0));
        } else {
            chart.setPadding(new RectangleInsets(padding.getTop(), padding.getLeft(), value, padding.getRight()));
        }
    }
}
