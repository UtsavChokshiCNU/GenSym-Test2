package gensym.charts.tests;

import java.awt.*;
import java.awt.event.MouseEvent;

import javax.swing.JPanel;

import gensym.charts.*;
import gensym.charts.actions.CreateChartAction;
import gensym.charts.dialogs.*;
import gensym.charts.scrolling.ChartScrolling;
import gensym.charts.hatching.HatchedPaint;
import gensym.charts.properties.hatching.SliceHetchingProperty;
import gensym.charts.properties.hatching.SubsetHatchProperty;

import org.jfree.chart.ChartMouseEvent;
import org.jfree.chart.editor.ChartEditor;
import org.jfree.chart.entity.ChartEntity;
import org.jfree.chart.entity.PieSectionEntity;
import org.jfree.chart.plot.PiePlot;
import org.jfree.data.general.DefaultPieDataset;
import org.jfree.data.general.PieDataset;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import junit.framework.TestCase;

/**
 * <p>
 * Test cases for Pie chart functionality.
 * </p>
 */
public class PieChartTest extends TestCase {
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
        JFreeChartHolder.getHolder(handle).getChart().updateChart();
    }
    
    /**
     * Creates chart
     */
    void doCreateChart() throws Exception {
        runAction("CreateChart", "title", "Pie chart", "type", CreateChartAction.PE_PIE_CHART,
                "x", -1, "y", -1, "width", 500, "height", 400);

        JFreeChartHolder holder = JFreeChartHolder.getHolder(handle); 
        assertNotNull(holder);
        assertTrue(holder.getChart() instanceof PieChart);
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
            assertTrue(chart instanceof PieChart);
            PieChart pie = (PieChart) chart;
            
            PiePlot piePlot = (PiePlot) chart.getChart().getPlot();

            int series = 2;
            chart.setSeriesCount(series);
            assertEquals(series, pie.getDataset().getColumnCount());
            
            chart.setSeriesCount(--series);
            assertEquals(series, pie.getDataset().getColumnCount());
            
            int items = 10;
            chart.setItemCount(items);
            assertEquals(items, pie.getDataset().getRowCount());
            
            chart.setSeriesColor(0, Color.RED);
            chart.updateChart();
            assertEquals(Color.RED, piePlot.getSectionPaint(pie.getDataset().getRowKey(0)));
            
            String label = "series1";
            chart.setSeriesLabel(0, label);
            assertEquals(label, pie.getDataset().getColumnKey(0));
            
            label = "point";
            chart.setPointLabel(3, label);
            assertEquals(label, pie.getDataset().getRowKey(3));
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
            assertTrue(chart instanceof PieChart);
            PieChart pie = (PieChart) chart;
            
            chart.setSeriesCount(1);
            // xdata
            Document doc = ChartServer.makeXMLMessage("SetDoubleArray", handle);
            ChartServer.addXMLData(doc, "property", 2135, "i", 0, "j", 0);
            Element xdata = doc.createElement("value");
            doc.getDocumentElement().appendChild(xdata);
            double xvalues[] = new double[] {10, 20, 30, 40, 15, 24};
            for (double f : xvalues) {
                ChartServer.addXMLElementData(doc, xdata, "item", f);
            }

            chart.setItemCount(xvalues.length - 1);
            assertEquals(chart.getItemCount(), xvalues.length - 1);

            ChartServer.processXML(doc);
            
            assertEquals(1, pie.getDataset().getColumnCount());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
	
    /**
     * Tests showing labels with zero data in legends
     */
    public void testShowPieZeroData() {
        try {
            doCreateChart();
            PieChart chart = (PieChart) JFreeChartHolder.getHolder(handle).getChart();
            
            chart.showPieZeroData(true);
            assertTrue(chart.isShowPieZeroData());
            chart.showPieZeroData(false);
            assertFalse(chart.isShowPieZeroData());
            
            runAction("SetInt", "property", 10002, "i", 0, "j", 0, "value", 1);
            assertTrue(chart.isShowPieZeroData());
            runAction("SetInt", "property", 10002, "i", 0, "j", 0, "value", 0);
            assertFalse(chart.isShowPieZeroData());

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests enabling toolTips
     */
    public void testToolTips() {
        try {
            doCreateChart();
            PieChart chart = (PieChart) JFreeChartHolder.getHolder(handle).getChart();

            chart.setTooltipsEnabled(true);
            assertTrue(chart.isTooltipsEnabled());
            chart.setTooltipsEnabled(false);
            assertFalse(chart.isTooltipsEnabled());

            runAction("SetInt", "property", 10000, "i", 0, "j", 0, "value", 1);
            assertTrue(chart.isTooltipsEnabled());
            runAction("SetInt", "property", 10000, "i", 0, "j", 0, "value", 0);
            assertFalse(chart.isTooltipsEnabled());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests showing labels inside/outside of charts
     */
    public void testShowLabelsInside() {
        try {
            doCreateChart();
            PieChart chart = (PieChart) JFreeChartHolder.getHolder(handle).getChart();
            
            chart.setShowLabelsInsideOfChart(true);
            assertTrue(chart.isShowLabelsInsideOfChart());
            chart.setShowLabelsInsideOfChart(false);
            assertFalse(chart.isShowLabelsInsideOfChart());
            
            runAction("SetInt", "property", 10001, "i", 0, "j", 0, "value", 1);
            assertTrue(chart.isShowLabelsInsideOfChart());
            runAction("SetInt", "property", 10001, "i", 0, "j", 0, "value", 0);
            assertFalse(chart.isShowLabelsInsideOfChart());

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Creating property editor test
     */
    public void testCreatePropertyEditor() {
        try {
            doCreateChart();
            PieChart chart = (PieChart) JFreeChartHolder.getHolder(handle).getChart();

            chart.setShowLabelsInsideOfChart(true);
            assertTrue(chart.isShowLabelsInsideOfChart());

            ChartEditor PropEd = chart.makeChartEditor();
            assertNotNull(PropEd);

            chart.setShowLabelsInsideOfChart(false);
            assertFalse(chart.isShowLabelsInsideOfChart());

            PropEd.updateChart(chart.getChart());
            assertTrue(chart.isShowLabelsInsideOfChart());
            
            PropEd.updateChart(null);
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Creating property editor dialog test
     */
    public void testCreatePropertyEditorDialog() {
        try {
            doCreateChart();
            PieChart chart = (PieChart) JFreeChartHolder.getHolder(handle).getChart();

            chart.setShowLabelsInsideOfChart(true);
            assertTrue(chart.isShowLabelsInsideOfChart());

            ChartEditor PropEdDlg = new ChartPropertiesDialog(chart);
            assertNotNull(PropEdDlg);

            chart.setShowLabelsInsideOfChart(false);
            assertFalse(chart.isShowLabelsInsideOfChart());

            PropEdDlg.updateChart(chart.getChart());
            assertTrue(chart.isShowLabelsInsideOfChart());

            PropEdDlg.updateChart(null);
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests scrolling
     */
    public void testScrolling() {
        try {
            doCreateChart();
            PieChart chart = (PieChart) JFreeChartHolder.getHolder(handle).getChart();
            
            chart.setSeriesCount(1);
            
            ChartScrolling scroll = chart.getVerticalScrollingInterface();
            assertNotNull(scroll);
            assertFalse(scroll.isScrollingSupported());
            assertEquals(1, scroll.getScrollItemsCount());
            
            chart.setSeriesCount(2);
            assertTrue(scroll.isScrollingSupported());
            assertEquals(2, scroll.getScrollItemsCount());
            
            scroll.updateScrollingPos(0);
            assertEquals(0, scroll.getScrollItemPos());
            scroll.updateScrollingPos(1);
            assertEquals(1, scroll.getScrollItemPos());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Hatches functions test
     */
    public void testHatchesFunctions() {
        try {
            doCreateChart();
            PieChart chart = (PieChart)JFreeChartHolder.getHolder(handle).getChart();
            PiePlot piePlot = (PiePlot) chart.getChart().getPlot();
            chart.setSeriesCount(1);
            chart.setItemCount(1);
            
            // test setSliceHatching(bool)
            chart.setSliceHatching(true);
            assertEquals(true, chart.isSliceHatching());
            chart.setSliceHatching(false);
            assertEquals(false, chart.isSliceHatching());

            runAction("SetInt", "property", 3923, "i", 0, "j", 0, "value", SliceHetchingProperty.PESH_MONOCHROME);
            HatchedPaint hp = (HatchedPaint) piePlot.getSectionPaint(chart.getDataset().getRowKey(0));
            assertEquals(false, chart.isSliceHatching());
            
            chart.setSeriesColor(0, Color.RED);
            chart.updateChart();
            assertEquals(Color.RED, piePlot.getSectionPaint(chart.getDataset().getRowKey(0)));

            chart.setSliceHatching(true);
            //test setSeriesHatch
            int styleMask = SubsetHatchProperty.getHatchStyleMaskFromPEHS(SubsetHatchProperty.PEHS_CROSS);
            chart.setSeriesHatch(0, styleMask);
            chart.updateChart();
            Paint p = piePlot.getSectionPaint(chart.getDataset().getRowKey(0));
            assertTrue(p instanceof HatchedPaint);
            hp = (HatchedPaint)p;
            assertEquals(styleMask, hp.getHatchStyleMask());

            runAction("SetInt", "property", 2940, "i", 0, "j", 0, "value", SubsetHatchProperty.PEHS_VERTICAL);
            hp = (HatchedPaint)piePlot.getSectionPaint(chart.getDataset().getRowKey(0));
            assertEquals(HatchedPaint.VERTICAL_LINE, hp.getHatchStyleMask());

            //test setSeriesColor()
            chart.setSeriesColor(0, Color.RED);
            chart.updateChart();
            hp = (HatchedPaint)piePlot.getSectionPaint(chart.getDataset().getRowKey(0));
            assertEquals(Color.RED, hp.getForegroundColor());

            runAction("SetInt", "property", 2190, "i", 0, "j", 0, "value", Color.RED.getRGB());
            hp = (HatchedPaint)piePlot.getSectionPaint(chart.getDataset().getRowKey(0));
            assertEquals(Color.BLUE, hp.getForegroundColor()); //RED == G2.BLUE
            
            // test setHatchBackColor(int)
            chart.setHatchBackColor(Color.BLUE);
            chart.updateChart();
            hp = (HatchedPaint)piePlot.getSectionPaint(chart.getDataset().getRowKey(0));
            assertEquals(Color.BLUE, hp.getBackgroundColor());

            runAction("SetInt", "property", 2941, "i", 0, "j", 0, "value", Color.RED.getRGB());
            hp = (HatchedPaint)piePlot.getSectionPaint(chart.getDataset().getRowKey(0));
            assertEquals(Color.BLUE, hp.getBackgroundColor()); //RED == G2.BLUE
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Hatch style conversions test
     */
    public void testHatchStyleConversions() {
        assertEquals(HatchedPaint.HORIZONTAL_LINE, 
                SubsetHatchProperty.getHatchStyleMaskFromPEHS(SubsetHatchProperty.PEHS_HORIZONTAL));
        assertEquals(HatchedPaint.VERTICAL_LINE, 
                SubsetHatchProperty.getHatchStyleMaskFromPEHS(SubsetHatchProperty.PEHS_VERTICAL));
        assertEquals(HatchedPaint.LB_RU_DIAGONAL_LINE, 
                SubsetHatchProperty.getHatchStyleMaskFromPEHS(SubsetHatchProperty.PEHS_BDIAGONAL));
        assertEquals(HatchedPaint.LU_RB_DIAGONAL_LINE, 
                SubsetHatchProperty.getHatchStyleMaskFromPEHS(SubsetHatchProperty.PEHS_FDIAGONAL));
        assertEquals(HatchedPaint.HORIZONTAL_LINE | HatchedPaint.VERTICAL_LINE, 
                SubsetHatchProperty.getHatchStyleMaskFromPEHS(SubsetHatchProperty.PEHS_CROSS));
        assertEquals(HatchedPaint.LU_RB_DIAGONAL_LINE | HatchedPaint.LB_RU_DIAGONAL_LINE, 
                SubsetHatchProperty.getHatchStyleMaskFromPEHS(SubsetHatchProperty.PEHS_DIAGCROSS));
        assertEquals(HatchedPaint.LINE_NONE, SubsetHatchProperty.getHatchStyleMaskFromPEHS(-100));
        assertEquals(HatchedPaint.LINE_NONE, SubsetHatchProperty.getHatchStyleMaskFromPEHS(100));
    }

    /**
     * Exploding pie sections test
     */
    public void testExplodeSections() {
        try {
            doCreateChart();
            JFreeChartHolder holder = JFreeChartHolder.getHolder(handle);
            PieChart chart = (PieChart)holder.getChart();
            PiePlot piePlot = (PiePlot) chart.getChart().getPlot();

            PieDataset dataset = new DefaultPieDataset();
            JPanel jp = new JPanel();
            int button = MouseEvent.BUTTON1;
            Shape sh = new Rectangle(10, 10, 10, 10);
            int clickCount = 2;
            int pieIndex = 0, sectionIndex = 0;

            chart.setSeriesCount(1);
            chart.setItemCount(2);
            String key = "row 1";
            int EventMask = 0xffff;

            runAction("SetInt", "property", 3920, "i", 0, "j", 0, "value", PieChart.AUTO_EXPLODE_NONE);

            MouseEvent me = new MouseEvent(jp, MouseEvent.MOUSE_CLICKED, 0, EventMask, 10, 10, clickCount, false, button);
            PieSectionEntity pse = new PieSectionEntity(sh, dataset, pieIndex, sectionIndex, clickCount, null, null);
            ChartMouseEvent cme = new ChartMouseEvent(chart.getChart(), me, pse);

            chart.chartMouseClicked(holder, cme);
            assertEquals(0.0, piePlot.getExplodePercent(key));

            runAction("SetInt", "property", 3920, "i", 0, "j", 0, "value", PieChart.AUTO_EXPLODE_INDSUBSETS);
            chart.chartMouseClicked(holder, cme);
            assertEquals(0.30, piePlot.getExplodePercent(key));
            chart.chartMouseClicked(holder, cme);
            assertEquals(0.0, piePlot.getExplodePercent(key));

            pieIndex = 1;
            pse = new PieSectionEntity(sh, dataset, pieIndex, sectionIndex, clickCount, null, null);
            cme = new ChartMouseEvent(chart.getChart(), me, pse);
            chart.chartMouseClicked(holder, cme);
            assertEquals(0.0, piePlot.getExplodePercent(key));

            runAction("SetInt", "property", 3920, "i", 0, "j", 0, "value", PieChart.AUTO_EXPLODE_ALLSUBSETS);
            chart.chartMouseClicked(holder, cme);
            assertEquals(0.30, piePlot.getExplodePercent(key));
            chart.chartMouseClicked(holder, cme);
            assertEquals(0.0, piePlot.getExplodePercent(key));
            
            ChartEntity ce = new ChartEntity(sh, null, null);
            cme = new ChartMouseEvent(chart.getChart(), me, ce);
            chart.chartMouseClicked(holder, cme);
            assertEquals(0.0, piePlot.getExplodePercent(key));

            pse = new PieSectionEntity(sh, dataset, pieIndex, sectionIndex, clickCount, null, null);
            
            button = MouseEvent.BUTTON2;
            me = new MouseEvent(jp, MouseEvent.MOUSE_CLICKED, 0, EventMask, 10, 10, clickCount, false, button);
            cme = new ChartMouseEvent(chart.getChart(), me, pse);
            chart.chartMouseClicked(holder, cme);
            assertEquals(0.0, piePlot.getExplodePercent(key));
            
            clickCount = 1;
            button = MouseEvent.BUTTON1;
            me = new MouseEvent(jp, MouseEvent.MOUSE_CLICKED, 0, EventMask, 10, 10, clickCount, false, button);
            cme = new ChartMouseEvent(chart.getChart(), me, pse);
            chart.chartMouseClicked(holder, cme);
            assertEquals(0.0, piePlot.getExplodePercent(key));

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
}
