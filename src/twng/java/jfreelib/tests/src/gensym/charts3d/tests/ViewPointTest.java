package gensym.charts3d.tests;

import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import gensym.charts.j3d.Point3D;
import gensym.charts.j3d.ViewPoint;
import junit.framework.TestCase;

/**
 * Test simple ViewPoint class
 */
public class ViewPointTest extends TestCase {

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

    /** Storage for Points2D as result of method toScreen(points3d[i]) */ 
    private Point2D[] pointsToScreen = {
        new Point2D.Double(-1036.31925748227, -162.81335442441),
        new Point2D.Double( 717.51997391163,  511.73161584869),
        new Point2D.Double(-301.70631578327,  418.86901361165),
        new Point2D.Double( 375.78621207910, -362.35755535654),
        new Point2D.Double(-354.92703387609, 1044.10008447176),
        new Point2D.Double( 384.53455751084,  285.18745218057),
        new Point2D.Double( -57.58477224053, -437.86751550174),
        new Point2D.Double( 609.21568118725,  573.11747053075),
        new Point2D.Double(-107.81099062572,  909.27767724731),
        new Point2D.Double( 871.97763801537,  -65.92126717913),
        new Point2D.Double(-187.37178025986,  439.28795304308),
        new Point2D.Double( 282.85758589944,  340.07003760322),
        new Point2D.Double( -40.94968416467, -1057.51742539752),
        new Point2D.Double( 205.11694714328,  570.67947889683),
        new Point2D.Double(-401.61762525941,  538.10591461607),
        new Point2D.Double( 549.51001901419, -564.04324065579),
        new Point2D.Double(-1654.35872583922,  149.98788466198),
        new Point2D.Double( 308.60299921073,  539.72976072424),
        new Point2D.Double(-388.73588543101, -108.38684427952),
        new Point2D.Double( 139.21672527578,  549.18004583210)};
    
    /** Storage for Points3D as result of method transform(points3d[i]) */ 
    private Point3D[] pointsTransform = {
        new Point3D( 914.61166190860, -407.76982710936,  -45.41000000000),
        new Point3D(-1079.95185454963,  -47.87838818116,  226.60000000000),
        new Point3D(  42.91994683404, -875.38348245998,  697.81000000000),
        new Point3D(-229.60982110149,  987.90456024544,  942.86000000000),
        new Point3D( -92.76350138033, -367.05416195932, -656.69000000000),
        new Point3D(-936.72688764951,  -59.00664754466,  960.50000000000),
        new Point3D( 536.48440002767,  629.25643693724,  872.37000000000),
        new Point3D(-951.58450720260, -172.81952045988,  156.29000000000),
        new Point3D(-297.08672065446, -603.86812642396, -265.01000000000),
        new Point3D(-746.75559689078,  568.48646730798,   73.25000000000),
        new Point3D(-114.78300386610, -660.54633427450,  403.84000000000),
        new Point3D(-653.67719621989, -203.46990647784,  547.74000000000),
        new Point3D( 447.84031074459,  635.43499948633, -265.44000000000),
        new Point3D(-769.36533897017, -585.51505633188,  594.31000000000),
        new Point3D(  47.75621572370, -723.16884616233,   79.36000000000),
        new Point3D(-231.97867116431, 1161.52349426296,  504.14000000000),
        new Point3D( 700.96572898441, -550.38234354797, -463.49000000000),
        new Point3D(-819.11590301808, -422.45940210022,  482.39000000000),
        new Point3D( 531.41115318424, -166.31345607435,  379.78000000000),
        new Point3D(-603.88933745521, -559.54878161596,  453.13000000000)};
    
    /** Storage for Points3D as result of method fitIntoArea(points3d[i].X, points3d[i].Y, points3d[i].Z) */ 
    private double[] zoomFitIntoArea = {
            0.044204,
            0.036800,
            0.067982,
            0.051020,
            0.204673,
            0.047804,
            0.101380,
            0.053190,
            0.127230,
            0.051674,
            0.105183,
            0.080973,
            0.117930,
            0.034652,
            0.086647,
            0.040411,
            0.056431,
            0.043373,
            0.110169,
            0.043560,
    };
    
    /**
     * Creating view point and initial values test
     */
    public void testCreateViewPointAndInitialValues() {
        try {
            ViewPoint vp = new ViewPoint();
            assertNotNull("assert #1", vp);
            assertTrue("assert #2", vp instanceof ViewPoint);
            
            //test initial values
            assertTrue("assert #3", vp.getPhi() == 0.0);
            assertTrue("assert #4", vp.getXi() == 0.0);
            assertTrue("assert #5", vp.getRho() == 10.0);
            assertTrue("assert #6", vp.getZoom() == 1.0);
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Get/Set field methods test
     */
    public void testViewPointGetSet() {
        try {
            ViewPoint viewPoint = new ViewPoint();
            double d1 = 2.5;
            double d2 = 5.5;
            
            viewPoint.setPhi(d1);
            assertEquals("assert #1", d1, viewPoint.getPhi(), 0.0001D);
            viewPoint.setPhi(d2);
            assertEquals("assert #2", d2, viewPoint.getPhi(), 0.0001D);
            
            viewPoint.setRho(d1);
            assertEquals("assert #2", d1, viewPoint.getRho(), 0.0001D);
            viewPoint.setRho(d2);
            assertEquals("assert #2", d2, viewPoint.getRho(), 0.0001D);

            viewPoint.setXi(d1);
            assertEquals("assert #3", d1, viewPoint.getXi(), 0.0001D);
            viewPoint.setXi(d2);
            assertEquals("assert #3", d2, viewPoint.getXi(), 0.0001D);
            
            viewPoint.setZoom(d1);
            assertEquals("assert #4", d1, viewPoint.getZoom(), 0.0001D);
            viewPoint.setZoom(d2);
            assertEquals("assert #4", d2, viewPoint.getZoom(), 0.0001D);
            
            // set zoom < 0            
            try {
                viewPoint.setZoom(-1.5);
                fail("This should never happen");
            }
            catch (RuntimeException e) {
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
     * Moving view point test
     */
    public void testViewPointMoveTo() {
        try {
            ViewPoint viewPoint = new ViewPoint();
            double dx = 1.0;
            viewPoint.moveToX(dx);
            assertEquals(dx, viewPoint.getMovingPoint().getX());
            
            dx = 0;
            viewPoint.moveToX(0);
            assertEquals(dx, viewPoint.getMovingPoint().getX());

            double dy = -11.0;
            viewPoint.moveToY(dy);
            assertEquals(dy, viewPoint.getMovingPoint().getY());
            
            dy = 0;
            viewPoint.moveToY(0);
            assertEquals(dy, viewPoint.getMovingPoint().getY());
            
            double dz = 10.0;
            viewPoint.moveToZ(dz);
            assertEquals(dz, viewPoint.getMovingPoint().getZ());
            
            dz = 0.0;
            viewPoint.moveToZ(dz);
            assertEquals(dz, viewPoint.getMovingPoint().getZ());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }


    /**
     * Calculating Point2D from Point3D test
     */
    public void testViewPointToScreen() {
        try {
            ViewPoint vp = new ViewPoint();
            assertEquals(new Point2D.Double(0, 0), vp.getScreenMoving());
            vp.moveScreen(10, 12);
            assertEquals(new Point2D.Double(10, 12), vp.getScreenMoving());
            vp.moveScreen(0, 0);
            assertEquals(new Point2D.Double(0, 0), vp.getScreenMoving());
            
            for (int i = 0; i < points3d.length; i++) {
                Point2D p2d = vp.toScreen(points3d[i]);
                assertEquals("assert toScreen().X #" + i, pointsToScreen[i].getX(), p2d.getX(), 0.00001D);
                assertEquals("assert toScreen().Y #" + i, pointsToScreen[i].getY(), p2d.getY(), 0.00001D);
            }
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Transforming Point3D by ViewPoint test
     */
    public void testViewPointTransform() {
        try {
            ViewPoint vp = new ViewPoint();
            
            for (int i = 0; i < points3d.length; i++) {
                Point3D p3d = vp.transform(points3d[i]);
                assertEquals("assert transform().X #" + i, pointsTransform[i].getX(), p3d.getX(), 0.00001D);
                assertEquals("assert transform().Y #" + i, pointsTransform[i].getY(), p3d.getY(), 0.00001D);
                assertEquals("assert transform().Z #" + i, pointsTransform[i].getZ(), p3d.getZ(), 0.00001D);
            }
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Fit Into Area Point3D by ViewPoint test
     */
    public void testViewPointFitIntoArea() {
        try {
            ViewPoint vp = new ViewPoint();
            
            vp.setZoom(1.0);
            assertEquals(1.0, vp.getZoom());
            
            vp.moveToX(0);
            vp.moveToY(0);
            vp.moveToZ(0);
            
            Rectangle2D area = Test3DUtils.genRectangle2D();

            for (int i = 0; i < points3d.length; i++) {
                vp.fitIntoArea(points3d[i].getX(), points3d[i].getY(), points3d[i].getZ(), area);
                assertEquals("assert fitIntoArea() #" + i, zoomFitIntoArea[i], vp.getZoomFactor(), 0.00001D);
            }
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
}
