package gensym.charts.tables;

import java.util.LinkedHashMap;
import java.util.Map;

public class TableCellData<T> {
    /**
     * Cells map ((row index, column index) => T)
     */
    private Map<Integer, Map<Integer, T>> map = new LinkedHashMap<Integer, Map<Integer, T>>();

    /**
     * Returns cell data
     * @param row cell row index
     * @param column cell column index
     * @return cell data
     */
    public T get(int row, int column) {
        Map<Integer, T> rowMap = map.get(row);
        if (rowMap != null) {
            return rowMap.get(column);
        }
        
        return null;
    }
    
    /**
     * Clears data
     */
    public void clear() {
        map.clear();
    }
    
    /**
     * Sets cell data
     * @param row row index
     * @param column column index
     * @param data cell data
     */
    public void setCellData(int row, int column, T data) {
        Map<Integer, T> rowMap = map.get(row);
        if (rowMap == null && data != null) {
            rowMap = new LinkedHashMap<Integer, T>();
            map.put(row, rowMap);
        }
        if (data != null) {
            rowMap.put(column, data);
        } else if (rowMap != null && rowMap.containsKey(column)) {
            rowMap.remove(column);
            if (rowMap.size() == 0) {
                map.remove(row);
            }
        }
    }
    
    /**
     * Clears row data
     * @param row row index
     */
    public void clearRowData(int row) {
        map.remove(row);
    }
    
    /**
     * Clears column data
     * @param column column index
     */
    public void clearColumnData(int column) {
        for (Map<Integer, T> rowMap : map.values()) {
            rowMap.remove(column);
        }
    }
}
