package gensym.charts.properties.axis;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>working-axis</b> int property class.
 * Sets working axis
 */
public class WorkingAxisProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public WorkingAxisProperty() {
        super(3006, "working-axis");
    }

    /**
     * {@inheritDoc}
     * Sets working axis
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getPlot().setWorkingAxis(value);
        }
    }
}
