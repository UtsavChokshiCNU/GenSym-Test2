package gensym.charts.j3d.primitives;

import gensym.charts.j3d.*;
import java.awt.*;
import java.awt.geom.Point2D;
import java.awt.geom.GeneralPath;

/**
 * 3D rectangle primitive
 */
public class Rectangle3DPrimitive extends Object3DPrimitive {
    
    /** Default rectangle stroke */
    public static final Stroke DEFAULT_RECTANGLE_STROKE = new BasicStroke(1.0f);
    
    /** The rectangle A point */
    private Point3D a;

    /** The rectangle B point */
    private Point3D b;

    /** The rectangle C point */
    private Point3D c;

    /** The rectangle D point */
    private Point3D d;

    /** Is shade needed */
    private boolean showShades = false;

    /**
     * Constructor
     * @param p1 the A point of ABCD rectangle
     * @param p2 the B point of ABCD rectangle
     * @param p3 the C point of ABCD rectangle
     * @param p4 the D point of ABCD rectangle
     */
    public Rectangle3DPrimitive(Point3D p1, Point3D p2, Point3D p3, Point3D p4) {
        this.a = p1;
        this.b = p2;
        this.c = p3;
        this.d = p4;

        setStroke(DEFAULT_RECTANGLE_STROKE);
    }

    /**
     * Gets the A point
     * @return the A point
     */
    public Point3D getA() {
        return a;
    }

    /**
     * Gets the B point
     * @return the B point
     */
    public Point3D getB() {
        return b;
    }

    /**
     * Gets the C point
     * @return the C point
     */
    public Point3D getC() {
        return c;
    }

    /**
     * Gets the D point
     * @return the D point
     */
    public Point3D getD() {
        return d;
    }

    /**
     * Tests whether shades are visible
     * @return true if shades are visible
     */
    public boolean isShadesVisible() {
        return showShades;
    }

    /**
     * Sets shades visibility flag
     * @param visible the new shades visibility flag
     */
    public void setShadesVisible(boolean visible) {
        showShades = visible;
    }

    /**
     * {@inheritDoc}
     */
    public double averageZValue() {
    	return (getA().getZ() + getB().getZ() + getC().getZ() + getD().getZ()) / 4;
    }

    /**
     * {@inheritDoc}
     */
    public Object3DPrimitive transform(ViewPoint viewPoint) {
        Point3D newA = viewPoint.transform(getA());
        Point3D newB = viewPoint.transform(getB());
        Point3D newC = viewPoint.transform(getC());
        Point3D newD = viewPoint.transform(getD());
        
        Rectangle3DPrimitive rect = new Rectangle3DPrimitive(newA, newB, newC, newD);
        rect.copy(this);
        rect.setShadesVisible(isShadesVisible());
        return rect;
    }

    /**
     * {@inheritDoc}
     */
    public void draw(Graphics2D g2, Point3D sun, ViewPoint viewPoint) {
        Shape rectangle = createRectangle(viewPoint);
        Paint newOutlinePaint = getOutlinePaint();
        if (getPaint() != null) {
            if (getPaint() instanceof Color) {
                Color newColor = isShadesVisible() ? Shade3D.getColor4Points(getA(),
                        getB(), getC(), getD(), (Color) getPaint(), sun, viewPoint) : (Color) getPaint();

                g2.setPaint(newColor);
                g2.fill(rectangle);

                if (newOutlinePaint == null) {
                    newOutlinePaint = newColor;
                }

            } else {
                g2.setPaint(getPaint());
                g2.fill(rectangle);
            }
        }

        if (newOutlinePaint != null) {
            g2.setPaint(newOutlinePaint);
            g2.setStroke(getStroke());
            g2.draw(rectangle);
        }
    }

    /**
     * Creates rectangle shape
     * @param viewPoint view point
     * @return the rectangle shape
     */
    protected Shape createRectangle(ViewPoint viewPoint) {
        Point2D scrA = viewPoint.toScreen(getA());
        Point2D scrB = viewPoint.toScreen(getB());
        Point2D scrC = viewPoint.toScreen(getC());
        Point2D scrD = viewPoint.toScreen(getD());

        GeneralPath rect = new GeneralPath();
        rect.moveTo((float) scrA.getX(), (float) scrA.getY());
        rect.lineTo((float) scrB.getX(), (float) scrB.getY());
        rect.lineTo((float) scrC.getX(), (float) scrC.getY());
        rect.lineTo((float) scrD.getX(), (float) scrD.getY());
        rect.lineTo((float) scrA.getX(), (float) scrA.getY());
        rect.closePath();

        return rect;
    }

    /**
     * {@inheritDoc}
     */
    public Point3D[] getPoints() {
        return new Point3D[] {getA(), getB(), getC(), getD()};
    }
    
    /**
     * {@inheritDoc}
     */
    public Shape getShape(ViewPoint viewPoint) {
        return createRectangle(viewPoint);
    }
}
