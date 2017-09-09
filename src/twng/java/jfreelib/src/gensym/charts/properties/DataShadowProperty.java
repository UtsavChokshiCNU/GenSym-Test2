package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

/**
 * <b>data-shadows</b> int property class.
 * Sets data shadowing
 */
public class DataShadowProperty extends PropValueBase<Integer> {
    /**
     * No Shadow or 3D effect
     */
    public static final int SHADOW_NONE = 0;
    
    /**
     * Shadow effect
     */
    public static final int SHADOW_SHADOWS = 1;

    /**
     * 3D effect
     */
    public static final int SHADOW_3D = 2;

    /**
     * Constructor
     */
    public DataShadowProperty() {
        super(2240, "data-shadows");
    }

    /**
     * {@inheritDoc}
     * Sets data shadowing
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        chart.getChart().setDataShadows(value == SHADOW_SHADOWS, value == SHADOW_3D);
    }
}
