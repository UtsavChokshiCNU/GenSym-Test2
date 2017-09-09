package gensym.charts.properties.annotations.line;

import java.util.List;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.annotations.line.LineAnnotationFactory;
import gensym.charts.properties.PropValueBase;

/**
 * <b>horz-line-annotation</b> double property class.
 * Sets position of horizontal line annotation
 */
public class HorzLineAnnotationProperty extends PropValueBase<List<Double>> {
    /**
     * Constructor
     */
    public HorzLineAnnotationProperty() {
        super(3213, "horz-line-annotation");
    }

    /**
     * {@inheritDoc}
     * Sets position of horizontal line annotation
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, List<Double> value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            LineAnnotationFactory annotations = graph.getAnnotations().getHorizontalLineAnnotations();
            
            int index = 0;
            for (double position : value) {
                annotations.get(index++).setPosition(position);
            }
        }
    }
}
