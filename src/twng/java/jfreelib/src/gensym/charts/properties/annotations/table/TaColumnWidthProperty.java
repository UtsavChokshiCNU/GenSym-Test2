package gensym.charts.properties.annotations.table;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>tacolumn-width</b> int property class.
 * Sets width of current table annotation column
 */
public class TaColumnWidthProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public TaColumnWidthProperty() {
        super(2959, "tacolumn-width");
    }

    /**
     * {@inheritDoc}
     * Sets width of current table annotation column
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getCurrentTableAnnotation().setColumnWidth(i, value);
        }
    }
}
