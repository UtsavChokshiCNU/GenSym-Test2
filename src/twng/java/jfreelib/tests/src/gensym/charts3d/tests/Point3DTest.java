package gensym.charts3d.tests;

import gensym.charts.j3d.Point3D;
import junit.framework.TestCase;

/**
 * Tests Point3D class
 */
public class Point3DTest extends TestCase {

    /**
     * Creates Point3D
     */
    public Point3D doCreatePoint3D(double x, double y, double z) throws Exception {
        Point3D p3d = new Point3D(x, y, z);
        assertEquals(x, p3d.getX());
        assertEquals(y, p3d.getY());
        assertEquals(z, p3d.getZ());
        return p3d;
    }

    /**
     * Creating Point3D test
     */
    public void testCreatePoint3D() {
        try {
            Point3D p3d = new Point3D();
            assertNotNull(p3d);
            assertTrue(p3d instanceof Point3D);

            doCreatePoint3D(10, 11, 12);
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Point3D Properties test
     */
    public void testPoint3DProperties() {
        try {
            Point3D p3d = doCreatePoint3D(10, 11, 12);

            assertEquals(10.0, p3d.getX().doubleValue());
            assertEquals(11.0, p3d.getY().doubleValue());
            assertEquals(12.0, p3d.getZ().doubleValue());

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Cloneable Point3D test
     */
    public void testPoint3DCloneable() {
        try {
            Point3D p3d = doCreatePoint3D(10, 11, 12);
            Point3D p3dClone = (Point3D) p3d.clone();

            assertTrue(p3d instanceof Cloneable);
            assertNotSame(p3d, p3dClone);
            assertEquals(10.0, p3dClone.getX().doubleValue());
            assertEquals(11.0, p3dClone.getY().doubleValue());
            assertEquals(12.0, p3dClone.getZ().doubleValue());

            assertTrue(p3d.equals(p3dClone));
            assertFalse(p3d.equals(new Integer(11)));

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests length and dotProduct functions
     */
    public void testSimpleFuctions() {
        Point3D point = new Point3D(0, 4.0, 3.0);
        assertEquals(point.length(), 5.0);
        assertEquals(point.dotProduct(new Point3D()), 0.0D);
        assertEquals(point.dotProduct(point), 25.0D);
    }
}
