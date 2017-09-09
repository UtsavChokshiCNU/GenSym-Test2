package gensym.charts.tests;

import junit.framework.TestCase;
import gensym.charts.*;
import gensym.charts.actions.IChartAction;

/**
 * <p>
 * Test cases for Chart classes functionality.
 * </p>
 */
public class ChartsTest extends TestCase {
    /**
     * Test for {@code ChartRunner} class.
     */
    public final void testChartRunner() {
        assertNotNull(new ChartsRunner());
        ChartsRunner.main(new String[0]);
        ChartsRunner.main(new String[]{"error"});
    }

    /**
     * Test for {@code ChartsCommon} class.
     */
    public final void testChartsCommon() {
        assertNotNull(new ChartsCommon());

        try {
            ChartsCommon.getIntValue("12f");
            fail("Exception should be thrown");
        } catch (IChartAction.ChartActionException e) {
        }

        try {
            ChartsCommon.getDoubleValue("12tt");
            fail("Exception should be thrown");
        } catch (IChartAction.ChartActionException e) {
        }
    }
}
