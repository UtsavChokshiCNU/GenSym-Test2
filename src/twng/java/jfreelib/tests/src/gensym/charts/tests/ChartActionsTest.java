package gensym.charts.tests;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.*;
import org.jfree.chart.title.*;
import org.jfree.data.xy.XYSeriesCollection;
import org.jfree.ui.*;

import java.util.List;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.awt.print.Printable;
 
import gensym.charts.properties.plotting.PlottingMethodProperty; 
import gensym.charts.GraphBubbleRenderer;
import gensym.charts.ChartLineTypes;
import gensym.charts.ChartServer;
import gensym.charts.ChartStyle;
import gensym.charts.ChartsCommon;
import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.ScientificChart;
import gensym.charts.actions.CreateChartAction;
import gensym.charts.actions.*;
import gensym.charts.axis.XYAxesPlot;
import gensym.charts.properties.DataShadowProperty;
import gensym.charts.properties.FontSizeProperty;
import gensym.charts.properties.GraphPlusTableProperty;
import gensym.charts.properties.GridLineControlProperty;
import gensym.charts.properties.GridStyleProperty;
import gensym.charts.properties.ShowPieLablesProperty;
import gensym.charts.properties.TableWhatProperty;
import gensym.charts.properties.bubble.BubbleSizeProperty;
import gensym.charts.properties.factory.PropValueFactory;
import gensym.charts.properties.legends.LegendLocationProperty;
import gensym.charts.properties.plotting.GraphRendererFactory;
import gensym.charts.subtitles.SimpleSubtitle;
import gensym.charts.tables.ColoredTable;

import java.awt.Color;
import java.awt.Stroke;
import java.awt.datatransfer.Clipboard;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.io.File;
import java.util.ArrayList;
import java.util.List;

import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.LogarithmicAxis;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.ClusteredXYBarRenderer;
import org.jfree.chart.renderer.xy.StackedXYBarRenderer;
import org.jfree.chart.renderer.xy.XYLine3DRenderer;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;
import org.jfree.chart.renderer.xy.XYSplineRenderer;
import org.jfree.chart.renderer.xy.XYStepAreaRenderer;
import org.jfree.chart.title.LegendTitle;
import org.jfree.chart.title.TextTitle;
import org.jfree.chart.title.Title;
import org.jfree.data.xy.XYSeriesCollection;
import org.jfree.ui.RectangleEdge;
import org.jfree.ui.RectangleInsets;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

/**
 * <p>
 * Test cases for Chart actions functionality.
 * </p>
 *
 */
public class ChartActionsTest extends TestChartBase {
    /**
     * Test for {@code PropValueFactory} class.
     */
    public final void testPropValueFactory() {
        assertNotNull(new PropValueFactory());
        List<String> names = PropValueFactory.getProperties();
        assertFalse(names.isEmpty());
    }

    /**
     * Test for {@code TestChartAction} class.
     */
    public final void testTestAction() {
        try {
            runAction("Test");
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests "Destroy" chart action
     */
    public final void testDestroyAction() {
        try {
            int subsets = 2;
            int points = 2;
            doCreateAction(false, true);
            runAction("SetInt", "property", 2115, "i", 0, "j", 0, "value", subsets);
            runAction("SetInt", "property", 2120, "i", 0, "j", 0, "value", points);

            assertNotNull(getChart());
            runAction("Destroy");
            assertNull(getChart());

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests "Copy" chart action
     */
    public final void testCopyAction() {
        try {
            int subsets = 2;
            int points = 2;
            doCreateAction(false, true);
            runAction("SetInt", "property", 2115, "i", 0, "j", 0, "value", subsets);
            runAction("SetInt", "property", 2120, "i", 0, "j", 0, "value", points);

            assertNotNull(getChart());
            runAction("Copy");
            final Clipboard clipboard = getHolder().getToolkit().getSystemClipboard();
            assertNotNull(clipboard.getContents(null));

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests "Export" chart action
     */
    public final void testExportAction() {
        try {
            int subsets = 2;
            int points = 2;
            doCreateAction(false, true);
            runAction("SetInt", "property", 2115, "i", 0, "j", 0, "value", subsets);
            runAction("SetInt", "property", 2120, "i", 0, "j", 0, "value", points);
            runAction("Export", "width", -1, "height", -1, "format", -1, "pathname", "");
            runAction("Export", "width", -1, "height", -1, "format", -1, "pathname", "C:\\\\\\//");
            assertNotNull(getChart());

            checkOneFileExport(-1, -1, 1, "C:\\weghuofowe324", "C:\\weghuofowe324.jpeg");
            checkOneFileExport(-1, -1, 2, "C:\\weghuofowe324", "C:\\weghuofowe324.png");
            checkOneFileExport(-1, -1, 3, "C:\\weghuofowe324", "C:\\weghuofowe324.bmp");
            checkOneFileExport(-1, -1, 4, "C:\\weghuofowe324", "C:\\weghuofowe324.wmf");
            checkOneFileExport(-1, -1, 5, "C:\\weghuofowe324", "C:\\weghuofowe324.svg");
            checkOneFileExport(-1, -1, -1, "C:\\weghuofowe324", "C:\\weghuofowe324.jpeg");
            checkOneFileExport(640, 480, 2, "C:\\weghuofowe324.bmp", "C:\\weghuofowe324.bmp");

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests creating one single file during image exporting process
     * @param w image width
     * @param h image height
     * @param format height format
     * @param path passed file name
     * @param checkPath file name to check
     */
    private final void checkOneFileExport(int w, int h, int format, String path, String checkPath) {
        try {
            runAction("Export", "width", w, "height", h, "format", format, "pathname", path);
            File f = new File(checkPath);
            assertTrue(f.exists());
            assertTrue(f.delete());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Test for {@code TestChartAction} class.
     */
    public final void testXYData() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        assertTrue(getChart() instanceof GraphChart);
        GraphChart graph = (GraphChart) getChart();

        try {
            int subsets = 2;
            int points = 2;
            runAction("SetInt", "property", 2115, "i", 0, "j", 0, "value", 2);
            runAction("SetInt", "property", 2120, "i", 0, "j", 0, "value", points);

            // xdata
            Document xdoc = ChartServer.makeXMLMessage("SetDoubleArray", getHandle());
            ChartServer.addXMLData(xdoc, "property", 2135, "i", 0, "j", 0);
            Element xdata = xdoc.createElement("value");
            xdoc.getDocumentElement().appendChild(xdata);
            double xvalues[] = new double[]{1, 2, 3, 4, 5};
            for (double f : xvalues) {
                ChartServer.addXMLElementData(xdoc, xdata, "item", f);
            }

            runAction(xdoc);

            assertNotNull(graph.getDataset());
            assertEquals(graph.getDataset().getSeriesCount(), subsets);
            assertTrue(graph.getDataset() instanceof XYSeriesCollection);
            XYSeriesCollection dataset = (XYSeriesCollection) graph.getDataset();
            assertEquals(graph.getItemCount(), points);

            assertEquals(dataset.getSeries(0).getX(0), xvalues[0]);
            assertEquals(dataset.getSeries(0).getX(1), xvalues[1]);
            assertEquals(dataset.getSeries(1).getX(0), xvalues[2]);
            assertEquals(dataset.getSeries(1).getX(1), xvalues[3]);

            // simple x data
            double simpleX = 0;
            runAction("SetDouble", "property", 2135, "i", 1, "j", 0, "value", simpleX);
            assertEquals(simpleX, dataset.getSeries(1).getX(0));

            // ydata
            Document ydoc = ChartServer.makeXMLMessage("SetDoubleArray", getHandle());
            ChartServer.addXMLData(ydoc, "property", 2140, "i", 0, "j", 0);
            Element ydata = ydoc.createElement("value");
            ydoc.getDocumentElement().appendChild(ydata);
            double yvalues[] = new double[]{1, 2, 3, 4, 5};
            for (double f : yvalues) {
                ChartServer.addXMLElementData(ydoc, ydata, "item", f);
            }

            runAction(ydoc);

            // zdata
            Document zdoc = ChartServer.makeXMLMessage("SetDoubleArray", getHandle());
            ChartServer.addXMLData(zdoc, "property", 2900, "i", 0, "j", 0);
            Element zdata = zdoc.createElement("value");
            zdoc.getDocumentElement().appendChild(zdata);
            double zvalues[] = new double[]{1, 2, 345, 4, 5};
            for (double f : zvalues) {
                ChartServer.addXMLElementData(zdoc, zdata, "item", f);
            }

            runAction(zdoc);

            // allow-bubble
            assertFalse(graph.isBubbleAllowed());
            runAction("SetInt", "property", 3640, "i", 0, "j", 0, "value", 1);
            assertTrue(graph.isBubbleAllowed());
            
            testPlottingMethod(graph.getChart(), GraphRendererFactory.PEGPM_BUBBLE, GraphBubbleRenderer.class);
            runAction("Update");
            Thread.sleep(100);

            // bubble-size
            testBubbleSize(graph, BubbleSizeProperty.SMALL, GraphBubbleRenderer.DIV_SMALL);
            testBubbleSize(graph, BubbleSizeProperty.MEDIUM, GraphBubbleRenderer.DIV_MEDIUM);
            testBubbleSize(graph, BubbleSizeProperty.LARGE, GraphBubbleRenderer.DIV_LARGE);
            testBubbleSize(graph, 435, GraphBubbleRenderer.DIV_MEDIUM);
            testBubbleSize(graph, -3435, GraphBubbleRenderer.DIV_MEDIUM);

            assertEquals(graph.getDataset().getSeriesCount(), subsets);
            assertTrue(graph.getDataset() instanceof XYSeriesCollection);
            dataset = (XYSeriesCollection) graph.getDataset();
            assertEquals(graph.getItemCount(), points);

            assertEquals(dataset.getSeries(0).getY(0), yvalues[0]);
            assertEquals(dataset.getSeries(0).getY(1), yvalues[1]);
            assertEquals(dataset.getSeries(1).getY(0), yvalues[2]);
            assertEquals(dataset.getSeries(1).getY(1), yvalues[3]);

            // simple y data
            double simpleY = 120;
            runAction("SetDouble", "property", 2140, "i", 1, "j", 0, "value", simpleY);
            assertEquals(simpleY, dataset.getSeries(1).getY(0));

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Test bubble szie
     * @param graphChart GraphChart to test
     * @param sizeToPass new bubbles size
     * @param sizeToTest expected size
     */
    private final void testBubbleSize(GraphChart graphChart, int sizeToPass, int sizeToTest) {
        try {
            runAction("SetInt", "property", 3641, "i", 0, "j", 0, "value", sizeToPass);
            assertTrue(graphChart.getPlot().getRenderer() instanceof GraphBubbleRenderer);
            GraphBubbleRenderer bubbleRenderer = 
                    (GraphBubbleRenderer) graphChart.getPlot().getRenderer();
            assertEquals(bubbleRenderer.getBubbleSize(), sizeToTest);
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Test for {@code SetIntValueAction} class.
     */
    public final void testSetIntValueAction() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        assertTrue(getChart() instanceof GraphChart);
        GraphChart graph = (GraphChart) getChart();

        try {
            assertNotNull(new SetValueActions());

            // subsets
            int subsets = 2;
            runAction("SetInt", "property", 2115, "i", 0, "j", 0, "value", subsets);
            assertEquals(graph.getDataset().getSeriesCount(), subsets);

            subsets = 0;
            runAction("SetInt", "property", 2115, "i", 0, "j", 0, "value", subsets);
            assertEquals(graph.getDataset().getSeriesCount(), subsets);

            // points
            int points = 15;
            runAction("SetInt", "property", 2120, "i", 0, "j", 0, "value", points);
            assertTrue(graph.getDataset() instanceof XYSeriesCollection);

            assertEquals(graph.getItemCount(), points);

            // plotting-method
            testPlottingMethod(graph.getChart(), GraphRendererFactory.PEGPM_LINE, XYLineAndShapeRenderer.class);
            testPlottingMethod(graph.getChart(), GraphRendererFactory.PEGPM_BAR, ClusteredXYBarRenderer.class);
            testPlottingMethod(graph.getChart(), GraphRendererFactory.PEGPM_POINT, XYLineAndShapeRenderer.class);
            // in future need to correct
            testPlottingMethod(graph.getChart(), GraphRendererFactory.PEGPM_AREA, XYLineAndShapeRenderer.class);

            testPlottingMethod(graph.getChart(), GraphRendererFactory.PEGPM_BARSTACKED, XYLineAndShapeRenderer.class);
            runAction("SetInt", "property", 3305, "i", 0, "j", 0, "value", 0); //no-stacked
            testPlottingMethod(graph.getChart(), GraphRendererFactory.PEGPM_BARSTACKED, StackedXYBarRenderer.class);
            testPlottingMethod(graph.getChart(), GraphRendererFactory.PEGPM_POINTSPLUSSPLINE, XYSplineRenderer.class);

            // allow-ribbon
            runAction("SetInt", "property", 3091, "i", 0, "j", 0, "value", 1);
            testPlottingMethod(graph.getChart(), GraphRendererFactory.PEGPM_RIBBON, XYLine3DRenderer.class);

            // allow-step
            runAction("SetInt", "property", 3067, "i", 0, "j", 0, "value", 1);
            testPlottingMethod(graph.getChart(), GraphRendererFactory.PEGPM_STEP, XYStepAreaRenderer.class);

            runAction("SetInt", "property", 3090, "i", 0, "j", 0, "value", 1);
            assertEquals(graph.getChart().getXYPlot().getRenderer().getClass(), ClusteredXYBarRenderer.class);

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Test for {@code CreateChartAction} class.
     */
    public final void testCreateAction() {
        doCreateAction(false, true);
        getHolder().dispose();
        doCreateAction(true, true);
    }

    /**
     * Test for disposing chart.
     */
    public final void testDisposing() {
        doCreateAction(false, true);
        JFreeChartHolder holder = getHolder();
        WindowEvent we = new WindowEvent(holder, WindowEvent.WINDOW_CLOSING);
        for (WindowListener l : holder.getWindowListeners()) {
            l.windowClosing(we);
        }
    }

    /**
     * Test for wrong action data.
     */
    public final void testWrongActionData() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);

        assertNull(PropValueFactory.makeValue(100, "WrongActionName")); 

        try {
            runAction("SetInt", "property", 3355, "i", 0);
            fail("Exception should be thrown");
        } catch (Exception e) {
            assertEquals(e.getClass(), IChartAction.ChartActionException.class);
        }
        try {
            runAction("SetInt", "property", 100, "i", 0, "j", 0, "value", 1);
            fail("Exception should be thrown");
        } catch (Exception e) {
            assertEquals(e.getClass(), IChartAction.ChartActionException.class);
        }

        getHolder().dispose();
        try {
            runAction("SetInt", "property", 3355, "i", 0, "j", 0, "value", 1);
            fail("Exception should be thrown");
        } catch (Exception e) {
            assertEquals(e.getClass(), IChartAction.ChartActionException.class);
        }

        try {
            runAction("Wrong", "property", 3355, "i", 0, "j", 0, "value", 1);
            fail("Exception should be thrown");
        } catch (Exception e) {
            assertEquals(e.getClass(), IChartAction.ChartActionException.class);
        }
    }

    /**
     * Tests allowing properties
     */
    public void testAllowingProperties() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        GraphChart graph = (GraphChart) getChart();
        try {
            // allow-horz-bar-stacked
            runAction("SetInt", "property", 3419, "i", 0, "j", 0, "value", 0);
            assertFalse(graph.isHorzBarStackedAllowed());
            runAction("SetInt", "property", 3419, "i", 0, "j", 0, "value", 1);
            assertTrue(graph.isHorzBarStackedAllowed());

            // allow-ribbon
            runAction("SetInt", "property", 3091, "i", 0, "j", 0, "value", 0);
            assertFalse(graph.isRibbonAllowed());
            runAction("SetInt", "property", 3091, "i", 0, "j", 0, "value", 1);
            assertTrue(graph.isRibbonAllowed());

            // allow-step
            runAction("SetInt", "property", 3067, "i", 0, "j", 0, "value", 0);
            assertFalse(graph.isStepAllowed());
            runAction("SetInt", "property", 3067, "i", 0, "j", 0, "value", 1);
            assertTrue(graph.isStepAllowed());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests view properties 
     */
    public void testViewProperties() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        JFreeChartHolder holder = getHolder();

        try {
            //allow-zooming
            runAction("SetInt", "property", 3282, "i", 0, "j", 0, "value", 0);
            assertFalse(holder.isZoomable());
            runAction("SetInt", "property", 3282, "i", 0, "j", 0, "value", 1);
            assertTrue(holder.isZoomable());

            // graph-plus-table
            runAction("SetInt", "property", 3355, "i", 0, "j", 0, "value", GraphPlusTableProperty.PEGPT_BOTH);
            assertTrue(holder.isChartVisible());
            assertTrue(holder.isTableVisible());
            runAction("SetInt", "property", 3355, "i", 0, "j", 0, "value", GraphPlusTableProperty.PEGPT_TABLE);
            assertFalse(holder.isChartVisible());
            assertTrue(holder.isTableVisible());
            runAction("SetInt", "property", 3355, "i", 0, "j", 0, "value", GraphPlusTableProperty.PEGPT_GRAPH);
            assertTrue(holder.isChartVisible());
            assertFalse(holder.isTableVisible());

            //focal-rect
            runAction("SetInt", "property", 2632, "i", 0, "j", 0, "value", 0);
            for (JFreeChart jchart : holder.getChart().getCharts()) {
                assertFalse(jchart.isBorderVisible());
            }
            runAction("SetInt", "property", 2632, "i", 0, "j", 0, "value", 1);
            for (JFreeChart jchart : holder.getChart().getCharts()) {
                assertTrue(jchart.isBorderVisible());
            }
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests view properties 
     */
    public void testNullDataProperties() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        try {
            runAction("SetDouble", "property", 3656, "i", 0, "j", 0, "value", 0.5);
            runAction("SetDouble", "property", 3268, "i", 0, "j", 0, "value", 0.5);
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests line type
     * @param type
     * @throws Exception 
     */
    private void doTestLineType(int type) throws Exception {
        runAction("SetInt", "property", 3271, "i", 0, "j", 0, "value", type);
        runAction("Update");

        GraphChart graph = (GraphChart) getChart();
        assertNotNull(graph.getPlot().getCurrentPlot());
        assertNotNull(graph.getPlot().getCurrentPlot().getRenderer());
        Stroke stroke = graph.getPlot().getCurrentPlot().getRenderer().getSeriesStroke(0);
        assertEquals(ChartLineTypes.makeBasicStroke(type), stroke);
    }

    /**
     * Tests subsets properties 
     */
    public void testSubsetsProperties() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        GraphChart graph = (GraphChart) getChart();

        try {
            int subsets = 2;
            runAction("SetInt", "property", 2115, "i", 0, "j", 0, "value", subsets);

            // subset-labels
            String label = "subs1";
            runAction("SetString", "property", 2125, "i", 0, "j", 0, "value", label);
            
            runAction("Update");
            
            XYSeriesCollection dataset = graph.getDataset();
            assertEquals(label, dataset.getSeriesKey(0));

            // subset-line-types
            new ChartLineTypes();
            for (int type = ChartLineTypes.LINE_THINSOLID; type <= ChartLineTypes.LINE_EXTRATHICKDASHDOTDOT; type++) {
                doTestLineType(type);
            }

            // subset-colors
            int bgr = 0x123456;
            runAction("SetInt", "property", 2190, "i", 0, "j", 0, "value", bgr);
            graph.updateChart();
            
            Color color = (Color) graph.getPlot().getCurrentPlot().getRenderer().getSeriesPaint(0);
            assertNotNull(color);
            assertEquals(0x12, color.getBlue());
            assertEquals(0x34, color.getGreen());
            assertEquals(0x56, color.getRed());

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests title properties 
     */
    public void testTitleProperties() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        JFreeChart jchart = getJChart();


        try {
            // main-title
            String title = "main-title";
            runAction("SetString", "property", 2105, "i", 0, "j", 0, "value", title);
            assertEquals(title, jchart.getTitle().getText());

            // main-title-bold
            runAction("SetInt", "property", 2450, "i", 0, "j", 0, "value", 1);
            assertTrue(jchart.getTitle().getFont().isBold());
            runAction("SetInt", "property", 2450, "i", 0, "j", 0, "value", 0);
            assertFalse(jchart.getTitle().getFont().isBold());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests plotting methods
     * @param chart chart for testing
     * @param value renderer enum
     * @param renderer expected renderer
     */
    private void testPlottingMethod(JFreeChart chart, int value, Class<?> renderer) {
        try {
            runAction("SetInt", "property", 3090, "i", 0, "j", 0, "value", value);
            assertTrue(renderer.isInstance(chart.getXYPlot().getRenderer()));
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Returns chart subtitle
     * @param titleClass title class
     * @return chart subtitle
     */
    private Title getSubtitle(Class<?> titleClass) {
        JFreeChart jchart = getJChart();

        for (Object obj : jchart.getSubtitles()) {
            Title subTitle = (Title) obj;
            if (titleClass.isInstance(subTitle)) {
                return subTitle;
            }
        }

        return null;
    }

    /**
     * Gets multi subtitles
     * @return subtitles
     */
    private TextTitle[] getSubtitle() {
        assertNotNull(getChart());
        return getChart().getSubtitle();
    }

    /**
     * Tests mutli subtitles
     * @param values titles that passed to chart
     * @param titles updated titles
     */
    private void doTestsMultiTitles(String[] values, TextTitle[] titles) {
        assertEquals(values.length, titles.length);
        for (int i = 0; i < values.length && i < titles.length; i++) {
            assertEquals(values[i], titles[i].getText());
        }
    }

    /**
     * Tests multi subtitles bold prop
     * @param titles updated titles
     * @param isBold true if bold
     */
    private void doTestsMultiTitlesBold(TextTitle[] titles, boolean isBold) {
        assertTrue(titles.length > 0);
        for (int i = 0; i < titles.length; i++) {
            assertEquals(isBold, titles[i].getFont().isBold());
        }
    }

    /**
     * Tests multi subtitles font name
     * @param titles updated titles
     * @param fontName name of the font
     */
    private void doTestsMultiTitlesFont(TextTitle[] titles, String fontName) {
        assertTrue(titles.length > 0);
        for (int i = 0; i < titles.length; i++) {
            assertEquals(fontName, titles[i].getFont().getName());
        }
    }

    /**
     * Tests multi subtitles color
     * @param titles updated titles
     * @param color color
     */
    private void doTestsMultiTitlesColor(TextTitle[] titles, Color color) {
        assertTrue(titles.length > 0);
        for (int i = 0; i < titles.length; i++) {
            assertEquals(color, titles[i].getPaint());
        }
    }

    /**
     * Tests subtitle properties 
     */
    final public void testSubTitleProperties() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);

        try {
            // subtitle test
            String[] values = {"Hello1", "12345 5555555", "owerkofwerokfew"};
            String title = values[0] + "|" + values[1] + "|" + values[2];
            runAction("SetString", "property", 2110, "i", 0, "j", 0, "value", title);
            doTestsMultiTitles(values, getSubtitle());

            // subtitle test
            String[] values1 = {"", "12345 5555555", ""};
            title = values1[0] + "|" + values1[1] + "|" + values1[2];
            runAction("SetString", "property", 2110, "i", 0, "j", 0, "value", title);
            doTestsMultiTitles(values1, getSubtitle());

            // subtitle-bold
            runAction("SetInt", "property", 2490, "i", 0, "j", 0, "value", 1);
            doTestsMultiTitlesBold(getSubtitle(), true);
            runAction("SetInt", "property", 2490, "i", 0, "j", 0, "value", 0);
            doTestsMultiTitlesBold(getSubtitle(), false);

            // text-color
            // main title
            runAction("SetString", "property", 2105, "i", 0, "j", 0, "value", "main");

            Color titleColor = Color.BLUE;
            int bgr = ChartsCommon.convertBGRtoRGB(titleColor.getRGB() & 0xFFFFFF);
            runAction("SetInt", "property", 2325, "i", 0, "j", 0, "value", bgr);
            assertEquals(titleColor, getChart().getChart().getTitle().getPaint());
            doTestsMultiTitlesColor(getSubtitle(), titleColor);

            // SimpleSubtitle class
            String test = "Hello World!!!!!!!!!!!!!!!!!!";
            SimpleSubtitle simpleTitle = new SimpleSubtitle(test);
            assertEquals(simpleTitle.getText(), test);
            simpleTitle.setSubtitleText(test + test);
            assertEquals(simpleTitle.getText(), test + test);

            // multi-subtitles, multi-bottom-titles
            runAction("SetString", "property", 2631, "i", 0, "j", 0, "value", "4|5|6");
            runAction("SetString", "property", 2630, "i", 0, "j", 0, "value", "1|2|3");
            TextTitle[] titles = getChart().getSubtitle();
            assertEquals(((Title) titles[0]).getPosition(), RectangleEdge.TOP);

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests label properties 
     */
    public void testLabelProperties() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);

        try {
            int subsets = 2;
            runAction("SetInt", "property", 2115, "i", 0, "j", 0, "value", subsets);

            LegendTitle legendTitle = (LegendTitle) getSubtitle(LegendTitle.class);
            assertNotNull(legendTitle);

            // label-bold
            runAction("SetInt", "property", 2530, "i", 0, "j", 0, "value", 1);
            assertTrue(legendTitle.getItemFont().isBold());
            runAction("SetInt", "property", 2530, "i", 0, "j", 0, "value", 0);
            assertFalse(legendTitle.getItemFont().isBold());

            // point-labels
            runAction("SetString", "property", 2130, "i", 0, "j", 0, "value", "point-label");
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests font size
     * @param size
     */
    void doTestFontSize(int size) throws Exception {
        LegendTitle legendTitle = (LegendTitle) getSubtitle(LegendTitle.class);
        assertNotNull(legendTitle);

        runAction("SetInt", "property", 2435, "i", 0, "j", 0, "value", size);

        float fontSize = FontSizeProperty.getFontSize(size);
        assertTrue(Math.abs(fontSize - legendTitle.getItemFont().getSize()) < 1.0f);
    }

    /**
     * Tests Font properties 
     */
    public void testFontProperties() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);

        try {
            int subsets = 2;
            runAction("SetInt", "property", 2115, "i", 0, "j", 0, "value", subsets);
            String title = "sub-title";
            runAction("SetString", "property", 2110, "i", 0, "j", 0, "value", title);


            // font-size
            doTestFontSize(FontSizeProperty.FONT_LARGE);
            doTestFontSize(FontSizeProperty.FONT_MEDIUM);
            doTestFontSize(FontSizeProperty.FONT_SMALL);
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests gradient mode
     * @param bitmapMode is bitmap mode set?
     * @param quickStyle quick style
     * @throws Exception
     */
    void doTestGradient(boolean bitmapMode, int quickStyle) throws Exception {
        JFreeChartHolder holder = getHolder();

        // bitmap-gradient-mode
        runAction("SetInt", "property", 2703, "i", 0, "j", 0, "value", bitmapMode ? 1 : 0);
        assertEquals(bitmapMode, holder.getStyle().isGradientMode());

        // quick-style
        runAction("SetInt", "property", 2672, "i", 0, "j", 0, "value", quickStyle);
        assertEquals(quickStyle, holder.getStyle().getStyle());
    }

    /**
     * Tests gradient properties 
     */
    public void testGradientProperties() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        JFreeChartHolder holder = getHolder();

        try {
            String title = "sub-title";
            runAction("SetString", "property", 2110, "i", 0, "j", 0, "value", title);

            for (int style = ChartStyle.STYLE_NO_STYLE; style <= ChartStyle.STYLE_DARK_NO_BORDER; style++) {
                doTestGradient(true, style);
                doTestGradient(false, style);
            }

            // quick-style wrong data
            int oldStyle = holder.getStyle().getStyle();
            runAction("SetInt", "property", 2672, "i", 0, "j", 0, "value", -1);
            assertEquals(oldStyle, holder.getStyle().getStyle());

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests image adjust properties 
     */
    public void testImageAdjustProperties() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        JFreeChartHolder holder = getHolder();

        try {
            //image-adjust-left
            holder.setPadding(null);
            int left = 200;
            runAction("SetInt", "property", 2982, "i", 0, "j", 0, "value", left);
            assertEquals(left, (int) holder.getPadding().getLeft());
            runAction("SetInt", "property", 2982, "i", 0, "j", 0, "value", 2 * left);
            assertEquals(2 * left, (int) holder.getPadding().getLeft());

            //image-adjust-top
            holder.setPadding(null);
            int top = 300;
            runAction("SetInt", "property", 2984, "i", 0, "j", 0, "value", top);
            assertEquals(top, (int) holder.getPadding().getTop());
            runAction("SetInt", "property", 2984, "i", 0, "j", 0, "value", 2 * top);
            assertEquals(2 * top, (int) holder.getPadding().getTop());

            //image-adjust-right
            holder.setPadding(null);
            int right = 400;
            runAction("SetInt", "property", 2983, "i", 0, "j", 0, "value", right);
            assertEquals(right, (int) holder.getPadding().getRight());
            runAction("SetInt", "property", 2983, "i", 0, "j", 0, "value", 2 * right);
            assertEquals(2 * right, (int) holder.getPadding().getRight());

            //image-adjust-bottom
            holder.setPadding(null);
            int bottom = 500;
            runAction("SetInt", "property", 2985, "i", 0, "j", 0, "value", bottom);
            assertEquals(bottom, (int) holder.getPadding().getBottom());
            runAction("SetInt", "property", 2985, "i", 0, "j", 0, "value", 2 * bottom);
            assertEquals(2 * bottom, (int) holder.getPadding().getBottom());

            // test all properties
            holder.setPadding(null);
            runAction("SetInt", "property", 2982, "i", 0, "j", 0, "value", left);
            runAction("SetInt", "property", 2984, "i", 0, "j", 0, "value", top);
            runAction("SetInt", "property", 2983, "i", 0, "j", 0, "value", right);
            runAction("SetInt", "property", 2985, "i", 0, "j", 0, "value", bottom);

            RectangleInsets padding = holder.getPadding();

            assertEquals(left, (int) padding.getLeft());
            assertEquals(top, (int) padding.getTop());
            assertEquals(right, (int) padding.getRight());
            assertEquals(bottom, (int) padding.getBottom());

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests pie properties 
     */
    public void testPieProperties() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);

        try {
            // show-pie-legend
            runAction("SetInt", "property", 3922, "i", 0, "j", 0, "value", 1);
            runAction("SetInt", "property", 3922, "i", 0, "j", 0, "value", 0);

            // show-pie-labels
            runAction("SetInt", "property", 3921, "i", 0, "j", 0, "value", ShowPieLablesProperty.SHOW_PERCENT_PLUS_LABEL);
            runAction("SetInt", "property", 3921, "i", 0, "j", 0, "value", ShowPieLablesProperty.SHOW_PERCENT);
            runAction("SetInt", "property", 3921, "i", 0, "j", 0, "value", ShowPieLablesProperty.SHOW_LABEL);
            runAction("SetInt", "property", 3921, "i", 0, "j", 0, "value", ShowPieLablesProperty.SHOW_NONE);
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests legend properties 
     */
    public void testLegendProperties() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);

        try {
            int subsets = 2;
            runAction("SetInt", "property", 2115, "i", 0, "j", 0, "value", subsets);

            LegendTitle legendTitle = (LegendTitle) getSubtitle(LegendTitle.class);
            assertNotNull(legendTitle);

            // legend-location
            runAction("SetInt", "property", 3082, "i", 0, "j", 0, "value", LegendLocationProperty.LOCATION_TOP);
            assertEquals(RectangleEdge.TOP, legendTitle.getPosition());

            runAction("SetInt", "property", 3082, "i", 0, "j", 0, "value", LegendLocationProperty.LOCATION_LEFT);
            assertEquals(RectangleEdge.LEFT, legendTitle.getPosition());

            runAction("SetInt", "property", 3082, "i", 0, "j", 0, "value", LegendLocationProperty.LOCATION_RIGHT);
            assertEquals(RectangleEdge.RIGHT, legendTitle.getPosition());

            runAction("SetInt", "property", 3082, "i", 0, "j", 0, "value", LegendLocationProperty.LOCATION_BOTTOM);
            assertEquals(RectangleEdge.BOTTOM, legendTitle.getPosition());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests other properties 
     */
    public void testOtherProperties() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        JFreeChart jchart = getJChart();

        try {
            int subsets = 2;
            runAction("SetInt", "property", 2115, "i", 0, "j", 0, "value", subsets);

            // graph-fore-color
            int bgr = 0xFEDCBA;
            runAction("SetInt", "property", 2335, "i", 0, "j", 0, "value", bgr);
            Color color = (Color) jchart.getXYPlot().getDomainAxis().getAxisLinePaint();
            assertEquals(0xFE, color.getBlue());
            assertEquals(0xDC, color.getGreen());
            assertEquals(0xBA, color.getRed());

            // data-shadows
            runAction("SetInt", "property", 2240, "i", 0, "j", 0, "value", DataShadowProperty.SHADOW_NONE);
            runAction("SetInt", "property", 2240, "i", 0, "j", 0, "value", DataShadowProperty.SHADOW_SHADOWS);
            runAction("SetInt", "property", 2240, "i", 0, "j", 0, "value", DataShadowProperty.SHADOW_3D);

            // grid-line-control
            runAction("SetInt", "property", 3100, "i", 0, "j", 0, "value", GridLineControlProperty.GRIDLINE_BOTH);
            assertTrue(jchart.getXYPlot().isDomainGridlinesVisible());
            assertTrue(jchart.getXYPlot().isRangeGridlinesVisible());

            runAction("SetInt", "property", 3100, "i", 0, "j", 0, "value", GridLineControlProperty.GRIDLINE_YAXIS);
            assertFalse(jchart.getXYPlot().isDomainGridlinesVisible());
            assertTrue(jchart.getXYPlot().isRangeGridlinesVisible());

            runAction("SetInt", "property", 3100, "i", 0, "j", 0, "value", GridLineControlProperty.GRIDLINE_XAXIS);
            assertTrue(jchart.getXYPlot().isDomainGridlinesVisible());
            assertFalse(jchart.getXYPlot().isRangeGridlinesVisible());

            runAction("SetInt", "property", 3100, "i", 0, "j", 0, "value", GridLineControlProperty.GRIDLINE_NONE);
            assertFalse(jchart.getXYPlot().isDomainGridlinesVisible());
            assertFalse(jchart.getXYPlot().isRangeGridlinesVisible());

            // grid-style
            XYPlot plot = jchart.getXYPlot();
            runAction("SetInt", "property", 3032, "i", 0, "j", 0, "value", GridStyleProperty.PEGS_THIN);
            assertEquals(ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THINSOLID), plot.getDomainGridlineStroke());
            assertEquals(ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THINSOLID), plot.getRangeGridlineStroke());

            runAction("SetInt", "property", 3032, "i", 0, "j", 0, "value", GridStyleProperty.PEGS_THICK);
            assertEquals(ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THICKSOLID), plot.getDomainGridlineStroke());
            assertEquals(ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_THICKSOLID), plot.getRangeGridlineStroke());

            runAction("SetInt", "property", 3032, "i", 0, "j", 0, "value", GridStyleProperty.PEGS_DOT);
            assertEquals(ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_DOT), plot.getDomainGridlineStroke());
            assertEquals(ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_DOT), plot.getRangeGridlineStroke());

            runAction("SetInt", "property", 3032, "i", 0, "j", 0, "value", GridStyleProperty.PEGS_DASH);
            assertEquals(ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_DASH), plot.getDomainGridlineStroke());
            assertEquals(ChartLineTypes.makeBasicStroke(ChartLineTypes.LINE_DASH), plot.getRangeGridlineStroke());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Test for {@code ScientificChart} class.
     */
    public final void testScientificActions() {
        doCreateAction(CreateChartAction.PE_SCIENTIFIC_CHART);
        assertTrue(getChart() instanceof ScientificChart);
        ScientificChart chart = (ScientificChart) getChart();
        JFreeChartHolder holder = getHolder();

        try {
            int subsets = 0;
            runAction(SetValueActions.SetInt, "property", 2115, "i", 0, "j", 0, "value", subsets);
            assertEquals(chart.getDataset().getSeriesCount(), subsets);

            // ydata
            Document ydocT = ChartServer.makeXMLMessage("SetDoubleArray", getHandle());
            ChartServer.addXMLData(ydocT, "property", 2140, "i", 0, "j", 0);
            Element ydataT = ydocT.createElement("value");
            ydocT.getDocumentElement().appendChild(ydataT);
            double yvaluesT[] = new double[]{1, 2, 3, 4, 5};
            for (double f : yvaluesT) {
                ChartServer.addXMLElementData(ydocT, ydataT, "item", f);
            }
            runAction(ydocT);

            // SubtitleProperty 2110 SetString
            String[] values = {"", "", "dffg drdrgd"};
            String title = values[0] + "|" + values[1] + "|" + values[2];
            runAction("SetString", "property", 2110, "i", 0, "j", 0, "value", title);
            doTestsMultiTitles(values, getSubtitle());

            // subtitle-bold
            runAction("SetInt", "property", 2490, "i", 0, "j", 0, "value", 1);
            doTestsMultiTitlesBold(getSubtitle(), true);
            runAction("SetInt", "property", 2490, "i", 0, "j", 0, "value", 0);
            doTestsMultiTitlesBold(getSubtitle(), false);

            // subtitle-font
            String fontName = "Arial";
            runAction("SetString", "property", 2485, "i", 0, "j", 0, "value", "Arial");
            doTestsMultiTitlesFont(getSubtitle(), fontName);

            // allow-data-hot-spots 3210 SetInt
            boolean allow = false;
            runAction(SetValueActions.SetInt, "property", 3210, "i", 0, "j", 0, "value", allow ? 1 : 0);
            assertEquals(chart.isDataHotSpotsAllowed(), allow);
            allow = true;
            runAction(SetValueActions.SetInt, "property", 3210, "i", 0, "j", 0, "value", allow ? 1 : 0);
            assertEquals(chart.isDataHotSpotsAllowed(), allow);

            // allow-point-hot-spots
            runAction(SetValueActions.SetInt, "property", 2605, "i", 0, "j", 0, "value", 1);
            assertTrue(chart.isPointHotSpotsAllowed());
            runAction(SetValueActions.SetInt, "property", 2605, "i", 0, "j", 0, "value", 0);
            assertFalse(chart.isPointHotSpotsAllowed());

            // allow-subset-hot-spots
            runAction(SetValueActions.SetInt, "property", 2600, "i", 0, "j", 0, "value", 1);
            assertTrue(chart.isSeriesHotSpotsAllowed());
            runAction(SetValueActions.SetInt, "property", 2600, "i", 0, "j", 0, "value", 0);
            assertFalse(chart.isSeriesHotSpotsAllowed());
            
            // x-axis-scale-control
            runAction(SetValueActions.SetInt, "property", 3610, "i", 0, "j", 0, "value", 0);
            assertTrue(chart.getPlot().getDomainAxis() instanceof NumberAxis);
            List<Double> xRange = new ArrayList<Double>();
            xRange.add(1d);
            xRange.add(11e3d);
            chart.setValuesX(xRange);
            runAction(SetValueActions.SetInt, "property", 3610, "i", 0, "j", 0, "value", 0);
            assertTrue(chart.getPlot().getDomainAxis() instanceof LogarithmicAxis);
            runAction(SetValueActions.SetInt, "property", 3610, "i", 0, "j", 0, "value", 1);
            assertTrue(chart.getPlot().getDomainAxis() instanceof NumberAxis);
            runAction(SetValueActions.SetInt, "property", 3610, "i", 0, "j", 0, "value", 2);
            assertTrue(chart.getPlot().getDomainAxis() instanceof LogarithmicAxis);

            // y-axis-scale-control
            runAction(SetValueActions.SetInt, "property", 3045, "i", 0, "j", 0, "value", 0);
            assertTrue(chart.getPlot().getCurrentPlot().getRangeAxis() instanceof NumberAxis);
            List<Double> yRange = new ArrayList<Double>();
            yRange.add(1d);
            yRange.add(11e3d);
            chart.setValuesY(yRange);
            runAction(SetValueActions.SetInt, "property", 3045, "i", 0, "j", 0, "value", 0);
            assertTrue(chart.getPlot().getCurrentPlot().getRangeAxis() instanceof LogarithmicAxis);
            runAction(SetValueActions.SetInt, "property", 3045, "i", 0, "j", 0, "value", 1);
            assertTrue(chart.getPlot().getCurrentPlot().getRangeAxis() instanceof NumberAxis);
            runAction(SetValueActions.SetInt, "property", 3045, "i", 0, "j", 0, "value", 2);
            assertTrue(chart.getPlot().getCurrentPlot().getRangeAxis() instanceof LogarithmicAxis);

            // QuickStyleProperty 2672 SetInt
            int style1 = ChartStyle.STYLE_LIGHT_INSET;
            int style2 = ChartStyle.STYLE_DARK_SHADOW;
            int style3 = ChartStyle.STYLE_MEDIUM_LINE;
            runAction(SetValueActions.SetInt, "property", 2672, "i", 0, "j", 0, "value", style1);
            assertEquals(holder.getStyle().getStyle(), style1);
            runAction(SetValueActions.SetInt, "property", 2672, "i", 0, "j", 0, "value", style2);
            assertEquals(holder.getStyle().getStyle(), style2);
            runAction(SetValueActions.SetInt, "property", 2672, "i", 0, "j", 0, "value", style3);
            assertEquals(holder.getStyle().getStyle(), style3);

            boolean flag = false;
            try {
                holder.getStyle().setStyle(-1);
            } catch (IChartAction.ChartActionException e) {
                flag = true;
            }
            assertTrue(flag);

            // BitmapGradientModeProperty 2703 SetInt
            boolean gradmod = false;
            runAction(SetValueActions.SetInt, "property", 2703, "i", 0, "j", 0, "value", gradmod ? 1 : 0);
            assertEquals(holder.getStyle().isGradientMode(), gradmod);
            gradmod = true;
            runAction(SetValueActions.SetInt, "property", 2703, "i", 0, "j", 0, "value", gradmod ? 1 : 0);
            assertEquals(holder.getStyle().isGradientMode(), gradmod);

            // LabelBoldProperty 2530 SetInt
            LegendTitle legendTitle = (LegendTitle) getSubtitle(LegendTitle.class);
            assertNotNull(legendTitle);
            runAction("SetInt", "property", 2530, "i", 0, "j", 0, "value", 1);
            assertTrue(legendTitle.getItemFont().isBold());
            runAction("SetInt", "property", 2530, "i", 0, "j", 0, "value", 0);
            assertFalse(legendTitle.getItemFont().isBold());

            // MarkDataPointsProperty 3215 SetInt
            int markData = 1;
            runAction("SetInt", "property", 3215, "i", 0, "j", 0, "value", markData);
            assertEquals(chart.getMarkPoints(), markData != 0);
            markData = 0;
            runAction("SetInt", "property", 3215, "i", 0, "j", 0, "value", markData);
            assertEquals(chart.getMarkPoints(), markData != 0);

            // DateTimeModeProperty 3018 SetInt
            runAction("SetInt", "property", 3018, "i", 0, "j", 0, "value", 1);

            // AppendXDataProperty 3658 SetDoubleArray
            int size = chart.getDataset().getItemCount(0);
            int points = 1;
            Document xdoc = ChartServer.makeXMLMessage(SetValueActions.SetDoubleArray, getHandle());
            ChartServer.addXMLData(xdoc, "property", 3658, "i", 0, "j", points);
            Element xdata = xdoc.createElement("value");
            xdoc.getDocumentElement().appendChild(xdata);
            double xvalues[] = new double[]{45569.23423};
            for (double f : xvalues) {
                ChartServer.addXMLElementData(xdoc, xdata, "item", f);
            }
            runAction(xdoc);

            // AppendYDataProperty 3276 SetDoubleArray
            Document ydoc = ChartServer.makeXMLMessage(SetValueActions.SetDoubleArray, getHandle());
            ChartServer.addXMLData(ydoc, "property", 3276, "i", 0, "j", points);
            Element ydata = ydoc.createElement("value");
            ydoc.getDocumentElement().appendChild(ydata);
            double yvalues[] = new double[]{1};
            for (double f : yvalues) {
                ChartServer.addXMLElementData(ydoc, ydata, "item", f);
            }
            runAction(ydoc);

            assertEquals(chart.getDataset().getItemCount(0), size + points);

            // to do: Mouse events
            //ChartEntity entity = new XYItemEntity(new Area(), jchart.getXYPlot().getDataset(), 0, 0, null, null);
            //ChartMouseEvent event = new ChartMouseEvent(jchart, null, entity);
            //Cursor cursor = holder.getCursor();
            //holder.chartMouseClicked(event);
            //holder.chartMouseMoved(event);
            //assertNotSame(holder.getCursor(), cursor);

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Test for XYData.
     */
    public final void testScientificXYData() {
        doCreateAction(CreateChartAction.PE_SCIENTIFIC_CHART);
        assertTrue(getChart() instanceof ScientificChart);
        ScientificChart chart = (ScientificChart) getChart();

        try {
            int subsets = 1;
            runAction(SetValueActions.SetInt, "property", 2115, "i", 0, "j", 0, "value", subsets);

            // xdata
            Document doc = ChartServer.makeXMLMessage(SetValueActions.SetDoubleArray, getHandle());
            ChartServer.addXMLData(doc, "property", 2140, "i", 0, "j", 0);
            Element data = doc.createElement("value");
            doc.getDocumentElement().appendChild(data);
            double values[] = new double[]{1, 2, 3, 4, 5};
            for (double f : values) {
                ChartServer.addXMLElementData(doc, data, "item", f);
            }
            runAction(doc);

            // ydata
            doc = ChartServer.makeXMLMessage(SetValueActions.SetDoubleArray, getHandle());
            ChartServer.addXMLData(doc, "property", 2135, "i", 0, "j", 0);
            data = doc.createElement("value");
            doc.getDocumentElement().appendChild(data);
            for (double f : values) {
                ChartServer.addXMLElementData(doc, data, "item", f);
            }
            runAction(doc);

            assertEquals(chart.getDataset().getSeriesCount(), subsets);
            assertTrue(chart.getDataset() instanceof XYSeriesCollection);
            XYSeriesCollection dataset = chart.getDataset();
            assertEquals(dataset.getSeries(0).getItemCount() - 1, 5);
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Tests scrolling
     */
    public void testScrolling() {
        try {
            doCreateAction(false, false, CreateChartAction.PE_GRAPH_CHART);
            JFreeChartHolder holder = getHolder();
            assertTrue(holder.getChart() instanceof GraphChart);
            GraphChart graph = (GraphChart) holder.getChart();

            // scrolling-subsets
            int items = 2;
            runAction(SetValueActions.SetInt, "property", 3070, "i", 0, "j", 0, "value", items);
            assertEquals(items, graph.getSeriesScrolling().getScrolledItems());
            
            // table-what
            ColoredTable table = holder.getTable();
            runAction(SetValueActions.SetInt, "property", 3365, "i", 0, "j", 0, "value", TableWhatProperty.PETW_ALLSUBSETS);
            assertTrue(table.getShowAllItems());
            assertTrue(table.getEnableSelect());
            runAction(SetValueActions.SetInt, "property", 3365, "i", 0, "j", 0, "value", TableWhatProperty.PETW_GRAPHED);
            assertFalse(table.getShowAllItems());
            assertTrue(table.getEnableSelect());
            runAction(SetValueActions.SetInt, "property", 3365, "i", 0, "j", 0, "value", TableWhatProperty.PETW_GRAYED);
            assertTrue(table.getShowAllItems());
            assertFalse(table.getEnableSelect());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Tests plotting-methods propriety
     */
    public void testPlottingMethods() {
        try {
            doCreateAction(false, false, CreateChartAction.PE_GRAPH_CHART);
            runAction("Update");
            
            JFreeChartHolder holder = getHolder();
            assertTrue(holder.getChart() instanceof GraphChart);
            GraphChart graph = (GraphChart) holder.getChart();

            List<XYAxesPlot> plots = graph.getPlot().getAllPlots();
            assertEquals(1, plots.size());
            
            XYAxesPlot plot = plots.get(0);
            assertNotNull(plot);

            // plotting-methods
            runAction("SetInt", "property", 3103, "i", 0, "j", 0, "value", GraphRendererFactory.PEGPM_POINT);
            runAction("SetInt", "property", 3103, "i", 1, "j", 0, "value", GraphRendererFactory.PEGPM_BAR);

            // Sets subset-colors
            runAction("SetInt", "property", 2190, "i", 0, "j", 0, "value", 0x123456);
            runAction("SetInt", "property", 2190, "i", 1, "j", 0, "value", 0x123456);
            
            runAction("Update");

            assertTrue(plot.getRenderer(0) instanceof XYLineAndShapeRenderer);
            assertTrue(plot.getRenderer(1) instanceof ClusteredXYBarRenderer);
            assertTrue(plot.getRenderer(2) instanceof XYLineAndShapeRenderer);
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests Print action
     */
    public void testPrintAction() {
        try {
            doCreateAction(false, false, CreateChartAction.PE_GRAPH_CHART);
            
            PrintChartAction action = new PrintChartAction();
            assertTrue(action.isChartRequired());
            assertEquals(action.getName(), ((PrintChartAction)action.clone()).getName());
            
            PrintChart print = new PrintChart(getHolder());
            BufferedImage img = new BufferedImage(100, 100, BufferedImage.TYPE_INT_ARGB);
            int result = print.print(img.createGraphics(), null, -1);
            assertEquals(Printable.NO_SUCH_PAGE, result);
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
}

