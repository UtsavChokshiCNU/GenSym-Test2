package gensym.charts.j3d.primitives;

import gensym.charts.j3d.*;
import java.awt.*;
import java.awt.geom.Line2D;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.util.List;

import org.jfree.chart.axis.NumberTick;
import org.jfree.chart.axis.TickType;
import org.jfree.text.TextUtilities;
import org.jfree.ui.RectangleInsets;
import org.jfree.ui.TextAnchor;

/**
 * 3D axis primitive
 * TODO: this class should be refactored
 */
public class AxisPlane3DPrimitive extends Rectangle3DPrimitive {
    
    /** Min grid length constant */
    public static float MIN_GRID_LENGTH = 10.0f;

    /** The default grid line stroke */
    public static final Stroke DEFAULT_GRIDLINE_STROKE = new BasicStroke(0.5f,
            BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL, 0.0f, new float[] {2.0f, 2.0f}, 0.0f);
    
    /** The default grid line paint */
    public static final Paint DEFAULT_GRIDLINE_PAINT = Color.LIGHT_GRAY;

    /** Axis plane normal */
    private Point3D normal = null;

    /** Horizontal Axis (for AB and CD sides) */
    private Axis3D horizontalAxis = null;

    /** Vertical Axis (for AD and BC sides) */
    private Axis3D verticalAxis = null;
    
    /**
     * Constructor
     * @param a the A point of ABCD rectangle
     * @param b the B point of ABCD rectangle
     * @param c the C point of ABCD rectangle
     * @param d the D point of ABCD rectangle
     * @param normal plane normal
     */
    public AxisPlane3DPrimitive(Point3D a, Point3D b, Point3D c, Point3D d, Point3D normal) {
        super(a, b, c, d);
        this.normal = normal;
    }

    /**
     * Sets vertical axis
     * @param axis the new vertical axis
     */
    public void setVerticalAxis(Axis3D axis) {
        verticalAxis = axis;
    }
    
    /**
     * Sets horizontal axis
     * @param axis the new horizontal axis
     */
    public void setHorizontalAxis(Axis3D axis) {
        horizontalAxis = axis;
    }

    /**
     * {@inheritDoc}
     */
    public double averageZValue() {
    	return Double.MAX_VALUE;
    }
    
    /**
     * Tests whether horizontal axis is visible
     * @return true if horizontal axis is visible
     */
    public boolean isHorizontalAxisVisible() {
        return horizontalAxis != null && horizontalAxis.isVisible();
    }

    /**
     * Tests whether vertical axis is visible
     * @return true if vertical axis is visible
     */
    public boolean isVerticalAxisVisible() {
        return verticalAxis != null && verticalAxis.isVisible();
    }
    
    /**
     * Tests axes visibility
     * @return true if one of axes is visible
     */
    public boolean isAxesVisible() {
        return isHorizontalAxisVisible() || isVerticalAxisVisible();
    }

    /**
     * {@inheritDoc}
     */
    public Object3DPrimitive transform(ViewPoint viewPoint) {
        Point3D newA = viewPoint.transform(getA());
        Point3D newB = viewPoint.transform(getB());
        Point3D newC = viewPoint.transform(getC());
        Point3D newD = viewPoint.transform(getD());

        Point3D newNormal = viewPoint.transform(normal, false);
        
        AxisPlane3DPrimitive plane = new AxisPlane3DPrimitive(newA, newB, newC, newD, newNormal);
        plane.copy(this);
        
        plane.setHorizontalAxis(horizontalAxis);
        plane.setVerticalAxis(verticalAxis);
        plane.setShadesVisible(isShadesVisible());

        return plane;
    }

    /**
     * {@inheritDoc}
     */
    public void draw(Graphics2D g2, Point3D sun, ViewPoint viewPoint) {
        if (isVisible()) {
            super.draw(g2, sun, viewPoint);

            if (isHorizontalAxisVisible()) {
                drawAxisGrid(g2, viewPoint, horizontalAxis, false);
            }
            
            if (isVerticalAxisVisible()) {
                drawAxisGrid(g2, viewPoint, verticalAxis, true);
            }
        }
    }

    /**
     * Tests visibility
     * @return true if primitive is visible
     */
    public boolean isVisible() {
        return normal.getZ() > 0 && isAxesVisible();
    }
    
    /**
     * Draws grid
     * @param g2 graphic object
     * @param viewPoint view point
     * @param axis corresponding axis
     * @param vertical vertical axis flag
     */
    private void drawAxisGrid(Graphics2D g2, ViewPoint viewPoint, Axis3D axis, boolean vertical) {
        Point2D start1 = viewPoint.toScreen(getA());
        Point2D end1 = viewPoint.toScreen(vertical ? getB() : getD());
        
        Point3D point = vertical ? getD() : getB();
        
        Point2D start2 = viewPoint.toScreen(point);
        Point2D end2 = viewPoint.toScreen(getC());
        
        Point2D line1 = makeVector(end1, start1);
        Point2D line2 = makeVector(end2, start2);
        double length1 = Math.sqrt(line1.getX() * line1.getX() + line1.getY() * line1.getY());
        double length2 = Math.sqrt(line2.getX() * line2.getX() + line2.getY() * line2.getY());
        if (length1 < MIN_GRID_LENGTH || length2 < MIN_GRID_LENGTH) {
            return;
        }
        
        List<NumberTick> ticks = null;
        if (length1 > length2) {
            ticks = axis.getTicks(g2, start1, end1);
        } else {
            ticks = axis.getTicks(g2, start2, end2);
        }
        
        double length = axis.getRange().getLength();
        double start = axis.getRange().getLowerBound();
        
        double tickWidth = 0;
        for (NumberTick tick : ticks) {
            double xx1 = start1.getX() - line1.getX() * (tick.getValue() - start) / length;
            double yy1 = start1.getY() - line1.getY() * (tick.getValue() - start) / length;
            
            double xx2 = start2.getX() - line2.getX() * (tick.getValue() - start) / length;
            double yy2 = start2.getY() - line2.getY() * (tick.getValue() - start) / length;
            
            if (tick.getTickType() == TickType.MAJOR) {
                g2.setPaint(DEFAULT_GRIDLINE_PAINT);
                g2.setStroke(DEFAULT_GRIDLINE_STROKE);
                
                g2.drawLine((int) xx1, (int) yy1, (int) xx2, (int) yy2);
                
                double width = 0;
                if (getA().getZ() > point.getZ()) {
                    width = drawTick(g2, xx2, yy2, makeVector(xx1, yy1, xx2, yy2), tick, axis);
                } else {
                    width = drawTick(g2, xx1, yy1, makeVector(xx2, yy2, xx1, yy1), tick, axis);
                }
                tickWidth = Math.max(tickWidth, width);
            }
        }
        
        double x1 = (start1.getX() + end1.getX()) / 2;
        double y1 = (start1.getY() + end1.getY()) / 2;
        double x2 = (start2.getX() + end2.getX()) / 2;
        double y2 = (start2.getY() + end2.getY()) / 2;
        if (getA().getZ() > point.getZ()) {
            drawAxisLabel(g2, x2, y2, makeVector(x1, y1, x2, y2), makeVector(start2, end2), tickWidth * 1.5, axis);
        } else {
            drawAxisLabel(g2, x1, y1, makeVector(x2, y2, x1, y1), makeVector(start1, end1), tickWidth * 1.5, axis);
        }
    }

    /**
     * Draws axis label
     * @param g2 graphic object
     * @param x label x position
     * @param y label y position
     * @param direction label offset direction
     * @param textDirection label text direction
     * @param distance label distance
     * @param axis corresponding axis
     */
    private void drawAxisLabel(Graphics2D g2, double x, double y, Point2D direction, Point2D textDirection, double distance, Axis3D axis) {
        if (axis.getLabel() == null || axis.getLabel().isEmpty()) {
            return;
        }
        
        double length = Math.sqrt(direction.getX() * direction.getX() + direction.getY() * direction.getY());
        double dx = direction.getX() / length;
        double dy = direction.getY() / length;

        Font font = axis.getLabelFont();
        RectangleInsets insets = axis.getLabelInsets();
        g2.setFont(font);
        g2.setPaint(axis.getLabelPaint());
        FontMetrics fm = g2.getFontMetrics();
        
        Rectangle2D labelBounds = TextUtilities.getTextBounds(axis.getLabel(), g2, fm);
        double labelx = x + distance * dx;
        double labely = y + distance * dy + insets.getBottom() * dy + dy * labelBounds.getHeight() / 2.0;
        
        double angle = Math.PI / 2;
        if (Math.abs(textDirection.getX()) < Double.MIN_VALUE) {
            angle = 0;
        } else {
            angle = Math.atan(textDirection.getY() / textDirection.getX());
        }

        TextUtilities.drawRotatedString(axis.getLabel(), g2, (float) labelx,
                (float) labely, TextAnchor.CENTER, angle, TextAnchor.CENTER);
    }
    /**
     * Draws tick 
     * @param g2 graphic object
     * @param x x mark screen coordinate
     * @param y y mark screen coordinate
     * @param direction mark direction
     * @param tick tick to draw
     * @param axis corresponding axis
     * @return tick text width
     */
    private double drawTick(Graphics2D g2, double x, double y, Point2D direction, NumberTick tick, Axis3D axis) {
        if (normal.getZ() < 0.025) {
            return 1.0;
        }
        double length = Math.sqrt(direction.getX() * direction.getX() + direction.getY() * direction.getY());
        double dx = direction.getX() / length;
        double dy = direction.getY() / length;

        double insideLength = axis.getTickMarkInsideLength();
        double outsideLength = axis.getTickMarkOutsideLength();
        if (axis.isGridLineVisible()) {
            g2.setPaint(axis.getTickMarkPaint());
            g2.setStroke(axis.getTickMarkStroke());
            if (insideLength > 0 || outsideLength > 0) {
                g2.draw(new Line2D.Double(x - dx * insideLength, y - dy * insideLength, x + dx * outsideLength, y + dy * outsideLength));
            }
        }
        
        g2.setPaint(axis.getTickLabelPaint());
        g2.setFont(axis.getTickLabelFont());
        double textX = x + dx * outsideLength;
        double textY = y + dy * outsideLength;
        Rectangle2D textBounds = g2.getFontMetrics().getStringBounds(tick.getText(), g2);

        if (Math.abs(dx) < Double.MIN_VALUE) {
            dx = Double.MIN_VALUE;
        }
        double angle = Math.atan(dy / dx);

        if (dx > 0) {
            textX += dx * axis.getLabelInsets().getLeft();
            textY += dy * axis.getLabelInsets().getLeft();
        } else {
            textX += dx * (axis.getLabelInsets().getRight() + textBounds.getWidth());
            textY += dy * (axis.getLabelInsets().getRight() + textBounds.getWidth());
        }
        
        TextUtilities.drawRotatedString(tick.getText(), g2, (float) textX, (float) textY + (float) g2.getFontMetrics().getHeight() / 3, angle, (float) textX, (float) textY);
        
        return outsideLength + textBounds.getWidth() + axis.getLabelInsets().getRight() + axis.getLabelInsets().getLeft();
    }

    /**
     * Creates vector
     * @param start vector start point
     * @param end vector end point
     * @return created vector
     */
    private Point2D makeVector(Point2D start, Point2D end) {
        return makeVector(start.getX(), start.getY(), end.getX(), end.getY());
    }

    /**
     * Creates vector
     * @param startX vector start X position
     * @param startY vector start Y position
     * @param endX vector end X position
     * @param endY vector end Y position
     * @return created vector
     */
    private Point2D makeVector(double startX, double startY, double endX, double endY) {
        return new Point2D.Double(endX - startX, endY - startY);
    }
}
