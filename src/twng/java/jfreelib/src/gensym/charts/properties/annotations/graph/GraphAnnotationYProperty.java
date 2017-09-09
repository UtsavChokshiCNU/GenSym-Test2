package gensym.charts.properties.annotations.graph;

import java.util.List;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.annotations.graph.AnnotationFactory;
import gensym.charts.properties.PropValueBase;

/**
 * <b>graph-annotation-y</b> double array property class.
 * Sets graph annotation Y position
 */
public class GraphAnnotationYProperty extends PropValueBase<List<Double>> {
    /**
     * Constructor
     */
    public GraphAnnotationYProperty() {
        super(3292, "graph-annotation-y");
    }

    /**
     * {@inheritDoc}
     * Sets graph annotation Y position
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, List<Double> value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            AnnotationFactory annotations = graph.getAnnotations().getGraphAnnotations();
            int index = 0;
            for (double position : value) {
                annotations.getInfo(index++).setY(position);
            }
        }
    }
}
