package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

import org.jfree.ui.RectangleInsets;

/**
 * <b>image-adjust-top</b> int property class.
 * Adjusts chart top
 */
public class ImageAdjustTopProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public ImageAdjustTopProperty() {
        super(2984, "image-adjust-top");
    }

    /**
     * {@inheritDoc}
     * Adjusts chart top
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        RectangleInsets padding = chart.getPadding();
        if (padding == null) {
            chart.setPadding(new RectangleInsets(value, 0, 0, 0));
        } else {
            chart.setPadding(new RectangleInsets(value, padding.getLeft(), padding.getBottom(), padding.getRight()));
        }
    }
}
