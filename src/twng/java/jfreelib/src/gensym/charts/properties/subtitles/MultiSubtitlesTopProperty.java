package gensym.charts.properties.subtitles;

import gensym.charts.properties.PropValueBase;
import gensym.charts.JFreeChartHolder;
import gensym.charts.subtitles.MultiSubtitle;

import org.jfree.ui.RectangleEdge;

/**
 * <b>multi-subtitles</b> string property class.
 * Sets multi subtitles
 */
public class MultiSubtitlesTopProperty extends PropValueBase<String> {
    /**
     * Constructor
     */
    public MultiSubtitlesTopProperty() {
        super(2630, "multi-subtitles");
    }
    /**
     * {@inheritDoc}
     * Sets multi subtitles
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, String value) {
        chart.getChart().getChart().addSubtitle(new MultiSubtitle(value, RectangleEdge.TOP));
    }
}
