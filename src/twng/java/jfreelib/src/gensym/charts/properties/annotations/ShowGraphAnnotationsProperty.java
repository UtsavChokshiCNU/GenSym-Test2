package gensym.charts.properties.annotations;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>show-graph-annotations</b> int property class.
 * Sets graph annotation visibility
 */
public class ShowGraphAnnotationsProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public ShowGraphAnnotationsProperty() {
        super(3223, "show-graph-annotations");
    }

    /**
     * {@inheritDoc}
     * Sets graph annotation visibility
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().setGraphAnnotationsVisible(value != 0);
        }
    }
}
