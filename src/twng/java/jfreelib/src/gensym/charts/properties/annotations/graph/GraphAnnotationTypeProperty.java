package gensym.charts.properties.annotations.graph;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>graph-annotation-type</b> int property class.
 * Sets graph annotation type
 */
public class GraphAnnotationTypeProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public GraphAnnotationTypeProperty() {
        super(3246, "graph-annotation-type");
    }

    /**
     * {@inheritDoc}
     * Sets graph annotation type
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getGraphAnnotations().getInfo(i).setType(value);
        }
    }
}
