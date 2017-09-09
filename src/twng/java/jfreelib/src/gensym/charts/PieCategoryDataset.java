package gensym.charts;

import java.util.*;

import org.jfree.data.category.CategoryDataset;
import org.jfree.data.general.AbstractDataset;

public class PieCategoryDataset extends AbstractDataset implements CategoryDataset {
    /**
     * Serial version ID 
     */
    private static final long serialVersionUID = 5222716490961177734L;
    
    /**
     * Allowing firing events flag
     */
    private boolean allowFiringEvents = true;

    /**
     * Firing events flag
     */
    private boolean doFireEvents = false;
    
    /**
     * Row keys
     */
    private ArrayList<String> rowKeys = new ArrayList<String>();

    /**
     * Column keys
     */
    private ArrayList<String> columnKeys = new ArrayList<String>();
    
    /**
     * Data
     */
    private ArrayList<ArrayList<Number>> data = new ArrayList<ArrayList<Number>>(); 

    /**
     * Constructor
     */
    public PieCategoryDataset() {
    }
    
    /**
     * Updates column key
     * @param column column index (zero based)
     * @param key column key
     */
    public void setColumnKey(int column, String key) {
        if (column < columnKeys.size()) {
            columnKeys.set(column, key);
            fireDatasetChanged();
        }
    }

    /**
     * Adds column
     * @param key column key
     */
    public void addColumn(String key) {
        columnKeys.add(key);
        updateDataSize();
        fireDatasetChanged();
    }
    

    /**
     * Updates row key
     * @param row row index (zero based)
     * @param key row key
     */
    public void setRowKey(int row, String key) {
        if (row < rowKeys.size()) {
            rowKeys.set(row, key);
            fireDatasetChanged();
        }
    }

    /**
     * Adds row
     * @param key row key
     */
    public void addRow(String key) {
        rowKeys.add(key);
        updateDataSize();
        fireDatasetChanged();
    }
    
    /**
     * Updates data size
     */
    public void updateDataSize() {
        // rows
        data.ensureCapacity(rowKeys.size());
        while (data.size() < rowKeys.size()) {
            data.add(new ArrayList<Number>());
        }
        
        while (data.size() > rowKeys.size()) {
            data.remove(data.size() - 1);
        }
        
        // add columns
        for (int i = 0; i < data.size(); i++) {
            ArrayList<Number> column = data.get(i);
            column.ensureCapacity(columnKeys.size());
            while (column.size() < columnKeys.size()) {
                column.add(null);
            }
            
            while (column.size() > columnKeys.size()) {
                column.remove(column.size() - 1);
            }
        }
    }

    /**
     * {@inheritDoc}
     */
    public Comparable<?> getColumnKey(int column) {
        return column < columnKeys.size() ? columnKeys.get(column) : null;
    }

    /**
     * {@inheritDoc}
     */
    public List<?> getColumnKeys() {
        return new LinkedList<Comparable<?>>(columnKeys);
    }
    
    /**
     * {@inheritDoc}
     */
    public Comparable<?> getRowKey(int row) {
        return row < rowKeys.size() ? rowKeys.get(row) : null;
    }
    
    /**
     * {@inheritDoc}
     */
    public List<?> getRowKeys() {
        return new LinkedList<Comparable<?>>(rowKeys);
    }

    /**
     * Tests events allowing flag
     * @return true if events allowed
     */
    public boolean isEventsAllowed() {
        return allowFiringEvents;
    }
    
    /**
     * Sets events allowing flag
     * @param allowed events allowing flag
     */
    public void setEventsAllowed(boolean allowed) {
        // fire events if necessary
        if (allowed && !allowFiringEvents && doFireEvents) {
            super.fireDatasetChanged();
            doFireEvents = false;
        }
        allowFiringEvents = allowed;
    }
    
    /**
     * {@inheritDoc}
     */
    protected void fireDatasetChanged() {
        if (isEventsAllowed()) {
            super.fireDatasetChanged();
        } else {
            doFireEvents = true;
        }
    }
    
    /**
     * Set value by position
     * @param value value to be set
     * @param row row index (zero based)
     * @param column column index (zero based)
     */
    public void setValue(double value, int row, int column) {
        data.get(row).set(column, value);
        fireDatasetChanged();
    }

    /**
     * {@inheritDoc}
     */
    public int getColumnIndex(Comparable key) {
        return columnKeys.indexOf(key);
    }

    /**
     * {@inheritDoc}
     */
    public int getRowIndex(Comparable key) {
        return rowKeys.indexOf(key);
    }

    /**
     * {@inheritDoc}
     */
    public Number getValue(Comparable rowKey, Comparable columnKey) {
        return getValue(getRowIndex(rowKey), getColumnIndex(columnKey));
    }

    /**
     * {@inheritDoc}
     */
    public int getColumnCount() {
        return columnKeys.size();
    }

    /**
     * {@inheritDoc}
     */
    public int getRowCount() {
        return rowKeys.size();
    }

    /**
     * {@inheritDoc}
     */
    public Number getValue(int row, int column) {
        return data.get(row).get(column);
    }
    
    /**
     * Sets rows count
     * @param rows rows count
     */
    public void setRowsCount(int rows) {
        boolean doFireEvents = false;
        while (rowKeys.size() < rows) {
            rowKeys.add("row " + (rowKeys.size() + 1));
            doFireEvents = true;
        }
        while (rowKeys.size() > rows) {
            rowKeys.remove(rowKeys.size() - 1);
            doFireEvents = true;
        }
        
        updateDataSize();
        if (doFireEvents) {
            fireDatasetChanged();
        }
    }
    
    /**
     * Sets columns count
     * @param columns columns count
     */
    public void setColumnsCount(int columns) {
        boolean doFireEvents = false;
        while (columnKeys.size() < columns) {
            columnKeys.add("column " + (columnKeys.size() + 1));
            doFireEvents = true;
        }
        while (columnKeys.size() > columns) {
            columnKeys.remove(columnKeys.size() - 1);
            doFireEvents = true;
        }
        
        updateDataSize();
        if (doFireEvents) {
            fireDatasetChanged();
        }
    }
}
