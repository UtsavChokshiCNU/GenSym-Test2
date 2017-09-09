package gensym.charts.properties.annotations.graph;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>graph-annotation-text-size</b> int property class.
 * Sets graph annotation text size
 */
public class GraphAnnotationTextSizeProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public GraphAnnotationTextSizeProperty() {
        super(3242, "graph-annotation-text-size");
    }

    /**
     * {@inheritDoc}
     * Sets graph annotation text size
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getGraphAnnotations().setTextSize(value);
        }
    }
}
