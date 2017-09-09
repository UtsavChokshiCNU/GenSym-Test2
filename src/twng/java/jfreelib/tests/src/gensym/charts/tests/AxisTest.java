package gensym.charts.tests;

import java.awt.Color;
import java.text.FieldPosition;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TimeZone;

import org.jfree.chart.axis.LogarithmicAxis;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.XYPlot;

import gensym.charts.ChartsCommon;
import gensym.charts.GraphChart;
import gensym.charts.ScientificChart;
import gensym.charts.actions.CreateChartAction;
import gensym.charts.axis.GraphAxesProvider;
import gensym.charts.axis.StringNumberFormat;
import gensym.charts.axis.TimeNumberFormat;
import gensym.charts.properties.axis.ShowYAxisProperty;

/**
 * Tests axis
 */
public class AxisTest extends TestChartBase {

    /**
     * Tests StringNumberFormat
     */
    public final void testStringNumberFormat() {
        StringNumberFormat format = new StringNumberFormat(null);
        assertNull(format.parse(null, null));
        format.setSource(new StringNumberFormat.DataSource() {
            public int indexOf(double value) {
                return -1;
            }
            public Double getValue(int index) {
                return null;
            }
        });
        assertNull(format.format(444, null, null));
        assertNotNull(format.getSource());
    }

    /**
     * Tests getLabels(), setLabel() functions
     */
    public final void testLabels() {
        StringNumberFormat format = new StringNumberFormat(null);
        assertNull(format.parse(null, null));
        format.setSource(new StringNumberFormat.DataSource() {
            public int indexOf(double value) {
                return 1;
            }
            public Double getValue(int index) {
                return 1.0;
            }
        });
        format.setLabel(1, "1");
        format.setLabel(2, "23");

        Map<Double, String> map = format.getLabels();
        assertNotNull(map);
        assertEquals(map.get(1.0), "23");

    }

    /**
     * Tests TimeNumberFormat
     */
    public final void testTimeNumberFormat() {
        TimeZone bakTimeZone = TimeZone.getDefault();
        TimeZone.setDefault(TimeZone.getTimeZone("GMT+0"));
        assertNull((new TimeNumberFormat()).parse(null, null));
        StringBuffer buff = (new TimeNumberFormat()).format((long) 44444,
                new StringBuffer("test"), new FieldPosition(34));
        String value = "test9/4/21 10:00 PM";
        assertEquals(value, buff.toString());
        TimeZone.setDefault(bakTimeZone);
    }

    /**
     * Tests x-axis-label, y-axis-label props
     */
    public final void testXYAxisLabel() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        assertTrue(getChart() instanceof GraphChart);
        GraphChart chart = (GraphChart) getChart();
        XYPlot plot = chart.getPlot().getCurrentPlot();
        assertNotNull(plot);
        try {
            // super(3000, "x-axis-label"),   super(3005, "y-axis-label");
            String label1 = "Hello World!", label2 = "dwwefweeweeeeee";

            // x-axis-labels
            runAction("SetString", "property", 3000, "i", 0, "j", 0, "value", label1);
            assertEquals(plot.getDomainAxis().getLabel(), label1);

            // y-axis-label
            runAction("SetString", "property", 3005, "i", 0, "j", 0, "value", label2);
            assertEquals(plot.getRangeAxis().getLabel(), label2);

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests start-time, show-y-axis, delta-x, force-vertical-points props
     */
    public final void testProps() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        assertTrue(getChart() instanceof GraphChart);
        GraphChart chart = (GraphChart) getChart();
        XYPlot plot = chart.getPlot().getCurrentPlot();
        assertNotNull(plot);
        ValueAxis axis = plot.getRangeAxis();
        try {
            double value = 34455.4543;
            // start-time
            runAction("SetDouble", "property", 3098, "i", 0, "j", 0, "value", value);
            assertEquals(chart.getStartTime(), value);

            // show-y-axis
            int yAxisValue = ShowYAxisProperty.PESA_GRIDNUMBERS;
            runAction("SetInt", "property", 3027, "i", 0, "j", 0, "value", yAxisValue);
            assertTrue(axis.isTickLabelsVisible());
            assertTrue(axis.isTickMarksVisible());

            yAxisValue = ShowYAxisProperty.PESA_AXIS_LABELS;
            runAction("SetInt", "property", 3027, "i", 0, "j", 0, "value", yAxisValue);
            assertTrue(axis.isTickLabelsVisible());
            assertFalse(axis.isTickMarksVisible());

            yAxisValue = ShowYAxisProperty.PESA_LABELONLY;
            runAction("SetInt", "property", 3027, "i", 0, "j", 0, "value", yAxisValue);
            assertFalse(axis.isTickLabelsVisible());
            assertFalse(axis.isTickMarksVisible());

            // delta-x
            int deltaX = 5555;
            runAction("SetInt", "property", 3096, "i", 0, "j", 0, "value", deltaX);
            assertEquals(chart.getDeltaX(), deltaX);

            // deltas-per-day
            int deltas = 3444;
            runAction("SetInt", "property", 3097, "i", 0, "j", 0, "value", deltas);
            assertEquals(chart.getDeltasPerDay(), deltas);

            // force-vertical-points
            runAction("SetInt", "property", 3345, "i", 0, "j", 0, "value", 1);
            assertTrue(plot.getDomainAxis().isVerticalTickLabels());
            runAction("SetInt", "property", 3345, "i", 0, "j", 0, "value", 0);
            assertFalse(plot.getDomainAxis().isVerticalTickLabels());

            // manual-max-y
            value = 555.666;
            runAction("SetDouble", "property", 3060, "i", 0, "j", 0, "value", value);
            assertEquals(plot.getRangeAxis().getUpperBound(), value);

            // manual-min-y
            value = 666.555;
            runAction("SetDouble", "property", 3055, "i", 0, "j", 0, "value", value);
            assertEquals(plot.getRangeAxis().getLowerBound(), value);

            // manual-scale-controly
            runAction("SetInt", "property", 3050, "i", 0, "j", 0, "value", 0);
            assertTrue(plot.getRangeAxis().isAutoRange());
            runAction("SetInt", "property", 3050, "i", 0, "j", 0, "value", 3);
            assertFalse(plot.getRangeAxis().isAutoRange());

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests y-axis-color, tick-color props
     */
    public final void testColorProps() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        assertTrue(getChart() instanceof GraphChart);
        GraphChart chart = (GraphChart) getChart();
        XYPlot plot = chart.getPlot().getCurrentPlot();
        assertNotNull(plot);

        try {
            // y-axis-color
            int axisColor = 444;
            Color axisPaint = new Color(ChartsCommon.convertBGRtoRGB(axisColor));

            runAction("SetInt", "property", 3036, "i", 0, "j", 0, "value", axisColor);
            assertEquals(axisPaint, plot.getRangeAxis().getLabelPaint());
            assertEquals(axisPaint, plot.getRangeAxis().getTickLabelPaint());

            // tick-color
            int tickColor = 555;
            Color tickPaint = new Color(ChartsCommon.convertBGRtoRGB(tickColor));
            runAction("SetInt", "property", 3159, "i", 0, "j", 0, "value", tickColor);
            assertEquals(tickPaint, plot.getDomainAxis().getTickMarkPaint());
            assertEquals(tickPaint, plot.getRangeAxis().getTickMarkPaint());

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Tests multiaxes properties
     */
    public void testMultiaxes() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        assertTrue(getChart() instanceof GraphChart);
        GraphChart chart = (GraphChart) getChart();

        try {
            // multi-axes-subsets
            int subsets = 2;
            runAction("SetInt", "property", 3001, "i", 0, "j", 0, "value", subsets);
            assertEquals(1, chart.getPlot().getAllPlots().size());
            runAction("SetInt", "property", 3001, "i", 1, "j", 0, "value", subsets);
            assertEquals(2, chart.getPlot().getAllPlots().size());
            
            // working-axis
            int working = 1;
            runAction("SetInt", "property", 3006, "i", 0, "j", 0, "value", working);
            assertEquals(chart.getPlot().getPlot(working), chart.getPlot().getCurrentPlot());
            assertEquals(chart.getPlot().getPlot(working), chart.getPlot().getCurrentPlot());
            working = 0;
            runAction("SetInt", "property", 3006, "i", 0, "j", 0, "value", working);
            assertEquals(chart.getPlot().getPlot(working), chart.getPlot().getCurrentPlot());
            assertEquals(chart.getPlot().getPlot(working), chart.getPlot().getCurrentPlot());
            
            //overlap-multi-axes
            runAction("SetInt", "property", 3059, "i", 0, "j", 0, "value", 2);
            runAction("Update");
            assertEquals(1, chart.getPlot().getAllPlots().size());
            assertEquals(chart.getPlot().getPlot(0), chart.getPlot().getCurrentPlot());
            assertEquals(2, chart.getPlot().getPlot(0).getRangeAxisCount());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Tests scale control axis
     */
    public void testScaleControlAxis() {
    	doCreateAction(CreateChartAction.PE_SCIENTIFIC_CHART);
        assertTrue(getChart() instanceof ScientificChart);
        ScientificChart chart = (ScientificChart) getChart();
        GraphAxesProvider provider = new GraphAxesProvider();
        
        try {
        	// auto scaling x axis
        	List<Double> range = new ArrayList<Double>();
        	range.add(0d);
       	    range.add(10e3d - 1);
            chart.setValuesX(range);
            provider.createAxisByScaleControl(chart, 0, GraphAxesProvider.AXIS_X);
        	assertTrue(chart.getPlot().getDomainAxis() instanceof NumberAxis);
        	assertFalse(chart.getPlot().getDomainAxis() instanceof LogarithmicAxis);
        	
        	range = new ArrayList<Double>();
        	range.add(0d);
        	range.add(10e3d);
            chart.setValuesX(range);
            provider.createAxisByScaleControl(chart, 0, GraphAxesProvider.AXIS_X);
            assertTrue(chart.getPlot().getDomainAxis() instanceof LogarithmicAxis);

            // auto scaling y axis
        	range = new ArrayList<Double>();
            range.add(0d);
       	    range.add(10e3d - 1);
            chart.setValuesY(range);
            provider.createAxisByScaleControl(chart, 0, GraphAxesProvider.AXIS_Y);
        	assertTrue(chart.getPlot().getCurrentPlot().getRangeAxis() instanceof NumberAxis);
        	assertFalse(chart.getPlot().getCurrentPlot().getRangeAxis() instanceof LogarithmicAxis);
        	
        	range = new ArrayList<Double>();
        	range.add(0d);
        	range.add(10e3d);
            chart.setValuesY(range);
            provider.createAxisByScaleControl(chart, 0, GraphAxesProvider.AXIS_Y);
            assertTrue(chart.getPlot().getCurrentPlot().getRangeAxis() instanceof LogarithmicAxis);

        	// normal scale axis
            provider.createAxisByScaleControl(chart, 1, GraphAxesProvider.AXIS_X);
        	assertTrue(chart.getPlot().getDomainAxis() instanceof NumberAxis);
        	assertFalse(chart.getPlot().getDomainAxis() instanceof LogarithmicAxis);
        	provider.createAxisByScaleControl(chart, 1, GraphAxesProvider.AXIS_Y);
        	assertTrue(chart.getPlot().getCurrentPlot().getRangeAxis() instanceof NumberAxis);
        	assertFalse(chart.getPlot().getCurrentPlot().getRangeAxis() instanceof LogarithmicAxis);

        	// log scale axis
        	provider.createAxisByScaleControl(chart, 2, GraphAxesProvider.AXIS_X);
        	assertTrue(chart.getPlot().getDomainAxis() instanceof LogarithmicAxis);
        	provider.createAxisByScaleControl(chart, 2, GraphAxesProvider.AXIS_Y);
        	assertTrue(chart.getPlot().getCurrentPlot().getRangeAxis() instanceof LogarithmicAxis);

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
}
    }
}
