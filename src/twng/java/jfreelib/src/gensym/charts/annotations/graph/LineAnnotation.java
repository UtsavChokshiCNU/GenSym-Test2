package gensym.charts.annotations.graph;

import gensym.charts.annotations.graph.ext.XYArrowAnnotation;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Stroke;
import java.awt.geom.Point2D;

import org.jfree.chart.annotations.XYAnnotation;
import org.jfree.chart.annotations.XYLineAnnotation;

/**
 * Line graph annotation
 */
public class LineAnnotation extends AbstractBuilder {

    /** Line continue annotation type */
    public static final int PEGAT_LINECONTINUE = 45;

    /** Vector values */
    public static final int PEGAT_VECTOR_SMALL = 181;
    public static final int PEGAT_VECTOR_MEDIUM = 182;
    public static final int PEGAT_VECTOR_LARGE = 183;

    /** Arrow values */
    public static final int PEGAT_ARROW_SMALL = 184;
    public static final int PEGAT_ARROW_MEDIUM = 185;
    public static final int PEGAT_ARROW_LARGE = 186;

    /** Line color */
    private Color lineColor = Color.BLACK;

    /** Line stroke */
    private Stroke lineStroke;

    /** Arrow stroke */
    private Stroke arrowStroke;

    /** The last line point */
    private Point2D lastPoint = null;

    /**
     * Constructor
     * @param info annotation info
     * @param lineWidth line width
     */
    LineAnnotation(AnnotationInfo info, BasicStroke lineStroke, BasicStroke arrowStroke) {
        setAxis(info.getAxis());
        this.lineStroke = lineStroke;
        this.arrowStroke = arrowStroke != null ? arrowStroke : lineStroke;
        if (info.getColor() != null) {
            lineColor = info.getColor();
        }
        addLine(info);
    }

    /**
     * Adds line
     * @param info annotation info
     */
    private void addLine(AnnotationInfo info) {
        if (lastPoint == null) {
            // create first point
            lastPoint = new Point2D.Double(info.getX(), info.getY());
        } else {
            addAnnotation(getAnnotation(info));
            lastPoint.setLocation(info.getX(), info.getY());
        }

        addText(info, lineColor);
    }

    /**
     * Gets required annotation
     * @param info of annotation
     * @return new XYAnnotation
     */
    private XYAnnotation getAnnotation(AnnotationInfo info) {
        XYAnnotation annotation = null;
        if (isArrowNeeded(info) || isVectorNeeded(info)) {
            XYArrowAnnotation arrowAnnotation = new XYArrowAnnotation(lastPoint.getX(), lastPoint.getY(),
                    info.getX(), info.getY(), getSize(info.getType()), lineStroke, arrowStroke, lineColor);
            arrowAnnotation.setRightVisible(!isVectorNeeded(info));
            annotation = arrowAnnotation;

        } else {
            XYLineAnnotation lineAnnotation = new XYLineAnnotation(lastPoint.getX(), lastPoint.getY(),
                    info.getX(), info.getY(), lineStroke, lineColor);
            annotation = lineAnnotation;
        }
        return annotation;
    }

    /**
     * Return true, if it's arrow annotation type
     * @param info of annotation
     * @return bool value
     */
    private boolean isArrowNeeded(AnnotationInfo info) {
        return info.getType() == PEGAT_ARROW_SMALL ||
                info.getType() == PEGAT_ARROW_MEDIUM ||
                info.getType() == PEGAT_ARROW_LARGE;
    }

    /**
     * Return true, if it's vector annotation type
     * @param info of annotation
     * @return bool value
     */
    private boolean isVectorNeeded(AnnotationInfo info) {
        return info.getType() == PEGAT_VECTOR_SMALL ||
                info.getType() == PEGAT_VECTOR_MEDIUM ||
                info.getType() == PEGAT_VECTOR_LARGE;
    }

    /**
     * Gets BasicStroke for vertors & arrows
     * @param type of figure
     * @return double size
     */
    private double getSize(int type) {
        double size = XYArrowAnnotation.MEDIUM;

        switch (type) {
            case PEGAT_VECTOR_SMALL:
            case PEGAT_ARROW_SMALL:
                size = XYArrowAnnotation.SMALL;
                break;

            case PEGAT_VECTOR_MEDIUM:
            case PEGAT_ARROW_MEDIUM:
                size = XYArrowAnnotation.MEDIUM;
                break;

            case PEGAT_VECTOR_LARGE:
            case PEGAT_ARROW_LARGE:
                size = XYArrowAnnotation.LARGE;
                break;
        }

        return size;
    }

    /**
     * {@inheritDoc}
     */
    public boolean isInfoUsed(AnnotationInfo info) {
        return info.getType() == PEGAT_LINECONTINUE ||
                isArrowNeeded(info) || isVectorNeeded(info);
    }

    /**
     * {@inheritDoc}
     */
    public void addInfo(AnnotationInfo info) {
        if (isInfoUsed(info)) {
            addLine(info);
        }
    }
}
