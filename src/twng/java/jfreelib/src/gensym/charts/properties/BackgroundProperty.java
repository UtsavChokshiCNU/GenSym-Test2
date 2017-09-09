package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;
import gensym.charts.ChartsCommon;
import java.awt.Color;

/**
 * Sets chart background color
 * <b>graph-back-color</b> int property class.
 */
public class BackgroundProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public BackgroundProperty() {
        super(2340, "graph-back-color");
    }

    /**
     * {@inheritDoc}
     * Sets chart background
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        chart.getStyle().setPlotColor(new Color(ChartsCommon.convertBGRtoRGB(value)));
        chart.updateChartStyle();
    }
}
