package gensym.charts.j3d.primitives;

import gensym.charts.j3d.*;
import java.awt.*;
import java.awt.geom.Line2D;
import java.awt.geom.Point2D;

/**
 * 3D line primitive
 */
public class Line3DPrimitive extends Object3DPrimitive {

    /** Default Line stroke */
    public static final Stroke DEFAULT_LINE_STROKE = new BasicStroke(1.0F);
    
    /** The A point of line */
    private Point3D a;

    /** The B point of line */
    private Point3D b;

    /**
     * Class constructor
     * @param p1 "A" value of the AB line
     * @param p2 "B" value of the AB line
     */
    public Line3DPrimitive(Point3D p1, Point3D p2) {
        this.a = p1;
        this.b = p2;
        setStroke(DEFAULT_LINE_STROKE);
    }

    /**
     * Gets A point
     * @return a point
     */
    public Point3D getA() {
        return a;
    }

    /**
     * Gets B point
     * @return b point
     */
    public Point3D getB() {
        return b;
    }

    /**
     * {@inheritDoc}
     */
    public double averageZValue() {
    	return (a.getZ() + b.getZ()) / 2;
    }

    /**
     * {@inheritDoc}
     */
    public Object3DPrimitive transform(ViewPoint viewPoint) {
        Point3D newA = viewPoint.transform(a);
        Point3D newB = viewPoint.transform(b);
        
        Line3DPrimitive primitive = new Line3DPrimitive(newA, newB);
        primitive.copy(this);

        return primitive;
    }

    /**
     * {@inheritDoc}
     */
    public void draw(Graphics2D g2, Point3D sun, ViewPoint viewPoint) {
        if (getPaint() != null && getStroke() != null) {
            g2.setPaint(getPaint());
            g2.setStroke(getStroke());
            g2.draw(getShape(viewPoint));
        }
    }
    
    /**
     * {@inheritDoc}
     */
    public Point3D[] getPoints() {
        return new Point3D[] {a, b};
    }
    
    /**
     * {@inheritDoc}
     */
    public Shape getShape(ViewPoint viewPoint) {
        Point2D scrA = viewPoint.toScreen(a);
        Point2D scrB = viewPoint.toScreen(b);
        
        return new Line2D.Double(scrA, scrB);
    }
}
