package gensym.charts.tests;

import java.awt.Color;
import java.awt.Paint;
import java.awt.RadialGradientPaint;
import java.awt.geom.Rectangle2D;

import org.jfree.chart.ChartRenderingInfo;
import org.jfree.chart.plot.PolarPlot;
import org.jfree.chart.renderer.DefaultPolarItemRenderer;
import org.jfree.data.xy.*;
import org.w3c.dom.*;

import gensym.charts.*;
import gensym.charts.actions.CreateChartAction;
import junit.framework.TestCase;

/**
 * <p>
 * Test cases for Polar chart functionality.
 * </p>
 */
public class PolarChartTest extends TestCase {
    /**
     * Chart handle
     */
    static int handle = 0;

    /**
     * Initializes test data
     */
    protected void setUp() {
        handle++;
    }

    /**
     * Destroys test data 
     */
    protected void tearDown() {
        JFreeChartHolder holder = JFreeChartHolder.getHolder(handle);
        if (holder != null) {
            holder.dispose();
        }
    }
    
    /**
     * Runs action
     * @param name action name
     * @param parameters action parameters
     * @throws Exception
     */
    private void runAction(String name, Object... parameters) throws Exception {
        Document doc = ChartServer.makeXMLMessage(name, handle);
        ChartServer.addXMLData(doc, parameters);
        ChartServer.processXML(doc);
    }
    
    /**
     * Creates chart
     */
    void doCreateChart() throws Exception {
        runAction("CreateChart", "title", "Pie chart", "type", CreateChartAction.PE_POLAR_CHART,
                "x", -1, "y", -1, "width", 500, "height", 400);

        JFreeChartHolder holder = JFreeChartHolder.getHolder(handle); 
        assertNotNull(holder);
        assertTrue(holder.getChart() instanceof PolarChart);
        assertNotNull(holder.getChart().getChart());
    }
    
    /**
     * Creating chart test
     */
    public void testCreateChart() {
        try {
            doCreateChart();
            AbstractChart chart = JFreeChartHolder.getHolder(handle).getChart(); 
            assertFalse(chart.isTableSupported());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Tests series
     */
    public void testSeries() {
        try {
            doCreateChart();
            AbstractChart chart = JFreeChartHolder.getHolder(handle).getChart();
            PolarPlot plot = (PolarPlot) chart.getChart().getPlot();
            
            int series = 2;
            chart.setSeriesCount(series);
            assertEquals(series, plot.getDataset().getSeriesCount());
            
            chart.setSeriesCount(--series);
            assertEquals(series, plot.getDataset().getSeriesCount());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Tests data
     */
    public void testData() {
        try {
            doCreateChart();
            AbstractChart chart = JFreeChartHolder.getHolder(handle).getChart();
            
            // ydata
            Document doc = ChartServer.makeXMLMessage("SetDoubleArray", handle);
            ChartServer.addXMLData(doc, "property", 2140, "i", 0, "j", 0);
            Element ydata = doc.createElement("value");
            doc.getDocumentElement().appendChild(ydata);
            double yvalues[] = new double[] {10, 20, -30, -40, 15, 24};
            for (double f : yvalues) {
                ChartServer.addXMLElementData(doc, ydata, "item", f);
            }

            chart.setItemCount(yvalues.length - 1);
            assertEquals(chart.getItemCount(), yvalues.length - 1);

            ChartServer.processXML(doc);

            PolarPlot plot = (PolarPlot) chart.getChart().getPlot();
            XYDataset dataset = plot.getDataset();
            assertEquals(dataset.getSeriesCount(), 1);
            assertEquals(chart.getItemCount(), yvalues.length - 1);

            assertEquals(yvalues.length + 1, dataset.getItemCount(0));
            assertEquals(yvalues[0], dataset.getYValue(0, 0));
            assertEquals(yvalues[1], dataset.getYValue(0, 1));
            assertEquals(0.0, dataset.getYValue(0, 2));
            assertEquals(-yvalues[2], dataset.getYValue(0, 3));
            assertEquals(-yvalues[3], dataset.getYValue(0, 4));
            assertEquals(0.0, dataset.getYValue(0, 5));
            assertEquals(yvalues[4], dataset.getYValue(0, 6));
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Tests paints
     */
    public void testPaints() {
        try {
            doCreateChart();
            AbstractChart chart = JFreeChartHolder.getHolder(handle).getChart();
            PolarPlot plot = (PolarPlot) chart.getChart().getPlot();
            
            // series color
            int series = 2;
            chart.setSeriesCount(series);
            assertEquals(series, plot.getDataset().getSeriesCount());
            
            Color color = new Color(0, 0xFF, 0x7F);
            chart.setSeriesColor(1, color);
            chart.updateChart();
            DefaultPolarItemRenderer renderer = (DefaultPolarItemRenderer) plot.getRenderer();
            assertEquals(color, renderer.getSeriesPaint(1));
            
            // axis color
            color = new Color(0x77, 0x23, 0x1F);
            chart.setAxisColor(color);
            assertEquals(color, plot.getAngleGridlinePaint());
            assertEquals(color, plot.getAngleLabelPaint());
            assertEquals(color, plot.getRadiusGridlinePaint());
            assertEquals(color, plot.getAxis().getAxisLinePaint());
            assertEquals(color, plot.getAxis().getLabelPaint());
            assertEquals(color, plot.getAxis().getTickLabelPaint());
            
            // background paint
            assertNull(chart.getBackgroundPaint(Color.BLACK, Color.WHITE, new ChartRenderingInfo()));
            
            ChartRenderingInfo info = new ChartRenderingInfo();
            info.getPlotInfo().setPlotArea(new Rectangle2D.Double(10, 10, 100, 100));
            Paint paint = chart.getBackgroundPaint(Color.BLACK, Color.WHITE, info);
            assertTrue(paint instanceof RadialGradientPaint);
            RadialGradientPaint radialPaint = (RadialGradientPaint) paint;
            assertEquals(Color.BLACK, radialPaint.getColors()[0]);
            assertEquals(Color.WHITE, radialPaint.getColors()[1]);
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests grid lines
     */
    private void doTestGridLines(boolean showX, boolean showY) {
        AbstractChart chart = JFreeChartHolder.getHolder(handle).getChart();
        PolarPlot plot = (PolarPlot) chart.getChart().getPlot();

        chart.showGridLines(showX, showY);
        assertEquals(showX, plot.isAngleGridlinesVisible());
        assertEquals(showY, plot.isRadiusGridlinesVisible());
    }
    /**
     * Tests lines
     */
    public void testLines() {
        try {
            doCreateChart();
            AbstractChart chart = JFreeChartHolder.getHolder(handle).getChart();
            PolarPlot plot = (PolarPlot) chart.getChart().getPlot();
            
            int series = 2;
            chart.setSeriesCount(series);
            assertEquals(series, plot.getDataset().getSeriesCount());
            
            // series line type
            chart.setSeriesLineType(0, ChartLineTypes.LINE_THINSOLID);
            DefaultPolarItemRenderer renderer = (DefaultPolarItemRenderer) plot.getRenderer();
            assertEquals(ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THINSOLID), renderer.getSeriesStroke(0));
            
            // grid lines
            doTestGridLines(true, true);
            doTestGridLines(true, false);
            doTestGridLines(false, true);
            doTestGridLines(false, false);
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
}
