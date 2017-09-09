package gensym.charts.properties.annotations;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>show-annotations</b> int property class.
 * Sets annotation visibility
 */
public class ShowAnnotationsProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public ShowAnnotationsProperty() {
        super(3290, "show-annotations");
    }

    /**
     * {@inheritDoc}
     * Sets annotation visibility
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().setAnnotationVisible(value != 0);
        }
    }
}
