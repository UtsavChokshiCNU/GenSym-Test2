package gensym.charts.annotations.table.ext;

import gensym.charts.dialogs.tables.TableColorSource;

import java.awt.Graphics2D;

import org.jfree.chart.block.RectangleConstraint;
import org.jfree.chart.title.TextTitle;
import org.jfree.ui.Size2D;

/**
 * Table cell title class
 */
public class TableCellTitle extends TextTitle {
    /**
     * Generated serial version UID
     */
    private static final long serialVersionUID = 2431881516191135330L;
    
    /**
     * Cell row
     */
    private int row = 0;
    
    /**
     * Cell column
     */
    private int column = 0;
    
    /**
     * Table color source
     */
    private TableColorSource source = null;

    /**
     * Constructor
     * @param text cell text
     * @param row the cell row index
     * @param column the cell column index
     * @param source table color source 
     */
    public TableCellTitle(String text, int row, int column, TableColorSource source) {
        super(text == null || text.length() == 0 ? " " : text);
        
        this.row = row;
        this.column = column;
        this.source = source;
    }
    
    /**
     * Returns cell row
     * @return row
     */
    public int getRow() {
        return row;
    }

    /**
     * Returns cell column
     * @return column
     */
    public int getColumn() {
        return column;
    }
    
    /**
     * {@inheritDoc}
     */
    public Size2D arrange(Graphics2D g2, RectangleConstraint constraint) {
        Size2D size = super.arrange(g2, constraint);
        if (getWidth() > 0) {
            size = new Size2D(getWidth(), size.getHeight());
        }
        return size;
    }
    
    /**
     * Returns table color source
     * @return the table color source
     */
    public TableColorSource getTableColorSource() {
        return source;
    }
}
