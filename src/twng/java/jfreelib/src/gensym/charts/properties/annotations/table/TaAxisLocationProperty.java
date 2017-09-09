package gensym.charts.properties.annotations.table;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>taaxis-location</b> int property class.
 * Sets axis location of current table annotation
 */
public class TaAxisLocationProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public TaAxisLocationProperty() {
        super(2966, "taaxis-location");
    }

    /**
     * {@inheritDoc}
     * Sets axis location of current table annotation
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getCurrentTableAnnotation().setAxisLocation(value);
        }
    }
}
