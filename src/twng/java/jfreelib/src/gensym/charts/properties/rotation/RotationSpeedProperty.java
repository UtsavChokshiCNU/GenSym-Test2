package gensym.charts.properties.rotation;

import gensym.charts.Chart3D;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>rotation-speed</b> int property class.
 * This property sets auto rotation speed
 */
public class RotationSpeedProperty extends PropValueBase<Integer> {

    /** Max possible value of this prop */
    public static final int maxValue = 32000;
    /** Min possible value of this prop */
    public static final int minValue = 1;
    /** Default value of this prop */
    public static final int defaultValue = 1000;

    /**
     * Constructor
     */
    public RotationSpeedProperty() {
        super(4011, "rotation-speed");
    }

    /**
     * {@inheritDoc}
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof Chart3D) {
            ((Chart3D) chart.getChart()).getAutoRotation().
                    setSpeed(value > maxValue || value < minValue ? defaultValue : value);
        }
    }
}
