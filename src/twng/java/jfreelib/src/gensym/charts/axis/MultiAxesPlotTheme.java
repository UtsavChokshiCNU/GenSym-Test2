package gensym.charts.axis;

import org.jfree.chart.StandardChartTheme;
import org.jfree.chart.plot.XYPlot;

public class MultiAxesPlotTheme extends StandardChartTheme {
    /**
     * Constructor
     */
    public MultiAxesPlotTheme() {
        super("JCharts");
    }

    /**
     * Generated serial version UID
     */
    private static final long serialVersionUID = 7783051885903905630L;

    /**
     * Sets plot view settings
     * @param plot the plot
     */
    public void processPlot(XYPlot plot) {
        applyToPlot(plot);
    }
}
