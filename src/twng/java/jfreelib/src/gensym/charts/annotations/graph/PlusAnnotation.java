package gensym.charts.annotations.graph;

import java.awt.Shape;

import org.jfree.util.ShapeUtilities;

/**
 * Plus graph annotation
 */
public class PlusAnnotation extends BaseShapeAnnotation {
    /**
     * Constructor
     * @param info annotation info
     * @param crossSize the cross size
     */
    PlusAnnotation(AnnotationInfo info, int crossSize) {
        super(info, crossSize, true);
    }
    
    /**
     * {@inheritDoc}
     */
    public Shape createShape(int crossSize) {
        return ShapeUtilities.createRegularCross(crossSize/2, 0);
    }
}
