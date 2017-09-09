package gensym.charts.tests;

import gensym.charts.GraphXYZDataset;
import java.util.ArrayList;
import java.util.List;
import junit.framework.TestCase;
import org.jfree.data.xy.XYDataItem;
import org.jfree.data.xy.XYSeries;


/**
 * Class for testing GraphXYZDataset class
 */
public class GraphXYZDatasetTest extends TestCase {

    /**
     * Tests main class functionality
     */
    public final void testMainFunctions() {
        GraphXYZDataset dataset1 = new GraphXYZDataset();
        assertNotNull(dataset1);
        assertEquals(dataset1.getZValue(0, 0), dataset1.getZ(0, 0).doubleValue());
        assertEquals(dataset1.getZValue(0, 1), dataset1.getZ(0, 0).doubleValue());

        XYSeries series = new XYSeries("s1");
        series.add(new XYDataItem(1, 1));
        series.add(new XYDataItem(2, 2));
        series.add(new XYDataItem(3, 3));
        series.add(new XYDataItem(4, 4));
        series.add(new XYDataItem(5, 5));
        series.add(new XYDataItem(6, 6));
        series.add(new XYDataItem(7, 7));
        GraphXYZDataset dataset2 = new GraphXYZDataset(series);
        dataset2.addSeries(new XYSeries("s2"));
        assertEquals(dataset2.getZValue(0, 0), dataset2.getZ(0, 0).doubleValue());
        assertEquals(dataset2.getZValue(1, 1), dataset2.getZ(0, 0).doubleValue());

        List<Double> zValues = new ArrayList<Double>();
        zValues.add(new Double(-1));
        zValues.add(new Double(2));
        zValues.add(new Double(3));
        zValues.add(new Double(4));
        zValues.add(new Double(100000));
        dataset2.setValuesZ(zValues);
        assertEquals(dataset2.getZValue(0, 0), new Double(-1));
        assertEquals(dataset2.getZValue(0, 4), new Double(100000));
    }
}
