package gensym.charts.annotations.graph;

import gensym.charts.ChartLineTypes;
import gensym.charts.hatching.*;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Paint;
import java.awt.Shape;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Point2D;

import java.awt.geom.Rectangle2D;
import java.awt.geom.RoundRectangle2D;
import org.jfree.chart.annotations.XYShapeAnnotation;

public class TopLeftBottomRightAnnotation extends AbstractBuilder {

    /** Top left annotation type */
    public static final int PEGAT_TOPLEFT = 46;

    /** Top left annotation type */
    public static final int PEGAT_BOTTOMRIGHT = 47;

    /** Rectangle values */
    public static final int PEGAT_RECT_THIN = 48;
    public static final int PEGAT_RECT_DASH = 49;
    public static final int PEGAT_RECT_DOT = 50;
    public static final int PEGAT_RECT_DASHDOT = 51;
    public static final int PEGAT_RECT_DASHDOTDOT = 52;
    public static final int PEGAT_RECT_MEDIUM = 53;
    public static final int PEGAT_RECT_THICK = 54;
    public static final int PEGAT_RECT_FILL = 55;

    /** Round rectangle values */
    public static final int PEGAT_ROUNDRECT_THIN = 56;
    public static final int PEGAT_ROUNDRECT_DASH = 57;
    public static final int PEGAT_ROUNDRECT_DOT = 58;
    public static final int PEGAT_ROUNDRECT_DASHDOT = 59;
    public static final int PEGAT_ROUNDRECT_DASHDOTDOT = 60;
    public static final int PEGAT_ROUNDRECT_MEDIUM = 61;
    public static final int PEGAT_ROUNDRECT_THICK = 62;
    public static final int PEGAT_ROUNDRECT_FILL = 63;

    /** Ellipse values */
    public static final int PEGAT_ELLIPSE_THIN = 64;
    public static final int PEGAT_ELLIPSE_DASH = 65;
    public static final int PEGAT_ELLIPSE_DOT = 66;
    public static final int PEGAT_ELLIPSE_DASHDOT = 67;
    public static final int PEGAT_ELLIPSE_DASHDOTDOT = 68;
    public static final int PEGAT_ELLIPSE_MEDIUM = 69;
    public static final int PEGAT_ELLIPSE_THICK = 70;
    public static final int PEGAT_ELLIPSE_FILL = 71;

    /** Rectangle values */
    public static final int PEGAT_RECT_MEDIUMDASH = 125;
    public static final int PEGAT_RECT_MEDIUMDOT = 126;
    public static final int PEGAT_RECT_MEDIUMDASHDOT = 127;
    public static final int PEGAT_RECT_MEDIUMDASHDOTDOT = 128;
    public static final int PEGAT_RECT_THICKDASH = 129;
    public static final int PEGAT_RECT_THICKDOT = 130;
    public static final int PEGAT_RECT_THICKDASHDOT = 131;
    public static final int PEGAT_RECT_THICKDASHDOTDOT = 132;

    /** Round rectangle values */
    public static final int PEGAT_ROUNDRECT_MEDIUMDASH = 133;
    public static final int PEGAT_ROUNDRECT_MEDIUMDOT = 134;
    public static final int PEGAT_ROUNDRECT_MEDIUMDASHDOT = 135;
    public static final int PEGAT_ROUNDRECT_MEDIUMDASHDOTDOT = 136;
    public static final int PEGAT_ROUNDRECT_THICKDASH = 137;
    public static final int PEGAT_ROUNDRECT_THICKDOT = 138;
    public static final int PEGAT_ROUNDRECT_THICKDASHDOT = 139;
    public static final int PEGAT_ROUNDRECT_THICKDASHDOTDOT = 140;

    /** Ellipse values */
    public static final int PEGAT_ELLIPSE_MEDIUMDASH = 141;
    public static final int PEGAT_ELLIPSE_MEDIUMDOT = 142;
    public static final int PEGAT_ELLIPSE_MEDIUMDASHDOT = 143;
    public static final int PEGAT_ELLIPSE_MEDIUMDASHDOTDOT = 144;
    public static final int PEGAT_ELLIPSE_THICKDASH = 145;
    public static final int PEGAT_ELLIPSE_THICKDOT = 146;
    public static final int PEGAT_ELLIPSE_THICKDASHDOT = 147;
    public static final int PEGAT_ELLIPSE_THICKDASHDOTDOT = 148;

    /** Rectangle values with hatching */
    public static final int PEGAT_RECT_HATCH_HORIZONTAL = 157;
    public static final int PEGAT_RECT_HATCH_VERTICAL = 158;
    public static final int PEGAT_RECT_HATCH_FDIAGONAL = 159;
    public static final int PEGAT_RECT_HATCH_BDIAGONAL = 160;
    public static final int PEGAT_RECT_HATCH_CROSS = 161;
    public static final int PEGAT_RECT_HATCH_DIAGCROSS = 162;

    /** Round rectangle values with hatching */
    public static final int PEGAT_ROUNDRECT_HATCH_HORIZONTAL = 163;
    public static final int PEGAT_ROUNDRECT_HATCH_VERTICAL = 164;
    public static final int PEGAT_ROUNDRECT_HATCH_FDIAGONAL = 165;
    public static final int PEGAT_ROUNDRECT_HATCH_BDIAGONAL = 166;
    public static final int PEGAT_ROUNDRECT_HATCH_CROSS = 167;
    public static final int PEGAT_ROUNDRECT_HATCH_DIAGCROSS = 168;

    /** Ellipse values with hatching */
    public static final int PEGAT_ELLIPSE_HATCH_HORIZONTAL = 169;
    public static final int PEGAT_ELLIPSE_HATCH_VERTICAL = 170;
    public static final int PEGAT_ELLIPSE_HATCH_FDIAGONAL = 171;
    public static final int PEGAT_ELLIPSE_HATCH_BDIAGONAL = 172;
    public static final int PEGAT_ELLIPSE_HATCH_CROSS = 173;
    public static final int PEGAT_ELLIPSE_HATCH_DIAGCROSS = 174;

    /** The top left point */
    private Point2D pointTopLeft = null;

    /** The bottom right point */
    private Point2D pointBottomRight = null;

    /**
     * Constructor
     * @param info annotation info
     */
    public TopLeftBottomRightAnnotation(AnnotationInfo info) {
        setAxis(info.getAxis());
        addInfo(info);
    }

    /**
     * {@inheritDoc}
     */
    public boolean isInfoUsed(AnnotationInfo info) {
        return pointTopLeft == null && info.getType() == PEGAT_TOPLEFT ||
                pointBottomRight == null && info.getType() == PEGAT_BOTTOMRIGHT ||
                pointTopLeft != null && pointBottomRight != null &&
                (info.getType() >= PEGAT_RECT_THIN && info.getType() <= PEGAT_ELLIPSE_FILL ||
                info.getType() >= PEGAT_RECT_MEDIUMDASH && info.getType() <= PEGAT_ELLIPSE_THICKDASHDOTDOT ||
                info.getType() >= PEGAT_RECT_HATCH_HORIZONTAL && info.getType() <= PEGAT_ELLIPSE_HATCH_DIAGCROSS);
    }

    /**
     * {@inheritDoc}
     */
    public void addInfo(AnnotationInfo info) {
        if (isInfoUsed(info)) {
            int type = info.getType();
            if (type == PEGAT_TOPLEFT) {
                pointTopLeft = new Point2D.Double(info.getX(), info.getY());
            } else if (type == PEGAT_BOTTOMRIGHT) {
                pointBottomRight = new Point2D.Double(info.getX(), info.getY());
            } else {
                XYShapeAnnotation annotation = new XYShapeAnnotation(GetShape(type),
                        getBasicStroke(type), info.getColor(),
                        getPaint(type, info.getColor()));

                addAnnotation(annotation);
                isFinished = true;
            }
        }
        addText(info, null);
    }

    /**
     * Gets shape by type
     * @param type of shape
     * @return new shape
     */
    private Shape GetShape(int type) {
        double width = pointBottomRight.getX() - pointTopLeft.getX();
        double hight = pointTopLeft.getY() - pointBottomRight.getY();

        Shape shape = new Ellipse2D.Double(pointTopLeft.getX(),
                pointBottomRight.getY(), width, hight);

        switch (type) {
            case PEGAT_RECT_THIN:
            case PEGAT_RECT_DASH:
            case PEGAT_RECT_DOT:
            case PEGAT_RECT_DASHDOT:
            case PEGAT_RECT_DASHDOTDOT:
            case PEGAT_RECT_MEDIUM:
            case PEGAT_RECT_THICK:
            case PEGAT_RECT_FILL:

            case PEGAT_RECT_MEDIUMDASH:
            case PEGAT_RECT_MEDIUMDOT:
            case PEGAT_RECT_MEDIUMDASHDOT:
            case PEGAT_RECT_MEDIUMDASHDOTDOT:
            case PEGAT_RECT_THICKDASH:
            case PEGAT_RECT_THICKDOT:
            case PEGAT_RECT_THICKDASHDOT:
            case PEGAT_RECT_THICKDASHDOTDOT:

            case PEGAT_RECT_HATCH_HORIZONTAL:
            case PEGAT_RECT_HATCH_VERTICAL:
            case PEGAT_RECT_HATCH_FDIAGONAL:
            case PEGAT_RECT_HATCH_BDIAGONAL:
            case PEGAT_RECT_HATCH_CROSS:
            case PEGAT_RECT_HATCH_DIAGCROSS:
                shape = new Rectangle2D.Double(pointTopLeft.getX(),
                        pointBottomRight.getY(), width, hight);
                break;

            case PEGAT_ROUNDRECT_THIN:
            case PEGAT_ROUNDRECT_DASH:
            case PEGAT_ROUNDRECT_DOT:
            case PEGAT_ROUNDRECT_DASHDOT:
            case PEGAT_ROUNDRECT_DASHDOTDOT:
            case PEGAT_ROUNDRECT_MEDIUM:
            case PEGAT_ROUNDRECT_THICK:
            case PEGAT_ROUNDRECT_FILL:

            case PEGAT_ROUNDRECT_MEDIUMDASH:
            case PEGAT_ROUNDRECT_MEDIUMDOT:
            case PEGAT_ROUNDRECT_MEDIUMDASHDOT:
            case PEGAT_ROUNDRECT_MEDIUMDASHDOTDOT:
            case PEGAT_ROUNDRECT_THICKDASH:
            case PEGAT_ROUNDRECT_THICKDOT:
            case PEGAT_ROUNDRECT_THICKDASHDOT:
            case PEGAT_ROUNDRECT_THICKDASHDOTDOT:

            case PEGAT_ROUNDRECT_HATCH_HORIZONTAL:
            case PEGAT_ROUNDRECT_HATCH_VERTICAL:
            case PEGAT_ROUNDRECT_HATCH_FDIAGONAL:
            case PEGAT_ROUNDRECT_HATCH_BDIAGONAL:
            case PEGAT_ROUNDRECT_HATCH_CROSS:
            case PEGAT_ROUNDRECT_HATCH_DIAGCROSS:
                shape = new RoundRectangle2D.Double(pointTopLeft.getX(),
                        pointBottomRight.getY(), width, hight, width / 5, hight / 5);
                break;
        }
        return shape;
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
            case PEGAT_ELLIPSE_FILL:
            case PEGAT_RECT_FILL:
            case PEGAT_ROUNDRECT_FILL:
                paint = color;
                break;
            case PEGAT_ELLIPSE_HATCH_HORIZONTAL:
            case PEGAT_RECT_HATCH_HORIZONTAL:
            case PEGAT_ROUNDRECT_HATCH_HORIZONTAL:
                paint = new HatchedPaint(HatchedPaint.HORIZONTAL_LINE, color, null);
                break;
            case PEGAT_ELLIPSE_HATCH_VERTICAL:
            case PEGAT_RECT_HATCH_VERTICAL:
            case PEGAT_ROUNDRECT_HATCH_VERTICAL:
                paint = new HatchedPaint(HatchedPaint.VERTICAL_LINE, color, null);
                break;
            case PEGAT_ELLIPSE_HATCH_FDIAGONAL:
            case PEGAT_RECT_HATCH_FDIAGONAL:
            case PEGAT_ROUNDRECT_HATCH_FDIAGONAL:
                paint = new HatchedPaint(HatchedPaint.LU_RB_DIAGONAL_LINE, color, null);
                break;
            case PEGAT_ELLIPSE_HATCH_BDIAGONAL:
            case PEGAT_RECT_HATCH_BDIAGONAL:
            case PEGAT_ROUNDRECT_HATCH_BDIAGONAL:
                paint = new HatchedPaint(HatchedPaint.LB_RU_DIAGONAL_LINE, color, null);
                break;
            case PEGAT_ELLIPSE_HATCH_CROSS:
            case PEGAT_RECT_HATCH_CROSS:
            case PEGAT_ROUNDRECT_HATCH_CROSS:
                paint = new HatchedPaint(HatchedPaint.HORIZONTAL_LINE | HatchedPaint.VERTICAL_LINE, color, null);
                break;
            case PEGAT_ELLIPSE_HATCH_DIAGCROSS:
            case PEGAT_RECT_HATCH_DIAGCROSS:
            case PEGAT_ROUNDRECT_HATCH_DIAGCROSS:
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
            case PEGAT_ELLIPSE_THIN:
            case PEGAT_RECT_THIN:
            case PEGAT_ROUNDRECT_THIN:

            case PEGAT_ELLIPSE_HATCH_HORIZONTAL:
            case PEGAT_ELLIPSE_HATCH_VERTICAL:
            case PEGAT_ELLIPSE_HATCH_FDIAGONAL:
            case PEGAT_ELLIPSE_HATCH_BDIAGONAL:
            case PEGAT_ELLIPSE_HATCH_CROSS:
            case PEGAT_ELLIPSE_HATCH_DIAGCROSS:

            case PEGAT_RECT_HATCH_HORIZONTAL:
            case PEGAT_RECT_HATCH_VERTICAL:
            case PEGAT_RECT_HATCH_FDIAGONAL:
            case PEGAT_RECT_HATCH_BDIAGONAL:
            case PEGAT_RECT_HATCH_CROSS:
            case PEGAT_RECT_HATCH_DIAGCROSS:

            case PEGAT_ROUNDRECT_HATCH_HORIZONTAL:
            case PEGAT_ROUNDRECT_HATCH_VERTICAL:
            case PEGAT_ROUNDRECT_HATCH_FDIAGONAL:
            case PEGAT_ROUNDRECT_HATCH_BDIAGONAL:
            case PEGAT_ROUNDRECT_HATCH_CROSS:
            case PEGAT_ROUNDRECT_HATCH_DIAGCROSS:

                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THINSOLID);
                break;
            case PEGAT_ELLIPSE_DASH:
            case PEGAT_RECT_DASH:
            case PEGAT_ROUNDRECT_DASH:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_DASH);
                break;
            case PEGAT_ELLIPSE_DOT:
            case PEGAT_RECT_DOT:
            case PEGAT_ROUNDRECT_DOT:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_DOT);
                break;
            case PEGAT_ELLIPSE_DASHDOT:
            case PEGAT_RECT_DASHDOT:
            case PEGAT_ROUNDRECT_DASHDOT:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_DASHDOT);
                break;
            case PEGAT_ELLIPSE_DASHDOTDOT:
            case PEGAT_RECT_DASHDOTDOT:
            case PEGAT_ROUNDRECT_DASHDOTDOT:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_DASHDOTDOT);
                break;
            case PEGAT_ELLIPSE_MEDIUM:
            case PEGAT_RECT_MEDIUM:
            case PEGAT_ROUNDRECT_MEDIUM:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMSOLID);
                break;
            case PEGAT_ELLIPSE_THICK:
            case PEGAT_RECT_THICK:
            case PEGAT_ROUNDRECT_THICK:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THICKSOLID);
                break;
            case PEGAT_ELLIPSE_FILL:
            case PEGAT_RECT_FILL:
            case PEGAT_ROUNDRECT_FILL:
                stroke = null;
                break;

            case PEGAT_ELLIPSE_MEDIUMDASH:
            case PEGAT_RECT_MEDIUMDASH:
            case PEGAT_ROUNDRECT_MEDIUMDASH:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMDASH);
                break;
            case PEGAT_ELLIPSE_MEDIUMDOT:
            case PEGAT_RECT_MEDIUMDOT:
            case PEGAT_ROUNDRECT_MEDIUMDOT:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMDOT);
                break;
            case PEGAT_ELLIPSE_MEDIUMDASHDOT:
            case PEGAT_RECT_MEDIUMDASHDOT:
            case PEGAT_ROUNDRECT_MEDIUMDASHDOT:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMDASHDOT);
                break;
            case PEGAT_ELLIPSE_MEDIUMDASHDOTDOT:
            case PEGAT_RECT_MEDIUMDASHDOTDOT:
            case PEGAT_ROUNDRECT_MEDIUMDASHDOTDOT:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_MEDIUMDASHDOTDOT);
                break;
            case PEGAT_ELLIPSE_THICKDASH:
            case PEGAT_RECT_THICKDASH:
            case PEGAT_ROUNDRECT_THICKDASH:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THICKDASH);
                break;
            case PEGAT_ELLIPSE_THICKDOT:
            case PEGAT_RECT_THICKDOT:
            case PEGAT_ROUNDRECT_THICKDOT:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THICKDOT);
                break;
            case PEGAT_ELLIPSE_THICKDASHDOT:
            case PEGAT_RECT_THICKDASHDOT:
            case PEGAT_ROUNDRECT_THICKDASHDOT:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THICKDASHDOT);
                break;
            case PEGAT_ELLIPSE_THICKDASHDOTDOT:
            case PEGAT_RECT_THICKDASHDOTDOT:
            case PEGAT_ROUNDRECT_THICKDASHDOTDOT:
                stroke = ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THICKDASHDOTDOT);
                break;
        }
        return stroke;
    }
}
