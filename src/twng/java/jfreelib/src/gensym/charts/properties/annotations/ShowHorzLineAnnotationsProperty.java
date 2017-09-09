package gensym.charts.properties.annotations;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>show-horz-line-annotations</b> int property class.
 * Sets visibility of horizontal line annotation
 */
public class ShowHorzLineAnnotationsProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public ShowHorzLineAnnotationsProperty() {
        super(3227, "show-horz-line-annotations");
    }

    /**
     * {@inheritDoc}
     * Sets visibility of horizontal line annotation
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().setLineAnnotationsVisible(value != 0);
        }
    }
}
