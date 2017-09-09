package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

/**
 * <b>border-types</b> int property class.
 * Sets border types
 */
public class BorderTypesProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public BorderTypesProperty() {
        super(2943, "border-types");
    }

    /**
     * {@inheritDoc}
     *  Sets border types
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        chart.getStyle().setBorderStyle(value);
        chart.updateChartStyle();
    }
}
