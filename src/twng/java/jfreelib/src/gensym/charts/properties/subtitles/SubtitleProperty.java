package gensym.charts.properties.subtitles;

import gensym.charts.properties.PropValueBase;
import gensym.charts.JFreeChartHolder;

/**
 * <b>subtitle</b> string property class.
 * Sets chart subtitle
 */
public class SubtitleProperty extends PropValueBase<String> {
    /**
     * Constructor
     */
    public SubtitleProperty() {
        super(2110, "subtitle");
    }

    /**
     * {@inheritDoc}
     * Sets chart subtitle
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, String value) {
        chart.getChart().setSubtitle(value);
    }
}
