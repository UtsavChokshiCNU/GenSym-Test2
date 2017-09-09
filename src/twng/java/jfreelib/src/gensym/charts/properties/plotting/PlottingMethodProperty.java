package gensym.charts.properties.plotting;

import gensym.charts.Chart3D;
import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;
import org.jfree.chart.renderer.xy.XYItemRenderer;

/**
 * <b>plotting-method</b> int property class.
 * Sets point count per each subset (series)
 */
public class PlottingMethodProperty extends PropValueBase<Integer> {

    /**
     * Constructor
     */
    public PlottingMethodProperty() {
        super(3090, "plotting-method");
    }

    /**
     * {@inheritDoc}
     * Changes plotting method used to render the object's data
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof Chart3D) {
            Chart3D graph = (Chart3D) chart.getChart();;
            graph.getPlot().setPlottingMethod(value);
        } else if ((chart.getChart() instanceof GraphChart)) {
            GraphChart graph = (GraphChart) chart.getChart();
            XYItemRenderer renderer = new GraphRendererFactory(graph).createRenderer(value);
            if (renderer != null) {
                graph.setRenderer(renderer);
            }
        }
    }
}
