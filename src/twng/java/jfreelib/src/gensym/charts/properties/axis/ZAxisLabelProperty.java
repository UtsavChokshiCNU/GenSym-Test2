package gensym.charts.properties.axis;

import gensym.charts.JFreeChartHolder;
import gensym.charts.j3d.Plot3D;
import gensym.charts.properties.PropValueBase;

import org.jfree.chart.plot.Plot;

/**
 * <b>z-axis-label</b> String property class.
 * This property sets label into Z axis
 */
public class ZAxisLabelProperty extends PropValueBase<String> {

    /**
     * Constructor
     */
    public ZAxisLabelProperty() {
        super(4000, "z-axis-label");
    }

    /**
     * {@inheritDoc}
     * Sets label into Z axis
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, String value) {
        Plot plot = chart.getChart().getChart().getPlot();
        if (plot instanceof Plot3D) {
            ((Plot3D) plot).getYAxis().setLabel(value);
        }
    }
}
