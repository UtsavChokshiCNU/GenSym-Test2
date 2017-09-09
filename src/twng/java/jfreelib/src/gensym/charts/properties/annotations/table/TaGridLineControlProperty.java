package gensym.charts.properties.annotations.table;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>ta-grid-line-control</b> int property class.
 * Sets grid line view of table annotation
 */
public class TaGridLineControlProperty extends PropValueBase<Integer> {
    /**
     * No grid lines
     */
    public static final int SHOW_NONE = 0;

    /**
     * Horizontal grid lines
     */
    public static final int SHOW_HORIZONTAL = 1;

    /**
     * Vertical grid lines
     */
    public static final int SHOW_VERTICAL = 2;

    /**
     * Both Horizontal and Vertical grid lines
     */
    public static final int SHOW_BOTH = 3;

    /**
     * Constructor
     */
    public TaGridLineControlProperty() {
        super(2967, "ta-grid-line-control");
    }

    /**
     * {@inheritDoc}
     * Sets grid line view of table annotation
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();

            graph.getAnnotations().getCurrentTableAnnotation().setShowHorizontalLines(value == SHOW_HORIZONTAL || value == SHOW_BOTH);
            graph.getAnnotations().getCurrentTableAnnotation().setShowVerticalLines(value == SHOW_VERTICAL || value == SHOW_BOTH);
        }
    }
}
