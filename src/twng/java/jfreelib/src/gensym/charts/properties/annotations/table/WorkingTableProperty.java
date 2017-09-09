package gensym.charts.properties.annotations.table;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>working-table</b> int property class.
 * Sets current table annotation ID
 */
public class WorkingTableProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public WorkingTableProperty() {
        super(2977, "working-table");
    }

    /**
     * {@inheritDoc}
     * Sets current table annotation ID
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().setCurrentTableAnnotation(value);
        }
    }
}
