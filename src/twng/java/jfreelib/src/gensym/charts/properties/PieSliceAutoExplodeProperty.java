package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;
import gensym.charts.PieChart;

/**
 * <b>auto-explode</b> int property class.
 * This property controls whether the Pie Chart will automatically explode 
 * pie slices when a point-label is double clicked
 */
public class PieSliceAutoExplodeProperty extends PropValueBase<Integer> {

    /**
     * Constructor of PieChart slice auto-explode property
     */
    public PieSliceAutoExplodeProperty() {
        super(3920, "auto-explode");
    }
    
    /**
     * {@inheritDoc}
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof PieChart) {
            PieChart pie = (PieChart) chart.getChart();
            pie.setSlicesAutoExplode(value);
        }
    }
}
