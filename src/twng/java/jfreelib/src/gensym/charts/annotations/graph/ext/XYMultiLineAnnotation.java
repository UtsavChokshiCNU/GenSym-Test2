package gensym.charts.annotations.graph.ext;

import java.awt.Graphics2D;
import java.awt.Shape;
import java.awt.geom.Rectangle2D;

import java.util.ArrayList;
import java.util.List;

import org.jfree.chart.annotations.XYTextAnnotation;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.Plot;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.PlotRenderingInfo;
import org.jfree.chart.plot.XYPlot;
import org.jfree.text.TextUtilities;
import org.jfree.ui.RectangleEdge;

/**
 * 
 * @author Administrator
 */
public class XYMultiLineAnnotation extends XYTextAnnotation {

    /** Serial version UID*/
    private static final long serialVersionUID = -7419762692915217252L;

    /** Multi line text */
    private String text[];
    
    /** Font height */
    private int fontHeight;
    
    /** X anchor */
    private float anchorX;
    
    /** Y anchor */
    private float anchorY;
    
    /** x offset*/
    private float offsetX;
    
    /** y offset*/
    private float offsetY;

    /**
     * Constructor
     * @param text to display
     * @param x position
     * @param y position
     */
    public XYMultiLineAnnotation(String text,
            double x, double y, float offsetX, float offsetY) {
        super(text, x, y);
        this.offsetX = offsetX;
        this.offsetY = offsetY;
    }

    /**
     * {@inheritDoc}
     */
    public void draw(Graphics2D g2, XYPlot plot, Rectangle2D dataArea,
            ValueAxis domainAxis, ValueAxis rangeAxis,
            int rendererIndex,
            PlotRenderingInfo info) {
        init(g2, plot, dataArea, domainAxis, rangeAxis);

        List<Shape> hotspots = getHotspots(g2);

        drawBackground(g2, hotspots);
        drawText(g2);
        drawOutline(g2, hotspots);
        drawToolTips(info, hotspots, rendererIndex);

    }

    /**
     * Initialize drawing values
     * @param g2 the graphics device
     * @param plot the plot
     * @param dataArea the data area
     * @param domainAxis the domain axis
     * @param rangeAxis the range axis
     */
    private void init(Graphics2D g2, XYPlot plot, Rectangle2D dataArea,
            ValueAxis domainAxis, ValueAxis rangeAxis) {
        g2.setFont(getFont());

        this.text = getText().split("\n");
        this.fontHeight = g2.getFontMetrics().getHeight();
        this.anchorX = getAnchorX(plot, dataArea, domainAxis);
        this.anchorY = getAnchorY(plot, dataArea, rangeAxis);

        doHorizontalRotation(plot);
    }

    /**
     * Gets x anchor for drawing
     * @param plot the plot
     * @param dataArea the data area
     * @param domainAxis the domain axis
     * @return x anchor
     */
    private float getAnchorX(XYPlot plot, Rectangle2D dataArea, ValueAxis domainAxis) {
        RectangleEdge domainEdge = Plot.resolveDomainAxisLocation(
                plot.getDomainAxisLocation(), plot.getOrientation());

        return (float) domainAxis.valueToJava2D(getX(), dataArea, domainEdge);
    }

    /**
     * Gets y anchor for drawing
     * @param plot the plot
     * @param dataArea the data area
     * @param rangeAxis the range axis
     * @return y anchor
     */
    private float getAnchorY(XYPlot plot, Rectangle2D dataArea, ValueAxis rangeAxis) {
        RectangleEdge rangeEdge = Plot.resolveRangeAxisLocation(
                plot.getRangeAxisLocation(), plot.getOrientation());
        return (float) rangeAxis.valueToJava2D(getY(), dataArea, rangeEdge);
    }

    /**
     * Do horizontal rotation if needed
     * @param plot the plot
     */
    private void doHorizontalRotation(XYPlot plot) {
        if (plot.getOrientation() == PlotOrientation.HORIZONTAL) {
            float tempAnchor = this.anchorX;
            this.anchorX = this.anchorY;
            this.anchorY = tempAnchor;
        }
    }

    /**
     * Gets hotspots for drawing background, outline and tooltips
     * @param g2 the graphics device
     * @return hotspots
     */
    private List<Shape> getHotspots(Graphics2D g2) {
        List<Shape> hotspots = new ArrayList<Shape>();

        for (int i = 0; i < text.length; i++) {
            hotspots.add(TextUtilities.calculateRotatedStringBounds(text[i],
                    g2, anchorX, anchorY + i * fontHeight,
                    getTextAnchor(), getRotationAngle(), getRotationAnchor()));
        }

        return hotspots;
    }

    /**
     * Draw background if nedded
     * @param g2 the graphics device
     * @param hotspots hotspots for drawing
     */
    private void drawBackground(Graphics2D g2, List<Shape> hotspots) {
        if (getBackgroundPaint() != null) {
            g2.setPaint(getBackgroundPaint());
            for (Shape hotspot : hotspots) {
                g2.fill(hotspot);
            }
        }
    }

    /**
     * Draw mutli line text
     * @param g2 the graphics device
     */
    private void drawText(Graphics2D g2) {
        g2.setPaint(getPaint());
        for (int i = 0; i < text.length; i++) {
            TextUtilities.drawRotatedString(text[i], g2,
                    anchorX + offsetX, offsetY + anchorY + i * fontHeight,
                    getTextAnchor(), getRotationAngle(), getRotationAnchor());
        }
    }

    /**
     * Draw outlines if needed
     * @param g2 the graphics device
     * @param hotspots hotspots for drawing
     */
    private void drawOutline(Graphics2D g2, List<Shape> hotspots) {
        if (isOutlineVisible()) {
            g2.setStroke(getOutlineStroke());
            g2.setPaint(getOutlinePaint());
            for (Shape hotspot : hotspots) {
                g2.draw(hotspot);
            }
        }
    }

    /**
     * Draw tooltips if needed
     * @param info an optional info object
     * that will be populated with entity information
     * @param hotspots hotspots for drawing
     * @param rendererIndex the renderer index
     */
    private void drawToolTips(PlotRenderingInfo info, List<Shape> hotspots, int rendererIndex) {
        String toolTip = getToolTipText();
        String url = getURL();
        if (toolTip != null || url != null) {
            for (Shape hotspot : hotspots) {
                addEntity(info, hotspot, rendererIndex, toolTip, url);
            }
        }
    }
}
