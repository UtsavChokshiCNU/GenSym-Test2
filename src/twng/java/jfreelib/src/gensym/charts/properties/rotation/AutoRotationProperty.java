package gensym.charts.properties.rotation;

import gensym.charts.Chart3D;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>auto-rotation</b> int property class.
 * This property enable/disable auto rotation
 */
public class AutoRotationProperty extends PropValueBase<Integer> {

    /**
     * Constructor
     */
    public AutoRotationProperty() {
        super(4003, "auto-rotation");
    }

    /**
     * {@inheritDoc}
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof Chart3D) {
            ((Chart3D)chart.getChart()).setAutoRotation(value != 0);
        }
    }
}
