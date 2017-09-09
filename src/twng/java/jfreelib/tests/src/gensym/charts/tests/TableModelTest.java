package gensym.charts.tests;

import java.util.LinkedList;

import gensym.charts.tables.ChartTableModel;
import junit.framework.TestCase;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

/**
 * Tests table model
 */
public class TableModelTest extends TestCase {
    /**
     * Creates table model
     * @return created model
     */
    private ChartTableModel createModel() {
        XYSeriesCollection dataset = new XYSeriesCollection();
        XYSeries series = new XYSeries("Subset 1", false, false);
        series.add(1.0, 2.0);
        series.add(3.0, 4.0);
        XYSeries series2 = new XYSeries("Subset 2", false, false);
        series2.add(1.0, 6.0);
        series2.add(3.0, 8.0);

        dataset.addSeries(series);
        dataset.addSeries(series2);
        return new ChartTableModel(dataset);
    }
    
    /**
     * Test model
     */
    public final void testChartTableModel() {
        ChartTableModel model = createModel();
        assertNull(model.getColumnName(999));
        assertEquals(Double.toString(1.0), model.getColumnName(1));
        assertEquals(Number.class, model.getColumnClass(99));
        assertEquals(String.class, model.getColumnClass(0));

        assertFalse(model.isUpdateAllowed());
        model.setUpdateAllowed(true);
        assertTrue(model.isUpdateAllowed());
        model.updateData();
        assertEquals(2.0, model.getValueAt(0, 1));
        assertEquals(4.0, model.getValueAt(0, 2));
        assertEquals("Subset 1", model.getValueAt(0, 0));
        assertNull(model.getValueAt(99, 99));
    }
    
    /**
     * Tests scrolling
     */
    public void testScrolling() {
        ChartTableModel model = createModel();
        LinkedList<Integer> items = new LinkedList<Integer>();
        items.add(1);
        items.add(-1);

        model.setShowAllItems(true);
        assertTrue(model.getShowAllItems());
        model.itemsScrolled(items);
        assertEquals(2.0, model.getValueAt(0, 1));
        assertEquals(6.0, model.getValueAt(1, 1));
        assertNull(model.getValueAt(-2, 1));

        model.setShowAllItems(false);
        assertFalse(model.getShowAllItems());
        model.itemsScrolled(items);
        assertEquals(6.0, model.getValueAt(0, 1));
        assertNull(model.getValueAt(1, 1));
        assertNull(model.getValueAt(2, 1));
        assertNull(model.getValueAt(-2, 1));
    }
}
