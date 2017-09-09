package gensym.charts.properties.axis;

import org.jfree.chart.axis.ValueAxis;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>manual-max-y</b> double property class.
 */
public class ManualMaxYProperty extends PropValueBase<Double> {
    /**
     * Constructor
     */
    public ManualMaxYProperty() {
        super(3060, "manual-max-y");
    }

    /**
     * {@inheritDoc}
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Double value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            ValueAxis axis = graph.getPlot().getCurrentAxis();
            if (axis != null) {
                axis.setUpperBound(value);
            }
        }
    }
}
