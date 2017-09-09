package gensym.charts3d.tests;

import gensym.charts.j3d.primitives.Point3DPrimitive;
import gensym.charts.j3d.Point3D;
import gensym.charts.j3d.ViewPoint;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.Shape;

import junit.framework.TestCase;

/**
 * Tests for Point3DPrimitive class
 */
public class Point3DPrimitiveTest extends TestCase {

    /**
     * Creating Point3DPrimitive and simple methods test
     */
    public void testCreatePoint3DPrimitiveAndSimpleMethods() {
        try {
            Point3D p = new Point3D(1.1, 1.2, 1.3);
            Point3DPrimitive pp = new Point3DPrimitive(p, null);
            assertNotNull("assert #1", pp);
            assertTrue("assert #2", pp instanceof Point3DPrimitive);
            
            //test averageZValue()
            assertTrue("assert #3", p.getZ().doubleValue() == pp.averageZValue());
            
            //test getPoints()
            assertEquals("assert #4", 1, pp.getPoints().length);
            assertEquals("assert #5", p, pp.getPoints()[0]);
            
            //test equals()
            assertTrue("assert #6", pp.equals(pp));
            assertTrue("assert #7", pp.equals(new Point3DPrimitive(p, null)));
            assertFalse("assert #8", pp.equals(null));
            assertFalse("assert #9", pp.equals(new Point3D()));
            assertFalse("assert #10", pp.equals(new Point3DPrimitive(null, null)));
            assertFalse("assert #11", pp.equals(new Point3DPrimitive(new Point3D(), null)));
            assertFalse("assert #12", pp.equals(new Point3DPrimitive(p, new Rectangle())));
            pp.setPaint(Color.RED);
            assertFalse("assert #13", pp.equals(new Point3DPrimitive(p, null)));
            pp.setPaint(null);
            pp.setOutlinePaint(Color.RED);
            assertFalse("assert #14", pp.equals(new Point3DPrimitive(p, null)));
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Transforming Point3DPrimitive test
     */
    public void testPoint3DPrimitiveTransform() {
        try {
            Point3D p = new Point3D(4.1, 4.2, 4.3);
            ViewPoint vp = new ViewPoint();

            Point3DPrimitive pp = new Point3DPrimitive(p, null);
            Point3DPrimitive pp1 = (Point3DPrimitive) pp.transform(vp);

            assertNotSame("assert #1", pp, pp1);
            assertFalse("assert #2", pp.equals(pp1));

            Point3DPrimitive pp2 = new Point3DPrimitive(vp.transform(p), null);
            assertEquals("assert #3", pp1, pp2);
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    
    /**
     * Drawing Point3DPrimitive test
     */
    public void testPoint3DPrimitiveDraw() {
        try {
            Point3D p = new Point3D(4.1, 4.2, 4.3);
            Point3D sun = new Point3D(1, 0, 10);
            ViewPoint vp = new ViewPoint();
            Shape sh = new Rectangle(0, 0, 2, 2);
            Graphics2D g2 = Test3DUtils.genGraphics2D();
            BasicStroke bs = new BasicStroke(0.1F);
            
            //(paint == null) && (outlinePaint == null) - check condition
            Point3DPrimitive pp = new Point3DPrimitive(p, sh);
            g2.setStroke(bs);
            g2.setPaint(Color.BLACK);
            pp.draw(g2, sun, vp);
            assertTrue("assert #1", g2.getPaint().equals(Color.BLACK));
            assertTrue("assert #2", bs.equals(g2.getStroke()));
            
            //if (paint != null) { check this body }
            pp = new Point3DPrimitive(p, sh);
            pp.setPaint(Color.CYAN);
            g2.setPaint(Color.BLACK);
            pp.draw(g2, sun, vp);
            assertTrue("assert #3", g2.getPaint().equals(Color.CYAN));
            assertTrue("assert #4", bs.equals(g2.getStroke()));
            
            //test setPaint()
            pp.setPaint(Color.GREEN);
            pp.draw(g2, sun, vp);
            assertTrue("assert #5", g2.getPaint().equals(Color.GREEN));
            assertTrue("assert #6", bs.equals(g2.getStroke()));

            // if (outlinePaint != null) { check this body }
            pp = new Point3DPrimitive(p, sh);
            pp.setOutlinePaint(Color.GREEN);
            g2.setPaint(Color.BLACK);
            pp.draw(g2, sun, vp);
            assertTrue("assert #7", g2.getPaint().equals(Color.GREEN));
            assertFalse("assert #8", bs.equals(g2.getStroke()));
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
}
