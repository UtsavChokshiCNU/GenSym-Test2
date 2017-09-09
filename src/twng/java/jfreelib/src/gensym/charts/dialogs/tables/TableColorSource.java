package gensym.charts.dialogs.tables;

import java.awt.Color;

/**
 * Table color source interface
 */
public interface TableColorSource {

    /**
     * Returns text color of specified Cell/Column/Row/Table
     * @param row table row index
     * @param column table column index
     * @return the text color for table cell if both row and column are not -1, for table row if column is -1,
     *  for table column is -1 or for whole table if both row and column are -1.
     */
    Color getTextColor(int row, int column);

    /**
     * Sets text color of specified Cell/Column/Row/Table.
     * <p>
     * Sets the text color for table cell if both row and column are not -1, for table row if column is -1,
     *  for table column is -1 or for whole table if both row and column are -1.
     * @param row table row index
     * @param column table column index
     * @param color the text color
     */
    void setTextColor(int row, int column, Color color);

    /**
     * Returns outline color of specified Cell/Column/Row/Table
     * @param row table row index
     * @param column table column index
     * @return The outline color for table cell if both row and column are not -1, for table row if column is -1,
     *  for table column is -1 or for whole table if both row and column are -1.
     */
    Color getOutlineColor(int row, int column);

    /**
     * Sets outline color of specified Cell/Column/Row/Table.
     * <p>
     * Sets the outline color for table cell if both row and column are not -1, for table row if column is -1,
     *  for table column is -1 or for whole table if both row and column are -1.
     * @param row table row index
     * @param column table column index
     * @param color the outline color
     */
    void setOutlineColor(int row, int column, Color color);
}
