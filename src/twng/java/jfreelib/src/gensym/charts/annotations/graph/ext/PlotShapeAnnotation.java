package gensym.charts.annotations.graph.ext;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Paint;
import java.awt.Shape;
import java.awt.Stroke;
import java.awt.geom.AffineTransform;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;

import org.jfree.chart.annotations.AbstractXYAnnotation;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.Plot;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.PlotRenderingInfo;
import org.jfree.chart.plot.XYPlot;
import org.jfree.ui.RectangleEdge;
import org.jfree.util.ObjectUtilities;
import org.jfree.util.PaintUtilities;

/**
 * Plot shape annotation.
 * The shape center coordinates are specified in data space.
 */
public class PlotShapeAnnotation extends AbstractXYAnnotation {
    /**
     * Default stroke constant
     */
    public static Stroke DAFAULT_STROKE = new BasicStroke(1.0f);
    
    /**
     * Default outline paint constant
     */
    public static Paint DEFAULT_OUTLINE_PAINT = Color.BLACK;
    
    /**
     * The annotation shape
     */
    private Shape shape = null;
    
    /**
     * The annotation stroke
     */
    private Stroke stroke = DAFAULT_STROKE;
    
    /**
     * The outline paint
     */
    private Paint outlinePaint = DEFAULT_OUTLINE_PAINT;

    /**
     * The paint used to fill the shape
     */
    private Paint fillPaint = null;
    
    /**
     * Shape center X position
     */
    private double centerX = 0;
    
    /**
     * Shape center Y position
     */
    private double centerY = 0;

    /**
     * Constructor
     * @param shape the shape
     * @param x the center X position (specified in data space)
     * @param y the center Y position (specified in data space)
     */
    public PlotShapeAnnotation(Shape shape, double x, double y) {
        this.shape = shape;
        centerX = x;
        centerY = y;
    }
    
    /**
     * {@inheritDoc}
     */
    public void draw(Graphics2D g2, XYPlot plot, Rectangle2D dataArea,
            ValueAxis domainAxis, ValueAxis rangeAxis, int rendererIndex,
            PlotRenderingInfo info) {
        
        PlotOrientation orientation = plot.getOrientation();
        RectangleEdge domainEdge = Plot.resolveDomainAxisLocation(
                plot.getDomainAxisLocation(), orientation);
        RectangleEdge rangeEdge = Plot.resolveRangeAxisLocation(
                plot.getRangeAxisLocation(), orientation);

        // compute transform matrix elements via sample points. Assume no
        // rotation or shear.
        Rectangle2D bounds = this.shape.getBounds2D();
        double x0 = bounds.getMinX();
        double x1 = bounds.getMaxX();
        double xx0 = domainAxis.valueToJava2D(x0, dataArea, domainEdge);
        double xx1 = domainAxis.valueToJava2D(x1, dataArea, domainEdge);
        double m00 = (xx1 - xx0) / (x1 - x0);
        double m02 = xx0 - x0 * m00;

        double y0 = bounds.getMaxY();
        double y1 = bounds.getMinY();
        double yy0 = rangeAxis.valueToJava2D(y0, dataArea, rangeEdge);
        double yy1 = rangeAxis.valueToJava2D(y1, dataArea, rangeEdge);
        double m11 = (yy1 - yy0) / (y1 - y0);
        double m12 = yy0 - m11 * y0;

        //  create transform, transform shape center and shape
        Point2D center = new Point2D.Double(centerX, centerY);
            AffineTransform moveCenter = new AffineTransform(m00, 0, 0, m11, m02, m12);
            center = moveCenter.transform(center, null);
        
        AffineTransform move = new AffineTransform(1.0f, 0.0f, 0.0f, 1.0f, center.getX(), center.getY());
        Shape s = move.createTransformedShape(shape);

        if (this.fillPaint != null) {
            g2.setPaint(this.fillPaint);
            g2.fill(s);
        }

        if (this.stroke != null && this.outlinePaint != null) {
            g2.setPaint(this.outlinePaint);
            g2.setStroke(this.stroke);
            g2.draw(s);
        }
        
        addEntity(info, s, rendererIndex, getToolTipText(), getURL());
    }

    /**
     * {@inheritDoc}
     */
    public boolean equals(Object obj) {
        if (super.equals(obj) && obj instanceof PlotShapeAnnotation) {
            PlotShapeAnnotation annotation = (PlotShapeAnnotation) obj;
            
            return centerX == annotation.centerX && centerY == annotation.centerY &&
                shape.equals(annotation.shape) && ObjectUtilities.equal(stroke, annotation.stroke) &&
                PaintUtilities.equal(outlinePaint, annotation.outlinePaint) &&
                PaintUtilities.equal(fillPaint, annotation.fillPaint);
            }
        return false;
    }

    /**
     * Returns shape stroke
     * @return the stroke
     */
    public Stroke getStroke() {
        return stroke;
    }
    /**
     * Sets shape stroke
     * @param stroke the stroke
     */
    public void setStroke(Stroke stroke) {
        this.stroke = stroke;
    }
    
    /**
     * Returns outline paint
     * @return the outline paint
     */
    public Paint getOutlinePaint() {
        return outlinePaint;
    }

    /**
     * Sets outline paint
     * @param paint the outline paint
     */
    public void setOutlinePaint(Paint paint) {
        outlinePaint = paint;
    }
    
    /**
     * Returns fill paint
     * @return the fill paint
     */
    public Paint getFillPaint() {
        return fillPaint;
    }

    /**
     * Sets fill paint
     * @param paint the fill paint
     */
    public void setFillPaint(Paint paint) {
        fillPaint = paint;
    }

    /**
     * Returns annotation shape
     * @return the shape
     */
    public Shape getShape() {
        return shape;
    }
}
