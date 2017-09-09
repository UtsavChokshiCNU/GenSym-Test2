package gensym.charts.properties.rotation;

import gensym.charts.Chart3D;
import gensym.charts.JFreeChartHolder;

import gensym.charts.properties.PropValueBase;
import gensym.charts.scrolling.ChartScrolling;

/**
 * <b>degree-of-rotation</b> int property class.
 * This property sets initial rotation angle.
 */
public class DegreeOfRotationProperty extends PropValueBase<Integer> {

    /** Max possible value of this prop */
    public static final int maxValue = 360;
    /** Min possible value of this prop */
    public static final int minValue = 0;

    /**
     * Constructor
     */
    public DegreeOfRotationProperty() {
        super(4001, "degree-of-rotation");
    }

    /**
     * {@inheritDoc}
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof Chart3D) {
            ChartScrolling scroll = ((Chart3D) chart.getChart()).getHorizontalScrollingInterface();
            double updateValue = 0;
            if (value > maxValue || value < minValue) {
                updateValue = minValue;
            } else {
                updateValue = scroll.getScrollItemsCount() * value;
                updateValue /= maxValue - minValue;
            }
            scroll.updateScrollingPos((int) updateValue);
        }
    }
}
