package gensym.charts.tests.multiaxes;

import gensym.charts.GraphXYZDataset;
import gensym.charts.axis.MultiAxesDataset;

import java.util.LinkedList;

import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import junit.framework.TestCase;

/**
 * Multiaxes dataset test
 */
public class MultiAxesDatasetTest extends TestCase {
    /**
     * Creates dataset
     * @return created dataset
     */
    private GraphXYZDataset createDataset() {
        GraphXYZDataset dataset = new GraphXYZDataset();
        XYSeries series = new XYSeries("Subset 1", false, false);
        series.add(1.0, 2.0);
        series.add(3.0, 4.0);
        dataset.addSeries(series);

        series = new XYSeries("Subset 2", false, false);
        series.add(1.0, 6.0);
        series.add(3.0, 8.0);
        dataset.addSeries(series);
        
        return dataset;
    }
    
    /**
     * Test creation
     */
    public void testCreating() {
        GraphXYZDataset dataset = createDataset();
        MultiAxesDataset multiDataset = new MultiAxesDataset(dataset);
        assertTrue(dataset.hasListener(multiDataset));
        
        assertEquals(multiDataset.getZValue(0, 0), new Double(0));
        assertNull(multiDataset.getZ(0, 0));
        
        multiDataset.setItems(null);
        assertEquals(0, multiDataset.getSeriesCount());
        
        assertEquals(0, multiDataset.getItemCount(0));
        assertEquals(0, multiDataset.getItemCount());
        
        assertNull(multiDataset.getSeriesKey(0));
        assertNull(multiDataset.getSeriesKey(1));
        
        assertNull(multiDataset.getEndX(0, 0));
        assertNull(multiDataset.getEndY(0, 0));
        assertNull(multiDataset.getStartX(0, 0));
        assertNull(multiDataset.getStartY(0, 0));

        assertNull(multiDataset.getX(0, 0));
        assertNull(multiDataset.getY(0, 0));
    }
    
    /**
     * Tests items
     */
    public void testItems() {
        GraphXYZDataset dataset = createDataset();
        MultiAxesDataset multiDataset = new MultiAxesDataset(dataset);
        
        doTestDataset(multiDataset, dataset, 0);
        doTestDataset(multiDataset, dataset, 1);
    }
    
    /**
     * Tests dataset
     * @param multiDataset dataset
     * @param dataset source dataset
     * @param series series number
     */
    private void doTestDataset(MultiAxesDataset multiDataset, XYSeriesCollection dataset, int series) {
        LinkedList<Integer> items = new LinkedList<Integer>();
        items.add(series);
        multiDataset.setItems(items);
        
        assertEquals(1, multiDataset.getSeriesCount());
        assertEquals(1, multiDataset.getSeriesCount());
        
        assertEquals(dataset.getItemCount(series), multiDataset.getItemCount(0));
        assertEquals(dataset.getItemCount(series), multiDataset.getItemCount());
        
        assertEquals(dataset.getSeriesKey(series), multiDataset.getSeriesKey(0));
        
        assertEquals(dataset.getEndX(series, 0), multiDataset.getEndX(0, 0));
        assertEquals(dataset.getEndY(series, 0), multiDataset.getEndY(0, 0));
        
        assertEquals(dataset.getStartX(series, 0), multiDataset.getStartX(0, 0));
        assertEquals(dataset.getStartY(series, 0), multiDataset.getStartY(0, 0));

        assertEquals(dataset.getX(series, 0), multiDataset.getX(0, 0));
        assertEquals(dataset.getY(series, 0), multiDataset.getY(0, 0));
    }
}
