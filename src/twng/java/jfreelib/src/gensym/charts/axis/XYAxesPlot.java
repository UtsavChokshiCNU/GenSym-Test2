package gensym.charts.axis;

import java.awt.Paint;
import java.util.*;
import java.util.Vector;
import gensym.charts.hatching.HatchedPaint;

import org.jfree.chart.axis.*;
import org.jfree.chart.plot.*;
import org.jfree.chart.renderer.xy.*;
import org.jfree.data.xy.*;
import org.jfree.util.PublicCloneable;

import gensym.charts.SourceXYZDataset;

/**
 * Axes plot, used in MultiAxesPlot
 */
public class XYAxesPlot extends XYPlot {
    
    /** Generated serial version UID*/
    private static final long serialVersionUID = -803749907299246930L;

    /** Source datasets */
    private Vector<SourceXYZDataset> datasets = new Vector<SourceXYZDataset>();

    /** Map of series assigned to concrete axis (axis index => list of series) */
    protected Map<Integer, List<SeriesInfo>> axisSeries = new HashMap<Integer, List<SeriesInfo>>();

    /**
     * Constructor
     * @param dataset  the dataset (<code>null</code> permitted).
     * @param domainAxis  the domain axis (<code>null</code> permitted).
     * @param rangeAxis  the range axis (<code>null</code> permitted).
     * @param renderer  the renderer (<code>null</code> permitted).
     */
    public XYAxesPlot(SourceXYZDataset dataset,
            ValueAxis domainAxis,
            ValueAxis rangeAxis,
            XYItemRenderer renderer) {
        super(null, domainAxis, rangeAxis, renderer);
        setDataset(dataset);
    }

    /**
     * Returns list of series for specified axis
     * @param index axis index
     * @return modifiable list of series for specified axis
     */
    protected List<SeriesInfo> getSeriesForAxis(int index) {
        List<SeriesInfo> series = axisSeries.get(index);
        if (series == null) {
            series = new LinkedList<SeriesInfo>();
            axisSeries.put(index, series);
        }
        return series;
    }
    
    /**
     * Clear axes map and axes dataset
     */
    public void clearAxesSeries() {
        datasets.clear();
        axisSeries.clear();
    }
    
    /**
     * Adds series info to axis
     * @param axis axis index
     * @param info series info
     */
    public void addSeriesToAxis(int axis, SeriesInfo info) {
        getSeriesForAxis(axis).add(info);
    }
    
    
    /**
     * Updates plot
     */
    public void updatePlot() {
        setNotify(false);
        
        clearDatasets();
        clearRenderers(true);
        updateSeries();

        setNotify(true);
    }
    
    /**
     * Updates series
     */
    protected void updateSeries() {
        setRangeAxesCount(getAxesCount());
        for (Integer axis : getAxes()) {
            processAxis(axis);
        }
    }
    
    /**
     * Returns axes count
     * @return axes count
     */
    public int getAxesCount() {
        return Collections.max(getAxes()) + 1;
    }
    
    /**
     * Returns collection that contains axes indexes
     * @return axes indexes collection
     */
    protected Collection<Integer> getAxes() {
        return axisSeries.keySet();
    }
    
    /**
     * Process axis
     * @param axis axis number
     */
    protected void processAxis(int axis) {
        Map<Integer, List<SeriesInfo>> renderersMap = collectSeriesRenderers(getSeriesForAxis(axis));
        List<Integer> renderers = new LinkedList<Integer>(renderersMap.keySet());
        Collections.sort(renderers);
        for (Integer rendererId : renderers) {
            List<SeriesInfo> series = renderersMap.get(rendererId);
            processRenderer(axis, series);
        }
    }
    
    /**
     * Get list of series indexes
     * @param original list of original items that contains all series info for axis
     * @param series list of series to be processed
     * @return list of series indexes
     */
    protected List<Integer> getSeriesList(List<SeriesInfo> original, List<SeriesInfo> series) {
        List<Integer> list = new ArrayList<Integer>(series.size());
        for (SeriesInfo info : series) {
            list.add(original.indexOf(info));
        }
        return list;
    }
    
    /**
     * Builds plot, assigns renderer and series
     * @param axis axis index
     * @param series series list
     */
    protected void processRenderer(int axis, List<SeriesInfo> series) {
        MultiAxesDataset dataset = new MultiAxesDataset(getAxisDataset(axis));
        dataset.setItems(getSeriesList(getSeriesForAxis(axis), series));

        XYItemRenderer renderer = getRenderer(axis != 0, series);
        if (axis == 0 && renderer == getRenderer()) {
            setDataset(0, dataset);
        } else {
            int index = getFirstRendererIndex();
            setDataset(index, dataset);
            setRenderer(index, renderer);
            
            mapDatasetToRangeAxis(index, axis);
        }

        setUpRenderer(renderer, series);
    }

    /**
     * Sets up renderer data (series color, stroke, shape etc)
     * @param renderer renderer
     * @param series series list
     */
    protected void setUpRenderer(XYItemRenderer renderer, List<SeriesInfo> series) {
        if (renderer != null) {
            int index = 0;
            boolean isHatched = false;

            for (SeriesInfo info : series) {
                Paint paint = info.getPaint();
                if (paint instanceof HatchedPaint) {
                    HatchedPaint hatched = (HatchedPaint) paint;
                    if (renderer instanceof XYBarRenderer) {
                        isHatched = true;
                    } else {
                        paint = hatched.getForegroundColor();
                    }
                }
                
                renderer.setSeriesPaint(index, paint);
                renderer.setSeriesStroke(index, info.getStroke());
                
                if (renderer instanceof XYLineAndShapeRenderer) {
                    XYLineAndShapeRenderer renderer2 = (XYLineAndShapeRenderer) renderer;
                    renderer2.setSeriesShapesVisible(index, info.isShapeVisible());
                    renderer2.setSeriesShape(index, info.getShape());
                    renderer2.setSeriesShapesFilled(index, info.isShapeFilled());
                }
                
                index++;
            }

            // set up hatched bars
            if (renderer instanceof XYBarRenderer) {
                XYBarRenderer br = (XYBarRenderer) renderer; 
                if (isHatched) {
                    br.setBarPainter(new StandardXYBarPainter());
                } else {
                    br.setBarPainter(new GradientXYBarPainter());
                }
            }
        }
    }

    /**
     * Returns renderer for series list
     * @param clone clone default renderer if is true
     * @param series series list
     * @return renderer for series list
     */
    private XYItemRenderer getRenderer(boolean clone, List<SeriesInfo> series) {
        XYItemRenderer renderer = null;
        if (series.size() > 0 && series.get(0).getRenderer() != null) {
            renderer = series.get(0).getRenderer();
        } else if (clone && getRenderer() instanceof PublicCloneable) {
            try {
                PublicCloneable pc = (PublicCloneable) getRenderer();
                renderer = (XYItemRenderer) pc.clone();
            } catch (CloneNotSupportedException e) {
                renderer = getRenderer();
            }
        } else {
            renderer = getRenderer();
        }
        return renderer;
    }
    
    /**
     * Assign series with the same renderer type and the single renderer
     * @param series series list
     * @return map (renderer Id => corresponding series)
     */
    private Map<Integer, List<SeriesInfo>> collectSeriesRenderers(List<SeriesInfo> series) {
        Map<Integer, List<SeriesInfo>> renderers = new HashMap<Integer, List<SeriesInfo>>();
        for (SeriesInfo info : series) {
            List<SeriesInfo> list = renderers.get(info.getRendererId());
            if (list == null) {
                list = new LinkedList<SeriesInfo>();
                renderers.put(info.getRendererId(), list);
            }
            list.add(info);
        }
        return renderers;
    }
    
    /**
     * {@inheritDoc}
     */
    public final void setDataset(XYDataset dataset) {
        if (dataset instanceof SourceXYZDataset) {
            setAxisDataset(0, (SourceXYZDataset) dataset);
        }
    }
    
    /**
     * Assign dataset with specified axis
     * @param axis axis index
     * @param dataset the corresponding dataset
     */
    public void setAxisDataset(int axis, SourceXYZDataset dataset) {
        if (datasets.size() <= axis) {
            datasets.setSize(axis + 1);
        }
        datasets.set(axis, dataset);
    }

    /**
     * {@inheritDoc}
     */
    public IntervalXYDataset getDataset() {
        return getAxisDataset(0);
    }

    /**
     * Returns dataset for specified axis
     * @param axis axis index
     * @return the corresponding dataset
     */
    public SourceXYZDataset getAxisDataset(int axis) {
        if (axis < datasets.size()) {
            return datasets.get(axis);
        }
        return null;
    }

    /**
     * Clean up datasets
     */
    private void clearDatasets() {
        for (int i = 0; i < getDatasetCount(); i++) {
            setDataset(i, null);
        }
    }
    
    /**
     * Clean up renderers
     * @param keepFirst indicates whether it needs to keep first renderer
     */
    private void clearRenderers(boolean keepFirst) {
        if (!keepFirst) {
            setRenderer(0, null, false);
        }
        
        for (int i = 1; i < getRendererCount(); i++) {
            setRenderer(i, null, false);
        }
    }
    
    /**
     * Calculates index of first free renderer
     * @return
     */
    private int getFirstRendererIndex() {
        int index = 0;
        while (index < getRendererCount() && getRenderer(index) != null) {
            index++;
        }
        return index;
    }


    /**
     * Sets count of range axes
     * @param count the count of range axes
     */
    private void setRangeAxesCount(int count) {
        for (int i = 0; i < count; i++) {
            if (getRangeAxis(i) == null) {
                setRangeAxis(i, new NumberAxis(), false);
            }
            if (getRangeAxisLocation(i) != AxisLocation.BOTTOM_OR_LEFT) {
                setRangeAxisLocation(i, AxisLocation.BOTTOM_OR_LEFT);
            }
        }

        for (int i = count; i < getRangeAxisCount(); i++) {
            setRangeAxis(i, null, false);
        }
    }
}
