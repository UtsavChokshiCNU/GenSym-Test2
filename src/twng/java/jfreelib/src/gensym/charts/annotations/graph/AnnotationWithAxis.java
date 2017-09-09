package gensym.charts.annotations.graph;

import org.jfree.chart.annotations.XYAnnotation;

/**
 * Simple graph annotation with specified axis class
 */
public class AnnotationWithAxis {
    
    /** XYAnnotation */
    private XYAnnotation annotation;

    /** Axis */
    private int axis = 0;

    /**
     * Constructor with specified XYAnnotation
     * @param annotation the XYAnnotation
     */
    public AnnotationWithAxis(XYAnnotation annotation, int axis) {
        if (annotation == null) {
            throw new IllegalArgumentException("The 'annotation' is null.");
        }
        this.annotation = annotation;
        this.axis = axis;
    }
    
    /**
     * Gets annotation
     * @return the annotation
     */
    public XYAnnotation getAnnotation() {
        return annotation;
    }
    
    /**
     * Gets axis
     * @return the axis
     */
    public int getAxis() {
        return axis;
    }
}
