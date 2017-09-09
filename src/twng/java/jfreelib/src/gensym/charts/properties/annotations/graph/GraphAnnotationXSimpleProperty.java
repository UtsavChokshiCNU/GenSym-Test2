package gensym.charts.properties.annotations.graph;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>graph-annotation-x</b> double property class.
 * Sets graph annotation X position
 */
public class GraphAnnotationXSimpleProperty extends PropValueBase<Double> {
    /**
     * Constructor
     */
    public GraphAnnotationXSimpleProperty() {
        super(3291, "graph-annotation-x");
    }

    /**
     * {@inheritDoc}
     * Sets graph annotation X position
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Double value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getGraphAnnotations().getInfo(i).setX(value);
        }
    }
}
