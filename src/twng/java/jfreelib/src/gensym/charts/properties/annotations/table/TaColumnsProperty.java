package gensym.charts.properties.annotations.table;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>tacolumns</b> int property class.
 * Sets columns count of current table annotation
 */
public class TaColumnsProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public TaColumnsProperty() {
        super(2952, "tacolumns");
    }

    /**
     * {@inheritDoc}
     * Sets columns count of current table annotation
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getCurrentTableAnnotation().setColumnsCount(value);
        }
    }
}
