package gensym.charts.tests.scrolling;

import java.util.ArrayList;
import java.util.List;

import gensym.charts.scrolling.GraphSeriesScrolling;
import gensym.charts.scrolling.SeriesScrollingListener;
import gensym.charts.GraphXYZDataset;

import org.jfree.data.xy.XYSeries;

import junit.framework.TestCase;

/**
 * Graph series scrolling test
 */
public class GraphSeriesScrollingTest extends TestCase{
    /**
     * Creates dataset
     * @return created dataset
     */
    private GraphXYZDataset createDataset() {
        GraphXYZDataset dataset = new GraphXYZDataset();
        XYSeries series = new XYSeries("S1", false, false);
        series.add(1.0, 3.0);
        series.add(2.0, 0.0);
        dataset.addSeries(series);

        series = new XYSeries("S2", false, false);
        series.add(1.0, -6.0);
        series.add(2.0, 2.0);
        dataset.addSeries(series);
        
        return dataset;
    }

    /**
     * Scrolling listener
     */
    private class ScrollingListener implements SeriesScrollingListener {
        public ArrayList<Integer> scrolledItems = null; 
        public void itemsScrolled(List<Integer> items) {
            scrolledItems = new ArrayList<Integer>(items);
        }
    }
    
    /**
     * Tests creating
     */
    public void testCreate() {
        GraphXYZDataset dataset = createDataset();
        GraphSeriesScrolling scroll = new GraphSeriesScrolling(1, dataset);
        
        assertEquals(1, scroll.getScrolledItems());
        assertEquals(2, scroll.getScrollItemsCount());
        assertTrue(scroll.isScrollingSupported());
        assertNotNull(scroll.getDataset());
        
        ScrollingListener listener = new ScrollingListener();
        scroll.addListener(listener);
        scroll.updateScrollingPos(1);
        assertEquals(1, scroll.getScrollItemPos());
        assertNotNull(listener.scrolledItems);
        assertEquals(1, listener.scrolledItems.size());
        assertEquals(1, (int) listener.scrolledItems.get(0));
        assertEquals(1, scroll.getScrollItemPos());
        
        scroll.removeListener(listener);
        
        listener = new ScrollingListener();
        scroll.addListener(listener);
        scroll.setScrollingItems(0, true);
        assertNull(listener.scrolledItems);
        assertEquals(0, scroll.getScrollItemsCount());
    }
}
