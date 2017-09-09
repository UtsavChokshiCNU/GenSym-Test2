package gensym.charts;

import gensym.charts.hatching.HatchedPaint;
import gensym.charts.legend.ChartLegend;
import gensym.charts.subtitles.MultiSubtitle;
import gensym.charts.scrolling.ChartScrolling;

import java.awt.*;
import java.awt.geom.Rectangle2D;
import java.awt.event.MouseAdapter;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.jfree.chart.*;
import org.jfree.chart.axis.*;
import org.jfree.chart.block.LineBorder;
import org.jfree.chart.editor.ChartEditor;
import org.jfree.ui.RectangleEdge;
import org.jfree.ui.RectangleInsets;
import org.jfree.chart.title.TextTitle;

/**
 * Abstract chart class
 */
public abstract class AbstractChart {
    /**
     * Item count per each series
     */
    private int itemCount = Integer.MAX_VALUE;

    /**
     * Chart object
     */
    private JFreeChart chart = null;
    
    /**
     * Null data value for X axis.
     */
    private Double nullX = null;

    /**
     * Null data value for Y axis.
     */
    private Double nullY = null;

    /**
     * Null data gaps flag
     */
    private boolean nullDataGaps = false;

    /**
     * Chart name
     */
    protected String name;

    /**
     * Sub title of the chart
     */
    private MultiSubtitle subTitle = new MultiSubtitle("", RectangleEdge.TOP);
    
    /**
     * Storage for series colors 
     */
    private Map<Integer, Color> subsetsColors = new HashMap<Integer, Color>();;

    /** 
     * Storage for series hatch styles 
     */
    private Map<Integer, HatchedPaint> subsetsHatch = new HashMap<Integer, HatchedPaint>();

    /** 
     * Hatch background color 
     */
    protected Color hatchBackgroundColor = Color.WHITE;

    /**
     * Constructor
     * @param chart chart object
     */
    public AbstractChart(JFreeChart chart) {
        this.chart = chart;
        
        chart.addSubtitle(0, subTitle);
        
        // set up legends
        if (chart.getLegend() != null) {
            chart.removeLegend();
        }
        ChartLegend legend = new ChartLegend(chart.getPlot());
        legend.setMargin(new RectangleInsets(1.0, 1.0, 1.0, 1.0));
        legend.setFrame(new LineBorder());
        legend.setBackgroundPaint(null);
        legend.setPosition(RectangleEdge.TOP);
        
        chart.addLegend(legend);
    }
    
    /**
     * Return chart object
     * @return chart
     */
    public JFreeChart getChart() {
        return chart;
    }
    
    /**
     * Returns chart name
     * @return the name
     */
    public String getName() {
    	return name;
    }
    /**
     * Return active charts
     * @return charts
     */
    public JFreeChart[] getCharts() {
        return new JFreeChart[] {chart};
    }
    
    /**
     * Returns item count
     * @return item count per each series
     */
    public int getItemCount() {
        return itemCount;
    }

    /**
     * Sets item count
     * @param count item count per each series
     */
    public void setItemCount(int count) {
        itemCount = count;
    }

    /**
     * Indicates whether table view is supported for this chart
     * @return true if table view is supported 
     */
    public boolean isTableSupported() {
        return false;
    }
    
    /**
     * Sets null data value for X axis. 
     * @param x X axis null data value
     */
    public void setNullDataValueX(double x) {
        nullX = new Double(x);
    }

    /**
     * Sets null data value for Y axis. 
     * @param y Y axis null data value
     */
    public void setNullDataValueY(double y) {
        nullY = new Double(y);
    }
    
    /**
     * Tests if point is null
     * @param x x value
     * @param y y value
     * @return true if point is less than null value
     */
    protected boolean isNullXY(double x, double y) {
        return isNullX(x) || isNullY(y); 
    }

    /**
     * Tests if point Y value is null
     * @param y y value
     * @return true if point Y value is less than null value
     */
    protected boolean isNullY(double y) {
        return nullY != null && nullY.doubleValue() >= y; 
    }
    
    /**
     * Tests if point X value is null
     * @param x x value
     * @return true if point X value is less than null value
     */
    protected boolean isNullX(double x) {
        return nullX != null && nullX.doubleValue() >= x; 
    }

    /**
     * Process mouse clicked event
     * @param holder the chart holder
     * @param paramChartMouseEvent data
     */
    public void chartMouseClicked(JFreeChartHolder holder, ChartMouseEvent paramChartMouseEvent) {
    }

    /**
     * Process mouse moved event
     * @param holder chart holder object
     * @param paramChartMouseEvent data
     */
    public void chartMouseMoved(JFreeChartHolder holder, ChartMouseEvent paramChartMouseEvent) {
    }

   /**
     * Sets series count
     * @param count series count
     */
    public abstract void setSeriesCount(int count);

    /**
     * Sets X data
     * @param values x data list
     */
    public abstract void setValuesX(List<Double> values);
    
    /**
     * Sets X value
     * @param series series index
     * @param index point index
     * @param value new X value
     */
    public void setValueX(int series, int index, double value) {
    }

    /**
     * Sets Y data
     * @param values Y data list
     */
    public abstract void setValuesY(List<Double> values);
    
    /**
     * Sets Y value
     * @param series series index
     * @param index point index
     * @param value new Y value
     */
    public void setValueY(int series, int index, double value) {
    }
    
    /**
     * Sets series label
     * @param series series number (zero based)
     * @param label series label
     */
    public abstract void setSeriesLabel(int series, String label);
    
    /**
     * Sets series line type
     * @param series series number (zero based)
     * @param lineType line type (see ChartLineTypes class)
     */
    public abstract void setSeriesLineType(int series, int lineType);
    
    /**
     * Sets series color
     * @param series series number (zero based)
     * @param color the new series color
     */
    public void setSeriesColor(int series, Color color) {
        subsetsColors.put(series, color);
    }
    
    /**
     * Sets series hatch style
     * @param series series number (zero based)
     * @param hatch series hatch mask
     */
    public void setSeriesHatch(int series, int hatch) {
        if (subsetsHatch.containsKey(series)) {
            HatchedPaint paint = subsetsHatch.get(series);
            paint.setHatchStyleMask(hatch);
        } else {
            Color color = null;
            if (subsetsColors.containsKey(series)) {
                color = subsetsColors.get(series);
            }
            subsetsHatch.put(series, new HatchedPaint(hatch, color, hatchBackgroundColor));
        }
    }
    
    /**
     * Sets hatch background color
     * @param color the new hatch background color
     */
    public void setHatchBackColor(Color color) {
        hatchBackgroundColor = color;
    }
    
    /**
     * Returns background paint
     * @param color1, color2 gradient colors
     * @param info chart rendering info
     * @return paint background paint
     */
    public Paint getBackgroundPaint(Color color1, Color color2, ChartRenderingInfo info) {
        Rectangle2D area = info.getChartArea();
        return new GradientPaint((float) area.getX(), (float) area.getY(), color1,
                (float) area.getX() + (float) area.getWidth(), (float) area.getY() + (float) area.getHeight(), color2);
    }
    
    /**
     * Returns list of chart axes
     * @return list of chart axes
     */
    protected abstract Axis[] getAxesList();
    
    /**
     * Sets chart axis color
     * @param color axis color
     */
    public void setAxisColor(Color color) {
        for (Axis axis : getAxesList()) {
            axis.setAxisLinePaint(color);
            axis.setLabelPaint(color);
            axis.setTickLabelPaint(color);
        }
    }
    
    /**
     * Show chart grid line
     * @param showXAxis flag indicates whether it needs to show X axis grid
     * @param showYAxis flag indicates whether it needs to show Y axis grid
     */
    public abstract void showGridLines(boolean showXAxis, boolean showYAxis);
    
    /**
     * Sets point label
     * @param point point index
     * @param label point label
     */
    public void setPointLabel(int point, String label) {
    }
    
    /**
     * Sets shadow effects
     * @param shadow use shadow effect
     * @param shadow3d use 3d effect
     */
    public void setDataShadows(boolean shadow, boolean shadow3d) {
    }
    
    /**
     * Shows legend
     * @param show showing flag
     */
    public void showLegend(boolean show) {
        if (getChart().getLegend() != null) {
            getChart().getLegend().setVisible(show);
        }
    }
    
    /**
     * Sets chart subtitle
     * @param subtitle chart subtitle
     */
    public void setSubtitle(String subtitle) {
        subTitle.setSubtitleText(subtitle);
    }
    
    /**
     * Gets chart subtitle
     * @return chart subtitle
     */
    public TextTitle[] getSubtitle() {
        return subTitle.getSubtitleText();
    }
    
    /**
     * Updates chart
     */
    public void updateChart() {
        updatePaints();
    }
    
    /**
     * Updates series paints
     */
    private void updatePaints() {
        Map<Integer, Paint> paints = new HashMap<Integer, Paint>();
        
        for (Integer series : subsetsHatch.keySet()) {
            HatchedPaint hatch = subsetsHatch.get(series);
            hatch.setForegroundColor(subsetsColors.get(series));
            hatch.setBackgroundColor(hatchBackgroundColor);
            paints.put(series, hatch);
        }
        for (Integer series : subsetsColors.keySet()) {
            if (!paints.containsKey(series)) {
                paints.put(series, subsetsColors.get(series));
            }
        }
        updatePaints(paints);
    }

    /**
     * Updates series colors
     * @param paints series paint map
     */
    protected abstract void updatePaints(Map<Integer, Paint> paints);

    /**
     * Tests if null data gaps flag is set
     * @return true if null data gaps flag is set
     */
    public boolean isNullDataGaps() {
        return nullDataGaps;
    }
    
    /**
     * Makes chart editor
     * @return the chart editor
     */
    public ChartEditor makeChartEditor() {
    	return null;
    }

    /**
     * Sets null data gaps flag
     * @param enabled the null data gaps enabling flag
     */
    public void setNullDataGaps(boolean enabled) {
        nullDataGaps = enabled;
    }
    
    /**
     * Returns vertical scrolling interface
     * @return scrolling interface (can be null).
     */
    public ChartScrolling getVerticalScrollingInterface() {
        return null;
    }

    /**
     * Returns horizontal scrolling interface
     * @return scrolling interface (can be null).
     */
    public ChartScrolling getHorizontalScrollingInterface() {
        return null;
    }

    /**
     * Gets MouseAdapter
     * @return MouseAdapter class instance
     */
    public MouseAdapter getMouseAdapter() {
        return null;
    }
}
