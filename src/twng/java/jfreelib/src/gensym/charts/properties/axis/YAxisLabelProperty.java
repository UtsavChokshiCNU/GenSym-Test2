package gensym.charts.properties.axis;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.j3d.Plot3D;
import gensym.charts.properties.PropValueBase;

import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.Plot;

/**
 * <b>x-axis-label</b> String property class.
 * This property sets label into Y axis
 */
public class YAxisLabelProperty extends PropValueBase<String> {
    /**
     * Constructor
     */
    public YAxisLabelProperty() {
        super(3005, "y-axis-label");
    }

    /**
     * {@inheritDoc}
     * Sets label into Y axis
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, String value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            ValueAxis axis = graph.getPlot().getCurrentAxis();
            if (axis != null) {
                axis.setLabel(value);
            }
        } else {
            Plot plot = chart.getChart().getChart().getPlot();
            if (plot instanceof Plot3D) {
                ((Plot3D)plot).getZAxis().setLabel(value);
            }
        }
    }
}
