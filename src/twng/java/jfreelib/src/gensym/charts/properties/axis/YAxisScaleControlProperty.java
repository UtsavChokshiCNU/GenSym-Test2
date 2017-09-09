package gensym.charts.properties.axis;

import gensym.charts.JFreeChartHolder;
import gensym.charts.ScientificChart;
import gensym.charts.axis.GraphAxesProvider;
import gensym.charts.properties.PropValueBase;


/**
 * <b>y-axis-scale-control</b> Integer property class.
 * This property sets Y axis scale control method
 */
public class YAxisScaleControlProperty extends PropValueBase<Integer> {
    
    /**
     * Constructor
     */
    public YAxisScaleControlProperty() {
        super(3045, "y-axis-scale-control");
    }

    /**
     * {@inheritDoc}
     * Sets Y axis scale control method
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof ScientificChart) {
            ScientificChart graph = (ScientificChart) chart.getChart();
            GraphAxesProvider provider = new GraphAxesProvider();
            provider.createAxisByScaleControl(graph, value, GraphAxesProvider.AXIS_Y);
        }
    }

}