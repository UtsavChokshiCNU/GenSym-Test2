package gensym.charts.properties.legends;

import gensym.charts.PieChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;


/**
 * <b>show-pie-legend</b> int property class.
 * Shows pie chart legend 
 */
public class ShowPieLegendProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public ShowPieLegendProperty() {
        super(3922, "show-pie-legend");
    }

    /**
     * {@inheritDoc}
     * Shows pie chart legend
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof PieChart) {
            chart.getChart().showLegend(value != 0);
        }
    }
}

