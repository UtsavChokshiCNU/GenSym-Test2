package gensym.charts.tables;

import java.util.LinkedHashMap;
import java.util.Map;

/**
 * Table data set class
 */
public class TablePropertySet<T> {

    /**
     * Rows data map (row index => data)
     */
    private Map<Integer, T> rowsData = new LinkedHashMap<Integer, T>();

    /**
     * Columns data map (column index => data)
     */
    private Map<Integer, T> columnData = new LinkedHashMap<Integer, T>();
    
    /**
     * Cell data
     */
    private TableCellData<T> cellData = new TableCellData<T>();
    
    /**
     * Main data
     */
    private T mainData = null;
    
    /**
     * Returns cell data
     * @param row row index
     * @param column column index
     * @return cell data
     */
    public T getData(int row, int column) {
        T data = null;
        if (row != -1 && column != -1) {
            data = cellData.get(row, column);
        }
        if (data == null && row != -1) {
            data = rowsData.get(row);
        }
        if (data == null && column != -1) {
            data = columnData.get(column);
        }
        
        return data != null ? data : mainData;
    }
    
    /**
     * Sets cell Data
     * @param row row index
     * @param column column index
     * @param data cell data
     */
    public void setData(int row, int column, T data) {
        T oldData = getData(row, column);
        if (oldData != data) {
            if (data == mainData) {
                if (row != -1 && column != -1) {
                    cellData.setCellData(row, column, null);
                } else if (row != -1) {
                    rowsData.remove(row);
                    cellData.clearRowData(row);
                } else if (column != -1) {
                    columnData.remove(column);
                    cellData.clearColumnData(column);
                }
            } else {
                if (row != -1 && column != -1) {
                    cellData.setCellData(row, column, data);
                } else if (row != -1) {
                    rowsData.put(row, data);
                    cellData.clearRowData(row);
                } else if (column != -1) {
                    columnData.put(column, data);
                    cellData.clearColumnData(column);
                } else {
                    clear();
                    mainData = data;
                }
            }
        }
    }
                    
    /**
     * Clears all data
     */
    public void clear() {
        mainData = null;
        rowsData.clear();
        columnData.clear();
        cellData.clear();
    }
}
