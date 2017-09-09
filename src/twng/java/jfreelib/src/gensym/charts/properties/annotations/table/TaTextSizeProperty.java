package gensym.charts.properties.annotations.table;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>tatext-size</b> int property class.
 * Sets graph annotation text size
 */
public class TaTextSizeProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public TaTextSizeProperty() {
        super(2965, "tatext-size");
    }

    /**
     * {@inheritDoc}
     * Sets graph annotation text size
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getCurrentTableAnnotation().setTextSize(value);
        }
    }
}
