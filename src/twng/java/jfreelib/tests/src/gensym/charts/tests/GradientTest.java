package gensym.charts.tests;

import gensym.charts.ChartsCommon;
import gensym.charts.actions.CreateChartAction;
import gensym.charts.gradients.*;

import java.awt.*;
import java.awt.geom.Rectangle2D;

/**
 * Tests gensym.charts.gradients package
 */
public class GradientTest extends TestChartBase {
    /**
     * GradientValues for test
     */
    private GradientValues values = new GradientValues();
    /**
     * Rectangle, needed for getGradientPaint
     */
    private Rectangle2D rect = new Rectangle(1, 2, 3, 4);
    /**
     * Rectangle with 0 values, needed for getGradientPaint
     */
    private Rectangle2D rectNull = new Rectangle(1, 2, 0, 0);

    /**
     * Tests GradientValues
     */
    public final void testGradientValues() {
        values = new GradientValues();
        Color start = null;
        Color end = null;
        int style = 0;

        assertEquals(values.getStyle(), style);
        assertEquals(values.getStart(), start);
        assertEquals(values.getEnd(), end);
        assertFalse(values.isGradientNeeded());

        start = Color.ORANGE;
        end = Color.YELLOW;
        style = GradientStyle.PEGS_LINEAR_BAR_UP;

        initGradientValues(values, start, end, style);

        assertEquals(values.getStyle(), style);
        assertEquals(values.getStart(), start);
        assertEquals(values.getEnd(), end);
        assertTrue(values.isGradientNeeded());
    }

    /**
     * Tests GradientsContainer
     */
    public final void testGradientsContainer() {
        GradientsContainer container = new GradientsContainer();
        Color start = Color.RED;
        Color end = Color.GRAY;
        int style = 346;

        container.setDeskGradientStart(start);
        container.setDeskGradientEnd(end);
        container.setDeskGradientStyle(style);

        container.setGraphGradientStart(start);
        container.setGraphGradientEnd(end);
        container.setGraphGradientStyle(style);

        assertEquals(container.getChartGradient().getStart(), container.getPlotGradient().getStart());
        assertEquals(container.getChartGradient().getEnd(), container.getPlotGradient().getEnd());
        assertEquals(container.getChartGradient().getStyle(), container.getPlotGradient().getStyle());
    }

    /**
     * Tests GradientStyle
     */
    public final void testGradientStyle() {
        assertNotNull(new GradientStyle());

        initGradientValues(values, Color.RED, Color.GRAY, GradientStyle.PEGS_NO_GRADIENT);
        assertNull(GradientStyle.getGradientPaint(rect, values));

        initGradientValues(values, Color.RED, Color.GRAY, GradientStyle.PEGS_VERTICAL);
        assertNotNull(GradientStyle.getGradientPaint(rect, values));
        assertNull(GradientStyle.getGradientPaint(rectNull, values));

        initGradientValues(values, Color.RED, Color.GRAY, GradientStyle.PEGS_HORIZONTAL);
        assertNotNull(GradientStyle.getGradientPaint(rect, values));

        initGradientValues(values, Color.RED, Color.GRAY, GradientStyle.PEGS_LINEAR_BAR_VERTICAL);
        assertNotNull(GradientStyle.getGradientPaint(rect, values));

        initGradientValues(values, Color.RED, Color.GRAY, GradientStyle.PEGS_LINEAR_BAR_HORIZONTAL);
        assertNotNull(GradientStyle.getGradientPaint(rect, values));

        initGradientValues(values, Color.RED, Color.GRAY, GradientStyle.PEGS_LINEAR_BAR_DOWN);
        assertNotNull(GradientStyle.getGradientPaint(rect, values));

        initGradientValues(values, Color.RED, Color.GRAY, GradientStyle.PEGS_LINEAR_BAR_UP);
        assertNotNull(GradientStyle.getGradientPaint(rect, values));

        initGradientValues(values, Color.RED, Color.GRAY, GradientStyle.PEGS_LINEAR_DIAGONAL_DOWN);
        assertNotNull(GradientStyle.getGradientPaint(rect, values));

        initGradientValues(values, Color.RED, Color.GRAY, GradientStyle.PEGS_LINEAR_DIAGONAL_UP);
        assertNotNull(GradientStyle.getGradientPaint(rect, values));

        initGradientValues(values, Color.RED, Color.GRAY, GradientStyle.PEGS_RECTANGLE_CROSS);
        // Need to implement PEGS_RECTANGLE_CROSS style
        assertNull(GradientStyle.getGradientPaint(rect, values));

        initGradientValues(values, Color.RED, Color.GRAY, GradientStyle.PEGS_RECTANGLE_PLUS);
        // Need to implement PEGS_RECTANGLE_PLUS style
        assertNull(GradientStyle.getGradientPaint(rect, values));

        initGradientValues(values, Color.RED, Color.GRAY, GradientStyle.PEGS_RADIAL_CENTERED);
        assertNotNull(GradientStyle.getGradientPaint(rect, values));

        initGradientValues(values, Color.RED, Color.GRAY, GradientStyle.PEGS_RADIAL_BOTTOM_RIGHT);
        assertNotNull(GradientStyle.getGradientPaint(rect, values));

        initGradientValues(values, Color.RED, Color.GRAY, GradientStyle.PEGS_RADIAL_TOP_RIGHT);
        assertNotNull(GradientStyle.getGradientPaint(rect, values));

        initGradientValues(values, Color.RED, Color.GRAY, GradientStyle.PEGS_RADIAL_BOTTOM_LEFT);
        assertNotNull(GradientStyle.getGradientPaint(rect, values));

        initGradientValues(values, Color.RED, Color.GRAY, GradientStyle.PEGS_RADIAL_TOP_LEFT);
        assertNotNull(GradientStyle.getGradientPaint(rect, values));

        // Tests default style
        initGradientValues(values, Color.RED, Color.GRAY, 999);
        assertNull(GradientStyle.getGradientPaint(rect, values));
    }

    /**
     * Tests setting gradient properties
     */
    public final void testGradientProperties() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);
        GradientsContainer container = getHolder().getStyle().getGradients();

        try {
            int testColor1 = 23523, testColor2 = 2132,
                    testColor3 = 666623, testColor4 = 9992,
                    style = GradientStyle.PEGS_LINEAR_BAR_HORIZONTAL;
            Color color1 = new Color(ChartsCommon.convertBGRtoRGB(testColor1));
            Color color2 = new Color(ChartsCommon.convertBGRtoRGB(testColor2));
            Color color3 = new Color(ChartsCommon.convertBGRtoRGB(testColor3));
            Color color4 = new Color(ChartsCommon.convertBGRtoRGB(testColor4));

            // bitmap-gradient-mode
            runAction("SetInt", "property", 2703, "i", 0, "j", 0, "value", 1);

            //desk-gradient-start
            runAction("SetInt", "property", 2687, "i", 0, "j", 0, "value", testColor1);
            assertEquals(container.getChartGradient().getStart(), color1);

            //desk-gradient-end
            runAction("SetInt", "property", 2688, "i", 0, "j", 0, "value", testColor2);
            assertEquals(container.getChartGradient().getEnd(), color2);

            //desk-gradient-style
            runAction("SetInt", "property", 2689, "i", 0, "j", 0, "value", style);
            assertEquals(container.getChartGradient().getStyle(), style);

            //graph-gradient-start
            runAction("SetInt", "property", 2692, "i", 0, "j", 0, "value", testColor3);
            assertEquals(container.getPlotGradient().getStart(), color3);

            //graph-gradient-end
            runAction("SetInt", "property", 2693, "i", 0, "j", 0, "value", testColor4);
            assertEquals(container.getPlotGradient().getEnd(), color4);

            //graph-gradient-style
            runAction("SetInt", "property", 2694, "i", 0, "j", 0, "value", style);
            assertEquals(container.getPlotGradient().getStyle(), style);

        } catch (Exception ex) {
            fail("Exception during running: " + ex.getMessage());
        }
    }

    /**
     * Initialize gradient values
     * @param values to init
     * @param start color
     * @param end color
     * @param style style
     */
    private void initGradientValues(GradientValues values, Color start, Color end, int style) {
        values.setStart(start);
        values.setEnd(end);
        values.setStyle(style);
    }
}
