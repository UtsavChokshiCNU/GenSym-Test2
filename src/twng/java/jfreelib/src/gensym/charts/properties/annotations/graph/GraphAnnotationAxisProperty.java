package gensym.charts.properties.annotations.graph;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>graph-annotation-axis</b> int property class.
 * Sets corresponding axis of graph annotation
 */
public class GraphAnnotationAxisProperty extends PropValueBase<Integer> {
    
    /** Constructor */
    public GraphAnnotationAxisProperty() {
        super(3002, "graph-annotation-axis");
    }

    /**
     * {@inheritDoc}
     * Sets corresponding axis of graph annotation
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getGraphAnnotations().getInfo(i).setAxis(value);
        }
    }

}
