package gensym.charts.properties.annotations.graph;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>graph-annotmoveable</b> int property class.
 * Sets graph annotation movable flag
 */
public class GraphAnnotationMoveableProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public GraphAnnotationMoveableProperty() {
        super(2324, "graph-annotmoveable");
    }

    /**
     * {@inheritDoc}
     * Sets graph annotation movable flag
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getGraphAnnotations().setMovable(value != 0);
        }
    }
}
