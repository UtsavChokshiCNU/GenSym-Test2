package gensym.charts.properties;

import gensym.charts.actions.IChartAction;
import gensym.charts.JFreeChartHolder;

/**
 * <b>quick-style</b> int property class.
 * Sets bitmap gradient mode flag
 */
public class QuickStyleProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public QuickStyleProperty() {
        super(2672, "quick-style");
    }

    /**
     * {@inheritDoc}
     * Sets bitmap gradient mode flag
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        try {
            chart.getStyle().setStyle(value);
            chart.updateChartStyle();
        } catch (IChartAction.ChartActionException e) {
            // do nothing
        }
    }
}
