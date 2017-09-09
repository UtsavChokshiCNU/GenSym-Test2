package gensym.charts.properties.plotting;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;
import org.jfree.chart.renderer.xy.XYItemRenderer;

public class PlottingMethodsProperty extends PropValueBase<Integer> {

    /**
     * Constructor
     */
    public PlottingMethodsProperty() {
        super(3103, "plotting-methods");
    }

    /**
     * {@inheritDoc}
     * Changes plotting methods used to render the object's data
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            XYItemRenderer renderer = new GraphRendererFactory(graph).createRenderer(value);
            if (renderer != null) {
                graph.getPlot().getSeriesInfo(i).setRenderer(value, renderer);
            }
        }
    }
}
