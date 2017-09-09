package gensym.charts.annotations.graph;

import java.awt.Shape;
import org.jfree.util.ShapeUtilities;

/**
 * Square graph annotation
 */
public class SquareAnnotation extends BaseShapeAnnotation {
    /**
     * Constructor
     * @param info annotation info
     * @param shapeSize the shape size
     */
    SquareAnnotation(AnnotationInfo info, int shapeSize, boolean solid) {
        super(info, shapeSize, solid);
    }
    
    /**
     * {@inheritDoc}
     */
    public Shape createShape(int shapeSize) {
        return ShapeUtilities.rotateShape(ShapeUtilities.createDiamond(shapeSize / 2), Math.PI/4, 0, 0);
    }
}
