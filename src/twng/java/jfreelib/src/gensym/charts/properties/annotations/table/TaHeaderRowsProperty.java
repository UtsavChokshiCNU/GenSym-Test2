package gensym.charts.properties.annotations.table;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>taheader-rows</b> int property class.
 * Sets rows header count of current table annotation
 */
public class TaHeaderRowsProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public TaHeaderRowsProperty() {
        super(2957, "taheader-rows");
    }

    /**
     * {@inheritDoc}
     * Sets columns count of current table annotation
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getCurrentTableAnnotation().setHeaderRows(value);
        }
    }
}
