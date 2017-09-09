package gensym.charts.properties.annotations.line;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>line-annotation-text-size</b> int property class.
 * Sets text size for horizontal line annotation
 */
public class LineAnnotationTextSizeProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public LineAnnotationTextSizeProperty() {
        super(3244, "line-annotation-text-size");
    }

    /**
     * {@inheritDoc}
     * Sets text size for horizontal line annotation
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getHorizontalLineAnnotations().setTextSize(value);
        }
    }
}
