package gensym.charts3d.tests;

import gensym.charts.j3d.Point3D;
import gensym.charts.j3d.Series3D;
import junit.framework.TestCase;

/**
 * Tests Series3D class
 */
public class Series3DTest extends TestCase {
    
    /**
     * Creates Series3D
     */
    public Series3D doCreateSeries3D() throws Exception {
        String key = "series1";
        Series3D s3d = new Series3D(key);
        assertNotNull(s3d);
        assertTrue(s3d instanceof Series3D);
        return s3d;
    }
    
    /**
     * Creating Series3D test
     */
    public void testCreateSeries3D() {
        try {
            Series3D s3d = doCreateSeries3D();
            assertTrue(s3d.isEmpty());
            s3d = null;

            String key = "series2";
            String desc = "Series 3D";
            s3d = new Series3D(key, desc);
            assertNotNull(s3d);
            assertTrue(s3d instanceof Series3D);
            assertEquals(desc, s3d.getDescription());
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Series3D items manipulations test
     */
    public void testSeries3DItemsManipulations() {
        try {
            Series3D s3d = doCreateSeries3D();
            Point3D p1 = new Point3D(10, 11, 12);

            s3d.addPoint3D(p1);
            assertEquals(1, s3d.getItemCount());
            assertEquals(0, s3d.indexOf(p1));
            String s3dAsString = "Series3D [Key: " + s3d.getKey().toString() + "; Description: " + s3d.getDescription() + "; " 
                + p1.toString()+ "]"; 
            assertEquals(s3dAsString, s3d.toString());
            
            s3d.addPoint3D(p1);
            assertEquals(1, s3d.getItemCount());
            
            Point3D p2 = new Point3D(10, 11, 12);
            assertEquals(0, s3d.indexOf(p2));
            
            s3d.addPoint3D(p2);
            assertEquals(1, s3d.getItemCount());
            
            Point3D p3 = new Point3D(11, 12, 13);
            s3d.addPoint3D(p3);
            assertEquals(2, s3d.getItemCount());
            assertEquals(s3d.indexOf(p3), s3d.indexOf(p3.getX(), p3.getY(), p3.getZ()));
            assertEquals(s3d.indexOf(p3), s3d.indexOf(11, 12, 13));
            assertEquals(p3, s3d.getPoint3D(1));
            assertNull(s3d.removePoint3D(null));

            try {
                s3d.insertPoint3D(s3d.getItemCount() + 2, p3);
                fail("This should never happen");
            }
            catch (IllegalArgumentException e) {
                ; //this Ok
            }
            catch (Exception e) {
                fail("Wrong exception: " + e.getMessage());
            }

            try {
                s3d.getPoint3D(s3d.getItemCount() + 2);
                fail("This should never happen");
            }
            catch (IllegalArgumentException e) {
                ; //this Ok
            }
            catch (Exception e) {
                fail("Wrong exception: " + e.getMessage());
            }
            
            s3dAsString = "Series3D [Key: " + s3d.getKey().toString() + "; Description: " + s3d.getDescription() + "; " 
                + p1.toString() + "; " + p3.toString() + "]";
            assertEquals(s3dAsString, s3d.toString());

            s3d.removePoint3D(0);
            assertEquals(1, s3d.getItemCount());
            assertEquals(0, s3d.indexOf(p3));
            assertEquals(p3, s3d.getPoint3D(0));
            
            assertTrue(s3d.insertPoint3D(0, p1));
            assertEquals(2, s3d.getItemCount());
            assertEquals(0, s3d.indexOf(p1));
            assertEquals(1, s3d.indexOf(p3));

            assertEquals(p3, s3d.removePoint3D(p3));
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }


    /**
     * Series3D item index calculates test
     */
    public void testSeries3DItemIndexCalculates() {
        try {
            Series3D s3d = doCreateSeries3D();
            
            Point3D p1 = new Point3D(10, 11, 12);
            s3d.addPoint3D(p1);
            
            Point3D p2 = new Point3D(11, 12, 13);
            s3d.addPoint3D(p2);

            assertEquals(2, s3d.getItemCount());

            assertEquals(0, s3d.indexOf(p1));
            assertEquals(0, s3d.indexOf(p1.getX(), p1.getY(), p1.getZ()));
            assertEquals(0, s3d.indexOf(10, 11, 12));
            
            assertEquals(1, s3d.indexOf(p2));
            assertEquals(1, s3d.indexOf(p2.getX(), p2.getY(), p2.getZ()));
            assertEquals(1, s3d.indexOf(11, 12, 13));
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    
    /**
     * Cloneable Series3D test
     */
    public void testSeries3DCloneable() {
        try {
            Series3D s3d = doCreateSeries3D();
            
            for (int i = 0; i < 3; i++) {
                assertTrue(s3d.addPoint3D(new Point3D(i + 1, i + 2, i + 3)));
            }
            
            Series3D s3dClone = (Series3D)s3d.clone();
            
            assertNotSame(s3d, s3dClone);
            assertEquals(s3d.getItemCount(), s3dClone.getItemCount());

            for (int i = 0; i < s3d.getItemCount(); i++) {
                assertEquals(s3d.getPoint3D(i), s3dClone.getPoint3D(i));
            }
            assertTrue(s3d.equals(s3dClone));
            
            s3d.removePoint3D(1);
            
            assertEquals(2, s3d.getItemCount());
            assertFalse(s3d.equals(s3dClone));
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

}
