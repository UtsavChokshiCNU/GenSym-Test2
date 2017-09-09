package gensym.charts3d.tests;

import gensym.charts.j3d.Point3D;
import gensym.charts.j3d.ViewPoint;
import gensym.charts.j3d.primitives.Contour3DPrimitive;
import java.awt.Color;
import junit.framework.TestCase;

public class Contour3DPrimitiveTest extends TestCase {

    /**
     * Tests Contour3DPrimitive class
     */
    public final void testContour3DPrimitive() {
        try {
            Point3D a = new Point3D(0, 0, 0);
            Point3D b = new Point3D(0, 0, 0);
            Point3D c = new Point3D(0, 0, 0);
            Point3D d = new Point3D(0, 0, 0);
            Point3D normal = new Point3D(0, 0, 1);

            Contour3DPrimitive contour = new Contour3DPrimitive(a, b, c, d, normal);
            assertEquals(contour.getOutlinePaint(), Color.BLACK);
            assertEquals(contour.getPaint(), null);
            assertEquals(contour.averageZValue(), Double.MAX_VALUE);
            assertEquals(contour.transform(new ViewPoint()).getClass(), Contour3DPrimitive.class);

            contour.setPaint(Color.GREEN);
            contour.setOutlinePaint(Color.GREEN);
            assertEquals(contour.getOutlinePaint(), Color.GREEN);
            assertEquals(contour.getPaint(), Color.GREEN);

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
}
