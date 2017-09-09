package gensym.charts.annotations.table.ext;

import java.awt.Font;
import java.awt.Paint;

import org.jfree.chart.block.BlockBorder;
import org.jfree.chart.block.BlockContainer;
import org.jfree.chart.block.ColumnArrangement;
import org.jfree.chart.block.GridArrangement;
import org.jfree.chart.title.CompositeTitle;
import org.jfree.ui.HorizontalAlignment;
import org.jfree.ui.RectangleEdge;
import org.jfree.ui.VerticalAlignment;
import org.jfree.util.PaintUtilities;

/**
 * Table title class
 */
public class TableTitle extends CompositeTitle{
    /**
     * Generated serial version UID
     */
    private static final long serialVersionUID = 4825012474199483688L;
    
    /**
     * Column width factor
     */
    public static final double COLUMN_WIDTH_FACTOR = 7;

    /**
     * Table source
     */
    private TableTitleSource source = null;
    
    /**
     * Constructor
     * @param source the table source
     */
    public TableTitle(TableTitleSource source) {
        this.source = source;
        setPosition(RectangleEdge.BOTTOM);
    }
    
    /**
     * Updates view
     */
    public void update() {
        update(0);
    }

        /**
     * Updates view
     * @param rowsToSkip count of rows to skip
     */
    public void update(int rowsToSkip) {
        int borderWidth = source.getBorderWidth();
        setFrame(new BlockBorder(borderWidth, borderWidth, borderWidth, borderWidth));
        
        BlockBorder cellBorder = createCellBorder();

        BlockContainer container = getContainer();
        container.clear();
        container.setArrangement(new ColumnArrangement(HorizontalAlignment.CENTER, VerticalAlignment.TOP, 0, 0));
        
        addEmptyRows(rowsToSkip, container);
        
        BlockContainer table = new BlockContainer(new GridArrangement(source.getRowsCount(), source.getColumnsCount()));
        for (int row = 0; row < source.getRowsCount(); row++) {
            for (int column = 0; column < source.getColumnsCount(); column++) {
                TableCellTitle title = createTitle(row, column, cellBorder);
                table.add(title, false);
            }
        }
        
        container.add(table, false);
    }

    /**
     * Adds empty rows to block container
     * @param count count of empty rows
     * @param container container
     */
    private void addEmptyRows(int count, BlockContainer container) {
        for (int i = 0; i < count; i++) {
            BlockContainer block = new BlockContainer(new GridArrangement(1, 1));
            block.add(new TableCellTitle(" ", -1, -1, null), false);
            container.add(block, false);
        }
    }
    
    /**
     * Creates cell title
     * @param row cell row index
     * @param column cell column index
     * @param cellBorder default cell border
     * @return created cell title
     */
    private TableCellTitle createTitle(int row, int column, BlockBorder cellBorder) {
        int horWidth = source.getShowHorizontalLines() ? 1 : 0;
        int verWidth = source.getShowVerticalLines() ? 1 : 0;

        TableCellTitle title = new TableCellTitle(source.getCellText(row, column), row, column, source.getColorSource());
        Paint paint = source.getCellTextPaint(row, column);
        if (paint != null) {
            title.setPaint(paint);
        }
        title.setBackgroundPaint(source.getCellPaint(row, column));
        
        Paint cellBorderPaint = source.getCellBorderPaint(row, column);
        if (cellBorderPaint == null || PaintUtilities.equal(cellBorderPaint, source.getCellBorderPaint(-1, -1))) {
            title.setFrame(cellBorder);
        } else {
            title.setFrame(new BlockBorder(horWidth, verWidth, horWidth, verWidth, cellBorderPaint));
        }
        
        Font font = source.getCellFont(row, column);
        if (font != null) {
            title.setFont(font);
        }
        
        if (source.getColumnWidth(column) > 0) {
            title.setWidth(COLUMN_WIDTH_FACTOR * source.getColumnWidth(column));
        }
        HorizontalAlignment hAlign = source.getAlignment(row, column);
        if (hAlign != null) {
            title.setTextAlignment(hAlign);
        }
        
        return title;
    }
    
    /**
     * Creates cell border
     * @return created cell border
     */
    private BlockBorder createCellBorder() {
        int horWidth = source.getShowHorizontalLines() ? 1 : 0;
        int verWidth = source.getShowVerticalLines() ? 1 : 0;

        Paint borderPaint = source.getCellBorderPaint(-1, -1);
        if (borderPaint != null) {
            return new BlockBorder(horWidth, verWidth, horWidth, verWidth, borderPaint);
        }
        return new BlockBorder(horWidth, verWidth, horWidth, verWidth);
    }
}
