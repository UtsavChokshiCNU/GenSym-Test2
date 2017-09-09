package gensym.charts.annotations.table.ext;

import gensym.charts.dialogs.tables.TableColorSource;

import java.awt.Font;
import java.awt.Paint;

import org.jfree.ui.HorizontalAlignment;

/**
 * Table Title source
 */
public interface TableTitleSource {
    /**
     * Returns rows count
     * @return rows count
     */
    int getRowsCount();

    /**
     * Returns columns count
     * @return columns count
     */
    int getColumnsCount();
    
    /**
     * Returns cell text
     * @param row the cell row
     * @param column the cell column
     * @return the cell text
     */
    String getCellText(int row, int column);
    
    /**
     * Returns cell text paint
     * @param row the cell row
     * @param column the cell column
     * @return the cell text paint
     */
    Paint getCellTextPaint(int row, int column);
    
    /**
     * Returns cell paint
     * @param row the cell row
     * @param column the cell column
     * @return the cell paint
     */
    Paint getCellPaint(int row, int column);
    
    /**
     * Returns cell border paint
     * @param row the cell row
     * @param column the cell column
     * @return the cell border paint
     */
    Paint getCellBorderPaint(int row, int column);

    /**
     * Tests if vertical grid lines are enabled
     * @return true if enabled
     */
    boolean getShowVerticalLines();
    
    /**
     * Tests if horizontal grid lines are enabled
     * @return true if enabled
     */
    boolean getShowHorizontalLines();
    
    /**
     * Gets table border width
     * @return table border width
     */
    int getBorderWidth();
    
    /**
     * Returns cell text font
     * @param row row index
     * @param column column index
     * @return the font
     */
    Font getCellFont(int row, int column);
    
    /**
     * Returns column width
     * @param column column index
     * @return
     */
    int getColumnWidth(int column);
    
    /**
     * Returns horizontal text alignment
     * @param row row index
     * @param column column index
     * @return the horizontal text alignment
     */
    HorizontalAlignment getAlignment(int row, int column);
    
    /**
     * Returns color source
     * @return color source
     */
    TableColorSource getColorSource();
}
