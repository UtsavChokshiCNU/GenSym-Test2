package gensym.charts.properties.bubble;

import gensym.charts.GraphBubbleRenderer;
import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>bubble-size</b> int property class.
 * Sets bubble comparative size
 */
public class BubbleSizeProperty extends PropValueBase<Integer> {

    /** Small comparative size */
    public static final int SMALL = 0;

    /** Medium comparative size */
    public static final int MEDIUM = 1;

    /** Large comparative size */
    public static final int LARGE = 2;

    /**
     * Constructor
     */
    public BubbleSizeProperty() {
        super(3641, "bubble-size");
    }

    /**
     * {@inheritDoc}
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            if (graph.getPlot().getRenderer() instanceof GraphBubbleRenderer) {
                GraphBubbleRenderer renderer = (GraphBubbleRenderer) graph.getPlot().getRenderer();
                int size = value.intValue();
                if (size < SMALL || size > LARGE) {
                    size = MEDIUM;
                }
                renderer.setBubbleSize(size);
                graph.setRenderer(renderer);
            }
        }
    }
}
