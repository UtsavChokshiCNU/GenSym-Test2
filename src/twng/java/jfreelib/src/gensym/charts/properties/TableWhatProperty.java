package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;
import gensym.charts.tables.ColoredTable;

/**
 * <b>table-what</b> int property class.
 * Sets table properties
 */
public class TableWhatProperty extends PropValueBase<Integer> {
    /**
     * Show graphed subsets
     */
    public static final int PETW_GRAPHED = 0;
    
    /**
     * Show all subsets, mark visible
     */
    public static final int PETW_ALLSUBSETS = 1;

    /**
     * Disable selection
     */
    public static final int PETW_GRAYED = 2;

    /**
     * Constructor
     */
    public TableWhatProperty() {
        super(3365, "table-what");
    }

    /**
     * {@inheritDoc}
     * Sets table properties
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        ColoredTable table = chart.getTable();
        if (table != null) {
            table.setShowAllItems(value != PETW_GRAPHED);
            table.setEnableSelect(value != PETW_GRAYED);
        }
    }
}
