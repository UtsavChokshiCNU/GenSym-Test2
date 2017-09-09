package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;
import gensym.charts.PieChart;

/**
 * <b>enable-pie-tooltips</b> int property class.
 * Enable tooltips on pie charts
 */
public class EnablePieTooltipsProperty extends PropValueBase<Integer> {
    /**
     * Disable ToolTips showing on charts
     */
    public static final int DISABLE_TOOLTIPS = 0;

    /**
     * Constructor
     */
    public EnablePieTooltipsProperty() {
        super(10000, "enable-pie-tooltips");
    }

    /**
     * {@inheritDoc}
     * Sets toolTips showing flag
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof PieChart) {
            ((PieChart) chart.getChart()).setTooltipsEnabled(value != DISABLE_TOOLTIPS);
        }
    } 
}
