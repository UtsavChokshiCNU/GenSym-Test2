package gensym.charts.properties.annotations.table;

import java.awt.Color;

import gensym.charts.ChartsCommon;
import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>taback-color</b> int property class.
 * Sets text color of current table annotation cell
 */
public class TaBackColorProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public TaBackColorProperty() {
        super(2963, "taback-color");
    }

    /**
     * {@inheritDoc}
     * Sets text color of current table annotation cell
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getCurrentTableAnnotation().setCellBackColor(i, j, new Color(ChartsCommon.convertBGRtoRGB(value)));
        }
    }
}
