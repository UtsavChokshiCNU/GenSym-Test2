package gensym.charts.annotations.graph;

import java.awt.Shape;

import org.jfree.util.ShapeUtilities;

/**
 * UpTriangle graph annotation
 */
public class UpTriangleAnnotation extends BaseShapeAnnotation {
    /**
     * Constructor
     * @param info annotation info
     * @param shapeSize the shape size
     */
    UpTriangleAnnotation(AnnotationInfo info, int shapeSize, boolean solid) {
        super(info, shapeSize, solid);
    }
    /**
     * {@inheritDoc}
     */
    public Shape createShape(int shapeSize) {
        return ShapeUtilities.createUpTriangle(shapeSize/2);
    }
}
