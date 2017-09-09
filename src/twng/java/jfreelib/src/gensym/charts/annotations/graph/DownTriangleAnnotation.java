package gensym.charts.annotations.graph;

import java.awt.Shape;

import org.jfree.util.ShapeUtilities;

/**
 * Pointer graph annotation
 */
public class DownTriangleAnnotation extends BaseShapeAnnotation {
    /**
     * Constructor
     * @param info annotation info
     * @param shapeSize the shape size
     */
    DownTriangleAnnotation(AnnotationInfo info, int shapeSize, boolean solid) {
        super(info, shapeSize, solid);
    }
    
    /**
     * {@inheritDoc}
     */
    public Shape createShape(int shapeSize) {
        return ShapeUtilities.createDownTriangle(shapeSize/2);
    }
}
