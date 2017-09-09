package gensym.charts.actions;

import gensym.charts.*;
import org.w3c.dom.Element;

public class DestroyChartAction implements IChartAction {

    /**
     * {@inheritDoc}
     */
    public void execute(JFreeChartHolder chart) throws ChartActionException {
        chart.dispose();
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
        return "Destroy";
    }

    /**
     * {@inheritDoc}
     */
    public boolean isChartRequired() {
        return true;
    }

    /**
     * {@inheritDoc}
     */
    public void setData(Element data) throws ChartActionException {
    }
}
