package gensym.charts.properties.gradients;

import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>bitmap-gradient-mode</b> int property class.
 * Sets bitmap gradient mode flag
 */
public class BitmapGradientModeProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public BitmapGradientModeProperty() {
        super(2703, "bitmap-gradient-mode");
    }

    /**
     * {@inheritDoc}
     * Sets bitmap gradient mode flag
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        chart.getStyle().setGradientMode(value != 0);
        chart.updateChartStyle();
    }
}
