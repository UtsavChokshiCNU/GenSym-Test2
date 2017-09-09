package gensym.charts.annotations.graph;

import gensym.charts.annotations.graph.ext.XYMultiLineAnnotation;
import java.awt.Color;
import java.util.LinkedList;
import java.util.List;

import org.jfree.chart.annotations.XYAnnotation;

/**
 * Abstract Graph annotation builder
 */
public abstract class AbstractBuilder {

    /** Text distance */
    private static final double TEXT_DISTANCE = 12;

    /** List of annotations */
    private List<AnnotationWithAxis> annotations = new LinkedList<AnnotationWithAxis>();

    /** Finished building flag */
    protected boolean isFinished = false;

    /** Corresponding axis */
    int axis = 0;
    
    /**
     * Tests if annotation info is used by Annotation 
     * @param info the annotation info
     * @return true if annotation info is used by Annotation
     */
    public boolean isInfoUsed(AnnotationInfo info) {
        return false;
    }
    
    /**
     * Adds annotation info to annotation
     * @param info the info to be added
     */
    public void addInfo(AnnotationInfo info) {
    }
    
    /**
     * Build annotation
     * @return the annotation
     */
    public AnnotationWithAxis[] build() {
        return annotations.toArray(new AnnotationWithAxis[0]);
    }
    
    /**
     * Tests if build routine is done
     * @return true if build routine is done
     */
    public boolean isBuildFinished() {
        return isFinished;
    }

    /**
     * Adds annotation to collection
     * @param info  the AnnotationInfo
     * @param annotation  the XYAnnotation
     */
    protected void addAnnotation(XYAnnotation annotation) {
        annotations.add(new AnnotationWithAxis(annotation, axis));
    }
    
    /**
     * Adds text to annotation
     * @param info annotation info
     * @param defColor default text color
     * @param textDistance specified text distance
     */
    protected void addText(AnnotationInfo info, Color defColor, double textDistance) {
        AnnotationTextInfo annotationText = AnnotationTextInfo.parseText(info.getText());
        if (annotationText != null) {
            double x = info.getX();
            double y = info.getY();
            if (annotationText.isCoordinatesUsed()) {
                x = annotationText.getX();
                y = annotationText.getY();
                textDistance = 0;
            }
            XYMultiLineAnnotation text = new
                    XYMultiLineAnnotation(annotationText.getText(), x, y, 0.0f, (float) -textDistance);

            if (info.getFactory().getFont() != null) {
                text.setFont(info.getFactory().getFont());
            }
            
            if (info.getColor() != null) {
                text.setPaint(info.getColor());
            } else if (defColor != null) {
                text.setPaint(defColor);
            }
            addAnnotation(text);
        }
    }
    
    /**
     * Adds text to annotation with text distance by default
     * @param info annotation info
     * @param defColor default text color
     */
    protected void addText(AnnotationInfo info, Color defColor) {
        addText(info, defColor, TEXT_DISTANCE);
    }

    /**
     * Returns corresponding axis
     * @return the corresponding axis
     */
    public int getAxis() {
        return axis;
    }

    /**
     * Set corresponding axis
     * @param axis  the corresponding axis to set
     */
    public void setAxis(int axis) {
        this.axis = axis;
    }
}
