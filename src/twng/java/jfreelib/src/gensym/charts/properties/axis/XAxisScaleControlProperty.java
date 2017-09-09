package gensym.charts.properties.axis;

import gensym.charts.JFreeChartHolder;
import gensym.charts.ScientificChart;
import gensym.charts.axis.GraphAxesProvider;
import gensym.charts.properties.PropValueBase;


/**
 * <b>x-axis-scale-control</b> Integer property class.
 * This property sets X axis scale control method
 */
public class XAxisScaleControlProperty extends PropValueBase<Integer> {
    
    /**
     * Constructor
     */
    public XAxisScaleControlProperty() {
        super(3610, "x-axis-scale-control");
    }

    /**
     * {@inheritDoc}
     * Sets X axis scale control method
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof ScientificChart) {
            ScientificChart graph = (ScientificChart) chart.getChart();
            GraphAxesProvider provider = new GraphAxesProvider();
            provider.createAxisByScaleControl(graph, value, GraphAxesProvider.AXIS_X);
        }
    }
}
