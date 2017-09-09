package gensym.charts.dialogs.tables;

import javax.swing.*;

/**
 * Radio button for color dialog
 */
public class TableColorRButton extends JRadioButton {
    /**
     * Generated serial version UID
     */
    private static final long serialVersionUID = -3029173300282679031L;
    /**
     * Table row
     */
    private int row;
    /**
     * Table column
     */
    private int column;

    /**
     * Constructor
     * @param text name of the button
     * @param selected sets is button selected
     * @param tableRow table row
     * @param tableColumn table column
     */
    public TableColorRButton(String text, boolean selected, int tableRow, int tableColumn) {
        super(text, selected);
        row = tableRow;
        column = tableColumn;
    }

    /**
     * Gets row
     * @return row
     */
    public int getRow() {
        return row;
    }

    /**
     * Gets column
     * @return column
     */
    public int getColumn() {
        return column;
    }
}
