package gensym.charts.annotations.graph;

import java.awt.Shape;

import org.jfree.util.ShapeUtilities;

/**
 * Diamond graph annotation
 */
public class DiamondAnnotation extends BaseShapeAnnotation {
    /**
     * Constructor
     * @param info annotation info
     * @param diamondSize the diamond size
     */
    DiamondAnnotation(AnnotationInfo info, int diamondSize, boolean solid) {
        super(info, diamondSize, solid);
    }
    
    /**
     * {@inheritDoc}
     */
    public Shape createShape(int shapeSize) {
        return ShapeUtilities.createDiamond(shapeSize/2);
    }
}
