package gensym.charts.scrolling;

import java.util.ArrayList;
import java.util.List;

import gensym.charts.SourceXYZDataset;

import org.jfree.data.general.DatasetChangeEvent;
import org.jfree.data.general.DatasetChangeListener;
import org.jfree.data.xy.AbstractIntervalXYDataset;
import org.jfree.data.xy.TableXYDataset;

public class ScrollingDataset extends AbstractIntervalXYDataset
            implements TableXYDataset, DatasetChangeListener, SourceXYZDataset {
    /**
     * Generated serial version UID
     */
    private static final long serialVersionUID = 7093974142741961552L;
    
    /**
     * Source dataset
     */
    private SourceXYZDataset dataset;
    
    /**
     * Visible items
     */
    private List<Integer> items = null;
    
    /**
     * Constructor
     * @param dataset the source dataset
     */
    public ScrollingDataset(SourceXYZDataset dataset) {
        this.dataset = dataset;
        dataset.addChangeListener(this);
    }
    
    /**
     * Sets visible items
     * @param items list of visible items
     */
    public void setItems(List<Integer> items) {
        if (items != null && items.size() > 0) {
            this.items = new ArrayList<Integer>(items);
        } else {
            this.items = null;
        }
        fireDatasetChanged();
    }

    /**
     * {@inheritDoc}
     */
    public int getSeriesCount() {
        return dataset.getSeriesCount();
    }

    /**
     * {@inheritDoc}
     */
    public Comparable<?> getSeriesKey(int series) {
        return dataset.getSeriesKey(series);
    }

    /**
     * {@inheritDoc}
     */
    public Number getEndX(int series, int item) {
        if (items == null || items.contains(series)) {
            return dataset.getEndX(series, item);
        }
        return null;
    }

    /**
     * {@inheritDoc}
     */
    public Number getEndY(int series, int item) {
        if (items == null || items.contains(series)) {
            return dataset.getEndY(series, item);
        }
        return null;
    }

    /**
     * {@inheritDoc}
     */
    public Number getStartX(int series, int item) {
        if (items == null || items.contains(series)) {
            return dataset.getStartX(series, item);
        }
        return null;
    }

    /**
     * {@inheritDoc}
     */
    public Number getStartY(int series, int item) {
        if (items == null || items.contains(series)) {
            return dataset.getStartY(series, item);
        }
        return null;
    }

    /**
     * {@inheritDoc}
     */
    public int getItemCount(int series) {
        if (items == null || items.contains(series)) {
            return dataset.getItemCount(series);
        }
        return 0;
    }

    /**
     * {@inheritDoc}
     */
    public Number getX(int series, int item) {
        if (items == null || items.contains(series)) {
            return dataset.getX(series, item);
        }
        return null;
    }

    /**
     * {@inheritDoc}
     */
    public Number getY(int series, int item) {
        if (items == null || items.contains(series)) {
            return dataset.getY(series, item);
        }
        return null;
    }

    /**
     * {@inheritDoc}
     */
    public int getItemCount() {
        return dataset.getSeriesCount() > 0 ? dataset.getItemCount(0) : 0;
    }

    /**
     * {@inheritDoc}
     */
    public void datasetChanged(DatasetChangeEvent event) {
        fireDatasetChanged();
    }

    /**
     * {@inheritDoc}
     */
    public Number getZ(int series, int item) {
        if (items == null || items.contains(series)) {
            return dataset.getZ(series, item);
        }
        return null;
    }

    /**
     * {@inheritDoc}
     */
    public double getZValue(int series, int item) {
        double result = Double.NaN;
        Number z = getZ(series, item);
        if (z != null) {
            result = z.doubleValue();
        }
        return result;
    }
}
