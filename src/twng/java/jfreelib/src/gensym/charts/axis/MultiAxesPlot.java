package gensym.charts.axis;

import java.awt.Paint;
import java.awt.Stroke;
import java.util.*;

import gensym.charts.SourceXYZDataset;

import org.jfree.chart.annotations.XYAnnotation;
import org.jfree.chart.axis.AxisLocation;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.CombinedDomainXYPlot;
import org.jfree.chart.plot.Marker;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.XYItemRenderer;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;
import org.jfree.data.Range;
import org.jfree.data.xy.XYDataset;
import org.jfree.ui.Layer;
import org.jfree.util.PublicCloneable;

public class MultiAxesPlot extends CombinedDomainXYPlot {
    /** Generated serial version UID */
    private static final long serialVersionUID = -9029808456967677818L;
    
    /** Plot Theme */
    public static final MultiAxesPlotTheme PLOT_THEME = new MultiAxesPlotTheme();

    /** Renderer */
    private XYItemRenderer itemRenderer;
    
    /** Current axis index */
    private int workingAxis = 0;

    /** Series indexes list */
    private Vector<Integer> series = new Vector<Integer>();
    
    /** Axes indexes list */
    private Vector<Integer> axes = new Vector<Integer>();
    
    /** Series info map (series index => info) */
    protected Map<Integer, SeriesInfo> seriesInfo = new HashMap<Integer, SeriesInfo>();

    /** Dataset */
    private SourceXYZDataset dataset;
    
    /**
     * Constructor
     * @param domainAxis the domain axis
     */
    public MultiAxesPlot(ValueAxis domainAxis) {
        super(domainAxis);
        setPlotCount(1);
        setRenderer(new XYLineAndShapeRenderer(true, false));
    }

    /**
     * Returns all plots
     * @return list of plots
     */
    public final List<XYAxesPlot> getAllPlots() {
        List<XYAxesPlot> plots = new LinkedList<XYAxesPlot>();
        
        for (Object obj : getSubplots()) {
            if (obj instanceof XYAxesPlot) {
                plots.add((XYAxesPlot) obj);
            }
        }
        return plots;
    }
    
    /**
     * Returns plot by index
     * @param index the plot index
     * @return plot or null if index is invalid
     */
    public XYAxesPlot getPlot(int index) {
        if (index >= 0 && index < getSubplots().size()) {
            return (XYAxesPlot) getSubplots().get(index);
        }
        return null;
    }
    
    /**
     * Returns current plot
     * @return the current plot
     */
    public XYAxesPlot getCurrentPlot() {
        return getPlot(getPlotIndex(workingAxis));
    }
    
    /**
     * Returns current axis
     * @return the current axis
     */
    public ValueAxis getCurrentAxis() {
        XYAxesPlot plot = getCurrentPlot();
        if (plot != null) {
            int axis = getAxisIndex(workingAxis);
            return plot.getRangeAxis(axis);
        }
        return null;
    }
    
    /**
     * Sets current working axis
     * @param index the working axis index
     */
    public void setWorkingAxis(int index) {
        workingAxis = index;
    }

    /**
     * Returns index of plot assigned to working axis 
     * @param axis working axis index
     * @return corresponding plot index
     */
    private int getPlotIndex(int axis) {
        return getIndex(axis, true);
    }
    
    /**
     * Returns index of plot or axis assigned to working axis
     * @param axis working axis index
     * @param isPlotIndex
     * @return index of plot or axis
     */
    private int getIndex(int axis, boolean isPlotIndex) {
        int axisCount = 0;
        int plot = 0;
        for (Integer index : getAxesList()) {
            if (axis >= axisCount && axis < index + axisCount) {
                return isPlotIndex ? plot : axis - axisCount;
            }
            axisCount += index;
            plot++;
        }
        return 0;
    }
    
    /**
     * Returns index of range axis of current plot
     * @param axis working axis index
     * @return axis index
     */
    private int getAxisIndex(int axis) {
        return getIndex(axis, false);
    }
    
    /**
     * {@inheritDoc}
     */
    public void setOutlineStroke(Stroke stroke) {
        super.setOutlineStroke(stroke);
        
        for (XYPlot plot : getAllPlots()) {
            plot.setOutlineStroke(stroke);
        }
    }
    
    /**
     * {@inheritDoc}
     */
    public void setBackgroundPaint(Paint paint) {
        super.setBackgroundPaint(paint);
        
        for (XYPlot plot : getAllPlots()) {
            plot.setBackgroundPaint(paint);
        }
    }
    
    /**
     * {@inheritDoc}
     */
    public List<XYAnnotation> getAnnotations() {
        List<XYAnnotation> annotations = new LinkedList<XYAnnotation>();
        for (XYPlot plot : getAllPlots()) {
            for (Object obj : plot.getAnnotations()) {
                annotations.add((XYAnnotation) obj);
            }
        }
        return annotations;
    }
    
    /**
     * {@inheritDoc}
     */
    public boolean removeAnnotation(XYAnnotation annotation, boolean notify) {
        for (XYPlot plot : getAllPlots()) {
            if (plot.removeAnnotation(annotation, notify)) {
                return true;
            }
        }
        return false;
    }
    
    /**
     * {@inheritDoc}
     */
    public void clearRangeMarkers() {
        for (XYPlot plot : getAllPlots()) {
            plot.clearRangeMarkers();
        }
    }
    
    /**
     * {@inheritDoc}
     */
    public Collection<?> getRangeMarkers(Layer layer) {
        List<Marker> markers = new LinkedList<Marker>();
        for (XYPlot plot : getAllPlots()) {
            Collection<?> plotMarkers = plot.getRangeMarkers(layer);
            if (plotMarkers != null) {
                for (Object obj : plot.getRangeMarkers(layer)) {
                    markers.add((Marker) obj);
                }
            }
        }
        return markers;
    }
    
    /**
     * {@inheritDoc}
     */
    public final void setRenderer(XYItemRenderer renderer) {
        itemRenderer = renderer;

        for (XYPlot plot : getAllPlots()) {
            plot.setRenderer(cloneRenderer());
        }
        
        fireChangeEvent();
    }
    
    /**
     * {@inheritDoc}
     */
    public XYItemRenderer getRenderer() {
        return itemRenderer;
    }
    
    /**
     * {@inheritDoc}
     */
    public void setDataset(XYDataset dataset) {
        if (dataset instanceof SourceXYZDataset) {
            this.dataset = (SourceXYZDataset) dataset;
            updateItems();
        }
    }
    
    /**
     * {@inheritDoc}
     */
    public XYDataset getDataset() {
        return dataset;
    }
    
    /**
     * Updates items
     */
    public void updateItems() {
        if (getDataset() == null) {
            return;
        }
        
        setPlotCount(calculatePlotCount());
        
        clearAllPlots();
        
        if (series.isEmpty()) {
            List<Integer> items = new ArrayList<Integer>(dataset.getSeriesCount());
            for (int i = 0; i < dataset.getSeriesCount(); i++) {
                items.add(i);
            }
            setPlotItems(0, 0, items);
        } else {
            int axisIndex = 0;
            int plotIndex = 0;
            for (Integer axisItem : getAxesList()) {
                processPlot(plotIndex++, axisIndex, axisItem);
                axisIndex += axisItem;
            }
        }
        
        updateAllPlots();
        fireChangeEvent();
    }
    
    /**
     * Updates all plots
     */
    protected void updateAllPlots() {
        for (XYAxesPlot plot : getAllPlots()) {
            plot.updatePlot();
        }
    }

    /**
     * Updates all plots
     */
    protected void clearAllPlots() {
        for (XYAxesPlot plot : getAllPlots()) {
            plot.clearAxesSeries();
        }
    }

    /**
     * 
     * @param plotIndex
     * @param startAxis
     * @param axesCount
     */
    private void processPlot(int plotIndex, int startAxis, int axesCount) {
        int startIndex = getAxisStartIndex(startAxis);
        
        for (int i = 0; i < axesCount && i + startAxis < series.size(); i++) {
            List<Integer> items = new LinkedList<Integer>();
            int count = series.get(i);
            for (int j = 0; j < count; j++) {
                items.add(startIndex + j);
            }
            setPlotItems(plotIndex, i, items);
            
            startIndex += count;
        }
    }

    /**
     * @param startAxis
     * @return
     */
    private int getAxisStartIndex(int startAxis) {
        int startIndex = 0;
        for (int i = 0; i < startAxis && i < series.size(); i++) {
            startIndex += series.get(i);
        }
        return startIndex;
    }
    
    /**
     * Calculates plots count depending on count of axes
     * @return Calculated plots count
     */
    protected int calculatePlotCount() {
        if (!series.isEmpty()) {
            return axes.isEmpty() ? series.size() : axes.size();
        }
        return 1;
    }
    
    /**
     * Sets plot items
     * @param plotIndex plot index
     * @param axisIndex axis index
     * @param items plot items assigned to axis
     */
    private void setPlotItems(int plotIndex, int axisIndex, List<Integer> items) {
        XYAxesPlot plot = getPlot(plotIndex);
        if (plot != null) {
            MultiAxesDataset dataset = new MultiAxesDataset(this.dataset);
            dataset.setItems(items);
            plot.setAxisDataset(axisIndex, dataset);
            
            for (Integer series : items) {
                plot.addSeriesToAxis(axisIndex, getSeriesInfo(series));
            }
        }
    }
    
    /**
     * Sets plot count
     * @param count plot count
     */
    private void setPlotCount(int count) {
        List<XYAxesPlot> plots = getAllPlots();
        int size = plots.size();
        if (size == count) {
            return;
        }
        
        while (size > count) {
            remove(plots.get(size - 1));
            size--;
        }
        
        while (size < count) {
            NumberAxis yAxis = new NumberAxis();
            yAxis.setAutoRangeIncludesZero(false);

            Range range = new Range(-Double.MAX_VALUE, Double.MAX_VALUE);
            yAxis.setDefaultAutoRange(range);
            yAxis.setAutoRange(true);
        	
            XYAxesPlot plot = new XYAxesPlot(null, null, yAxis, cloneRenderer());
            plot.setOrientation(PlotOrientation.VERTICAL);
            plot.setRangeAxisLocation(AxisLocation.BOTTOM_OR_LEFT);
            
            PLOT_THEME.processPlot(plot);
            
            add(plot);
            size++;
        }
    }
    
    /**
     * Clone current renderer
     * @return cloned renderer
     */
    private XYItemRenderer cloneRenderer() {
        XYItemRenderer renderer = itemRenderer;
        if (itemRenderer instanceof PublicCloneable) {
            try {
                PublicCloneable pc = (PublicCloneable) itemRenderer;
                renderer = (XYItemRenderer) pc.clone();
            } catch (CloneNotSupportedException e) {
                ;
            }
        }
        return renderer;
    }
    
    /**
     * Sets plot series count
     * @param plot plot index
     * @param count series count
     */
    public void setPlotSeries(int plot, int count) {
        if (series.size() <= plot) {
            series.setSize(plot + 1);
        }
        Integer old = series.get(plot);
        if (old == null || old != count) {
            series.set(plot, count);
            updateItems();
        }
    }
    
    /**
     * Overlaps axes
     * @param axis axis index
     * @param count axes count
     */
    public void overlapAxes(int axis, int count) {
        if (axes.size() <= axis) {
            axes.setSize(axis + 1);
        }
        Integer old = axes.get(axis);
        if (old == null || old != count) {
            axes.set(axis, count);
            updateItems();
        }
    }
    
    /**
     * Sets series paints
     * @param paints paints map
     */
    public void setSeriesPaints(Map<Integer, Paint> paints) {
        for (Map.Entry<Integer, Paint> entry : paints.entrySet()) {
            getSeriesInfo(entry.getKey()).setPaint(entry.getValue());
        }
    }
    
    /**
     * Sets series stroke
     * @param index series index
     * @param stroke the new series stroke
     */
    public void setSeriesStroke(int index, Stroke stroke) {
        getSeriesInfo(index).setStroke(stroke);
    }
    
    /**
     * Returns axes list
     * @return axes list
     */
    protected List<Integer> getAxesList() {
        return axes.isEmpty() ? Collections.nCopies(series.size(), 1) : axes;
    }
    
    /**
     * Returns series info
     * @param index series index
     * @return series info
     */
    public SeriesInfo getSeriesInfo(int index) {
        SeriesInfo info = seriesInfo.get(index);
        if (info == null) {
            info = new SeriesInfo();
            seriesInfo.put(index, info);
        }
        return info;
    }
}
