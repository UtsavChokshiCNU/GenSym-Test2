package gensym.charts.properties.annotations.table;

import java.awt.Color;

import gensym.charts.ChartsCommon;
import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>tacolor</b> int property class.
 * Sets text color of current table annotation cell
 */
public class TaColorProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public TaColorProperty() {
        super(2955, "tacolor");
    }

    /**
     * {@inheritDoc}
     * Sets text color of current table annotation cell
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getCurrentTableAnnotation().setCellTextColor(i, j, new Color(ChartsCommon.convertBGRtoRGB(value)));
        }
    }
}
