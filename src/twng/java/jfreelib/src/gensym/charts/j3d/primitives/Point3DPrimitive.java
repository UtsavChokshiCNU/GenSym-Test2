package gensym.charts.j3d.primitives;

import gensym.charts.j3d.Point3D;
import gensym.charts.j3d.ViewPoint;

import java.awt.BasicStroke;
import java.awt.Graphics2D;
import java.awt.Shape;
import java.awt.Stroke;
import java.awt.geom.Point2D;

import org.jfree.util.ShapeUtilities;

/**
 *  3D point primitive
 */
public class Point3DPrimitive extends Object3DPrimitive {

    /** Default point stroke */
    public static final Stroke DEFAULT_POINT_STROKE = new BasicStroke(1.0F);

    /** Point */
    private Point3D point;
    
    /** Shape to draw */
    private Shape shape;

    /**
     * Constructor 
     * @param point the point 
     * @param shape the point shape
     */
    public Point3DPrimitive(Point3D point, Shape shape) {
        this.point = point;
        this.shape = shape;

        setStroke(DEFAULT_POINT_STROKE);
    }
    
    /**
     * {@inheritDoc}
     */
    public double averageZValue() {
        return point.getZ();
    }

    /**
     * {@inheritDoc}
     */
    public Object3DPrimitive transform(ViewPoint viewPoint) {
        Point3D newPoint = viewPoint.transform(point);

        Object3DPrimitive primitive = new Point3DPrimitive(newPoint, shape);
        primitive.copy(this);

        return primitive;
    }

    /**
     * {@inheritDoc}
     */
    public void draw(Graphics2D g2, Point3D sun, ViewPoint viewPoint) {
        Shape shapeToDraw = getShape(viewPoint);
        
        if (getPaint() != null) {
            g2.setPaint(getPaint());
            g2.fill(shapeToDraw);
        }

        if (getOutlinePaint() != null) {
            g2.setStroke(getStroke());
            g2.setPaint(getOutlinePaint());
            g2.draw(shapeToDraw);
        }
    }
	
    /**
     * {@inheritDoc}
     */
    public Point3D[] getPoints() {
        return new Point3D[] {point};
    }

    /**
     * Determines whether or not two object are equal.
     * @param obj1  a first object
     * @param obj2  a second object
     * @return <code>true</code> if both objects are nullable or equals, 
     * otherwise <code>false</code>.
     */
    public static boolean isTwoObjectsEquals(Object obj1, Object obj2) {
        if (obj1 != null) {
            return (obj2 != null) && obj1.equals(obj2);
        }
        return obj2 == null;
    }
    
    /**
     * Determines whether or not two points primitive are equal. Two instances 
     * of <code>Point3DPrimitive</code> are equal if the all member fields, 
     * are the same.
     * 
     * @param obj an object to be compared with this <code>Point3DPrimitive</code>
     * @return <code>true</code> or <code>false</code>.
     */
    
    public boolean equals(Object obj) {
        if ((obj != null) && (obj instanceof Point3DPrimitive)) {
            Point3DPrimitive pp = (Point3DPrimitive) obj;
            
            return (this == obj) 
                || isTwoObjectsEquals(point, pp.point) && isTwoObjectsEquals(shape, pp.shape) 
                && isTwoObjectsEquals(getPaint(), pp.getPaint())
                && isTwoObjectsEquals(getOutlinePaint(), pp.getOutlinePaint());
        }
        return false;
    }
    
    /**
     * {@inheritDoc}
     */
    public Shape getShape(ViewPoint viewPoint) {
        Point2D scrPoint = viewPoint.toScreen(point);
        return ShapeUtilities.createTranslatedShape(shape, scrPoint.getX(), scrPoint.getY());
    }
}
