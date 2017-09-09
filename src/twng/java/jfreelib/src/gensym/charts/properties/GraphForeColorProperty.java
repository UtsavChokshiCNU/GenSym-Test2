package gensym.charts.properties;

import gensym.charts.*;
import java.awt.Color;

/**
 * <b>graph-fore-color</b> int property class.
 * Sets graph lines color
 */
public class GraphForeColorProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public GraphForeColorProperty() {
        super(2335, "graph-fore-color");
    }

    /**
     * {@inheritDoc}
     * Sets graph lines color
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        // G2 sends color in format 0xBBGGRR, so it needs to convert it
        chart.getChart().setAxisColor(new Color(ChartsCommon.convertBGRtoRGB(value)));
    }
}
