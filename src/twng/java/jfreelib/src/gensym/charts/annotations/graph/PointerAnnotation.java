package gensym.charts.annotations.graph;

import gensym.charts.annotations.graph.ext.PointerShapeBuilder;

import java.awt.Shape;
import java.awt.geom.Rectangle2D;

/**
 * Simple pointer graph annotation
 */
public class PointerAnnotation extends BaseShapeAnnotation {

    /** Pointer shape */
    public static final int POINTER = 1;

    /** Small vector shape */
    public static final int VECTOR_SMALL = 2;

    /** Medium vector shape */
    public static final int VECTOR_MEDIUM = 3;

    /** Large vector shape */
    public static final int VECTOR_LARGE = 4;

    /** Small arrow shape */
    public static final int ARROW_SMALL = 5;

    /** Medium arrow shape */
    public static final int ARROW_MEDIUM = 6;

    /** Large arrow shape */
    public static final int ARROW_LARGE = 7;

    /** Default angle: the 45 degrees */
    public static final double DEFAULT_ANGLE = -Math.PI/4;

    /**
     * Constructor
     */
    public PointerAnnotation(AnnotationInfo info, int figure) {
        super(info, figure, true);
    }

    /**
     * {@inheritDoc}
     */
    public Shape createShape(int figure) {
        PointerShapeBuilder psb = new PointerShapeBuilder();
        psb.setLineThickness(0.0);
        psb.setArrowAngle(Math.PI/8.0);

        switch (figure) {
            case POINTER:
                psb.setArrowToLengthRatio(1/8.0);
                psb.setLength(20);
                return psb.buildPointer(DEFAULT_ANGLE);
            case VECTOR_SMALL:
                psb.setLength(30);
                return psb.buildVector(DEFAULT_ANGLE);
            case VECTOR_MEDIUM:
                psb.setLength(45);
                psb.setLineThickness(1.0);
                return psb.buildVector(DEFAULT_ANGLE);
            case VECTOR_LARGE:
                psb.setLength(60);
                psb.setLineThickness(2.0);
                return psb.buildVector(DEFAULT_ANGLE);
            case ARROW_SMALL:
                psb.setLength(30);
                return psb.buildArrow(DEFAULT_ANGLE);
            case ARROW_MEDIUM:
                psb.setLength(45);
                psb.setLineThickness(1.0);
                return psb.buildArrow(DEFAULT_ANGLE);
            case ARROW_LARGE:
                psb.setLength(60);
                psb.setLineThickness(2.0);
                return psb.buildArrow(DEFAULT_ANGLE);
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
