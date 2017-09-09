package gensym.charts.properties.legends;

import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>show-legend</b> int property class.
 * Sets chart legend visibility
 */
public class ShowLegendProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public ShowLegendProperty() {
        super(2666, "show-legend");
    }

    /**
     * {@inheritDoc}
     * Sets chart legend visibility
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        chart.getChart().showLegend(value != 0);
    }
}
