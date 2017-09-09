package gensym.charts.j3d.primitives;

import gensym.charts.j3d.Point3D;
import gensym.charts.j3d.ViewPoint;
import java.awt.Color;

/**
 * 3D rectangle primitive for surface contour
 */
public class SurfaceContour3DPrimitive extends Rectangle3DPrimitive {

    /**
     * Constructor
     * @param a A point of ABCD rect
     * @param b B point of ABCD rect
     * @param c C point of ABCD rect
     * @param d D point of ABCD rect
     */
    public SurfaceContour3DPrimitive(Point3D a, Point3D b, Point3D c, Point3D d) {
        super(a, b, c, d);
        setOutlinePaint(Color.BLACK);
    }

    /**
     * {@inheritDoc}
     */
    public double averageZValue() {
        return Math.min(Math.min(getA().getZ(),
                getB().getZ()), Math.min(getC().getZ(), getD().getZ()));
    }

    /**
     * {@inheritDoc}
     */
    public Object3DPrimitive transform(ViewPoint viewPoint) {
        Point3D newA = viewPoint.transform(getA());
        Point3D newB = viewPoint.transform(getB());
        Point3D newC = viewPoint.transform(getC());
        Point3D newD = viewPoint.transform(getD());

        SurfaceContour3DPrimitive rect = new SurfaceContour3DPrimitive(newA, newB, newC, newD);
        rect.copy(this);
        rect.setShadesVisible(isShadesVisible());
        return rect;
    }
}