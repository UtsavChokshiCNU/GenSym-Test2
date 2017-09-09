package gensym.charts.properties.annotations.table;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>tatext</b> string property class.
 * Sets text of current table annotation cell
 */
public class TaTextProperty extends PropValueBase<String> {
    /**
     * Constructor
     */
    public TaTextProperty() {
        super(2954, "tatext");
    }

    /**
     * {@inheritDoc}
     * Sets text of current table annotation cell
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, String value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            if (j == -1) {
                j = i;
                i = 0;
            }
            graph.getAnnotations().getCurrentTableAnnotation().setCellText(i, j, value);
        }
    }
}
