package gensym.charts.properties;

import java.util.List;

import gensym.charts.JFreeChartHolder;
import gensym.charts.ScientificChart;

/**
 * <b>append-xdata</b> double array property class.
 * This property is for transferring new XData into a Scientific Graph Object
 * which is being used in a real-time implementation.
 * Existing XData will first be shifted to make room for the new data.
 */
public class AppendXDataProperty extends PropValueBase<List<Double>> {
    /**
     * Constructor
     */
    public AppendXDataProperty() {
        super(3658, "append-xdata");
    }

    /**
     * {@inheritDoc}
     *  Append X values
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, List<Double> value) {
        if (chart.getChart() instanceof ScientificChart) {
            ScientificChart graph = (ScientificChart) chart.getChart();
            graph.appendValuesX(value);
            chart.updateChartData();
        }
    }
}
