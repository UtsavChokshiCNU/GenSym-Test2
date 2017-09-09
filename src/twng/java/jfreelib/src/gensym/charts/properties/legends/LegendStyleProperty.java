package gensym.charts.properties.legends;

import gensym.charts.properties.*;
import org.jfree.chart.title.LegendTitle;

import gensym.charts.JFreeChartHolder;
import gensym.charts.legend.ChartLegend;

/**
 * <b>legend-style</b> int property class.
 * Sets legend style
 */
public class LegendStyleProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public LegendStyleProperty() {
        super(2975, "legend-style");
    }

    /**
     * {@inheritDoc}
     * Sets legend style
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        LegendTitle legend = chart.getChart().getChart().getLegend();
        if (legend instanceof ChartLegend) {
            ((ChartLegend) legend).setStyle(value);
        }
    }
}
