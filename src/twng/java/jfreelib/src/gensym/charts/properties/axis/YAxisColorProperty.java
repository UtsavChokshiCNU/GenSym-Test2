package gensym.charts.properties.axis;

import java.awt.Color;

import org.jfree.chart.axis.ValueAxis;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>y-axis-color</b> int property class.
 * Sets Y axis color
 */
public class YAxisColorProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public YAxisColorProperty() {
        super(3036, "y-axis-color");
    }

    /**
     * {@inheritDoc}
     * Sets Y axis color
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            ValueAxis axis = graph.getPlot().getCurrentAxis();
            if (axis != null) {
                int red = value & 0xFF;
                int green = (value >> 8) & 0xFF;
                int blue = (value >> 16) & 0xFF;
                int alpha = value == 1 ? 0 : 0xFF;
                Color color = new Color(red, green, blue, alpha);
        
                axis.setLabelPaint(color);
                axis.setTickLabelPaint(color);
            }
        }
    }
}
