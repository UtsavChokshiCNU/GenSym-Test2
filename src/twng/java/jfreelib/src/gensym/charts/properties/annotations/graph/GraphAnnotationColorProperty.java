package gensym.charts.properties.annotations.graph;

import gensym.charts.ChartsCommon;
import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

import java.awt.Color;

/**
 * <b>graph-annotation-color</b> int property class.
 * Sets graph annotation color
 */
public class GraphAnnotationColorProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public GraphAnnotationColorProperty() {
        super(3236, "graph-annotation-color");
    }

    /**
     * {@inheritDoc}
     * Sets graph annotation color
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            graph.getAnnotations().getGraphAnnotations().getInfo(i).setColor(new Color(ChartsCommon.convertBGRtoRGB(value)));
        }
    }
}
