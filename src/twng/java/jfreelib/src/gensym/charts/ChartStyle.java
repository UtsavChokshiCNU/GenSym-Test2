package gensym.charts;

import gensym.charts.gradients.*;
import org.jfree.chart.*;
import java.awt.*;

/**
 * Chart style class
 */
public class ChartStyle extends DefaultChartStyle {

    /**
     * Color of the desk
     */
    protected Color chartColor = null;

    /**
     * Color of the charts background
     */
    protected Color plotColor = null;

    /**
     * Values of the chart/plot(desk/graph) gradients
     */
    protected GradientsContainer gradients = new GradientsContainer();

    /**
     * {@inheritDoc}
     */
    public ChartStyle(AbstractChart chart) {
        super(chart);
    }

    /**
     * Sets chart color
     * @param color of the chart
     */
    public void setChartColor(Color color) {
        chartColor = color;
    }

    /**
     * Gets chart color
     * @return chart color
     */
    public Color getChartColor() {
        return chartColor;
    }

    /**
     * Sets plot color
     * @param color of the plot
     */
    public void setPlotColor(Color color) {
        plotColor = color;
    }

    /**
     * Gets plot color
     * @return plot color
     */
    public Color getPlotColor() {
        return plotColor;
    }

    /**
     * Checks if color is transparent
     * @param cl color
     * @return true, if transparent
     */
    public boolean isColorTransparent(Color cl) {
        return cl != null && ChartsCommon.convertBGRtoRGB(cl.getRGB()) == 1;
    }

    /**
     * Getter of gradients
     * @return container of the gradients
     */
    public GradientsContainer getGradients() {
        return gradients;
    }

    /**
     * Checks if gradient required
     * @param cl color of the field
     * @param values of the gradient proprieties
     * @return true, if gradient needed
     */
    public boolean isGradientNeeded(Color cl, GradientValues values) {
        return isColorTransparent(cl) && isGradientMode() && values.isGradientNeeded();
    }

    /**
     * {@inheritDoc}
     */
    protected Paint getChartBackground(ChartRenderingInfo info) {
        if (isGradientNeeded(chartColor, getGradients().getChartGradient())) {
            return GradientStyle.getGradientPaint(info.getChartArea(), getGradients().getChartGradient());
        }
        return chartColor == null || isColorTransparent(chartColor) ? super.getChartBackground(info) : chartColor;
    }

    /**
     * {@inheritDoc}
     */
    protected Paint getPlotBackground(ChartRenderingInfo info) {
        if (isGradientNeeded(plotColor, getGradients().getPlotGradient())) {
            return GradientStyle.getGradientPaint(info.getPlotInfo().getDataArea(), getGradients().getPlotGradient());
        } else if (isColorTransparent(plotColor) &&
                isGradientNeeded(chartColor, getGradients().getChartGradient())) {
            return null;
        }
        return plotColor == null || isColorTransparent(plotColor) ? super.getPlotBackground(info) : plotColor;
    }
}
