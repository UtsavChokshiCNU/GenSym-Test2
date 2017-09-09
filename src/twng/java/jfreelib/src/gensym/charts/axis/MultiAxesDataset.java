package gensym.charts.axis;

import java.util.ArrayList;
import java.util.List;

import org.jfree.data.general.DatasetChangeEvent;
import org.jfree.data.general.DatasetChangeListener;
import org.jfree.data.xy.AbstractIntervalXYDataset;
import org.jfree.data.xy.TableXYDataset;

import gensym.charts.SourceXYZDataset;

public class MultiAxesDataset extends AbstractIntervalXYDataset
            implements TableXYDataset, DatasetChangeListener, SourceXYZDataset {
    /**
     * Generated serial version UID
     */
    private static final long serialVersionUID = 5602868202778724844L;

    /**
     * Source dataset
     */
    private SourceXYZDataset dataset;
    
    /**
     * Visible items
     */
    private List<Integer> items = null;
    
    /**
     * Visible items
     */
    private List<Integer> originalItems = null;

    /**
     * Constructor
     * @param dataset the source dataset
     */
    public MultiAxesDataset(SourceXYZDataset dataset) {
        this.dataset = dataset;
        dataset.addChangeListener(this);
    }
    
    /**
     * Sets visible items
     * @param items list of visible items
     */
    public void setItems(List<Integer> items) {
        if (items != null && items.size() > 0) {
            originalItems = new ArrayList<Integer>(items);
        } else {
            originalItems = null;
        }
        datasetChanged(null);
    }

    /**
     * {@inheritDoc}
     */
    public int getSeriesCount() {
        return items != null ? items.size() : 0;
    }
    
    /**
     * Update series indexes
     */
    private void updateSeries() {
        if (originalItems != null) {
            items = new ArrayList<Integer>(originalItems.size());
            for (Integer series : originalItems) {
                if (series >= 0 && series < dataset.getSeriesCount()) {
                    items.add(series);
                }
            }
        } else {
            items = null;
        }
    }

    /**
     * {@inheritDoc}
     */
    public Comparable<?> getSeriesKey(int series) {
        if (isSeriesValid(series)) {
            return dataset.getSeriesKey(items.get(series));
        }
        return null;
    }
    
    /**
     * Tests if series index is valid
     * @param series the series index
     * @return true if series index is valid
     */
    private boolean isSeriesValid(int series) {
        return series >= 0 && series < getSeriesCount() && items.get(series) < dataset.getSeriesCount(); 
    }

    /**
     * {@inheritDoc}
     */
    public Number getEndX(int series, int item) {
        if (isSeriesValid(series)) {
            return dataset.getEndX(items.get(series), item);
        }
        return null;
    }

    /**
     * {@inheritDoc}
     */
    public Number getEndY(int series, int item) {
        if (isSeriesValid(series)) {
            return dataset.getEndY(items.get(series), item);
        }
        return null;
    }

    /**
     * {@inheritDoc}
     */
    public Number getStartX(int series, int item) {
        if (isSeriesValid(series)) {
            return dataset.getStartX(items.get(series), item);
        }
        return null;
    }

    /**
     * {@inheritDoc}
     */
    public Number getStartY(int series, int item) {
        if (isSeriesValid(series)) {
            return dataset.getStartY(items.get(series), item);
        }
        return null;
    }

    /**
     * {@inheritDoc}
     */
    public int getItemCount(int series) {
        if (isSeriesValid(series)) {
            return dataset.getItemCount(items.get(series));
        }
        return 0;
    }

    /**
     * {@inheritDoc}
     */
    public Number getZ(int series, int item) {
        if (isSeriesValid(series)) {
            return dataset.getZ(series, item);
        }
        return null;
    }

    /**
     * {@inheritDoc}
     */
    public double getZValue(int series, int item) {
        if (isSeriesValid(series)) {
            return dataset.getZValue(series, item);
        }
        return 0;
    }

    /**
     * {@inheritDoc}
     */
    public Number getX(int series, int item) {
        if (isSeriesValid(series)) {
            return dataset.getX(items.get(series), item);
        }
        return null;
    }

    /**
     * {@inheritDoc}
     */
    public Number getY(int series, int item) {
        if (isSeriesValid(series)) {
            return dataset.getY(items.get(series), item);
        }
        return null;
    }

    /**
     * {@inheritDoc}
     */
    public int getItemCount() {
        return isSeriesValid(0) ? dataset.getItemCount(items.get(0)) : 0;
    }

    /**
     * {@inheritDoc}
     */
    public void datasetChanged(DatasetChangeEvent event) {
        updateSeries();
        fireDatasetChanged();
    }
}
