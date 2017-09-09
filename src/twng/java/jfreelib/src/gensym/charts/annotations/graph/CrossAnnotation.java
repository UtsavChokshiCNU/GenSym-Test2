package gensym.charts.annotations.graph;

import java.awt.Shape;

import org.jfree.util.ShapeUtilities;

/**
 * Cross graph annotation
 */
public class CrossAnnotation extends BaseShapeAnnotation {
    /**
     * Constructor
     * @param info annotation info
     * @param crossSize the cross size
     */
    CrossAnnotation(AnnotationInfo info, int crossSize) {
        super(info, crossSize, true);
    }
    
    /**
     * {@inheritDoc}
     */
    public Shape createShape(int crossSize) {
        return ShapeUtilities.createDiagonalCross(crossSize / 2, 0);
    }
    
}
