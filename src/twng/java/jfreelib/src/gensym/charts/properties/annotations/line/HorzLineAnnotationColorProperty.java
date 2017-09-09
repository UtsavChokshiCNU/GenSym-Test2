package gensym.charts.properties.annotations.line;

import java.awt.Color;

import gensym.charts.ChartsCommon;
import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.annotations.line.LineAnnotation;
import gensym.charts.properties.PropValueBase;

/**
 * <b>horz-line-annotation-color</b> int property class.
 * Sets color of horizontal line annotation
 */
public class HorzLineAnnotationColorProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public HorzLineAnnotationColorProperty() {
        super(3217, "horz-line-annotation-color");
    }

    /**
     * {@inheritDoc}
     * Sets color of horizontal line annotation
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            LineAnnotation annotation = graph.getAnnotations().getHorizontalLineAnnotations().get(i);
            annotation.setColor(new Color(ChartsCommon.convertBGRtoRGB(value)));
        }
    }
}
