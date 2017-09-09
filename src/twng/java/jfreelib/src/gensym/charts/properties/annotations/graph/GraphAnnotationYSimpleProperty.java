package gensym.charts.properties.annotations.graph;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>graph-annotation-y</b> double property class.
 * Sets graph annotation Y position
 */
public class GraphAnnotationYSimpleProperty extends PropValueBase<Double> {
    /**
     * Constructor
     */
    public GraphAnnotationYSimpleProperty() {
        super(3292, "graph-annotation-y");
    }

    /**
     * {@inheritDoc}
     * Sets graph annotation Y position
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Double value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getGraphAnnotations().getInfo(i).setY(value);
        }
    }
}
