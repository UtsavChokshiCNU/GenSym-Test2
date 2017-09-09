package gensym.charts.properties.annotations.table;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>talocation</b> int property class.
 * Sets location of current table annotation
 */
public class TaLocationProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public TaLocationProperty() {
        super(2961, "talocation");
    }

    /**
     * {@inheritDoc}
     * Sets location of current table annotation
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getCurrentTableAnnotation().setPosition(value);
        }
    }
}
