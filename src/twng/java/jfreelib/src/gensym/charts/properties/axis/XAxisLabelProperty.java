package gensym.charts.properties.axis;

import gensym.charts.JFreeChartHolder;
import gensym.charts.j3d.Plot3D;
import gensym.charts.properties.PropValueBase;

import org.jfree.chart.plot.Plot;
import org.jfree.chart.plot.XYPlot;

/**
 * <b>x-axis-label</b> String property class.
 * This property sets label into X axis
 */
public class XAxisLabelProperty extends PropValueBase<String> {
    /**
     * Constructor
     */
    public XAxisLabelProperty() {
        super(3000, "x-axis-label");
    }

    /**
     * {@inheritDoc}
     * Sets label into X axis
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, String value) {
        Plot plot = chart.getChart().getChart().getPlot();
        if (plot instanceof XYPlot) {
            XYPlot xyPlot = (XYPlot)plot;
            xyPlot.getDomainAxis().setLabel(value);
        } else if (plot instanceof Plot3D) {
            ((Plot3D)plot).getXAxis().setLabel(value);
        }
    }
}
