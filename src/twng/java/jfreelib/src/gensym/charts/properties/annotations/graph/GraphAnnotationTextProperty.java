package gensym.charts.properties.annotations.graph;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>graph-annotation-text</b> string property class.
 * Sets graph annotation text
 */
public class GraphAnnotationTextProperty extends PropValueBase<String> {
    /**
     * Constructor
     */
    public GraphAnnotationTextProperty() {
        super(3293, "graph-annotation-text");
    }

    /**
     * {@inheritDoc}
     * Sets graph annotation text
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, String value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getGraphAnnotations().getInfo(i).setText(value);
        }
    }
}
