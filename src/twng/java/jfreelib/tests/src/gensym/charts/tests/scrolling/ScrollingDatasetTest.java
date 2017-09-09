package gensym.charts.tests.scrolling;

import java.util.LinkedList;

import gensym.charts.scrolling.ScrollingDataset;
import gensym.charts.GraphXYZDataset;

import org.jfree.data.xy.XYSeries;

import junit.framework.TestCase;

/**
 * Scrolling dataset test
 */
public class ScrollingDatasetTest extends TestCase {
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
        ScrollingDataset scroll = new ScrollingDataset(dataset);
        assertTrue(dataset.hasListener(scroll));
        
        assertEquals(scroll.getZValue(0, 0), new Double(0));
        assertNotNull(scroll.getZ(0, 0));
        
        scroll.setItems(null);
        assertEquals(dataset.getSeriesCount(), scroll.getSeriesCount());
        dataset.addSeries(new XYSeries("Subset 3", false, false));
        assertEquals(dataset.getSeriesCount(), scroll.getSeriesCount());
        
        assertEquals(dataset.getItemCount(0), scroll.getItemCount(0));
        assertEquals(dataset.getItemCount(0), scroll.getItemCount());
        
        assertEquals(dataset.getSeriesKey(0), scroll.getSeriesKey(0));
        assertEquals(dataset.getSeriesKey(1), scroll.getSeriesKey(1));
        
        assertEquals(dataset.getEndX(0, 0), scroll.getEndX(0, 0));
        assertEquals(dataset.getEndY(0, 0), scroll.getEndY(0, 0));
        assertEquals(dataset.getStartX(0, 0), scroll.getStartX(0, 0));
        assertEquals(dataset.getStartY(0, 0), scroll.getStartY(0, 0));

        assertEquals(dataset.getX(0, 0), scroll.getX(0, 0));
        assertEquals(dataset.getY(0, 0), scroll.getY(0, 0));
        
        assertEquals(0, new ScrollingDataset(new GraphXYZDataset()).getItemCount());
    }
    
    /**
     * Tests scrolling
     */
    public void testScrolling() {
        LinkedList<Integer> items = new LinkedList<Integer>();
        items.add(1);
        
        GraphXYZDataset dataset = createDataset();
        ScrollingDataset scroll = new ScrollingDataset(dataset);

        scroll.setItems(items);
        assertEquals(dataset.getSeriesCount(), scroll.getSeriesCount());
        assertEquals(dataset.getSeriesCount(), scroll.getSeriesCount());
        
        assertEquals(0, scroll.getItemCount(0));
        assertEquals(dataset.getItemCount(1), scroll.getItemCount(1));
        
        assertEquals(dataset.getSeriesKey(0), scroll.getSeriesKey(0));
        assertEquals(dataset.getSeriesKey(1), scroll.getSeriesKey(1));
        
        assertNull(scroll.getEndX(0, 0));
        assertEquals(dataset.getEndX(1, 0), scroll.getEndX(1, 0));
        assertNull(scroll.getEndY(0, 0));
        assertEquals(dataset.getEndY(1, 0), scroll.getEndY(1, 0));
        
        assertNull(scroll.getStartX(0, 0));
        assertEquals(dataset.getStartX(1, 0), scroll.getStartX(1, 0));
        assertNull(scroll.getStartY(0, 0));
        assertEquals(dataset.getStartY(1, 0), scroll.getStartY(1, 0));

        assertNull(scroll.getX(0, 0));
        assertEquals(dataset.getX(1, 0), scroll.getX(1, 0));
        assertNull(scroll.getY(0, 0));
        assertEquals(dataset.getY(1, 0), scroll.getY(1, 0));
    }
}
