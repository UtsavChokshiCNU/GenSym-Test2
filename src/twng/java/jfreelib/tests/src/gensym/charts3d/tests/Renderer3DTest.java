package gensym.charts3d.tests;

import java.awt.Color;

import org.jfree.chart.LegendItem;

import gensym.charts.j3d.Dataset3D;
import gensym.charts.j3d.Object3D;
import gensym.charts.j3d.renderers.Renderer3D;
import junit.framework.TestCase;

/**
 * Tests Renderer3D class
 */
public class Renderer3DTest extends TestCase {

    /** Temporary Renderer3D Test class */
    private class TestRenderer3D extends Renderer3D {
        
        /** Constructor */
        public TestRenderer3D() {
        }
        
        /** 
         * {@inheritDoc}
         */
        public Object3D createObject3D(Dataset3D dataset, int plottingMethod, int plottingDetails) {
            return null;
        }

		@Override
		public LegendItem getLegendItem(String label, int series) {
			return null;
		}
    }

    /**
     * Creates TestRenderer3D
     */
    public TestRenderer3D doCreateTestRenderer3D() throws Exception {
        TestRenderer3D r3d = new TestRenderer3D();
        assertNotNull(r3d);
        assertTrue(r3d instanceof Renderer3D);
        return r3d;
    }
    
    /**
     * Creating Renderer3D test
     */
    public void testCreateRenderer3D() {
        try {
            doCreateTestRenderer3D();
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Renderer3D methods test
     */
    public void testRenderer3DMethods() {
        try {
            TestRenderer3D r3d = doCreateTestRenderer3D();
            for (int i = 0; i < 100; i += 9) {
                assertEquals(Color.BLUE, (Color)r3d.getSeriesPaint(i));
                assertEquals(Color.CYAN, (Color)r3d.getSeriesPaint(i+1));
                assertEquals(Color.GRAY, (Color)r3d.getSeriesPaint(i+2));
                assertEquals(Color.GREEN, (Color)r3d.getSeriesPaint(i+3));
                assertEquals(Color.MAGENTA, (Color)r3d.getSeriesPaint(i+4));
                assertEquals(Color.ORANGE, (Color)r3d.getSeriesPaint(i+5));
                assertEquals(Color.PINK, (Color)r3d.getSeriesPaint(i+6));
                assertEquals(Color.RED, (Color)r3d.getSeriesPaint(i+7));
                assertEquals(Color.YELLOW, (Color)r3d.getSeriesPaint(i+8));
            }
            r3d.setSeriesPaint(100, Color.BLACK);
            assertEquals(Color.BLACK, (Color)r3d.getSeriesPaint(100));
            
            assertNull(r3d.getLegendItem("test", 0));
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

}
