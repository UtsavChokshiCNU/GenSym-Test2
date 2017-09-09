package gensym.charts.tables;

import gensym.charts.scrolling.SeriesScrollingListener;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;

import javax.swing.table.AbstractTableModel;

import org.jfree.data.general.DatasetChangeEvent;
import org.jfree.data.general.DatasetChangeListener;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

/**
 * Chart table model.
 * Works with XYSeriesCollection dataset.
 */
public class ChartTableModel extends AbstractTableModel implements SeriesScrollingListener {
    /**
     * Generated serial version UID
     */
    private static final long serialVersionUID = 6508679517453461359L;

    /**
     * Source dataset 
     */
    private XYSeriesCollection dataset = null;
    
    /**
     * X values list
     */
    private ArrayList<Double> xValues = new ArrayList<Double>();
    
    /**
     * Updating flag
     */
    private boolean doUpdate = false;
    
    /**
     * Visible items
     */
    private List<Integer> visibleItems = new LinkedList<Integer>();
    
    /**
     * Show all items flag
     */
    private boolean showAllItems = true;
    
    /**
     * Constructor
     * @param dataset source dataset
     */
    public ChartTableModel(XYSeriesCollection dataset) {
        this.dataset = dataset;
        
        dataset.addChangeListener(new DatasetChangeListener() {
            public void datasetChanged(DatasetChangeEvent event) {
                if (isUpdateAllowed()) {
                    updateData();
                }
            }
        });
        updateData();
    }
    
    /**
     * {@inheritDoc}
     */
    public int getRowCount() {
        return getShowAllItems() ? dataset.getSeriesCount() : visibleItems.size();
    }

    /**
     * {@inheritDoc}
     */
    public int getColumnCount() {
        return xValues.size() + 1;
    }

    /**
     * {@inheritDoc}
     */
    public Object getValueAt(int rowIndex, int columnIndex) {
        if (rowIndex >= 0 && rowIndex < getRowCount() &&
                columnIndex >= 0 && columnIndex < getColumnCount()) {
            if (!getShowAllItems()) {
                rowIndex = visibleItems.get(rowIndex);
                if (rowIndex < 0 || rowIndex >= dataset.getSeriesCount()) {
                    return null;
                }
            }
            if (columnIndex == 0) {
                return dataset.getSeries(rowIndex).getKey();
            }
            
            Double x = xValues.get(columnIndex - 1);
            XYSeries series = dataset.getSeries(rowIndex);
            int index = series.indexOf(x);
            if (index >= 0) {
                return series.getY(index);
            }
        }
        return null;
    }

    /**
     * {@inheritDoc}
     */
    public Class<?> getColumnClass(int columnIndex) {
        return columnIndex == 0 ? String.class : Number.class;
    }
    
    /**
     * {@inheritDoc}
     */
    public String getColumnName(int column) {
        if (column < getColumnCount()) {
            return column == 0 ? "X value" : xValues.get(column - 1).toString();
        }
        return null;
    }
    
    /**
     * Updates table data
     */
    public final void updateData() {
        xValues.clear();
        
        HashSet<Double> points = new HashSet<Double>();
        for (int i = 0; i < dataset.getSeriesCount(); i++) {
            if (getShowAllItems() || visibleItems.contains(i)) {
                XYSeries series = dataset.getSeries(i);
                for (int x = 0; x < series.getItemCount(); x++) {
                    points.add(series.getX(x).doubleValue());
                }
            }
        }
        
        xValues.addAll(points);
        Collections.sort(xValues);
        
        fireTableStructureChanged();
        fireTableDataChanged();
    }
    
    /**
     * Tests if updating is allowed
     * @return
     */
    public boolean isUpdateAllowed() {
        return doUpdate;
    }

    /**
     * Tests if updating is allowed
     */
    public void setUpdateAllowed(boolean allowed) {
        doUpdate = allowed;
    }

    /**
     * {@inheritDoc}
     */
    public void itemsScrolled(List<Integer> items) {
        visibleItems.clear();
        visibleItems.addAll(items);
        if (!showAllItems) {
            updateData();
        }
    }
    
    /**
     * Sets show all items flag
     * @param show new showing state
     */
    public void setShowAllItems(boolean show) {
        showAllItems = show;
        updateData();
    }
    
    /**
     * Returns show all items flag
     * @return the show all items flag
     */
    public boolean getShowAllItems() {
        return showAllItems;
    }
}
