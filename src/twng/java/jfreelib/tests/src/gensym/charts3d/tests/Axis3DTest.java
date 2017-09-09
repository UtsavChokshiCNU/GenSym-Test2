package gensym.charts3d.tests;

import org.jfree.chart.axis.NumberAxis;

import gensym.charts.j3d.Axis3D;
import junit.framework.TestCase;

/**
 * Tests Axis3D class
 */
public class Axis3DTest extends TestCase {

    /**
     * Creates Axis3D
     */
    public Axis3D doCreateAxis3D() {
        Axis3D a3d = new Axis3D();
        assertNotNull("The 'a3d' is null", a3d);
        assertTrue("The 'a3d' isn't instance of NumberAxis", a3d instanceof NumberAxis);
        assertTrue("The 'a3d' isn't instance of Axis3D", a3d instanceof Axis3D);
        return a3d;
    }
    
    /**
     * Create Axis3D test
     */
    public void testCreateAxis3D() {
        try {
            Axis3D a3d = doCreateAxis3D();
            assertNull(a3d.draw(null, 0, null, null, null, null));
            assertNotNull(a3d.getLabelFormat());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
}
