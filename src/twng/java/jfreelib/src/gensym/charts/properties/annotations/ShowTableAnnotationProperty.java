package gensym.charts.properties.annotations;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>show-table-annotation</b> int property class.
 * Sets table annotation visibility
 */
public class ShowTableAnnotationProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public ShowTableAnnotationProperty() {
        super(2968, "show-table-annotation");
    }

    /**
     * {@inheritDoc}
     * Sets table annotation visibility
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().setTableAnnotationsVisible(value != 0);
        }
    }
}
