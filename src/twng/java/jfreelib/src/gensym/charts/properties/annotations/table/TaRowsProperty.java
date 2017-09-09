package gensym.charts.properties.annotations.table;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>tarows</b> int property class.
 * Sets rows count of current table annotation
 */
public class TaRowsProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public TaRowsProperty() {
        super(2951, "tarows");
    }

    /**
     * {@inheritDoc}
     * Sets columns count of current table annotation
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getCurrentTableAnnotation().setRowsCount(value);
        }
    }
}
