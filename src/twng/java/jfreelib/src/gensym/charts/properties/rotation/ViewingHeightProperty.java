package gensym.charts.properties.rotation;

import gensym.charts.Chart3D;
import gensym.charts.JFreeChartHolder;

import gensym.charts.properties.PropValueBase;
import gensym.charts.scrolling.ChartScrolling;

/**
 * <b>viewing-height</b> int property class.
 * This property sets initial rotation angle.
 */
public class ViewingHeightProperty extends PropValueBase<Integer> {

    /** Max possible value of this prop */
    public static final int maxValue = 50;
    /** Min possible value of this prop */
    public static final int minValue = -50;

    /**
     * Constructor
     */
    public ViewingHeightProperty() {
        super(4008, "viewing-height");
    }

    /**
     * {@inheritDoc}
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof Chart3D) {
            ChartScrolling scroll = ((Chart3D) chart.getChart()).getVerticalScrollingInterface();
            double updateValue = 0;
            if (value <= maxValue && value > minValue) {
                updateValue = (0.5D + (double) value / 180) * scroll.getScrollItemsCount();
            }
            scroll.updateScrollingPos((int) updateValue);
        }
    }
}
