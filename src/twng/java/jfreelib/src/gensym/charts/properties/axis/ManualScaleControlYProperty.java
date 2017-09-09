package gensym.charts.properties.axis;

import org.jfree.chart.axis.ValueAxis;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>manual-scale-controly</b> int property class.
 */
public class ManualScaleControlYProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public ManualScaleControlYProperty() {
        super(3050, "manual-scale-controly");
    }

    /**
     * {@inheritDoc}
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            ValueAxis axis = graph.getPlot().getCurrentAxis();
            if (axis != null) {
                axis.setAutoRange(value != 3); // PEMSC_MINMAX
            }
        }
    }
}
