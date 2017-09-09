package gensym.charts.properties.subtitles;

import gensym.charts.properties.PropValueBase;
import java.awt.Font;

import org.jfree.chart.title.Title;

import gensym.charts.JFreeChartHolder;
import gensym.charts.subtitles.ISubtitle;

/**
 * <b>subtitle-font</b> string property class.
 * Sets chart subtitle font (by the font name)
 */
public class SubtitleFontProperty extends PropValueBase<String> {
    /**
     * Constructor
     */
    public SubtitleFontProperty() {
        super(2485, "subtitle-font");
    }
    /**
     * {@inheritDoc}
     * Sets chart sub titles font
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, String value) {
        for(Object obj : chart.getChart().getChart().getSubtitles()) {
            Title title = (Title) obj;
            if (title != null && title instanceof ISubtitle) {
                ISubtitle subtitle = (ISubtitle)title;
                subtitle.setFont(Font.decode(value));
            }
        }
    }
}
