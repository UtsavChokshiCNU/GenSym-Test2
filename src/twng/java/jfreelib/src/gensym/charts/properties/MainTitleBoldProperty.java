package gensym.charts.properties;

import gensym.charts.*;
import java.awt.Font;
import org.jfree.chart.title.TextTitle;

/**
 * <b>main-title-bold</b> int property class.
 * Sets main title bold
 */
public class MainTitleBoldProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public MainTitleBoldProperty() {
        super(2450, "main-title-bold");
    }

    /**
     * {@inheritDoc}
     * Sets main title bold
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        TextTitle title = chart.getChart().getChart().getTitle();
        ChartsCommon.updateTitleFont(title, Font.BOLD, value != 0);
    }
}
