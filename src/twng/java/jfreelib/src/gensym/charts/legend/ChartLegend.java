package gensym.charts.legend;

import org.jfree.chart.annotations.XYTitleAnnotation;
import org.jfree.chart.plot.CombinedDomainXYPlot;
import org.jfree.chart.plot.Plot;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.title.LegendTitle;
import org.jfree.ui.RectangleAnchor;
import org.jfree.ui.RectangleEdge;
import org.jfree.ui.VerticalAlignment;

public class ChartLegend extends LegendTitle {
    /**
     * Generated serial version UID
     */
    private static final long serialVersionUID = -3894248691471745047L;
    
    /**
     * Two Lines per legend
     */
    public static final int STYLE_2_LINE = 0;
    
    /**
     * Single Line
     */
    public static final int STYLE_1_LINE = 1;

    /**
     * Single Line Inside Axis
     */
    public static final int STYLE_1_LINE_INSIDE_AXIS = 2;

    /**
     * Single Line Top Of Axis
     */
    public static final int STYLE_1_LINE_TOP_OF_AXIS = 3;
    
    /**
     * Single Line Inside and Overlapping Axis
     */
    public static final int STYLE_1_LINE_INSIDE_OVERLAP = 4;
    
    /**
     * Single Line Left of Axis stacked vertically
     */
    public static final int STYLE_1_LINE_LEFT_OF_AXIS = 5;

    /**
     * Legend style
     */
    private int style = STYLE_1_LINE;
    
    /**
     * Old Legend Position
     */
    private RectangleEdge oldPosition = null;
    
    /**
     * Corresponding title annotation
     */
    private XYTitleAnnotation annotation = null;
    
    /**
     * The plot
     */
    XYPlot plot = null;

    /**
     * Constructor
     * @param source the source.
     */
    public ChartLegend(Plot plot) {
        super(plot);
        
        if (plot instanceof CombinedDomainXYPlot) {
            CombinedDomainXYPlot combPlot = (CombinedDomainXYPlot) plot;
            if (combPlot.getSubplots().size() > 0) {
                plot = (Plot) combPlot.getSubplots().get(0);
            } else {
                plot = null;
            }
        }

        if (plot instanceof XYPlot) {
            this.plot = (XYPlot) plot;
        }
        
        setDefaultLegendProperties();
    }

    /**
     * Returns Legend style
     * @return the style
     */
    public int getStyle() {
        return style;
    }
    
    /**
     * Sets default legend parameters
     */
    private void setDefaultLegendProperties() {
        setLegendItemGraphicEdge(RectangleEdge.LEFT);
        setVerticalAlignment(DEFAULT_VERTICAL_ALIGNMENT);
        if (oldPosition != null) {
            setPosition(oldPosition);
            oldPosition = null;
        }
        
        if (plot != null && annotation != null) {
            plot.removeAnnotation(annotation);
            annotation = null;
        }
        super.setVisible(true);
    }
    
    /**
     * {@inheritDoc}
     */
    public void setVisible(boolean visible) {
        if (plot != null && style >= STYLE_1_LINE_INSIDE_AXIS && style < STYLE_1_LINE_LEFT_OF_AXIS) {
            if (!visible && annotation != null) {
                plot.removeAnnotation(annotation);
                annotation = null;
            } else if (visible && annotation == null) {
                annotation = new XYTitleAnnotation(0.02, 0.98, this, RectangleAnchor.TOP_LEFT);
                annotation.setMaxWidth(0.5);
                plot.addAnnotation(annotation);
            }
        } else {
            super.setVisible(visible);
        }
    }
    
    /**
     * Sets legend style
     * @param newStyle the new style
     */
    public void setStyle(int newStyle) {
        if (newStyle < STYLE_2_LINE || newStyle > STYLE_1_LINE_LEFT_OF_AXIS) {
            return;
        }
        
        setDefaultLegendProperties();
        style = newStyle;
        
        switch (newStyle) {
        case STYLE_1_LINE:
            // setDefaultLegendProperties() already sets default data
            break;
        case STYLE_2_LINE:
            setLegendItemGraphicEdge(RectangleEdge.TOP);
            break;
        case STYLE_1_LINE_LEFT_OF_AXIS:
            oldPosition = getPosition();
            setPosition(RectangleEdge.LEFT);
            setVerticalAlignment(VerticalAlignment.TOP);
            break;
        default:
            // show legend inside chart
            setVisible(isVisible());
            super.setVisible(false);
        }
    }
}
