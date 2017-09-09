package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;
import gensym.charts.PieChart;

/**
 * <b>show-pie-zero-data</b> int property class.
 * Shows labels in pie chart legend even if its values is zero
 */
public class ShowPieZeroDataProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public ShowPieZeroDataProperty() {
        super(10002, "show-pie-zero-data");
    }

    /**
     * {@inheritDoc}
     * Shows/hides labels in pie chart legend even if its values is zero
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof PieChart){
            ((PieChart)chart.getChart()).showPieZeroData(value != 0);
        }
    }
}

