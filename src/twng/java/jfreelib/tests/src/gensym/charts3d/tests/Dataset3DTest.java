package gensym.charts3d.tests;

import org.jfree.data.DomainOrder;

import gensym.charts.j3d.Point3D;
import gensym.charts.j3d.Series3D;
import gensym.charts.j3d.Dataset3D;

import junit.framework.TestCase;

/**
 * Tests for Dataset3D class
 */
public class Dataset3DTest extends TestCase {
    
    /**
     * Creates Series3D for the specified series index 
     */
    public Series3D doCreateSeries3D(int indexSeries) throws Exception {
        Series3D s3d = Test3DUtils.doCreateSeries3D(indexSeries); 
        assertNotNull(s3d);
        assertEquals(indexSeries, s3d.getItemCount());
        return s3d;
    }

    /**
     * Creates Dataset3D
     */
    public Dataset3D doCreateDataset3D() throws Exception {
        Dataset3D d3d = new Dataset3D();
        assertNotNull(d3d);
        assertTrue(d3d instanceof Dataset3D);
        return d3d;
    }
    
    /**
     * Creating Dataset3D test
     */
    public void testCreateDataset3D() {
        try {
            Dataset3D d3d = doCreateDataset3D();
            assertEquals(0, d3d.getSeriesCount());
            assertEquals(DomainOrder.NONE, d3d.getDomainOrder());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Dataset3D series manipulations test
     */
    public void testDataset3DSeriesManipulations() {
        try {
            Dataset3D d3d = doCreateDataset3D();
            int cntSeries = 3;
            StringBuffer str = new StringBuffer("Dataset3D[");
            
            for (int seriesIndex = 0; seriesIndex < cntSeries; seriesIndex++) {
                Series3D s3d = Test3DUtils.doCreateSeries3D(seriesIndex);
                str.append("\n " + s3d.toString());
                d3d.addSeries(s3d);

                assertEquals(seriesIndex, d3d.getItemCount(seriesIndex));
                assertEquals(d3d.getSeriesKey(seriesIndex), Test3DUtils.genKeyByIndex(seriesIndex));
                assertEquals(s3d, d3d.getSeries3D(seriesIndex));
            }
            str.append("]");
            assertEquals(str.toString(), d3d.toString());
            
            d3d.removeSeries(2);
           
            assertEquals(2, d3d.getSeriesCount());
            assertEquals(-1, d3d.indexOf(Test3DUtils.genKeyByIndex(2)));
            
            // adding series with same key - should override
            int seriesIndex = 0;
            assertEquals(0, d3d.getItemCount(seriesIndex));
            Series3D s3d = Test3DUtils.doCreateSeries3D(seriesIndex);
            s3d.addPoint3D(new Point3D(10, 12, 11));
            
            d3d.addSeries(s3d);

            assertEquals(2, d3d.getSeriesCount());            
            assertEquals(1, d3d.getItemCount(seriesIndex));
            assertFalse(d3d.equals(s3d));
            
            assertFalse(s3d.equals(d3d.getSeries3D(0)));
            
            // adding nullable series            
            try {
                d3d.addSeries(null);
                fail("This should never happen");
            }
            catch (IllegalArgumentException e) {
                ; //this Ok
            }
            catch (Exception e) {
                fail("Wrong exception: " + e.getMessage());
            }

            // get key for non-existing series
            try {
                d3d.getSeriesKey(2);
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
     * Dataset3D point values manipulations test
     */
    public void testDataset3DValuesManipulations() {
        try {
            Dataset3D d3d = Test3DUtils.doCreateDataset3DWithData(4);

            for (int seriesIndex = 0; seriesIndex < d3d.getSeriesCount(); seriesIndex++) {
                for (int itemIndex = 0; itemIndex < d3d.getItemCount(seriesIndex); itemIndex++) {

                    assertEquals(d3d.getXValue(seriesIndex, itemIndex), Test3DUtils.genValueByIndex(Test3DUtils.AxisEnum.X, itemIndex), 0.001D);
                    assertEquals(d3d.getYValue(seriesIndex, itemIndex), Test3DUtils.genValueByIndex(Test3DUtils.AxisEnum.Y, itemIndex), 0.001D);
                    assertEquals(d3d.getZValue(seriesIndex, itemIndex), Test3DUtils.genValueByIndex(Test3DUtils.AxisEnum.Z, itemIndex), 0.001D);
                    
                    assertEquals((Double)d3d.getX(seriesIndex, itemIndex), new Double(Test3DUtils.genValueByIndex(Test3DUtils.AxisEnum.X, itemIndex)));
                    assertEquals((Double)d3d.getY(seriesIndex, itemIndex), new Double(Test3DUtils.genValueByIndex(Test3DUtils.AxisEnum.Y, itemIndex)));
                    assertEquals((Double)d3d.getZ(seriesIndex, itemIndex), new Double(Test3DUtils.genValueByIndex(Test3DUtils.AxisEnum.Z, itemIndex)));
                }
            }
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }


    /**
     * Cloneable Dataset3D test
     */
    public void testDataset3DCloneable() {
        try {
            Dataset3D d3d = Test3DUtils.doCreateDataset3DWithData(4);
            Dataset3D d3dClone = (Dataset3D)d3d.clone();
            
            assertNotSame(d3d, d3dClone);
            assertEquals(d3d.getSeriesCount(), d3dClone.getSeriesCount());

            for (int seriesIndex = 0; seriesIndex < d3d.getSeriesCount(); seriesIndex++) {
                assertEquals(d3d.getItemCount(seriesIndex), d3dClone.getItemCount(seriesIndex));
                
                for (int itemIndex = 0; itemIndex < d3d.getItemCount(seriesIndex); itemIndex++) {
                    assertEquals(d3d.getX(seriesIndex, itemIndex), d3dClone.getX(seriesIndex, itemIndex));
                }
            }
            
            assertTrue(d3d.equals(d3dClone));
            d3d.removeSeries(2);
            assertFalse(d3d.equals(d3dClone));
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
}
