package gensym.charts.tests;

import junit.framework.TestCase;
import gensym.charts.*;
import gensym.charts.actions.ChartActionsFactory;
import gensym.charts.actions.IChartAction;
import org.w3c.dom.Element;

/**
 * <p>
 * Test cases for Chart action factory functionality.
 * </p>
 *
 */

public class ChartActionsFactoryTest extends TestCase {
    /**
     * Test for {@code ChartActionsFactory.makeAction()}.
     */
    public final void testMakeAction() {
        assertNotNull(new ChartActionsFactory());
        createActionTest("CreateChart", true);
        createActionTest("123", false);
    }

    /**
     * Test for {@code ChartActionsFactory.registerAction()}.
     */
    public final void testRegisterAction() {
        IChartAction action = new IChartAction() {
            public void setData(Element data) throws ChartActionException {}
            public void execute(JFreeChartHolder chart) throws ChartActionException {}
            public Object clone() throws CloneNotSupportedException { return super.clone(); }
            public String getName() { return "UnitTestAction"; }
            public boolean isChartRequired() { return false; }
        };

        ChartActionsFactory.registerAction(action);
        createActionTest(action.getName(), true);

        IChartAction action2 = new IChartAction() {
            public void setData(Element data) throws ChartActionException {}
            public void execute(JFreeChartHolder chart) throws ChartActionException {}
            public Object clone() throws CloneNotSupportedException {
                throw new CloneNotSupportedException();
            }
            public String getName() { return "UnitTestAction2"; }
            public boolean isChartRequired() { return false; }
        };

        ChartActionsFactory.registerAction(action2);
        createActionTest(action2.getName(), false);
    }

    /**
     * Tests creation action by name
     * @param name action name
     * @param isValid flag indicates if action with specified shouild be exists
     */
    private void createActionTest(String name, boolean isValid) {
        try {
            IChartAction action = ChartActionsFactory.makeAction(name);
            assertNotNull(action);
            assertEquals(name, action.getName());
            assertTrue("There should be exception for invalid action", isValid);
        } catch (ChartActionsFactory.ChartActionsFactoryException ex) {
            assertFalse("Create action exception: " + ex.getMessage(), isValid);
        }
    }
}
