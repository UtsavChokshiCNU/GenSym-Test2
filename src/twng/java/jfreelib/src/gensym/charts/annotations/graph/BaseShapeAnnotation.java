package gensym.charts.annotations.graph;

import gensym.charts.annotations.graph.ext.PlotShapeAnnotation;

import java.awt.BasicStroke;
import java.awt.Shape;
import java.awt.geom.Rectangle2D;

/**
 * Basic shape annotation
 */
public abstract class BaseShapeAnnotation extends AbstractBuilder {
    /**
     * Constructor
     * @param info annotation info
     * @param shapeSize the cross size
     */
    protected BaseShapeAnnotation(AnnotationInfo info, int shapeSize, boolean solid) {
        setAxis(info.getAxis());
        Shape shape = createShape(shapeSize); 
        
        PlotShapeAnnotation shapeAnnotation = new PlotShapeAnnotation(shape, info.getX(), info.getY());
        shapeAnnotation.setStroke(new BasicStroke(0.5f));
        
        if (info.getColor() != null) {
            shapeAnnotation.setOutlinePaint(info.getColor());
            if (solid) {
                shapeAnnotation.setFillPaint(info.getColor());
            }
        }
        addAnnotation(shapeAnnotation);
        addText(info, null, getLabelOffset(shape));
        isFinished = true;
    }
    
    /**
     * Create appropriate shape
     * @param shapeSize the size of shape
     * @return Shape
     */
    public abstract Shape createShape(int shapeSize);
    
    /**
     * Gets label offset
     * @param shapeSize the shape size
     * @return the offset value
     */
    public double getLabelOffset(Shape shape) {
        Rectangle2D r2d = shape.getBounds2D();
        return 5.0 + r2d.getY() + r2d.getHeight(); 
    }
}
