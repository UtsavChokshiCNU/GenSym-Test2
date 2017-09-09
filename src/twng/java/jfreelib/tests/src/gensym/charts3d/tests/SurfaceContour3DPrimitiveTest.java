package gensym.charts3d.tests;

import gensym.charts.j3d.Point3D;
import gensym.charts.j3d.ViewPoint;
import gensym.charts.j3d.primitives.SurfaceContour3DPrimitive;
import junit.framework.TestCase;

/**
 * Tests for SurfaceContour3DPrimitive class
 */
public class SurfaceContour3DPrimitiveTest extends TestCase {

    /**
     * Tests main class functionality
     */
    public void testPrimitive1() {
        try {
            Point3D a = new Point3D(47, 12, 1);
            Point3D b = new Point3D(23, 43, 2);
            Point3D c = new Point3D(411, 83, 3);
            Point3D d = new Point3D(1, 222, 4888);
            SurfaceContour3DPrimitive prim = new SurfaceContour3DPrimitive(a, b, c, d);
            assertEquals(prim.averageZValue(), 1.0D);

            ViewPoint vp = new ViewPoint();
            SurfaceContour3DPrimitive tPrim = (SurfaceContour3DPrimitive) prim.transform(vp);
            assertEquals(vp.transform(a), tPrim.getA());
            assertEquals(vp.transform(b), tPrim.getB());
            assertEquals(vp.transform(c), tPrim.getC());
            assertEquals(vp.transform(d), tPrim.getD());

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
}
