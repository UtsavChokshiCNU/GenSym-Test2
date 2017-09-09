package gensym.charts.actions;

import gensym.charts.JFreeChartHolder;

import org.w3c.dom.Element;

public class UpdateChartAction implements IChartAction {
    /**
     * {@inheritDoc}
     */
    public void execute(JFreeChartHolder chart) throws ChartActionException {
        chart.getChart().updateChart();
        chart.updateChartView();
        chart.updateChartData();
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
        return "Update";
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
