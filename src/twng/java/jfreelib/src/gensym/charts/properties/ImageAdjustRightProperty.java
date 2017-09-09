package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

import org.jfree.ui.RectangleInsets;

/**
 * <b>image-adjust-right</b> int property class.
 * Adjusts chart right
 */
public class ImageAdjustRightProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public ImageAdjustRightProperty() {
        super(2983, "image-adjust-right");
    }

    /**
     * {@inheritDoc}
     * Adjusts chart right
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        RectangleInsets padding = chart.getPadding();
        if (padding == null) {
            chart.setPadding(new RectangleInsets(0, 0, 0, value));
        } else {
            chart.setPadding(new RectangleInsets(padding.getTop(), padding.getLeft(), padding.getBottom(), value));
        }
    }
}
