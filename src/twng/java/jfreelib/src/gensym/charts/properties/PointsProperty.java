package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

/**
 * <b>points</b> int property class.
 * Sets point count per each subset (series)
 */
public class PointsProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public PointsProperty() {
        super(2120, "points");
    }

    /**
     * {@inheritDoc}
     * Sets point count per each subset (series)
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        chart.getChart().setItemCount(value);
    }
}
