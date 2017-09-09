package gensym.charts.actions;

import gensym.charts.*;
import org.w3c.dom.Element;

/**
 * Create chart action class.
 * Creates JFree chart.
 * XML data tags:
 *  <b>title</b> - chart title
 *  <b>type</b> - chart type
 *  <b>x</b> and <b>y</b> - chart position
 *  <b>width</b> and <b>height</b> - chart sizes 
 */
public class CreateChartAction implements IChartAction {

    /** Chart simple type constant */
    public static final int PE_GRAPH_CHART = 300;

    /** Chart polar type constant */
    public static final int PE_PIE_CHART = 302;

    /** Chart scientific type constant */
    public static final int PE_SCIENTIFIC_CHART = 304;

    /** Chart polar type constant */
    public static final int PE_POLAR_CHART = 308;

    /** Chart 3D type constant */
    public static final int PE_3D_CHART = 312;

    /** Chart title */
    private String title;

    /** Chart type */
    private int type;

    /** Chart x position */
    private int x;
    /** Chart y position */
    private int y;

    /** Chart width */
    private int width;
    /** Chart height */
    private int height;

    /** Chart handle */
    private int handle;

    /**
     * {@inheritDoc}
     */
    public void setData(Element data) throws ChartActionException {
        title = ChartsCommon.getElementValue(data, "title");
        type = ChartsCommon.getIntValue(data, "type");
        x = Math.max(ChartsCommon.getIntValue(data, "x"), 0);
        y = Math.max(ChartsCommon.getIntValue(data, "y"), 0);
        width = ChartsCommon.getIntValue(data, "width");
        height = ChartsCommon.getIntValue(data, "height");

        handle = ChartsCommon.getIntValue(data, "handle"); 
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
        return "CreateChart";
    }

    /**
     * {@inheritDoc}
     * Creates chart according to type. 
     */
    public void execute(JFreeChartHolder holder) throws ChartActionException {
        if (width <= 0 || height <= 0) {
            width = JFreeChartHolder.DEFAULT_WIDTH;
            height = JFreeChartHolder.DEFAULT_HEIGHT;
        }

        AbstractChart chart = null;
        if (type == PE_GRAPH_CHART) {
            chart = new GraphChart(title);
        } else if (type == PE_POLAR_CHART) {
            chart = new PolarChart(title);
        } else if (type == PE_PIE_CHART) {
            chart = new PieChart(title);
        } else if (type == PE_SCIENTIFIC_CHART) {
            chart = new ScientificChart(title);
        } else if (type == PE_3D_CHART) {
            chart = new Chart3D(title);
        } else {
            throw new ChartActionException("Unknown chart type: " + type); 
        }
        holder = JFreeChartHolder.makeHolder(handle);
        holder.createChartView(chart, x, y, width, height);
    }

    /**
     * {@inheritDoc}
     * Returns false.
     */
    public boolean isChartRequired() {
        return false;
    }
}
