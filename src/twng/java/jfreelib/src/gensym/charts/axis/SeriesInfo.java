package gensym.charts.axis;

import java.awt.Paint;
import java.awt.Shape;
import java.awt.Stroke;

import org.jfree.chart.renderer.xy.XYItemRenderer;

/**
 * Series info class.
 * Contains info about series from multi axes plot
 */
public class SeriesInfo {
    /** Renderer id*/
    private int rendererId = -1;
    
    /** Renderer */
    private XYItemRenderer renderer;
    
    /** Series paint */
    private Paint paint;
    
    /** Series stroke */
    private Stroke stroke;
    
    /** Show shape flag */
    private boolean showShape = false;
    
    /** Fill shape flag */
    private boolean fillShape = false;
    
    /** Series shape*/
    private Shape shape;
    
    /**
     * Returns renderer id
     * @return the series renderer id
     */
    public int getRendererId() {
        return rendererId;
    }
    
    /**
     * Returns renderer
     * @return the series renderer
     */
    public XYItemRenderer getRenderer() {
        return renderer;
    }
    
    /**
     * Sets renderer
     * @param id renderer id
     * @param renderer the series renderer
     */
    public void setRenderer(int id, XYItemRenderer renderer) {
        rendererId = id;
        this.renderer = renderer;
    }
    
    /**
     * Returns series paint
     * @return the series paint
     */
    public Paint getPaint() {
        return paint;
    }
    
    /**
     * Sets series paint
     * @param paint the new series paint
     */
    public void setPaint(Paint paint) {
        this.paint = paint;
    }

    /**
     * Returns series stroke
     * @return the series stroke
     */
    public Stroke getStroke() {
        return stroke;
    }
    
    /**
     * Sets series stroke
     * @param stroke the series stroke
     */
    public void setStroke(Stroke stroke) {
        this.stroke = stroke;
    }
    
    /**
     * Tests whether series shape is visible
     * @return true if visible
     */
    public boolean isShapeVisible() {
        return showShape;
    }
    
    /**
     * Sets shape visibility
     * @param visible visibility flag
     */
    public void setShapeVisible(boolean visible) {
        showShape = visible;
    }

    /**
     * Tests whether series shape is filled
     * @return true if filled
     */
    public boolean isShapeFilled() {
        return fillShape;
    }
    
    /**
     * Sets shape filling flag
     * @param fill filling flag
     */
    public void setShapeFilled(boolean fill) {
        fillShape = fill;
    }
    
    /**
     * Returns series shape
     * @return series shape
     */
    public Shape getShape() {
        return shape;
    }
    
    /**
     * Sets series shape
     * @param shape series shape
     */
    public void setShape(Shape shape) {
        this.shape = shape;
    }
}
