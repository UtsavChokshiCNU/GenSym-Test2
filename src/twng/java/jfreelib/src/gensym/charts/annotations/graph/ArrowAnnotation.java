package gensym.charts.annotations.graph;

import gensym.charts.annotations.graph.ext.PointerShapeBuilder;

import java.awt.Shape;
import java.awt.geom.Rectangle2D;

/**
 * Simple arrow graph annotation
 */
public class ArrowAnnotation extends BaseShapeAnnotation {

    /** Arrow to west */
    public static final int ARROW_W = 1;

    /** Arrow to north-west */
    public static final int ARROW_NW = 2;

    /** Arrow to north */
    public static final int ARROW_N = 3;

    /** Arrow to north-east */
    public static final int ARROW_NE = 4;

    /** Arrow to east */
    public static final int ARROW_E = 5;

    /** Arrow to south-east */
    public static final int ARROW_SE = 6;

    /** Arrow to south */
    public static final int ARROW_S = 7;

    /** Arrow to south-west */
    public static final int ARROW_SW = 8;

    /**
     * Constructor
     */
    ArrowAnnotation(AnnotationInfo info, int figure) {
        super(info, figure, true);
    }

    /**
     * {@inheritDoc}
     */
    public Shape createShape(int figure) {
        PointerShapeBuilder psb = new PointerShapeBuilder();
        psb.setLineThickness(0.0);
        psb.setArrowAngle(Math.PI/4.0);
        psb.setArrowToLengthRatio(1/2.4);
        psb.setLength(10);
        for (int i = ARROW_W; i <= ARROW_SW; i++) {
            if (figure == i) {
                return psb.buildArrow(Math.PI/4 * (i-1));
            }
        }
        return null;
    }
    
    /**
     * {@inheritDoc}
     */
    public double getLabelOffset(Shape shape) {
        Rectangle2D r2d = shape.getBounds2D();
        return 5.0 + (r2d.getCenterY() <= 0.0 ? r2d.getHeight() : 0.0);
    }
}
