package gensym.charts.properties.axis;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>force-vertical-points</b> int property class.
 * Sets the flag that controls whether the tick labels are displayed vertically.
 */
public class ForceVerticalPointsProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public ForceVerticalPointsProperty() {
        super(3345, "force-vertical-points");
    }

    /**
     * {@inheritDoc}
     * Sets the flag that controls whether the tick labels are displayed vertically.
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart sChart = (GraphChart) chart.getChart();
            sChart.showPointsVertically(value == 1); // PEFVP_VERT
        }
    }
}
