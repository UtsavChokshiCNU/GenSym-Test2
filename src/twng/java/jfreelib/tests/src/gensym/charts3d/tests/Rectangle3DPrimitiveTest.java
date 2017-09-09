package gensym.charts3d.tests;

import gensym.charts.j3d.primitives.Rectangle3DPrimitive;
import gensym.charts.j3d.Point3D;
import gensym.charts.j3d.ViewPoint;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Shape;

import junit.framework.TestCase;

public class Rectangle3DPrimitiveTest extends TestCase {

    /** First line point */
    private Point3D P1 = new Point3D(Test3DUtils.X_BASE, Test3DUtils.Y_BASE, Test3DUtils.Z_BASE);

    /** Second line point */
    private Point3D P2 = new Point3D(Test3DUtils.X_BASE + 10, Test3DUtils.Y_BASE + 10, Test3DUtils.Z_BASE + 10);

    /** Third line point */
    private Point3D P3 = new Point3D(Test3DUtils.X_BASE + 20, Test3DUtils.Y_BASE + 20, Test3DUtils.Z_BASE + 20);

    /** Forth line point */
    private Point3D P4 = new Point3D(Test3DUtils.X_BASE + 30, Test3DUtils.Y_BASE + 30, Test3DUtils.Z_BASE + 30);

    /** Storage for Points3D */ 
    private Point3D[] points3d = {
        new Point3D( -989.26,  -155.42,   -45.41),
        new Point3D(  880.11,   627.69,   226.60),
        new Point3D( -512.24,   711.16,   697.81),
        new Point3D(  730.10,  -704.01,   942.86),
        new Point3D( -121.85,   358.45,  -656.69),
        new Point3D(  753.88,   559.11,   960.50),
        new Point3D( -107.82,  -819.85,   872.37),
        new Point3D(  704.43,   662.69,   156.29),
        new Point3D(  -79.24,   668.31,  -265.01),
        new Point3D(  935.85,   -70.75,    73.25),
        new Point3D( -263.04,   616.69,   403.84),
        new Point3D(  437.79,   526.34,   547.74),
        new Point3D(  -30.08,  -776.81,  -265.44),
        new Point3D(  327.02,   909.84,   594.31),
        new Point3D( -433.49,   580.81,    79.36),
        new Point3D(  826.54,  -848.40,   504.14),
        new Point3D( -887.58,    80.47,  -463.49),
        new Point3D(  457.47,   800.09,   482.39),
        new Point3D( -536.37,  -149.55,   379.78),
        new Point3D(  202.30,   798.03,   453.13)
    };

    private static Point3D[] transfPoints3d = {
        new Point3D( 914.61166, -407.76983,  -45.41000),
        new Point3D(-1079.95185,  -47.87839,  226.60000),
        new Point3D(  42.91995, -875.38348,  697.81000),
        new Point3D(-229.60982,  987.90456,  942.86000),
        new Point3D( -92.76350, -367.05416, -656.69000),
        new Point3D(-936.72689,  -59.00665,  960.50000),
        new Point3D( 536.48440,  629.25644,  872.37000),
        new Point3D(-951.58451, -172.81952,  156.29000),
        new Point3D(-297.08672, -603.86813, -265.01000),
        new Point3D(-746.75560,  568.48647,   73.25000),
        new Point3D(-114.78300, -660.54633,  403.84000),
        new Point3D(-653.67720, -203.46991,  547.74000),
        new Point3D( 447.84031,  635.43500, -265.44000),
        new Point3D(-769.36534, -585.51506,  594.31000),
        new Point3D(  47.75622, -723.16885,   79.36000),
        new Point3D(-231.97867, 1161.52349,  504.14000),
        new Point3D( 700.96573, -550.38234, -463.49000),
        new Point3D(-819.11590, -422.45940,  482.39000),
        new Point3D( 531.41115, -166.31346,  379.78000),
        new Point3D(-603.88934, -559.54878,  453.13000)};
    
    /**
     * Creates Rectangle3DPrimitive
     */
    public Rectangle3DPrimitive doCreateRectangle3DPrimitive() throws Exception {
        Rectangle3DPrimitive r3d = new Rectangle3DPrimitive(P1, P2, P3, P4);
        r3d.setPaint(Color.BLACK);
        r3d.setOutlinePaint(Color.BLACK);
        r3d.setShadesVisible(true);

        assertEquals(Color.BLACK, r3d.getPaint());
        assertEquals(Color.BLACK, r3d.getOutlinePaint());
        assertTrue(r3d.isShadesVisible());
        return r3d;
    }
    
    /**
     * Creating Rectangle3DPrimitive and geters test
     */
    public void testCreateRectangle3DPrimitiveAndSimpleMethods() {
        try {
            Rectangle3DPrimitive r3d = doCreateRectangle3DPrimitive();
            assertEquals(P1, r3d.getA());
            assertEquals(P2, r3d.getB());
            assertEquals(P3, r3d.getC());
            assertEquals(P4, r3d.getD());
            assertEquals(Color.BLACK, r3d.getPaint());
            assertEquals(Color.BLACK, r3d.getOutlinePaint());
            
            r3d = new Rectangle3DPrimitive(P1, P2, P3, P4);
            r3d.setPaint(Color.CYAN);
            r3d.setOutlinePaint(Color.RED);
            assertNotNull(r3d);
            assertTrue(r3d instanceof Rectangle3DPrimitive);
            assertEquals(Color.CYAN, r3d.getPaint());
            assertEquals(Color.RED, r3d.getOutlinePaint());
            
            //averageZValue()
            assertEquals((Test3DUtils.Z_BASE * 4 + 60) / 4, r3d.averageZValue(), 0.0001);
            
            //getPoints()
            Point3D[] points = r3d.getPoints();  
            assertEquals(4, points.length);
            assertEquals(P1, points[0]);
            assertEquals(P2, points[1]);
            assertEquals(P3, points[2]);
            assertEquals(P4, points[3]);
            
            ViewPoint vp = new ViewPoint();
            assertNotNull(r3d.getShape(vp));
            assertTrue(r3d.getShape(vp) instanceof Shape);
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    
    /**
     * Transforming Rectangle3DPrimitive test
     */
    public void testRectangle3DPrimitiveTransform() {
        try {
            ViewPoint vp = new ViewPoint();

            for (int i = 0; i < points3d.length; i+=4) {
                Rectangle3DPrimitive orig = new Rectangle3DPrimitive(points3d[i], points3d[i+1], points3d[i+2], points3d[i+3]);
                orig.setPaint(Color.GRAY);
                orig.setOutlinePaint(Color.RED);
                Rectangle3DPrimitive rect = (Rectangle3DPrimitive) orig.transform(vp);

                assertEquals("assert A.x #" + i, transfPoints3d[i].getX(), rect.getA().getX(), 0.0001D);
                assertEquals("assert A.y #" + i, transfPoints3d[i].getY(), rect.getA().getY(), 0.0001D);
                assertEquals("assert A.z #" + i, transfPoints3d[i].getZ(), rect.getA().getZ(), 0.0001D);

                assertEquals("assert B.x #" + i, transfPoints3d[i+1].getX(), rect.getB().getX(), 0.0001D);
                assertEquals("assert B.y #" + i, transfPoints3d[i+1].getY(), rect.getB().getY(), 0.0001D);
                assertEquals("assert B.z #" + i, transfPoints3d[i+1].getZ(), rect.getB().getZ(), 0.0001D);

                assertEquals("assert C.x #" + i, transfPoints3d[i+2].getX(), rect.getC().getX(), 0.0001D);
                assertEquals("assert C.y #" + i, transfPoints3d[i+2].getY(), rect.getC().getY(), 0.0001D);
                assertEquals("assert C.z #" + i, transfPoints3d[i+2].getZ(), rect.getC().getZ(), 0.0001D);

                assertEquals("assert D.x #" + i, transfPoints3d[i+3].getX(), rect.getD().getX(), 0.0001D);
                assertEquals("assert D.y #" + i, transfPoints3d[i+3].getY(), rect.getD().getY(), 0.0001D);
                assertEquals("assert D.z #" + i, transfPoints3d[i+3].getZ(), rect.getD().getZ(), 0.0001D);
            }
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Drawing Rectangle3DPrimitive test
     */
    public void testRectangle3DPrimitiveDraw() {
        try {
            Graphics2D g2 = Test3DUtils.genGraphics2D();
            Point3D sun = Test3DUtils.defaultSunPoint();
            ViewPoint viewPoint = new ViewPoint();
            BasicStroke bs01 = new BasicStroke(0.1F);
            BasicStroke bs10 = new BasicStroke(1.0F);

            Rectangle3DPrimitive r3d = new Rectangle3DPrimitive(P1, P2, P3, P4);
            r3d.setShadesVisible(true);
            
            g2.setPaint(Color.WHITE);
            g2.setStroke(bs01);
            r3d.draw(g2, sun, viewPoint);
            assertEquals(Color.WHITE, g2.getPaint());
            assertEquals(bs01, g2.getStroke());
            
            r3d = new Rectangle3DPrimitive(P1, P2, P3, P4);
            r3d.setPaint(Color.RED);
            r3d.setShadesVisible(false);
            
            r3d.draw(g2, sun, viewPoint);
            assertEquals(Color.RED, g2.getPaint());
            assertEquals(Rectangle3DPrimitive.DEFAULT_RECTANGLE_STROKE, g2.getStroke());

            r3d = new Rectangle3DPrimitive(P1, P2, P3, P4);
            r3d.setShadesVisible(true);
            r3d.setPaint(Color.RED);
            r3d.setOutlinePaint(Color.GRAY);
            r3d.draw(g2, sun, viewPoint);
            assertEquals(Color.GRAY, g2.getPaint());
            assertEquals(bs10, g2.getStroke());
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
}
