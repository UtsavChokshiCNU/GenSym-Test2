package gensym.charts.subtitles;

import org.jfree.chart.title.TextTitle;

public class SimpleSubtitle extends TextTitle implements ISubtitle {
    /**
     * Generated version UID
     */
    private static final long serialVersionUID = -2341476462555453220L;

    /**
     * Constructor
     * @param text subtitle text
     */
    public SimpleSubtitle(String text) {
        super(text);
    }
    
    /**
     * {@inheritDoc}
     */
    public void setSubtitleText(String text) {
        setText(text);
    }
}
