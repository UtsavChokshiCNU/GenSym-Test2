package gensym.charts.properties.hatching;

import java.awt.Color;

import gensym.charts.ChartsCommon;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>hatch-back-color</b> int property class.
 * Sets hatch background color
 */
public class HatchBackColorProperty extends PropValueBase<Integer> {

    /**
     * Constructor
     */
    public HatchBackColorProperty() {
        super(2941, "hatch-back-color");
    }

    /**
     * {@inheritDoc}
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        Color color = new Color(ChartsCommon.convertBGRtoRGB(value));
        chart.getChart().setHatchBackColor(color);
    }
}
