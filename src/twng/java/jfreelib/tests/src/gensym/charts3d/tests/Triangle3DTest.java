package gensym.charts3d.tests;

import gensym.charts.j3d.Point3D;
import gensym.charts.j3d.Triangle3D;
import junit.framework.TestCase;

/**
 * Test Triangle3D class
 */
public class Triangle3DTest extends TestCase {

    /**
     * Tests main class functionality
     */
    public void testPrimitive1() {
        try {
            Point3D a = new Point3D(47, 12, 1);
            Point3D b = new Point3D(23, 43, 2);
            Point3D c = new Point3D(411, 83, -9);

            Triangle3D tr = new Triangle3D(a, b, c);
            assertEquals(tr.getA(), a);
            assertEquals(tr.getB(), b);
            assertEquals(tr.getC(), c);
            assertEquals(tr, tr.clone());
            assertEquals(tr.getZRange().getLowerBound(), -9.0D);
            assertEquals(tr.getZRange().getUpperBound(), 2.0D);
            assertEquals(tr.averageZValue(), -2.0D);
            assertTrue(tr.equals(tr.clone()));
            assertFalse(tr.equals(45));

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
}
