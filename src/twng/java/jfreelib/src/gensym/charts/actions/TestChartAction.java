package gensym.charts.actions;

import gensym.charts.JFreeChartHolder;

import org.w3c.dom.Element;

/**
 * Test message class. Does nothing.
 */
public class TestChartAction implements IChartAction {
    /**
     * {@inheritDoc}
     * Does nothing.
     */
    public void setData(Element data) throws ChartActionException {
    }

    /**
     * {@inheritDoc}
     */
    public Object clone() throws CloneNotSupportedException {
        return super.clone();
    }

    /**
     * {@inheritDoc}
     */
    public String getName() {
        return "Test";
    }

    /**
     * {@inheritDoc}
     * Does nothis.
     */
    public void execute(JFreeChartHolder chart) throws ChartActionException {
    }

    /**
     * {@inheritDoc}
     * Returns false.
     */
    public boolean isChartRequired() {
        return false;
    }
}