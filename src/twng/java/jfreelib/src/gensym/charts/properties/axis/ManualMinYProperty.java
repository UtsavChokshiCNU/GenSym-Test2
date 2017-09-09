package gensym.charts.properties.axis;

import org.jfree.chart.axis.ValueAxis;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>manual-min-y</b> double property class.
 */
public class ManualMinYProperty extends PropValueBase<Double> {
    /**
     * Constructor
     */
    public ManualMinYProperty() {
        super(3055, "manual-min-y");
    }

    /**
     * {@inheritDoc}
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Double value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            ValueAxis axis = graph.getPlot().getCurrentAxis();
            if (axis != null) {
                axis.setLowerBound(value);
            }
        }
    }
}
