package gensym.charts.axis;

import org.jfree.chart.axis.*;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.Range;

import gensym.charts.ScientificChart;

public class GraphAxesProvider {
    
    /**
     * X axis constant
     */
    public static final int AXIS_X = 1000;
    
    /**
     * Y axis constant
     */
    public static final int AXIS_Y = 1001;
    
    /**
     * Z axis constant
     */
    public static final int AXIS_Z = 1002;
    
    /**
     * Auto scaling axis
     */
    private static final int PEAC_AUTO = 0;
    
    /**
     * Normal scale axis
     */
    private static final int PEAC_NORMAL = 1;
    
    /**
     * Log scale axis
     */
    private static final int PEAC_LOG = 2;
    
    
    /**
     * Create graph axis according to the scale control property
     * @param graph the graph
     * @param value the scale control property value
     * @param axisType the axis type
     */
    public void createAxisByScaleControl(
            ScientificChart graph, int value, int axisType) {
        
        XYPlot plot = null;
        if (axisType == AXIS_X)
            plot = graph.getPlot();
        else if (axisType == AXIS_Y)
            plot = graph.getPlot().getCurrentPlot();
        
        switch (value) {
        case PEAC_LOG:
            createLogarithmicAxis(plot, axisType);
            break;
        case PEAC_NORMAL:
            createNumberAxis(plot, axisType);
            break;
        case PEAC_AUTO:
            Range range = null;
            if (axisType == AXIS_X)
                range = plot.getDataRange(plot.getDomainAxis());
            else if (axisType == AXIS_Y)
                range = plot.getDataRange(plot.getRangeAxis());
            
            if (range.getUpperBound() - range.getLowerBound() >= 10e3)
                createLogarithmicAxis(plot, axisType);
            else
                createNumberAxis(plot, axisType);
            break;
        default:
            break;
        }
    }
        
    /**
     * Create number axis for the plot
     * @param plot the plot
     * @param axisType the axis type
     */
    private void createNumberAxis(XYPlot plot, int axisType) {
        NumberAxis axis = new NumberAxis();
        axis.setAutoRangeIncludesZero(false);
        updateAxis(plot, axis, axisType);
    }
    
    /**
     * Create log axis for the plot
     * @param plot the plot
     * @param axisType the axis type
     */
    private void createLogarithmicAxis(XYPlot plot, int axisType) {
        LogarithmicAxis axis = new LogarithmicAxis("");
        axis.setExpTickLabelsFlag(true);
        axis.setStrictValuesFlag(false);
        updateAxis(plot, axis, axisType);
    }
    
    /**
     * Update axis for the plot
     * @param plot the plot
     * @param axis the axis
     * @param axisType the axis type
     */
    private void updateAxis(XYPlot plot, NumberAxis axis, int axisType) {
        ValueAxis oldAxis = null;
        if (axisType == AXIS_X) 
            oldAxis = plot.getDomainAxis();
        else if (axisType == AXIS_Y)
            oldAxis = plot.getRangeAxis();
        
        axis.setLabelPaint(oldAxis.getLabelPaint());
        axis.setTickLabelPaint(oldAxis.getTickLabelPaint());
        axis.setLabel(oldAxis.getLabel());
        axis.setLabelFont(oldAxis.getLabelFont().deriveFont(14.0f));
        axis.setTickLabelFont(oldAxis.getTickLabelFont().deriveFont(14.0f));
        
        if (axisType == AXIS_X) {
            plot.setDomainAxis(axis);
        } else if (axisType == AXIS_Y) {
            axis.setTickLabelsVisible(oldAxis.isTickLabelsVisible());
            axis.setTickMarksVisible(oldAxis.isTickMarksVisible());
            plot.setRangeAxis(axis);
        }
    }

}
