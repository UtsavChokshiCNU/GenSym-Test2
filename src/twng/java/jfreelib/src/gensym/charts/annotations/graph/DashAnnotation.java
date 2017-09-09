package gensym.charts.annotations.graph;

import java.awt.Shape;
import java.awt.geom.Rectangle2D;

/**
 * Dash graph annotation
 */
public class DashAnnotation extends BaseShapeAnnotation {

    /**
     * Constructor
     * @param info annotation info
     */
    DashAnnotation(AnnotationInfo info) {
        super(info, 
              AnnotationBuildersFactory.SHAPE_SIZE_SMALL, 
              AnnotationBuildersFactory.SHAPE_SOLID_NO);
    }

    /**
     * {@inheritDoc}
     */
    public Shape createShape(int shapeSize) {
        return new Rectangle2D.Double(-shapeSize/2, 0, shapeSize, 0.05);
    }
}
