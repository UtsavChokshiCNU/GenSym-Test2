package gensym.charts.annotations.graph;

import java.awt.Shape;
import java.awt.geom.Ellipse2D;

/**
 * Dot graph annotation
 */
public class DotAnnotation extends BaseShapeAnnotation {

    /**
     * Constructor
     * @param info annotation info
     * @param dotSize the dot size
     */
    DotAnnotation(AnnotationInfo info, int dotSize, boolean solid) {
        super(info, dotSize, solid);
    }

    /**
     * {@inheritDoc}
     */
    public Shape createShape(int dotSize) {
        return new Ellipse2D.Double(-dotSize/2, -dotSize/2, dotSize, dotSize);
    }
}
