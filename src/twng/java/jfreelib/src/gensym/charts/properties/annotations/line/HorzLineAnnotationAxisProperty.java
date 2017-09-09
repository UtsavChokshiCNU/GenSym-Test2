package gensym.charts.properties.annotations.line;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>horz-line-annotation-axis</b> int property class.
 * Sets corresponding axis of horizontal line annotation
 */
public class HorzLineAnnotationAxisProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public HorzLineAnnotationAxisProperty() {
        super(3003, "horz-line-annotation-axis");
    }

    /**
     * {@inheritDoc}
     * Sets corresponding axis of horizontal line annotation
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getHorizontalLineAnnotations().get(i).setAxis(value);
        }
    }
}
