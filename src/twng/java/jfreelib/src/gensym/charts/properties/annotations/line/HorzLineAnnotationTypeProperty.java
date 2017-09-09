package gensym.charts.properties.annotations.line;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>horz-line-annotation-type</b> int property class.
 * Sets type of horizontal line annotation
 */
public class HorzLineAnnotationTypeProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public HorzLineAnnotationTypeProperty() {
        super(3216, "horz-line-annotation-type");
    }

    /**
     * {@inheritDoc}
     * Sets type of horizontal line annotation
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getHorizontalLineAnnotations().get(i).setType(value);
        }
    }
}
