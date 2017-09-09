package gensym.charts.properties;

import java.awt.Color;

import gensym.charts.*;

/**
 * <b>subset-colors</b> int property class.
 * Sets series color
 */
public class SubsetColorsProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public SubsetColorsProperty() {
        super(2190, "subset-colors");
    }

    /**
     * {@inheritDoc}
     * Sets series color
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        // G2 sends color in format 0xBBGGRR, so it needs to convert it
        Color color = new Color(ChartsCommon.convertBGRtoRGB(value));
        chart.getChart().setSeriesColor(i, color);
    }
}
