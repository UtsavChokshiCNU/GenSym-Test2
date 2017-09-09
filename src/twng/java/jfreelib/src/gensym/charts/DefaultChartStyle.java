package gensym.charts;

import gensym.charts.actions.IChartAction;

import java.awt.*;

import org.jfree.chart.*;
import org.jfree.chart.title.LegendTitle;
import org.jfree.chart.title.TextTitle;
import org.jfree.chart.title.Title;

/**
 * Default chart style class
 */
public class DefaultChartStyle {
    /**
     * Light color
     */
    private final static Color LIGHT_COLOR = Color.LIGHT_GRAY;
    
    /**
     * Medium color
     */
    private final static Color MEDIUM_COLOR = new Color(0x007F00);

    /**
     * Dark color
     */
    private final static Color DARK_COLOR = Color.GRAY;  

    /**
     * Extra dark color
     */
    private final static Color EXTRA_DARK_COLOR = Color.LIGHT_GRAY;
    
    /**
     * No style
     */
    public final static int STYLE_NO_STYLE = 0;
    
    /**
     * Light Colors with Inset Border
     */
    public final static int STYLE_LIGHT_INSET = 1;
    
    /**
     * Light Colors with Shadow Border
     */
    public final static int STYLE_LIGHT_SHADOW = 2;
    
    /**
     * Light Colors with Line Border
     */
    public final static int STYLE_LIGHT_LINE = 3;
    
    /**
     * Light Colors with No Border
     */
    public final static int STYLE_LIGHT_NO_BORDER = 4;
    
    /**
     * Medium Colors with Inset Border
     */
    public final static int STYLE_MEDIUM_INSET = 5;
    
    /**
     * Medium Colors with Shadow Border
     */
    public final static int STYLE_MEDIUM_SHADOW = 6;
    
    /**
     * Medium Colors with Line Border
     */
    public final static int STYLE_MEDIUM_LINE = 7;
    
    /**
     * Medium Colors with No Border
     */
    public final static int STYLE_MEDIUM_NO_BORDER = 8;

    /**
     * Dark Colors with Inset Border
     */
    public final static int STYLE_DARK_INSET = 9;
    
    /**
     * Dark Colors with Shadow Border
     */
    public final static int STYLE_DARK_SHADOW = 10;
    
    /**
     * Dark Colors with Line Border
     */
    public final static int STYLE_DARK_LINE = 11;
    
    /**
     * Dark Colors with No Border
     */
    public final static int STYLE_DARK_NO_BORDER = 12;

    /**
     * Border Single line style
     */
    public final static int BORDER_SINGLE_LINE = 1;

    /**
     * No Border style
     */
    public final static int BORDER_NO_BORDER = 2;

    /**
     * Border Thick line style
     */
    public final static int BORDER_THICK_LINE = 4;

    /**
     * Style
     */
    private int style = STYLE_NO_STYLE;
    
    /**
     * Plot Border stroke
     */
    private BasicStroke border = null;
    
    /**
     * Gradient mode usage flag
     */
    private boolean useGradientMode = false;
    
    /**
     * Chart
     */
    private AbstractChart chart = null;
    
    /**
     * Constructor
     * @param chart chart object
     */
    public DefaultChartStyle(AbstractChart chart) {
        this.chart = chart;
    }

    /**
     * Tests whether gradient mode is set
     * @return true if gradient mode is set
     */
    public boolean isGradientMode() {
        return useGradientMode;
    }

    /**
     * Gets border
     * @return BasicStroke border
     */
    public BasicStroke getBorder() {
        return border;
    }
    
    /**
     * Sets gradient mode flag
     * @param useGradient gradient mode flag
     */
    public void setGradientMode(boolean useGradient) {
        useGradientMode = useGradient;
    }
    
    /**
     * Returns chart style
     * @return chart style
     */
    public int getStyle() {
        return style;
    }
    
    /**
     * Sets chart style
     * @param style chart style
     * @throws ChartActionException if style is invalid
     */
    public void setStyle(int style) throws IChartAction.ChartActionException {
        if (style < STYLE_NO_STYLE || style > STYLE_DARK_NO_BORDER) {
            throw new IChartAction.ChartActionException("Invalid style");
        }
        
        this.style = style;
    }
    
    /**
     * Sets grid border style
     * @param style the new border style
     */
    public void setBorderStyle(int style) {
        switch (style) {
        case BORDER_NO_BORDER:
            border = null;
            break;
        case BORDER_THICK_LINE:
            border = new BasicStroke(2);
            break;
        case BORDER_SINGLE_LINE:
        default:
            border = new BasicStroke(1);
        }
    }
    
    /**
     * Returns gradient color according to current style
     * @param start flag indicates if it is the start gradient color 
     * @return gradient color
     */
    private Color getGradientColor(boolean start) {
        switch (getStyle()) {
            case STYLE_LIGHT_INSET:
            case STYLE_LIGHT_SHADOW:
            case STYLE_LIGHT_LINE:
            case STYLE_LIGHT_NO_BORDER:
                return start ? MEDIUM_COLOR : LIGHT_COLOR;

            case STYLE_MEDIUM_INSET:
            case STYLE_MEDIUM_SHADOW:
            case STYLE_MEDIUM_LINE:
            case STYLE_MEDIUM_NO_BORDER:
                return start ? DARK_COLOR : MEDIUM_COLOR;
        }
        
        return start ? EXTRA_DARK_COLOR : DARK_COLOR;
    }
    
    /**
     * Returns background paint
     * @param plot flag indicates if it needs to use plot
     * @return background paint for chart if plot is false otherwise returns background paint for plot
     */
    private Paint getBackgroundPaint(boolean plot) {
        switch (getStyle()) {
            case STYLE_LIGHT_INSET:
            case STYLE_LIGHT_SHADOW:
            case STYLE_LIGHT_LINE:
            case STYLE_LIGHT_NO_BORDER:
                return plot ? LIGHT_COLOR : MEDIUM_COLOR;

            case STYLE_MEDIUM_INSET:
            case STYLE_MEDIUM_SHADOW:
            case STYLE_MEDIUM_LINE:
            case STYLE_MEDIUM_NO_BORDER:
                return plot ? MEDIUM_COLOR : DARK_COLOR;
                
            case STYLE_DARK_INSET:
            case STYLE_DARK_SHADOW:
            case STYLE_DARK_LINE:
            case STYLE_DARK_NO_BORDER:
                return plot ? DARK_COLOR : EXTRA_DARK_COLOR;
        }
        return plot ? Color.LIGHT_GRAY : JFreeChart.DEFAULT_BACKGROUND_PAINT;
    }

    /**
     * Tests whether current style has no border 
     * @return true if current style has no border
     */
    private boolean isNoBorder() {
        return style == STYLE_LIGHT_NO_BORDER || style == STYLE_MEDIUM_NO_BORDER || style == STYLE_DARK_NO_BORDER;
    }

    /**
     * Updates chart
     * @param jchart chart
     * @param info rendering info
     */
    private void updateChart(JFreeChart jchart, ChartRenderingInfo info) {
        if (jchart == chart.getChart()) {
            jchart.setBackgroundPaint(getChartBackground(info));
            if (border != null || isNoBorder()) {
                jchart.getPlot().setOutlineStroke(border);
            } else {
                jchart.getPlot().setOutlineStroke(new BasicStroke(1));
            }
            jchart.getPlot().setBackgroundPaint(getPlotBackground(info));
        }
        else {
            jchart.setBackgroundPaint(null);
            jchart.getPlot().setOutlineVisible(false);
            jchart.getPlot().setBackgroundPaint(null);
        }
        
        // update subtitles
        for (Object obj : jchart.getSubtitles()) {
            Title title  = (Title) obj;
            if (title instanceof LegendTitle) {
                LegendTitle legendTitle = (LegendTitle) title;
                legendTitle.setBackgroundPaint(null);
            } else if (title instanceof TextTitle) {
                TextTitle textTitle = (TextTitle) title; 
                textTitle.setBackgroundPaint(null);
            }
        }
    }
    /**
     * Updates charts
     * @param info chart rendering info
     */
    public void updateCharts(ChartRenderingInfo info) {
        for (JFreeChart jchart : chart.getCharts()) {
            updateChart(jchart, info);
        }
    }

    /**
     * Makes chart background
     * @param info chart rendering info
     * @return chart background
     */
    protected Paint getChartBackground(ChartRenderingInfo info) {
        if (isGradientMode() && isNoBorder()) {
            return chart.getBackgroundPaint(getGradientColor(true), getGradientColor(false), info);
        }
        return getBackgroundPaint(false);
    }

    /**
     * Makes plot background
     * @param info chart rendering info
     * @return plot background
     */
    protected Paint getPlotBackground(ChartRenderingInfo info) {
        if (isGradientMode() && getStyle() != STYLE_NO_STYLE) {
            return isNoBorder() ?
                    null : chart.getBackgroundPaint(getGradientColor(true), getGradientColor(false), info);
        }
        return getBackgroundPaint(true);
    }
}
