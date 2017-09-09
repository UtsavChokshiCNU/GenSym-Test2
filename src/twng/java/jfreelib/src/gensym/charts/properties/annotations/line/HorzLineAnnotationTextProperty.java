package gensym.charts.properties.annotations.line;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>horz-line-annotation-text</b> string property class.
 * Sets text of horizontal line annotation
 */
public class HorzLineAnnotationTextProperty extends PropValueBase<String> {
    /**
     * Constructor
     */
    public HorzLineAnnotationTextProperty() {
        super(3214, "horz-line-annotation-text");
    }

    /**
     * {@inheritDoc}
     * Sets text of horizontal line annotation
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, String value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getHorizontalLineAnnotations().get(i).setText(value);
        }
    }
}
