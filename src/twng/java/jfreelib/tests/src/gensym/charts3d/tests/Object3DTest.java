package gensym.charts3d.tests;

import gensym.charts.j3d.*;
import gensym.charts.j3d.primitives.*;
import junit.framework.TestCase;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.util.LinkedList;
import java.util.List;

import org.jfree.chart.ChartRenderingInfo;
import org.jfree.chart.plot.PlotRenderingInfo;
import org.jfree.data.Range;

/**
 * Tests Object3D class
 */
public class Object3DTest extends TestCase {

    /** Storage of primitives that draws */
    private List<Object3DPrimitive> transformedPrimitives = new LinkedList<Object3DPrimitive>();

    /** 
     * Temporary class for testing Point3DPrimitive class 
     * with decorates some methods 
     */
    private class TestPointPrimitive extends Point3DPrimitive {
        
        /** Duplicates of Z coordinates by Point3DPrimitive */
        private double z = 0;
        
        /** Constructor */
        public TestPointPrimitive (double x, double y, double z) {
            super(new Point3D(x, y, z), new Rectangle(1, 1, 2, 2));
            setPaint(Color.BLUE);
            setOutlinePaint(Color.GRAY);
        }
        
        /** Override Draw method for checks sorting items */
        public void draw(Graphics2D g2, Point3D sun, ViewPoint viewPoint) {
            transformedPrimitives.add(this);
        }
        /** Override Equals method for use in tests */
        public boolean equals(Object obj) {
            return z == ((TestPointPrimitive)obj).z;
        }
        
        /** Override Transform method for tests Drawing */
        public Object3DPrimitive transform(ViewPoint viewPoint) {
            return this;
        }
    }
    
    /**
     * Creates Object3D
     */
    public Object3D doCreateObject3D() throws Exception {
    	Object3D o3d = new Object3D();
        assertNotNull("The 'o3d' object is null", o3d);
        assertTrue("The 'o3d' isn't instance of Object3D class.", o3d instanceof Object3D);
        return o3d;
    }
    
    /**
     * Creating Object3D test
     */
    public void testCreatePlot3D() {
        try {
            Object3D o3d = doCreateObject3D();
            assertTrue("The 'o3d' isn't empty.", o3d.isEmpty());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Object3D Triangles test
     */
    public void testObject3DTriangles() {
        try {
        	Object3D o3d = doCreateObject3D();
            Point3D p1 = new Point3D(1, 2, 3);
            Point3D p2 = new Point3D(2, 3, 4);
            Point3D p3 = new Point3D(3, 4, 5);
            
            Triangle3DPrimitive t1 = new Triangle3DPrimitive(new Triangle3D(p1, p2, p3));
            o3d.addPrimitive(t1);
            
            assertFalse("The 'o3d' is empty.", o3d.isEmpty());

            Triangle3DPrimitive t2 = (Triangle3DPrimitive) o3d.getPrimitive(0);
            
            assertTrue("The 't1' and 't2' isn't same objects.", t1 == t2);
            assertEquals(t1.getTriangle3D(), t2.getTriangle3D());
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Object3D lines test
     */
    public void testObject3DLines() {
        try {
        	Object3D o3d = doCreateObject3D();
            Point3D p1 = new Point3D(1, 2, 3);
            Point3D p2 = new Point3D(2, 3, 4);
            
            Line3DPrimitive l1 = new Line3DPrimitive(p1, p2);
            o3d.addPrimitive(l1);

            assertFalse("The 'o3d' is empty.", o3d.isEmpty());
            
            Line3DPrimitive l2 = (Line3DPrimitive)o3d.getPrimitive(0);
            
            assertTrue("The 'l1' and 'l2' isn't same objects.", l1 == l2);
            assertEquals(l1.getA(), l2.getA());
            assertEquals(l1.getB(), l2.getB());
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Object3D points test
     */
    public void testObject3DPoints() {
        try {
        	Object3D o3d = doCreateObject3D();
            Point3DPrimitive p1 = new Point3DPrimitive(new Point3D(1, 2, 3), null);
            Point3DPrimitive p2 = new Point3DPrimitive(new Point3D(2, 3, 4), null);
            Point3DPrimitive p3 = new Point3DPrimitive(new Point3D(3, 4, 5), null);
            
            o3d.addPrimitive(p1);
            o3d.addPrimitive(p2);
            o3d.addPrimitive(p3);

            assertFalse("The 'o3d' is empty.", o3d.isEmpty());
            
            Point3DPrimitive p4 = (Point3DPrimitive)o3d.getPrimitive(1);
            assertEquals(3, o3d.getPrimitivesCount());

            assertTrue("The 'l1' and 'l2' isn't same objects.", p2 == p4);
            
            assertEquals(p1, (Point3DPrimitive)o3d.getPrimitive(0));
            assertEquals(p2, (Point3DPrimitive)o3d.getPrimitive(1));
            assertEquals(p3, (Point3DPrimitive)o3d.getPrimitive(2));
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Object3D mess objects test
     */
    public void testObject3DMessObjects() {
        try {
        	Object3D o3d = doCreateObject3D();

            Point3D p1 = new Point3D(1, 2, 3);
            Point3D p2 = new Point3D(2, 3, 4);
            Point3D p3 = new Point3D(3, 4, 5);
            Triangle3DPrimitive t1 = new Triangle3DPrimitive(new Triangle3D(p1, p2, p3));
            o3d.addPrimitive(t1);

            assertFalse("The 'o3d' is empty.", o3d.isEmpty());

            Line3DPrimitive l1 = new Line3DPrimitive(p1, p2);
            o3d.addPrimitive(l1);
            
            Point3DPrimitive p6 = new Point3DPrimitive(new Point3D(1, 2, 3), null);
            o3d.addPrimitive(p6);

            assertTrue("The 't1' and 'o3d.getPrimitive(0)' isn't same objects.", t1 == o3d.getPrimitive(0));
            assertTrue("The 'l1' and 'o3d.getPrimitive(1)' isn't same objects.", l1 == o3d.getPrimitive(1));
            assertTrue("The 'p6' and 'o3d.getPrimitive(2)' isn't same objects.", p6 == o3d.getPrimitive(2));
            
            assertTrue("The 'o3d.getPrimitive(0)' object isn't instanceof Triangle3DPrimitive", o3d.getPrimitive(0) instanceof Triangle3DPrimitive);
            assertTrue("The 'o3d.getPrimitive(1)' object isn't instanceof Line3DPrimitive", o3d.getPrimitive(1) instanceof Line3DPrimitive);
            assertTrue("The 'o3d.getPrimitive(2)' object isn't instanceof Point3DPrimitive", o3d.getPrimitive(2) instanceof Point3DPrimitive);
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Object3D draw method test
     */
    public void testObject3DDraw() {
        try {
            Object3D o3d = doCreateObject3D();
            
            o3d.addPrimitive(new TestPointPrimitive(Test3DUtils.X_BASE + 5, Test3DUtils.Y_BASE + 5, Test3DUtils.Z_BASE + 13));
            for (int i = 0; i < 4; i++) {
                o3d.addPrimitive(new TestPointPrimitive(Test3DUtils.X_BASE + i, Test3DUtils.Y_BASE + i, Test3DUtils.Z_BASE + 10 * i));
            }
            o3d.addPrimitive(new TestPointPrimitive(Test3DUtils.X_BASE + 4, Test3DUtils.Y_BASE + 4, Test3DUtils.Z_BASE + 13));
            PlotRenderingInfo info = new PlotRenderingInfo(new ChartRenderingInfo());
            o3d.draw(null, null, new ViewPoint(), info);
            
            // obj1.z == obj2.z;
            assertEquals("assert #1", (TestPointPrimitive)o3d.getPrimitive(0), (TestPointPrimitive)transformedPrimitives.get(2));
            assertEquals("assert #2", (TestPointPrimitive)o3d.getPrimitive(1), (TestPointPrimitive)transformedPrimitives.get(5));
            assertEquals("assert #3", (TestPointPrimitive)o3d.getPrimitive(2), (TestPointPrimitive)transformedPrimitives.get(4));
            assertEquals("assert #4", (TestPointPrimitive)o3d.getPrimitive(3), (TestPointPrimitive)transformedPrimitives.get(1));
            assertEquals("assert #5", (TestPointPrimitive)o3d.getPrimitive(4), (TestPointPrimitive)transformedPrimitives.get(0));
            assertEquals("assert #6", (TestPointPrimitive)o3d.getPrimitive(5), (TestPointPrimitive)transformedPrimitives.get(3));
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    
    /**
     * Object3D list methods test
     */
    public void testObject3DListMethods() {
        try {
            Object3D o3d = doCreateObject3D();
            assertEquals(0, o3d.getPrimitivesCount());
            try {
                o3d.getPrimitive(100);
                fail("This should never happen");
            }
            catch (IllegalArgumentException e) {
                ; //this Ok
            }
            catch (Exception e) {
                fail("Wrong exception: " + e.getMessage());
            }
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Object3D bounds test
     */
    public void testObject3DBounds() {
        try {
            Object3D o3d = doCreateObject3D();
            Range[] Bounds = o3d.getBounds();

            assertEquals("assert #1", 3, Bounds.length);
            assertNull("assert #2", Bounds[0]);
            assertNull("assert #3", Bounds[1]);
            assertNull("assert #4", Bounds[2]);
            
            Point3DPrimitive p1 = new Point3DPrimitive(new Point3D(1, 2, 3), null);
            o3d.addPrimitive(p1);
            Bounds = o3d.getBounds();

            assertEquals("assert #5", new Range(p1.getPoints()[0].getX(), p1.getPoints()[0].getX()), Bounds[0]);
            assertEquals("assert #6", new Range(p1.getPoints()[0].getY(), p1.getPoints()[0].getY()), Bounds[1]);
            assertEquals("assert #7", new Range(p1.getPoints()[0].getZ(), p1.getPoints()[0].getZ()), Bounds[2]);

            Point3DPrimitive p2 = new Point3DPrimitive(new Point3D(2, 3, 4), null);
            o3d.addPrimitive(p2);
            Bounds = o3d.getBounds();
            
            assertEquals("assert #8", new Range(p1.getPoints()[0].getX(), p2.getPoints()[0].getX()), Bounds[0]);
            assertEquals("assert #9", new Range(p1.getPoints()[0].getY(), p2.getPoints()[0].getY()), Bounds[1]);
            assertEquals("assert #10", new Range(p1.getPoints()[0].getZ(), p2.getPoints()[0].getZ()), Bounds[2]);

            Point3DPrimitive p3 = new Point3DPrimitive(new Point3D(13, 14, 15), null);
            o3d.addPrimitive(p3);
            Bounds = o3d.getBounds();
            
            assertEquals("assert #11", new Range(p1.getPoints()[0].getX(), p3.getPoints()[0].getX()), Bounds[0]);
            assertEquals("assert #12", new Range(p1.getPoints()[0].getY(), p3.getPoints()[0].getY()), Bounds[1]);
            assertEquals("assert #13", new Range(p1.getPoints()[0].getZ(), p3.getPoints()[0].getZ()), Bounds[2]);

            Point3DPrimitive p4 = new Point3DPrimitive(new Point3D(3, 4, 5), null);
            o3d.addPrimitive(p4);
            Bounds = o3d.getBounds();
            
            assertEquals("assert #14", new Range(p1.getPoints()[0].getX(), p3.getPoints()[0].getX()), Bounds[0]);
            assertEquals("assert #15", new Range(p1.getPoints()[0].getY(), p3.getPoints()[0].getY()), Bounds[1]);
            assertEquals("assert #16", new Range(p1.getPoints()[0].getZ(), p3.getPoints()[0].getZ()), Bounds[2]);
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
}
