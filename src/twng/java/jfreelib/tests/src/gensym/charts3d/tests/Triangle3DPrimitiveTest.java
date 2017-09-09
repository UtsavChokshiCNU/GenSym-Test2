package gensym.charts3d.tests;

import gensym.charts.j3d.Point3D;
import gensym.charts.j3d.Triangle3D;
import gensym.charts.j3d.ViewPoint;
import gensym.charts.j3d.primitives.Triangle3DPrimitive;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.GradientPaint;
import java.awt.Graphics2D;
import java.awt.Paint;
import java.awt.Shape;

import junit.framework.TestCase;

/**
 * Test simple triangle class
 */
public class Triangle3DPrimitiveTest extends TestCase {

    /** The first point of tested triangle */
    private final Point3D P1 = new Point3D(1.1, 1.2, 1.3);

    /** The second point of tested triangle */
    private final Point3D P2 = new Point3D(2.1, 2.2, 2.3);

    /** The third point of tested triangle */
    private final Point3D P3 = new Point3D(3.1, 3.2, 3.3);
    
    /**
     * Creates Triangle3DPrimitive by points (p1, p2, p3) and specified paint 
     * and outline paint
     * 
     * @param paint  the paint
     * @param outlPaint  the outline paint
     * 
     * @return Triangle3DPrimitive object with normalPoint.Z < 0
     */
    private Triangle3DPrimitive doCreateTriangle3DPrimitive(Paint paint, Paint outlPaint) {
        Triangle3DPrimitive primitive = new Triangle3DPrimitive(new Triangle3D(P1, P2, P3));
        primitive.setPaint(paint);
        primitive.setOutlinePaint(outlPaint);
        return primitive;
    }
    
    /**
     * Creates Triangle3DPrimitive by points (p3, p2, p1) and specified paint 
     * and outline paint
     * 
     * @param paint  the paint
     * @param outlPaint  the outline paint
     * 
     * @return Triangle3DPrimitive object with normalPoint.Z = 0
     */
    private Triangle3DPrimitive doCreateTriangle3DPrimitive2(Paint paint, Paint outlPaint) {
        Triangle3DPrimitive primitive = new Triangle3DPrimitive(new Triangle3D(P3, P2, P1));
        primitive.setPaint(paint);
        primitive.setOutlinePaint(outlPaint);
        return primitive;
    }

    /**
     * Creating Triangle3DPrimitive and simple methods test
     */
    public void testCreateTriangle3DPrimitiveAndSimpleMethods() {
        try {
            Triangle3DPrimitive tp = doCreateTriangle3DPrimitive(Color.GREEN, null);
            Triangle3D tr = tp.getTriangle3D();

            assertNotNull(tp);
            assertNotNull(tr);
            assertTrue("assert #1", tp instanceof Triangle3DPrimitive);
            
            //test averageZValue()
            double avgZ = (tr.getA().getZ() + tr.getB().getZ() + tr.getC().getZ()) / 3;
            assertTrue("assert #2", tp.averageZValue() == tr.averageZValue());
            assertTrue("assert #3", tp.averageZValue() == avgZ);
            
            //test getPoints()
            assertEquals("assert #4", 3, tp.getPoints().length);
            assertEquals("assert #5", tr.getA(), tp.getPoints()[0]);
            assertEquals("assert #6", tr.getB(), tp.getPoints()[1]);
            assertEquals("assert #7", tr.getC(), tp.getPoints()[2]);
            
            //test getA(), getB(), getC()
            assertEquals("assert #8", P1, tr.getA());
            assertEquals("assert #9", P2, tr.getB());
            assertEquals("assert #10", P3, tr.getC());
            
            assertEquals("assert #11", Color.GREEN, tp.getPaint());
            
            ViewPoint vp = new ViewPoint();
            assertNotNull(tp.getShape(vp));
            assertTrue(tp.getShape(vp) instanceof Shape);
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Transforming Triangle3DPrimitive test
     */
    public void testTriangle3DPrimitiveTransform() {
        try {
            Triangle3DPrimitive tp = doCreateTriangle3DPrimitive(Color.GREEN, null);
            ViewPoint vp = new ViewPoint();

            Triangle3DPrimitive tp1 = (Triangle3DPrimitive) tp.transform(vp);
            Triangle3D tr = tp1.getTriangle3D();

            assertNotSame("assert #1", tp, tp1);
            assertFalse("assert #2", tp.equals(tp1));
            assertEquals("assert #3", tp.getPaint(), tp1.getPaint());
            assertEquals("assert #4", vp.transform(P1), tr.getA());
            assertEquals("assert #5", vp.transform(P2), tr.getB());
            assertEquals("assert #6", vp.transform(P3), tr.getC());

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Calculate normal of triangle (point1, point2, point3)
     * @param p1  the first point of triangle
     * @param p2  the second point of triangle
     * @param p3  the third point of triangle
     * @return Point3D object
     */
    private Point3D triangleNormal(Point3D p1, Point3D p2, Point3D p3) {
        Point3D bma = new Point3D(p2.getX() - p1.getX(), p2.getY() - p1.getY(), p2.getZ() - p1.getZ());
        Point3D cma = new Point3D(p3.getX() - p1.getX(), p3.getY() - p1.getY(), p3.getZ() - p1.getZ());
        Point3D prod = new Point3D(bma.getY() * cma.getZ() - bma.getZ() * cma.getY(), 
                                   bma.getZ() * cma.getX() - bma.getX() * cma.getZ(), 
                                   bma.getX() * cma.getY() - bma.getY() * cma.getX()); 
        double length = prod.length();
        return new Point3D(prod.getX() / length, prod.getY() / length, prod.getZ() / length);
    }
    
    /**
     * Get color with shade by specified color 
     * @param color specified color object
     * @param shade specified shade value
     * @return Color object
     */
    private Color genShaderedColor(Color color, double shade) {
        int r = (int) (color.getRed() * shade);
        int g = (int) (color.getGreen() * shade);
        int b = (int) (color.getBlue() * shade);
        
        return new Color(r, g, b, color.getAlpha());
    }
    
    /**
     * Drawing Triangle3DPrimitive test
     */
    public void testTriangle3DPrimitiveDraw() {
        try {
            Point3D sun = new Point3D(1, 0, 10);
            ViewPoint vp = new ViewPoint();
            Graphics2D g2 = Test3DUtils.genGraphics2D();
            BasicStroke bs = new BasicStroke(0.1F);
            
            //(normal().getZ() < 0)
            Triangle3DPrimitive tp = doCreateTriangle3DPrimitive(Color.BLUE, Color.CYAN);
            g2.setStroke(bs);
            g2.setPaint(Color.BLACK);
            tp.draw(g2, sun, vp);
            assertTrue("assert #1", g2.getPaint().equals(Color.CYAN));
            assertFalse("assert #2", bs.equals(g2.getStroke()));

            //(paint == null) && (outlinePaint == null) - check condition
            Triangle3DPrimitive tp1 = doCreateTriangle3DPrimitive2(null, null);
            Triangle3D tr1 = tp1.getTriangle3D();
                    
            g2.setStroke(bs);
            g2.setPaint(Color.BLACK);
            tp1.draw(g2, sun, vp);
            assertTrue("assert #3", g2.getPaint().equals(Color.BLACK));
            assertTrue("assert #4", bs.equals(g2.getStroke()));
            
            //if (paint != null) && (paint not instanceof Color) { check this body }
            GradientPaint gp = new GradientPaint(1, 5, Color.BLUE, 3, 6, Color.CYAN);
            tp1 = doCreateTriangle3DPrimitive2(gp, null);
            g2.setPaint(Color.BLACK);
            tp1.draw(g2, sun, vp);
            assertTrue("assert #5", g2.getPaint().equals(gp));
            assertTrue("assert #6", bs.equals(g2.getStroke()));

            //if (paint != null) && (paint instanceof Color) 
            //  && (outlinePaint == null && color.getAlpha() <> 0xFF) { check this body }
            Color color = new Color(0, 255, 0, 10);
            tp1 = doCreateTriangle3DPrimitive2(color, null);
            tp1.setShadesVisible(true);
            g2.setPaint(Color.BLACK);
            tp1.draw(g2, sun, vp);
            double shade = (triangleNormal(tr1.getA(), tr1.getB(), tr1.getC()).dotProduct(sun) + 1) / 2;
            assertTrue("assert #7", g2.getPaint().equals(genShaderedColor(color, shade)));
            assertFalse("assert #8", bs.equals(g2.getStroke()));
            
            //if (paint != null) && (paint instanceof Color) 
            //  && (outlinePaint == null && color.getAlpha() == 0xFF) { check this body }
            color = new Color(0, 255, 0, 0xFF);
            tp1 = doCreateTriangle3DPrimitive2(color, null);
            tp1.setShadesVisible(true);
            g2.setPaint(Color.BLACK);
            tp1.draw(g2, sun, vp);
            assertTrue("assert #9", g2.getPaint().equals(genShaderedColor(color, shade)));
            assertFalse("assert #10", bs.equals(g2.getStroke()));
            
            // if (outlinePaint != null) { check this body }
            tp1 = doCreateTriangle3DPrimitive2(null, Color.GREEN);
            g2.setPaint(Color.BLACK);
            tp1.draw(g2, sun, vp);
            assertTrue("assert #11", g2.getPaint().equals(Color.GREEN));
            assertFalse("assert #12", bs.equals(g2.getStroke()));
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

}
