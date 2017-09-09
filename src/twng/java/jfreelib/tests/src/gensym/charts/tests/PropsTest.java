package gensym.charts.tests;

import gensym.charts.ChartLineTypes;
import gensym.charts.ChartsCommon;
import gensym.charts.actions.CreateChartAction;
import gensym.charts.DefaultChartStyle;
import gensym.charts.PieChart;
import gensym.charts.properties.*;
import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;

import java.awt.Shape;
import java.awt.geom.AffineTransform;
import java.awt.geom.GeneralPath;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Stroke;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;
import java.awt.geom.Rectangle2D;


import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PiePlot;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.labels.*;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;
import org.jfree.util.ShapeUtilities;

public class PropsTest extends TestChartBase {
    /**
     * Tests graph-back-color&desk-color props
     */
    public final void testBackAndDeskColor() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        assertNotNull(getHolder());
        JFreeChartHolder holder = getHolder();

        int intColor1 = 333, intColor2 = 222;
        Color color1 = new Color(ChartsCommon.convertBGRtoRGB(intColor1));
        Color color2 = new Color(ChartsCommon.convertBGRtoRGB(intColor2));

        try {
            // graph-back-color
            runAction("SetInt", "property", 2340, "i", 0,
                    "j", 0, "value", intColor1);
            assertNotNull(holder.getStyle());
            assertEquals(holder.getStyle().getPlotColor(), color1);

            // desk-color
            runAction("SetInt", "property", 2320, "i", 0,
                    "j", 0, "value", intColor2);
            assertNotNull(holder.getStyle());
            assertEquals(holder.getStyle().getChartColor(), color2);

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests border types
     */
    public final void testBorderTypes() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        assertNotNull(getHolder());
        JFreeChartHolder holder = getHolder();

        try {
            // border-types
            runAction("SetInt", "property", 2943, "i", 0,
                    "j", 0, "value", DefaultChartStyle.BORDER_NO_BORDER);
            assertNotNull(holder.getStyle());
            assertNull(holder.getStyle().getBorder());

            runAction("SetInt", "property", 2943, "i", 0,
                    "j", 0, "value", DefaultChartStyle.BORDER_THICK_LINE);
            assertNotNull(holder.getStyle());
            assertEquals(holder.getStyle().getBorder(), new BasicStroke(2));

            runAction("SetInt", "property", 2943, "i", 0,
                    "j", 0, "value", DefaultChartStyle.BORDER_SINGLE_LINE);
            assertNotNull(holder.getStyle());
            assertEquals(holder.getStyle().getBorder(), new BasicStroke(1));

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests allow-horz-bar-stacked, allow-ribbon, allow-step, null-data-gaps props
     */
    public final void testSomeAllowProps() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        assertNotNull(getChart());
        assertTrue(getChart() instanceof GraphChart);
        GraphChart chart = (GraphChart) getChart();
        try {
            // allow-horz-bar-stacked
            runAction("SetInt", "property", 3419, "i", 0,
                    "j", 0, "value", 1);
            assertTrue(chart.isHorzBarStackedAllowed());
            runAction("SetInt", "property", 3419, "i", 0,
                    "j", 0, "value", 0);
            assertFalse(chart.isHorzBarStackedAllowed());

            // allow-ribbon
            runAction("SetInt", "property", 3091, "i", 0,
                    "j", 0, "value", 1);
            assertTrue(chart.isRibbonAllowed());
            runAction("SetInt", "property", 3091, "i", 0,
                    "j", 0, "value", 0);
            assertFalse(chart.isRibbonAllowed());

            // allow-step
            runAction("SetInt", "property", 3067, "i", 0,
                    "j", 0, "value", 1);
            assertTrue(chart.isStepAllowed());
            runAction("SetInt", "property", 3067, "i", 0,
                    "j", 0, "value", 0);
            assertFalse(chart.isStepAllowed());

            // null-data-gaps
            runAction("SetInt", "property", 3066, "i", 0,
                    "j", 0, "value", 1);
            assertTrue(chart.isNullDataGaps());
            runAction("SetInt", "property", 3066, "i", 0,
                    "j", 0, "value", 0);
            assertFalse(chart.isNullDataGaps());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests show-pie-legend, show-pie-labels props
     */
    public final void testShowPieProps() {
        doCreateAction(CreateChartAction.PE_PIE_CHART);
        assertNotNull(getChart());
        assertEquals(getChart().getClass(), PieChart.class);
        JFreeChart chart = getJChart();
        PiePlot plot = (PiePlot) chart.getPlot();

        try {
            // show-pie-legend
            runAction("SetInt", "property", 3922, "i", 0,
                    "j", 0, "value", 1);
            assertTrue(chart.getLegend().isVisible());
            runAction("SetInt", "property", 3922, "i", 0,
                    "j", 0, "value", 0);
            assertFalse(chart.getLegend().isVisible());

            // show-pie-labels
            testOneShowPieLabels(ShowPieLablesProperty.SHOW_PERCENT_PLUS_LABEL,
                    new StandardPieSectionLabelGenerator("{2} - {0}"), plot);
            testOneShowPieLabels(ShowPieLablesProperty.SHOW_PERCENT,
                    new StandardPieSectionLabelGenerator("{2}"), plot);
            testOneShowPieLabels(ShowPieLablesProperty.SHOW_LABEL,
                    new StandardPieSectionLabelGenerator("{0}"), plot);
            testOneShowPieLabels(ShowPieLablesProperty.SHOW_NONE,
                    null, plot);

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests subset-point-types property
     */
    public final void testSubsetPointTypesProperty() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        try {
            // subsets
            runAction("SetInt", "property", 2115, "i", 0, "j", 0, "value", 2);
            // xdata
            runAction("SetDouble", "property", 2135, "i", 0,
                    "j", 0, "value", 1);
            // ydata
            runAction("SetDouble", "property", 2140, "i", 0,
                    "j", 0, "value", 2);
            // set mark-data-points prop
            runAction("SetInt", "property", 3215, "i", 0, "j", 0, "value", 1);

            // subset-point-types
            final float POINT_SIZE = 6;

            Rectangle2D rect = ShapeUtilities.createRegularCross(POINT_SIZE / 2, 1).getBounds2D();
            testOneShape(SubsetPointTypesProperty.PEPT_PLUS, rect, 0);
            testOneShape(SubsetPointTypesProperty.PEPT_CROSS, rect, 0);

            rect = (new Ellipse2D.Float(-POINT_SIZE / 2, -POINT_SIZE / 2, POINT_SIZE, POINT_SIZE)).getBounds2D();
            testOneShape(SubsetPointTypesProperty.PEPT_DOT, rect, 0);
            testOneShape(SubsetPointTypesProperty.PEPT_DOTSOLID, rect, 0);

            rect = (new Rectangle2D.Float(-POINT_SIZE / 2, -POINT_SIZE / 2, POINT_SIZE, POINT_SIZE)).getBounds2D();
            testOneShape(SubsetPointTypesProperty.PEPT_SQUARE, rect, 0);
            testOneShape(SubsetPointTypesProperty.PEPT_SQUARESOLID, rect, 0);

            rect = (ShapeUtilities.createDiamond(POINT_SIZE / 2)).getBounds2D();
            testOneShape(SubsetPointTypesProperty.PEPT_DIAMOND, rect, 0);
            testOneShape(SubsetPointTypesProperty.PEPT_DIAMONDSOLID, rect, 0);

            rect = (ShapeUtilities.createUpTriangle(POINT_SIZE / 2)).getBounds2D();
            testOneShape(SubsetPointTypesProperty.PEPT_UPTRIANGLE, rect, 0);
            testOneShape(SubsetPointTypesProperty.PEPT_UPTRIANGLESOLID, rect, 0);

            rect = (ShapeUtilities.createDownTriangle(POINT_SIZE / 2)).getBounds2D();
            testOneShape(SubsetPointTypesProperty.PEPT_DOWNTRIANGLE, rect, 0);
            testOneShape(SubsetPointTypesProperty.PEPT_DOWNTRIANGLESOLID, rect, 0);

            rect = (new Line2D.Float(-2, 0, 2, 0)).getBounds2D();
            testOneShape(SubsetPointTypesProperty.PEPT_DASH, rect, 0);

            rect = (new Ellipse2D.Float(-0.5f, -0.5f, 1, 1)).getBounds2D();
            testOneShape(SubsetPointTypesProperty.PEPT_PIXEL, rect, 0);

            rect = createArrow(0, POINT_SIZE).getBounds2D();
            testOneShape(SubsetPointTypesProperty.PEPT_ARROW_N, rect, 0);

            rect = createArrow(Math.PI / 4, POINT_SIZE).getBounds2D();
            testOneShape(SubsetPointTypesProperty.PEPT_ARROW_NW, rect, 0);

            rect = createArrow(Math.PI / 2, POINT_SIZE).getBounds2D();
            testOneShape(SubsetPointTypesProperty.PEPT_ARROW_W, rect, 0);

            rect = createArrow(3 * Math.PI / 4, POINT_SIZE).getBounds2D();
            testOneShape(SubsetPointTypesProperty.PEPT_ARROW_SW, rect, 0);

            rect = createArrow(Math.PI, POINT_SIZE).getBounds2D();
            testOneShape(SubsetPointTypesProperty.PEPT_ARROW_S, rect, 0);

            rect = createArrow(5 * Math.PI / 4, POINT_SIZE).getBounds2D();
            testOneShape(SubsetPointTypesProperty.PEPT_ARROW_SE, rect, 0);

            rect = createArrow(3 * Math.PI / 2, POINT_SIZE).getBounds2D();
            testOneShape(SubsetPointTypesProperty.PEPT_ARROW_E, rect, 0);

            rect = createArrow(7 * Math.PI / 4, POINT_SIZE).getBounds2D();
            testOneShape(SubsetPointTypesProperty.PEPT_ARROW_NE, rect, 0);

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests xdata, ydata
     */
    public final void testXYSimpleProperty() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        assertTrue(getChart() instanceof GraphChart);
        GraphChart chart = (GraphChart) getChart();

        double x = 555.555, y = 9999.0;
        int i = 0, j = 0;
        try {
            // subsets
            runAction("SetInt", "property", 2115, "i", i, "j", j, "value", 1);

            // xdata
            runAction("SetDouble", "property", 2135, "i", i,
                    "j", j, "value", x);
            // ydata
            runAction("SetDouble", "property", 2140, "i", i,
                    "j", j, "value", y);

            assertNotNull(chart.getDataset());
            assertEquals(chart.getDataset().getX(i, j), x);
            assertEquals(chart.getDataset().getY(i, j), y);

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests grid-style property
     */
    public final void testGridStyleProperty() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);

        testOneStyle(GridStyleProperty.PEGS_THIN, ChartLineTypes.LINE_THINSOLID);
        testOneStyle(GridStyleProperty.PEGS_THICK, ChartLineTypes.LINE_THICKSOLID);
        testOneStyle(GridStyleProperty.PEGS_DOT, ChartLineTypes.LINE_DOT);
        testOneStyle(GridStyleProperty.PEGS_DASH, ChartLineTypes.LINE_DASH);
    }

    /**
     * Tests one grid style set up
     * @param value grid style value
     * @param strokeValue value for stroke
     */
    private final void testOneStyle(int value, int strokeValue) {
        try {
            // grid-style
            runAction("SetInt", "property",
                    3032, "i", 0, "j", 0, "value", value);
            Stroke stroke = ChartLineTypes.makeBasicStroke(strokeValue);
            assertNotNull(stroke);

            assertTrue(getJChart().getPlot() instanceof XYPlot);
            XYPlot plot = (XYPlot) getJChart().getPlot();
            assertEquals(plot.getDomainGridlineStroke(), stroke);
            assertEquals(plot.getDomainGridlineStroke(), stroke);

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests show-pie-labels porop
     * @param type to pass
     * @param lGenerator class to check
     * @param plot PiePlot
     */
    private final void testOneShowPieLabels(int type,
            StandardPieSectionLabelGenerator lGenerator, PiePlot plot) {
        try {
            // show-pie-labels
            runAction("SetInt", "property", 3921, "i", 0,
                    "j", 0, "value", type);
            assertEquals(plot.getLabelGenerator(), lGenerator);
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests one shape
     * @param type to test
     * @param rect Rectangle2D
     * @param series number of series
     */
    private final void testOneShape(int type, Rectangle2D rect, int series) {
        try {
            runAction("SetInt", "property", 3270, "i", series, "j", 0, "value", type);
            runAction("Update");
            GraphChart graph = (GraphChart) getChart();
            assertNotNull(graph.getPlot().getCurrentPlot());

            XYPlot plot = graph.getPlot().getCurrentPlot();
            assertTrue(plot.getRenderer()instanceof XYLineAndShapeRenderer);
            XYLineAndShapeRenderer renderer = (XYLineAndShapeRenderer) plot.getRenderer();

            assertEquals(rect, renderer.getSeriesShape(series).getBounds2D());

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Creates arrow shape
     * @param rotateAngle angle to rotate (in radians)
     * @param height arrow height
     * @return created arrow shape
     */
    private final Shape createArrow(double rotateAngle, float height) {
        GeneralPath shape = new GeneralPath();
        shape.moveTo(-height / 2, 0);
        shape.lineTo(0, height / 2);
        shape.lineTo(height / 2, height / 2);
        shape.moveTo(0, height / 2);
        shape.lineTo(0, -height / 2);
        shape.closePath();

        AffineTransform rotate = new AffineTransform(0.0f, Math.cos(rotateAngle), Math.sin(rotateAngle),
                0.0f, 0.0f, 0.0f);

        return rotate.createTransformedShape(shape);
    }
}
