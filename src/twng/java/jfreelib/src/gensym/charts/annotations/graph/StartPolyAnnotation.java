package gensym.charts.annotations.graph;

import gensym.charts.ChartLineTypes;
import gensym.charts.hatching.HatchedPaint;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Paint;
import java.awt.geom.Point2D;

import java.util.LinkedList;
import java.util.List;

import org.jfree.chart.annotations.XYPolygonAnnotation;

public class StartPolyAnnotation extends AbstractBuilder {

    /** Add polygon point annotation type */
    public static final int PEGAT_ADDPOLYPOINT = 75;

    /** End polygon annotation type */
    public static final int PEGAT_ENDPOLYGON = 76;

    /** Polyline values */
    public static final int PEGAT_ENDPOLYLINE_THIN = 77;
    public static final int PEGAT_ENDPOLYLINE_MEDIUM = 78;
    public static final int PEGAT_ENDPOLYLINE_THICK = 79;
    public static final int PEGAT_ENDPOLYLINE_DASH = 80;
    public static final int PEGAT_ENDPOLYLINE_DOT = 81;
    public static final int PEGAT_ENDPOLYLINE_DASHDOT = 82;
    public static final int PEGAT_ENDPOLYLINE_DASHDOTDOT = 83;

    /** Polyline values */
    public static final int PEGAT_ENDPOLYLINE_MEDIUMDASH = 149;
    public static final int PEGAT_ENDPOLYLINE_MEDIUMDOT = 150;
    public static final int PEGAT_ENDPOLYLINE_MEDIUMDASHDOT = 151;
    public static final int PEGAT_ENDPOLYLINE_MEDIUMDASHDOTDOT = 152;
    public static final int PEGAT_ENDPOLYLINE_THICKDASH = 153;
    public static final int PEGAT_ENDPOLYLINE_THICKDOT = 154;
    public static final int PEGAT_ENDPOLYLINE_THICKDASHDOT = 155;
    public static final int PEGAT_ENDPOLYLINE_THICKDASHDOTDOT = 156;

    /** Polygon values with hatching */
    public static final int PEGAT_ENDPOLYGON_HATCH_HORIZONTAL = 175;
    public static final int PEGAT_ENDPOLYGON_HATCH_VERTICAL = 176;
    public static final int PEGAT_ENDPOLYGON_HATCH_FDIAGONAL = 177;
    public static final int PEGAT_ENDPOLYGON_HATCH_BDIAGONAL = 178;
    public static final int PEGAT_ENDPOLYGON_HATCH_CROSS = 179;
    public static final int PEGAT_ENDPOLYGON_HATCH_DIAGCROSS = 180;

    /** Points */
    List<Point2D> points = new LinkedList<Point2D>();

    /**
     * Constructor
     * @param info annotation info
     */
    StartPolyAnnotation(AnnotationInfo info) {
        setAxis(info.getAxis());
        points.add(new Point2D.Double(info.getX(), info.getY()));
        addText(info, null);
    }

    /**
     * {@inheritDoc}
     */
    public boolean isInfoUsed(AnnotationInfo info) {
        int type = info.getType();
        return type >= PEGAT_ADDPOLYPOINT && type <= PEGAT_ENDPOLYLINE_DASHDOTDOT ||
                type >= PEGAT_ENDPOLYLINE_MEDIUMDASH && type <= PEGAT_ENDPOLYLINE_THICKDASHDOTDOT ||
                type >= PEGAT_ENDPOLYGON_HATCH_HORIZONTAL && type <= PEGAT_ENDPOLYGON_HATCH_DIAGCROSS;
    }

    /**
     * {@inheritDoc}
     */
    public void addInfo(AnnotationInfo info) {
        if (isInfoUsed(info)) {
            int type = info.getType();
            points.add(new Point2D.Double(info.getX(), info.getY()));

            switch (type) {
                case PEGAT_ADDPOLYPOINT:
                    break;

                case PEGAT_ENDPOLYGON:
                case PEGAT_ENDPOLYLINE_THIN:
                case PEGAT_ENDPOLYLINE_MEDIUM:
                case PEGAT_ENDPOLYLINE_THICK:
                case PEGAT_ENDPOLYLINE_DASH:
                case PEGAT_ENDPOLYLINE_DOT:
                case PEGAT_ENDPOLYLINE_DASHDOT:
                case PEGAT_ENDPOLYLINE_DASHDOTDOT:

                case PEGAT_ENDPOLYLINE_MEDIUMDASH:
                case PEGAT_ENDPOLYLINE_MEDIUMDOT:
                case PEGAT_ENDPOLYLINE_MEDIUMDASHDOT:
                case PEGAT_ENDPOLYLINE_MEDIUMDASHDOTDOT:
                case PEGAT_ENDPOLYLINE_THICKDASH:
                case PEGAT_ENDPOLYLINE_THICKDOT:
                case PEGAT_ENDPOLYLINE_THICKDASHDOT:
                case PEGAT_ENDPOLYLINE_THICKDASHDOTDOT:

                case PEGAT_ENDPOLYGON_HATCH_HORIZONTAL:
                case PEGAT_ENDPOLYGON_HATCH_VERTICAL:
                case PEGAT_ENDPOLYGON_HATCH_FDIAGONAL:
                case PEGAT_ENDPOLYGON_HATCH_BDIAGONAL:
                case PEGAT_ENDPOLYGON_HATCH_CROSS:
                case PEGAT_ENDPOLYGON_HATCH_DIAGCROSS:

                    XYPolygonAnnotation annotation =
                            new XYPolygonAnnotation(createPolygonArray(), getBasicStroke(type),
                            info.getColor(), getPaint(type, info.getColor()));
                    addAnnotation(annotation);
                    isFinished = true;
                    break;
            }
        }

        addText(info, null);
    }

    /**
     * Creates polygon array
     * @return points array
     */
    private double[] createPolygonArray() {
        double[] array = new double[points.size() * 2];

        int index = 0;
        for (Point2D point : points) {
            array[index++] = point.getX();
            array[index++] = point.getY();
        }

        return array;
    }

    /**
     * Gets figure paint
     * @param type of figure
     * @param color of lines
     * @return new Paint
     */
    private Paint getPaint(int type, Color color) {
        Paint paint = null;
        switch (type) {
            case PEGAT_ENDPOLYGON:
                paint = color;
                break;
            case PEGAT_ENDPOLYGON_HATCH_HORIZONTAL:
                paint = new HatchedPaint(HatchedPaint.HORIZONTAL_LINE, color, null);
                break;
            case PEGAT_ENDPOLYGON_HATCH_VERTICAL:
                paint = new HatchedPaint(HatchedPaint.VERTICAL_LINE, color, null);
                break;
            case PEGAT_ENDPOLYGON_HATCH_FDIAGONAL:
                paint = new HatchedPaint(HatchedPaint.LU_RB_DIAGONAL_LINE, color, null);
                break;
            case PEGAT_ENDPOLYGON_HATCH_BDIAGONAL:
                paint = new HatchedPaint(HatchedPaint.LB_RU_DIAGONAL_LINE, color, null);
                break;
            case PEGAT_ENDPOLYGON_HATCH_CROSS:
                paint = new HatchedPaint(HatchedPaint.HORIZONTAL_LINE | HatchedPaint.VERTICAL_LINE, color, null);
                break;
            case PEGAT_ENDPOLYGON_HATCH_DIAGCROSS:
                paint = new HatchedPaint(HatchedPaint.LU_RB_DIAGONAL_LINE | HatchedPaint.LB_RU_DIAGONAL_LINE, color, null);
                break;
        }
        return paint;
    }

    /**
     * Gets BasicStroke for ellipse
     * @param type of ellipse
     * @return BasicStroke
     */
    private BasicStroke getBasicStroke(int type) {
        BasicStroke stroke = null;

        switch (type) {
            case PEGAT_ENDPOLYLINE_THIN:
            case PEGAT_ENDPOLYGON_HATCH_HORIZONTAL:
            case PEGAT_ENDPOLYGON_HATCH_VERTICAL:
            case PEGAT_ENDPOLYGON_HATCH_FDIAGONAL:
            case PEGAT_ENDPOLYGON_HATCH_BDIAGONAL:
            case PEGAT_ENDPOLYGON_HATCH_CROSS:
            case PEGAT_ENDPOLYGON_HATCH_DIAGCROSS:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THINSOLID);
                break;
            case PEGAT_ENDPOLYLINE_DASH:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_DASH);
                break;
            case PEGAT_ENDPOLYLINE_DOT:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_DOT);
                break;
            case PEGAT_ENDPOLYLINE_DASHDOT:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_DASHDOT);
                break;
            case PEGAT_ENDPOLYLINE_DASHDOTDOT:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_DASHDOTDOT);
                break;
            case PEGAT_ENDPOLYLINE_MEDIUM:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMSOLID);
                break;
            case PEGAT_ENDPOLYLINE_THICK:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THICKSOLID);
                break;
            case PEGAT_ENDPOLYLINE_MEDIUMDASH:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMDASH);
                break;
            case PEGAT_ENDPOLYLINE_MEDIUMDOT:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMDOT);
                break;
            case PEGAT_ENDPOLYLINE_MEDIUMDASHDOT:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMDASHDOT);
                break;
            case PEGAT_ENDPOLYLINE_MEDIUMDASHDOTDOT:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMDASHDOTDOT);
                break;
            case PEGAT_ENDPOLYLINE_THICKDASH:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THICKDASH);
                break;
            case PEGAT_ENDPOLYLINE_THICKDOT:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THICKDOT);
                break;
            case PEGAT_ENDPOLYLINE_THICKDASHDOT:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THICKDASHDOT);
                break;
            case PEGAT_ENDPOLYLINE_THICKDASHDOTDOT:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THICKDASHDOTDOT);
                break;
        }
        return stroke;
    }
}
