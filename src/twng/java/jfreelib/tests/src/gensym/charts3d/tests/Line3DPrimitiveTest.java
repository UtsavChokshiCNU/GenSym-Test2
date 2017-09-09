package gensym.charts3d.tests;

import java.awt.Color;
import java.awt.Graphics2D;

import gensym.charts.j3d.primitives.Line3DPrimitive;
import gensym.charts.j3d.Point3D;
import gensym.charts.j3d.ViewPoint;
import junit.framework.TestCase;

/**
 * Tests for Line3DPrimitive class
 */
public class Line3DPrimitiveTest extends TestCase {

    /** First line point */
    private Point3D p1 = new Point3D(Test3DUtils.X_BASE, Test3DUtils.Y_BASE, Test3DUtils.Z_BASE);

    /** Second line point */
    private Point3D p2 = new Point3D(Test3DUtils.X_BASE + 10, Test3DUtils.Y_BASE + 10, Test3DUtils.Z_BASE + 10);
    
    /**
     * Creates Line3DPrimitive
     */
    public Line3DPrimitive doCreateLine3DPrimitive() throws Exception {
        Line3DPrimitive l3d = new Line3DPrimitive(p1, p2);
        l3d.setPaint(Color.BLACK);
        l3d.setOutlinePaint(Color.BLACK);
        
        assertEquals(Color.BLACK, l3d.getPaint());
        assertEquals(Color.BLACK, l3d.getOutlinePaint());
        return l3d;
    }
    
    /**
     * Creating Line3DPrimitive test
     */
    public void testCreateLine3DPrimitive() {
        try {
            doCreateLine3DPrimitive();
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Line3DPrimitive geters test
     */
    public void testCreateLine3DPrimitiveGeters() {
        try {
            Line3DPrimitive l3d = doCreateLine3DPrimitive();
            
            assertEquals(p1, l3d.getA());
            assertEquals(p2, l3d.getB());
            
            assertEquals(Color.BLACK, l3d.getPaint());
            
            assertEquals((p1.getZ().doubleValue() + p2.getZ().doubleValue()) / 2, l3d.averageZValue(), 0.0001D);
            
            Point3D[] points = l3d.getPoints();
            assertEquals(2, points.length);
            assertEquals(p1, points[0]);
            assertEquals(p2, points[1]);
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Line3DPrimitive transform test
     */
    public void testCreateLine3DPrimitiveTransform() {
        try {
            Line3DPrimitive l1 = doCreateLine3DPrimitive();
            ViewPoint vp = new ViewPoint();
            Line3DPrimitive l2 = (Line3DPrimitive) l1.transform(vp);
            
            assertNotSame(l1, l2);
            assertEquals(l1.getPaint(), l2.getPaint());
            assertEquals(l2.getA(), vp.transform(p1));
            assertEquals(l2.getB(), vp.transform(p2));
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Line3DPrimitive draw test
     */
    public void testCreateLine3DPrimitiveDraw() {
        try {
            Line3DPrimitive l1 = doCreateLine3DPrimitive();
            ViewPoint vp = new ViewPoint();
            Line3DPrimitive l2 = (Line3DPrimitive) l1.transform(vp);
            
            assertNotSame(l1, l2);
            assertEquals(l1.getPaint(), l2.getPaint());
            assertEquals(l2.getA(), vp.transform(p1));
            assertEquals(l2.getB(), vp.transform(p2));
            
            Graphics2D g1 = Test3DUtils.genGraphics2D();
            l2.draw(g1, null, vp);
            Graphics2D g2 = (Graphics2D) g1.create();
            
            assertFalse(g1.equals(g2));
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
}
