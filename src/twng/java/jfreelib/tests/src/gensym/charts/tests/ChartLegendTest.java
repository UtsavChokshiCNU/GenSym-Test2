package gensym.charts.tests;

import gensym.charts.Chart3D;
import gensym.charts.actions.CreateChartAction;
import gensym.charts.legend.ChartLegend;
import gensym.charts.GraphChart;

import org.jfree.chart.plot.XYPlot;

/**
 * Tests ChartLegend class
 */
public class ChartLegendTest extends TestChartBase {

    /**
     * Tests ChartLegend class
     */
    public final void testChartLegend() {
        ChartLegend legend = new ChartLegend(null);
        assertNotNull(legend);
        legend = new ChartLegend(new XYPlot());
        assertNotNull(legend);
        assertEquals(legend.getStyle(), ChartLegend.STYLE_1_LINE);
        legend.setStyle(ChartLegend.STYLE_1_LINE);
        assertEquals(legend.getStyle(), ChartLegend.STYLE_1_LINE);

        legend.setStyle(ChartLegend.STYLE_2_LINE);
        assertEquals(legend.getStyle(), ChartLegend.STYLE_2_LINE);

        legend.setStyle(ChartLegend.STYLE_1_LINE_INSIDE_AXIS);
        assertEquals(legend.getStyle(), ChartLegend.STYLE_1_LINE_INSIDE_AXIS);

        legend.setStyle(ChartLegend.STYLE_1_LINE_TOP_OF_AXIS);
        assertEquals(legend.getStyle(), ChartLegend.STYLE_1_LINE_TOP_OF_AXIS);
        legend.setVisible(false);
        assertFalse(legend.isVisible());

        legend.setStyle(ChartLegend.STYLE_1_LINE_LEFT_OF_AXIS);
        assertEquals(legend.getStyle(), ChartLegend.STYLE_1_LINE_LEFT_OF_AXIS);
        legend.setVisible(true);
        assertTrue(legend.isVisible());

        legend.setStyle(ChartLegend.STYLE_1_LINE_INSIDE_OVERLAP);
        assertEquals(legend.getStyle(), ChartLegend.STYLE_1_LINE_INSIDE_OVERLAP);

        legend.setStyle(Integer.MAX_VALUE);
        assertEquals(legend.getStyle(), ChartLegend.STYLE_1_LINE_INSIDE_OVERLAP);
    }

    /**
     * Tests legend-style property
     */
    public final void testLegendStyleProperty() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        assertNotNull(getChart());
        assertEquals(GraphChart.class, getChart().getClass());
        GraphChart chart = (GraphChart) getChart();
        try {
            // legend-style
            int value = ChartLegend.STYLE_1_LINE_INSIDE_AXIS;
            runAction("SetInt", "property", 2975, "i", 0, "j", 0, "value", value);
            assertEquals(chart.getChart().getLegend().getClass(), ChartLegend.class);
            ChartLegend legend = (ChartLegend) chart.getChart().getLegend();
            assertNotNull(legend);
            assertEquals(legend.getStyle(), value);
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests show-legend property
     */
    public final void testLegendShowProperty() {
        doCreateAction(CreateChartAction.PE_3D_CHART);
        assertNotNull(getChart());
        assertEquals(Chart3D.class, getChart().getClass());
        Chart3D chart = (Chart3D) getChart();
        try {
            // show-legend
            runAction("SetInt", "property", 2666, "i", 0, "j", 0, "value", 1);
            assertNotNull(chart.getChart().getLegend());
            assertTrue(chart.getChart().getLegend().isVisible());
            runAction("SetInt", "property", 2666, "i", 0, "j", 0, "value", 0);
            assertFalse(chart.getChart().getLegend().isVisible());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
}
