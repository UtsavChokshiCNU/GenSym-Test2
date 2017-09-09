package gensym.charts.subtitles;

import java.awt.Font;

/**
 * Chart subtitle interface 
 */
public interface ISubtitle {
    /**
     * Sets text
     * @param text subtitle text
     */
    void setSubtitleText(String text);
    
    /**
     * Returns the font used to display the title string.
     * @return The font (never <code>null</code>).
     */
    public Font getFont();

    /**
     * Sets the font used to display the title string.
     * @param font the new font
     */
    public void setFont(Font font);
}
