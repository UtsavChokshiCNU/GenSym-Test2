package gensym.charts.properties.subtitles;

import gensym.charts.properties.PropValueBase;
import gensym.charts.JFreeChartHolder;
import gensym.charts.subtitles.MultiSubtitle;

import org.jfree.ui.RectangleEdge;

/**
 * <b>multi-subtitles</b> string property class.
 * Sets multi buttom subtitles
 */
public class MultiSubtitlesBottomProperty extends PropValueBase<String> {
    /**
     * Constructor
     */
    public MultiSubtitlesBottomProperty() {
        super(2631, "multi-bottom-titles");
    }
    /**
     * {@inheritDoc}
     * Sets multi buttom subtitles
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, String value) {
        chart.getChart().getChart().addSubtitle(new MultiSubtitle(value, RectangleEdge.BOTTOM));
    }
}
