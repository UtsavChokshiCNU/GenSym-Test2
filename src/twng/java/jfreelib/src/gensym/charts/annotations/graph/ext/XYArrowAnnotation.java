package gensym.charts.annotations.graph.ext;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Paint;
import java.awt.Stroke;
import java.awt.geom.Line2D;
import java.awt.geom.Rectangle2D;

import org.jfree.chart.annotations.AbstractXYAnnotation;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.Plot;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.PlotRenderingInfo;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.util.LineUtilities;
import org.jfree.ui.RectangleEdge;

public class XYArrowAnnotation extends AbstractXYAnnotation {

    /** Generated serial version UID */
    private static final long serialVersionUID = -6257739000802844981L;

    /** The x-coordinate. */
    private double x1;

    /** The y-coordinate. */
    private double y1;

    /** The x-coordinate. */
    private double x2;

    /** The y-coordinate. */
    private double y2;

    /** Arrow size*/
    private double size;

    /** The line stroke. */
    private transient Stroke lineStroke;

    /** The arrow stroke. */
    private transient Stroke arrowStroke;

    /** The line color. */
    private transient Paint paint;

    /** Controls left arrow visible */
    private boolean leftArrowVisible = true;

    /** Controls right arrow visible */
    private boolean rightArrowVisible = true;

    /** Small arrow size */
    public static final double SMALL = 10;

    /** Small arrow size */
    public static final double MEDIUM = 15;

    /** Small arrow size */
    public static final double LARGE = 20;

    /**
     * Constructor
     *
     * @param x1  the x-coordinate for the start of the arrow.
     * @param y1  the y-coordinate for the start of the arrow.
     * @param x2  the x-coordinate for the end of the arrow.
     * @param y2  the y-coordinate for the end of the arrow.
     */
    public XYArrowAnnotation(double x1, double y1, double x2, double y2) {
        this(x1, y1, x2, y2, MEDIUM,
                new BasicStroke(1.0f), new BasicStroke(1.0f), Color.black);
    }

    /**
     * Constructor
     *
     * @param x1  the x-coordinate for the start of the arrow.
     * @param y1  the y-coordinate for the start of the arrow.
     * @param x2  the x-coordinate for the end of the arrow.
     * @param y2  the y-coordinate for the end of the arrow.
     * @param size arrow size
     * @param stroke  the arrow stroke.
     * @param paint  the arrow color.
     */
    public XYArrowAnnotation(double x1, double y1, double x2, double y2, double size,
            Stroke lineStroke, Stroke arrowStroke, Paint paint) {

        this.x1 = x1;
        this.y1 = y1;
        this.x2 = x2;
        this.y2 = y2;
        this.size = size;
        this.lineStroke = lineStroke;
        this.arrowStroke = arrowStroke;
        this.paint = paint;
    }

    /**
     * Draws the annotation.
     * 
     * @param g2  the graphics device.
     * @param plot  the plot.
     * @param dataArea  the data area.
     * @param domainAxis  the domain axis.
     * @param rangeAxis  the range axis.
     * @param rendererIndex  the renderer index.
     * @param info  if supplied, this info object will be populated with
     *              entity information.
     */
    public void draw(Graphics2D g2, XYPlot plot, Rectangle2D dataArea,
            ValueAxis domainAxis, ValueAxis rangeAxis,
            int rendererIndex,
            PlotRenderingInfo info) {

        PlotOrientation orientation = plot.getOrientation();
        RectangleEdge domainEdge = Plot.resolveDomainAxisLocation(
                plot.getDomainAxisLocation(), orientation);
        RectangleEdge rangeEdge = Plot.resolveRangeAxisLocation(
                plot.getRangeAxisLocation(), orientation);

        float startX = 0;
        float startY = 0;
        float endX = 0;
        float endY = 0;
        if (orientation == PlotOrientation.VERTICAL) {
            startX = (float) domainAxis.valueToJava2D(this.x1, dataArea,
                    domainEdge);
            startY = (float) rangeAxis.valueToJava2D(this.y1, dataArea,
                    rangeEdge);
            endX = (float) domainAxis.valueToJava2D(this.x2, dataArea,
                    domainEdge);
            endY = (float) rangeAxis.valueToJava2D(this.y2, dataArea,
                    rangeEdge);
        } else if (orientation == PlotOrientation.HORIZONTAL) {
            startX = (float) rangeAxis.valueToJava2D(this.y1, dataArea,
                    rangeEdge);
            startY = (float) domainAxis.valueToJava2D(this.x1, dataArea,
                    domainEdge);
            endX = (float) rangeAxis.valueToJava2D(this.y2, dataArea,
                    rangeEdge);
            endY = (float) domainAxis.valueToJava2D(this.x2, dataArea,
                    domainEdge);
        }
        if (paint != null) {
            g2.setPaint(paint);
        }

        if (lineStroke != null) {
            g2.setStroke(lineStroke);
        }

        Line2D line = new Line2D.Float(startX, startY, endX, endY);
        if (LineUtilities.clipLine(line, dataArea)) {
            g2.draw(line);
        }

        if (arrowStroke != null) {
            g2.setStroke(arrowStroke);
        }
        Line2D arrow1 = createArrowLine(startX, startY, endX, endY, true);
        if (LineUtilities.clipLine(arrow1, dataArea) && getLeftVisible()) {
            g2.draw(arrow1);
        }

        Line2D arrow2 = createArrowLine(startX, startY, endX, endY, false);
        if (LineUtilities.clipLine(arrow2, dataArea) && geRightVisible()) {
            g2.draw(arrow2);
        }
    }

    /**
     * Creates arrows (line direction)
     * @param startX x coord of start point
     * @param startY y coord of start point
     * @param endX x coord of end point
     * @param endY y coord of end point
     * @param left arrow rotation (left/rigth)
     * @return line to draws
     */
    protected Line2D createArrowLine(double startX, double startY, double endX, double endY, boolean left) {
        double x = startX - endX;
        double y = startY - endY;

        // create lines
        double rotate = Math.PI / 6;
        if (left) {
            rotate = -rotate;
        }
        double arrowX = Math.cos(rotate) * x - Math.sin(rotate) * y;
        double arrowY = Math.sin(rotate) * x + Math.cos(rotate) * y;

        double length = Math.sqrt(arrowX * arrowX + arrowY * arrowY);

        if (length == 0.0) {
            return null;
        }

        return new Line2D.Double(endX, endY, endX + size * arrowX / length, endY + size * arrowY / length);
    }

    /**
     * Sets left arrow visible
     * @param leftArrowVisible new left arrow visible
     */
    public void setLeftVisible(boolean leftArrowVisible) {
        this.leftArrowVisible = leftArrowVisible;
    }

    /**
     * Gets left arrow visible
     * @return true, if visible
     */
    public boolean getLeftVisible() {
        return leftArrowVisible;
    }

    /**
     * Sets right arrow visible
     * @param rightArrowVisible new right arrow visible
     */
    public void setRightVisible(boolean rightArrowVisible) {
        this.rightArrowVisible = rightArrowVisible;
    }

    /**
     * Gets right arrow visible
     * @return true, if visible
     */
    public boolean geRightVisible() {
        return rightArrowVisible;
    }
}
