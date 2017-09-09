package gensym.charts.properties.annotations.graph;

import java.util.List;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.annotations.graph.AnnotationFactory;
import gensym.charts.properties.PropValueBase;

/**
 * <b>graph-annotation-x</b> double array property class.
 * Sets graph annotation X position
 */
public class GraphAnnotationXProperty extends PropValueBase<List<Double>> {
    /**
     * Constructor
     */
    public GraphAnnotationXProperty() {
        super(3291, "graph-annotation-x");
    }

    /**
     * {@inheritDoc}
     * Sets graph annotation X position
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, List<Double> value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            AnnotationFactory annotations = graph.getAnnotations().getGraphAnnotations();
            int index = 0;
            for (double position : value) {
                annotations.getInfo(index++).setX(position);
            }
        }
    }
}
