package gensym.charts.properties;

import java.util.List;

import gensym.charts.JFreeChartHolder;
import gensym.charts.ScientificChart;

/**
 * <b>append-ydata</b> double array property class.
 * This property is for transferring new YData into a graph which is being
 * used in a real-time implementation. Existing YData will first be shifted
 * to make room for the new data.
 */
public class AppendYDataProperty extends PropValueBase<List<Double>> {
    /**
     * Constructor
     */
    public AppendYDataProperty() {
        super(3276, "append-ydata");
    }

    /**
     * {@inheritDoc}
     *  Append Y values
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, List<Double> value) {
        if (chart.getChart() instanceof ScientificChart) {
            ScientificChart graph = (ScientificChart) chart.getChart();
            graph.appendValuesY(value);
            chart.updateChartData();
        }
    }
}
