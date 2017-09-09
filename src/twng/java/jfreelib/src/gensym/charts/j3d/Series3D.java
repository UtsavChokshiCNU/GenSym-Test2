package gensym.charts.j3d;

import java.util.LinkedList;
import java.util.List;

import org.jfree.data.general.Series;
import org.jfree.util.ObjectUtilities;

/**
 * Simple Series 3D class
 */
public class Series3D extends Series {

    /** Serial VersionUID */
    private static final long serialVersionUID = 8289179052611072974L;

    /** Storage for the series items */
    private List<Point3D> seriesData = new LinkedList<Point3D>();

    /**
     * Constructor with the specified key.
     * 
     * @param key the key of series
     */
    public Series3D(Comparable<?> key) {
        super(key);
    }

    /**
     * Constructor with the specified key and description.
     * 
     * @param key the key of series
     * @param description the description of series
     */
    public Series3D(Comparable<?> key, String description) {
        super(key, description);
    }

    /**
     * Checks the item index in the list bounds and throw the exception if false
     *  
     * @param itemIndex  the specified index of item
     * 
     * @exception IllegalArgumentException if index out of list bounds.
     */
    private void checkItemIndex(int itemIndex) {
        if ((itemIndex < 0) || (itemIndex >= getItemCount())) {
            throw new IllegalArgumentException("Item index out of bounds");
        }
    }

    /**
     * Gets the Point3D object for specified index in this series
     * 
     * @param index the index of item in series
     * 
     * @return The Point3D item instance
     */
    public Point3D getPoint3D(int index) {
        checkItemIndex(index);
        return seriesData.get(index);
    }

    /**
     * Inserts the specified Point3D at the specified position in this series.
     * Shifts the Point3D currently at that position (if any) and any
     * subsequent Points to the right (adds one to their indices).
     * 
     * @param index  index at which the specified element is to be inserted
     * @param p3d Point3D to be inserted
     * 
     * @return true if this series changed as a result of the call

     * @exception IllegalArgumentException if index out of list bounds.
     */
    public boolean insertPoint3D(int index, Point3D p3d) {
        if ((index < 0) || (index > getItemCount())) {
            throw new IllegalArgumentException("Inserting index out of bounds");
        }
        if ((p3d != null) && (indexOf(p3d) == -1)) {
            seriesData.add(index, p3d);
            fireSeriesChanged();
            return true;
        }
        return false;
    }

    /**
     * Appends the specified Point3D to the end of list.
     * 
     * @param p3d  Point3D to be added
     * 
     * @return true if this series changed as a result of the call
     */
    public boolean addPoint3D(Point3D p3d) {
        return insertPoint3D(seriesData.size(), p3d);
    }

    /**
     * Removes the Point3D at the specified position in this series.
     * Shifts any subsequent Point3D items to the left.
     * Returns the Point3D that was removed from the list.
     *
     * @param index  the index of the Point3D to be removed
     * 
     * @return the Point3D previously at the specified position
     * 
     * @exception IllegalArgumentException if index out of list bounds.
     */
    public Point3D removePoint3D(int index) {
        checkItemIndex(index);
        Point3D p = seriesData.remove(index);
        fireSeriesChanged();
        return p;
    }

    /**
     * Removes the Point3D at the specified position in this series.
     * Shifts any subsequent Point3D items to the left.
     * Returns the Point3D that was removed from the list.
     *
     * @param index  the index of the Point3D to be removed
     * 
     * @return the Point3D previously at the specified position
     */
    public Point3D removePoint3D(Point3D p3d) {
        int index = indexOf(p3d);
        if (index > -1) {
            return removePoint3D(index);
        }
        return null;
    }

    /**
     * Clears data
     */
    public void clear() {
        if (!seriesData.isEmpty()) {
            seriesData.clear();
            fireSeriesChanged();
        }
    }

    /**
     * Returns the index of the first occurrence of the specified Point3D
     * in this series.
     *
     * @param p3d  the Point3D object
     * 
     * @return the index, or -1 if this list does not contain the Point3D
     */
    public int indexOf(Point3D p3d) {
        return seriesData.indexOf(p3d);
    }

    /**
     * Returns the index of the first occurrence of Point3D by the double values 
     * of specified point coordinates in this series.
     *
     * @param x  the double value of Point3D X coordinate.
     * @param y  the double value of Point3D Y coordinate.
     * @param z  the double value of Point3D Z coordinate.
     * 
     * @return the index, or -1 if this list does not contain the Point3D
     */
    public int indexOf(double x, double y, double z) {
        return indexOf(new Point3D(x, y, z));
    }

    /**
     * Returns the index of the first occurrence of Point3D by the Number values 
     * of specified Point3D in this series.
     *
     * @param x  the Number value of Point3D X coordinate.
     * @param y  the Number value of Point3D Y coordinate.
     * @param z  the Number value of Point3D Z coordinate.
     * 
     * @return the index, or -1 if this list does not contain the Point3D
     */
    public int indexOf(Number x, Number y, Number z) {
        return indexOf(x.doubleValue(), y.doubleValue(), z.doubleValue());
    }

    /**
     * {@inheritDoc}
     */
    public int getItemCount() {
        return seriesData.size();
    }

    /**
     * Tests the Series3D for equality with another object.
     *
     * @param obj  the object (<code>null</code> permitted).
     *
     * @return <code>true</code> or <code>false</code>.
     */
    public boolean equals(Object obj) {
        if (!((obj instanceof Series3D) && super.equals(obj))) {
            return false;
        }
        Series3D that = (Series3D) obj;
        if (!ObjectUtilities.equal(seriesData, that.seriesData)) {
            return false;
        }
        return true;
    }

    /**
     * Creates a new object of the same class and with the
     * same contents as this object.
     * 
     * @return a clone of this instance.
     */
    public Object clone() throws CloneNotSupportedException {
            Series3D s3d = (Series3D) super.clone();
            s3d.seriesData = (List<Point3D>) ObjectUtilities.deepClone(seriesData);
            return s3d;
    }

    /**
     * Returns a <code>String</code> that represents the value 
     * of this <code>Series3D</code>.
     * 
     * @return a string representation of this <code>Series3D</code>.
     */
    public String toString() {
        StringBuffer str = new StringBuffer("Series3D [Key: ");
        str.append(getKey().toString());
        str.append("; Description: ");
        str.append(getDescription());
        for (Point3D p : seriesData) {
            str.append("; " + p.toString());
        }
        str.append("]");
        return str.toString();
    }
}
