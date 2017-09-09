package gensym.charts.properties.gradients;

import gensym.charts.properties.PropValueBase;
import gensym.charts.JFreeChartHolder;

/**
 * Sets chart desk gradient style
 * <b>desk-gradient-style</b> int property class.
 */
public class DeskGradientStyleProperty extends PropValueBase<Integer>{
    /**
     * Constructor
     */
    public DeskGradientStyleProperty() {
        super(2689, "desk-gradient-style");
    }

    /**
     * {@inheritDoc}
     * Sets chart desk gradient style
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        chart.getStyle().getGradients().setDeskGradientStyle(value);
        chart.updateChartStyle();
    }
}
