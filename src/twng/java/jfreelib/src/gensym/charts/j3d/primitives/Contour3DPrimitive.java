package gensym.charts.j3d.primitives;

import gensym.charts.j3d.Point3D;
import gensym.charts.j3d.ViewPoint;

import java.awt.Color;

/**
 * 3D contour primitive
 */
public class Contour3DPrimitive extends Rectangle3DPrimitive {

    /** Normal to contour */
    private Point3D normal = null;

    /**
     * Constructor
     * @param a the A point of ABCD rectangle
     * @param b the B point of ABCD rectangle
     * @param c the C point of ABCD rectangle
     * @param d the D point of ABCD rectangle
     * @param normal normal to contour
     */
    public Contour3DPrimitive(Point3D a, Point3D b, Point3D c, Point3D d, Point3D normal) {
        super(a, b, c, d);
        this.normal = normal;

        setOutlinePaint(Color.BLACK);
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

        return new Contour3DPrimitive(newA, newB, newC, newD, newNormal);
    }

    /**
     * {@inheritDoc}
     */
    public double averageZValue() {
        return normal.getZ() > 0 ? Double.MAX_VALUE : -Double.MAX_VALUE;
    }
}
