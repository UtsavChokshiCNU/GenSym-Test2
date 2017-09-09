package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

import org.jfree.chart.JFreeChart;
import org.jfree.chart.title.*;

/**
 * <b>font-size</b> int property class.
 * Sets (sub)titles font size
 */
public class FontSizeProperty extends PropValueBase<Integer> {
    /**
     * Large font
     */
    public final static int FONT_LARGE = 0;
    
    /**
     * Large font size
     */
    private final static float FONT_SIZE_LARGE = 16.0f;

    /**
     * Medium font
     */
    public final static int FONT_MEDIUM = 1;
    /**
     * Medium font size
     */
    private final static float FONT_SIZE_MEDIUM = 13.0f;

    /**
     * Small font
     */
    public final static int FONT_SMALL = 2;
    /**
     * Small font size
     */
    private final static float FONT_SIZE_SMALL = 10.0f;
    
    /**
     * Main title factor
     */
    public final static float MAIN_TITLE_FACTOR = 1.5f;
    
    /**
     * Constructor
     */
    public FontSizeProperty() {
        super(2435, "font-size");
    }

    /**
     * Returns font size corresponded to specified font size type 
     * @param type font size type
     * @return font size corresponded to font size type
     */
    public static float getFontSize(int type) {
        switch (type) {
        case FONT_LARGE:
            return FONT_SIZE_LARGE;
        case FONT_SMALL:
            return FONT_SIZE_SMALL;
        default:
            return FONT_SIZE_MEDIUM;
        }
    }
    
    /**
     * Updates font size of TextTitle object
     * @param title TextTitle object
     * @param size font size
     */
    private void updateTextTitle(TextTitle title, float size) {
        title.setFont(title.getFont().deriveFont(size));
    }
    
    /**
     * Process chart updating
     * @param jchart chart
     * @param value font size flag
     */
    private void processChart(JFreeChart jchart, int value) {
        // title
        updateTextTitle(jchart.getTitle(), getFontSize(value) * MAIN_TITLE_FACTOR);

        // subtitles
        for (Object obj : jchart.getSubtitles()) {
            Title title  = (Title) obj;
            if (title instanceof LegendTitle) {
                LegendTitle legendTitle = (LegendTitle) title;
                legendTitle.setItemFont(legendTitle.getItemFont().deriveFont(getFontSize(value)));
            } else if (title instanceof TextTitle) {
                updateTextTitle((TextTitle) title, getFontSize(value));
            }
        }
    }
    /**
     * {@inheritDoc}
     * Sets (sub)titles font size
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        for (JFreeChart jchart : chart.getChart().getCharts()) {
            processChart(jchart, value);
        }
    }
}
