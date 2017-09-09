package gensym.charts.properties.annotations.table;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>taheader-column</b> int property class.
 * Sets columns header of current table annotation
 */
public class TaHeaderColumnProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public TaHeaderColumnProperty() {
        super(2958, "taheader-column");
    }

    /**
     * {@inheritDoc}
     * Sets columns header of current table annotation
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getCurrentTableAnnotation().setHeaderColumns(value != 0 ? 1 : 0);
        }
    }
}
