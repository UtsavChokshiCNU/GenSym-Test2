package gensym.charts.properties;

import java.awt.Color;

import gensym.charts.ChartsCommon;
import gensym.charts.JFreeChartHolder;
import gensym.charts.subtitles.MultiSubtitle;

import org.jfree.chart.JFreeChart;
import org.jfree.chart.title.TextTitle;
import org.jfree.chart.title.Title;


/**
 * <b>text-color</b> int property class.
 * Sets (sub)titles text color
 */
public class TextColorProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public TextColorProperty() {
        super(2325, "text-color");
    }

    /**
     * Process chart updating
     * @param jchart chart
     * @param value text color
     */
    private void processChart(JFreeChart jchart, int value) {
        Color color = new Color(ChartsCommon.convertBGRtoRGB(value));
        
        // title
        ((TextTitle) jchart.getTitle()).setPaint(color);

        // subtitles
        for (Object obj : jchart.getSubtitles()) {
            Title title  = (Title) obj;
            if (title instanceof TextTitle) {
                ((TextTitle) title).setPaint(color);
            } else if (title instanceof MultiSubtitle) {
                ((MultiSubtitle) title).setPaint(color);
            }
        }
    }
    /**
     * {@inheritDoc}
     * Sets (sub)titles text color
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        for (JFreeChart jchart : chart.getChart().getCharts()) {
            processChart(jchart, value);
        }
    }
}
