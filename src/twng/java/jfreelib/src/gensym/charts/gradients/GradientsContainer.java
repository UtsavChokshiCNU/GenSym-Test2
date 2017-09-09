package gensym.charts.gradients;

import java.awt.Color;

public class GradientsContainer {
    /**
     * Values of the chart(desk) gradient
     */
    protected GradientValues chartGradient = new GradientValues();

    /**
     * Values of the plot(graph) gradient
     */
    protected GradientValues plotGradient = new GradientValues();

    /**
     * Getter for chartGradient
     * @return chartGradient
     */
    public GradientValues getChartGradient() {
        return chartGradient;
    }

    /**
     * Gets plot gradient values
     * @return plotGradient
     */
    public GradientValues getPlotGradient() {
        return plotGradient;
    }

    /**
     * Sets chart gradient start color
     * @param start color
     */
    public void setDeskGradientStart(Color color) {
        chartGradient.setStart(color);
    }

    /**
     * Sets chart gradient end color
     * @param start color
     */
    public void setDeskGradientEnd(Color color) {
        chartGradient.setEnd(color);
    }

    /**
     * Sets chart gradient style
     * @param desk style
     */
    public void setDeskGradientStyle(int style) {
        chartGradient.setStyle(style);
    }

    /**
     * Sets plot gradient start color
     * @param start color
     */
    public void setGraphGradientStart(Color color) {
        plotGradient.setStart(color);
    }

    /**
     * Sets plot gradient end color
     * @param end color
     */
    public void setGraphGradientEnd(Color color) {
        plotGradient.setEnd(color);
    }

    /**
     * Sets plot gradient end color
     * @param graph style
     */
    public void setGraphGradientStyle(int style) {
        plotGradient.setStyle(style);
    }

}
