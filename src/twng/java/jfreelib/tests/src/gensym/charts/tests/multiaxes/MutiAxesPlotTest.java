package gensym.charts.tests.multiaxes;

import gensym.charts.axis.MultiAxesPlot;
import gensym.charts.axis.XYAxesPlot;

import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;
import gensym.charts.GraphXYZDataset;

import junit.framework.TestCase;

public class MutiAxesPlotTest extends TestCase {
    /**
     * Tests creating of multi-axes plot
     */
    public void testPlot() {
        ValueAxis axis = new NumberAxis();
        
        MultiAxesPlot plot = new MultiAxesPlot(axis);
        assertNotNull(plot.getCurrentPlot());
        assertNotNull(plot.getPlot(0));
        assertNull(plot.getPlot(1));
        assertEquals(axis, plot.getDomainAxis());
        assertEquals(1, plot.getAllPlots().size());
        
        plot.setPlotSeries(0, 1);
        plot.setPlotSeries(1, 2);
        plot.setDataset(new GraphXYZDataset());
        
        assertEquals(2, plot.getAllPlots().size());
        plot.setWorkingAxis(1);
        assertEquals(plot.getPlot(1), plot.getCurrentPlot());
        assertEquals(plot.getPlot(1).getRangeAxis(), plot.getCurrentAxis());
        
        plot.setWorkingAxis(2);
        assertEquals(plot.getPlot(0), plot.getCurrentPlot());
    }
    
    /**
     * Tests axis plot functionality
     */
    public void testAxisPlot() {
        GraphXYZDataset dataset = new GraphXYZDataset();
        XYAxesPlot plot = new XYAxesPlot(dataset, null, new NumberAxis(), new XYLineAndShapeRenderer(true, false));
        
        assertEquals(dataset, plot.getDataset());
        assertEquals(dataset, plot.getAxisDataset(0));
        assertNull(plot.getAxisDataset(1));
    }
}
