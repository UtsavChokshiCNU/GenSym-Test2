package gensym.charts.j3d;

import java.util.LinkedList;
import java.util.List;

import org.jfree.data.general.DatasetChangeEvent;
import org.jfree.data.xy.AbstractXYZDataset;
import org.jfree.util.ObjectUtilities;

/**
 * Simple dataset 3D class
 */
public class Dataset3D extends AbstractXYZDataset {

    /** Generated version UID */
    private static final long serialVersionUID = -1350242782564420208L;
    
    /** Storage for the series */
    private List<Series3D> seriesList = new LinkedList<Series3D>();
    
    /**
     * Constructor
     */
    public Dataset3D() {
    }

    /**
     * Returns the number of series in the dataset.
     *
     * @return The series count.
     */
    public int getSeriesCount() {
        return seriesList.size();
    }
    
    /**
     * Check series index out of bounds
     * 
     * @param series the series index
     * 
     * @exception IllegalArgumentException if index out of list bounds.
     */
    private void checkSeriesIndex(int series) {
        if ((series < 0) || (series >= getSeriesCount())) {
            throw new IllegalArgumentException("Series index out of bounds");
        }
    }
    
    /**
     * {@inheritDoc}
     */
    public Comparable<?> getSeriesKey(int series) {
        checkSeriesIndex(series);
        return seriesList.get(series).getKey();
    }
    
    /**
     * Returns the Point3D item of the specified series and item index
     * 
     * @param series  the series index
     * @param item  the item index
     * 
     * @return The Point3D item instance
     */
    public Series3D getSeries3D(int series) {
        checkSeriesIndex(series);
        return seriesList.get(series);
    }
 
    /**
     * {@inheritDoc}
     */
    public int getItemCount(int series) {
        checkSeriesIndex(series);
        return seriesList.get(series).getItemCount();
    }
    
    /**
     * Returns the Point3D item of the specified series and item index
     * For internal use
     * 
     * @param series the series index
     * @param item the item index
     * 
     * @return The Point3D item
     */
    private Point3D getPoint3D(int series, int item) {
        checkSeriesIndex(series);
        return seriesList.get(series).getPoint3D(item);
    }

    /**
     * {@inheritDoc}
     */
    public Number getX(int series, int item) {
        return getPoint3D(series, item).getX();
    }

    /**
     * {@inheritDoc}
     */
    public Number getY(int series, int item) {
        return getPoint3D(series, item).getY();
    }
    
    /**
     * {@inheritDoc}
     */
    public Number getZ(int series, int item) {
        return getPoint3D(series, item).getZ();
    }
    
    /**
     * Adds a series or if a series with the same key already exists replaces
     * the data for that series, then sends a {@link DatasetChangeEvent} to
     * all registered listeners.
     *
     * @param seriesKey  the series key (<code>null</code> not permitted).
     * @param s3d  the Series3D data
     */
    public void addSeries(Series3D s3d) {
        if (s3d == null) {
            throw new IllegalArgumentException("The 's3d' is null.");
        }
        int index = indexOf(s3d.getKey());
        if (index > -1) {
            removeSeries(index);
        }
        seriesList.add(s3d);
        s3d.addChangeListener(this);
        fireDatasetChanged();
    }

    /**
     * Removes a series from the dataset, then sends a
     * {@link DatasetChangeEvent} to all registered listeners.
     *
     * @param series the series index.
     *
     */
    public void removeSeries(int series) {
        checkSeriesIndex(series);
        Series3D s3d = seriesList.remove(series);
        s3d.removeChangeListener(this);
        fireDatasetChanged();
    }
    
     /**
     * Creates an independent copy of this Dataset3D.
     *
     * @return The cloned dataset3D.
     */
    public Object clone() throws CloneNotSupportedException {
        Dataset3D clone = (Dataset3D) super.clone();
        clone.seriesList = (List<Series3D>) ObjectUtilities.deepClone(this.seriesList);
        return clone;
    }

    /**
     * Tests the Dataset3D for equality with another object.
     *
     * @param obj  the object (<code>null</code> permitted).
     *
     * @return <code>true</code> or <code>false</code>.
     */
    public boolean equals(Object obj) {
        if ((obj == null) || (getClass() != obj.getClass())) {
            return false;
        }
        if (this == obj) {
            return true;
        }

        Dataset3D that = (Dataset3D) obj;
        
        if (! ObjectUtilities.equal(seriesList, that.seriesList)) {
            return false;
        }
        return true;
    }

    /**
     * Returns a <code>String</code> that represents the value 
     * of this <code>Dataset3D</code>.
     * @return a string representation of this <code>Dataset3D</code>.
     */
    public String toString() {
        StringBuffer str = new StringBuffer("Dataset3D[");
        for (Series3D s : seriesList) {
            str.append("\n " + s.toString());
        }
        str.append("]");
        return str.toString();
    }
}
