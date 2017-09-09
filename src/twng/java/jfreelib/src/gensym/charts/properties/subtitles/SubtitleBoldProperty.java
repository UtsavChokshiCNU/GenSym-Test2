package gensym.charts.properties.subtitles;

import gensym.charts.properties.PropValueBase;
import gensym.charts.ChartsCommon;
import gensym.charts.JFreeChartHolder;
import gensym.charts.subtitles.ISubtitle;

import java.awt.Font;

import org.jfree.chart.JFreeChart;
import org.jfree.chart.title.*;

/**
 * <b>subtitle-bold</b> string property class.
 * Sets chart subtitle bold
 */
public class SubtitleBoldProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public SubtitleBoldProperty() {
        super(2490, "subtitle-bold");
    }

    /**
     * {@inheritDoc}
     * Sets chart subtitle bold
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        JFreeChart jchart = chart.getChart().getChart();
        for (Object obj : jchart.getSubtitles()) {
            Title title  = (Title) obj;
            if (title instanceof ISubtitle) {
                ISubtitle subtitle = (ISubtitle) title;
                subtitle.setFont(ChartsCommon.deriveFont(subtitle.getFont(), Font.BOLD, value != 0));
            }
        }
    }
}
