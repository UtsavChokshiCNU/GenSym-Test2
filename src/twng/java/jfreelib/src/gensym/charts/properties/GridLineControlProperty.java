package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

/**
 * <b>grid-line-control</b> int property class.
 * Sets chart grid lines visibility
 */
public class GridLineControlProperty extends PropValueBase<Integer> {
    /**
     * Both horizontal and vertical grid lines.
     */
    public static final int GRIDLINE_BOTH = 0;
    
    /**
     * Horizontal grid lines.
     */
    public static final int GRIDLINE_YAXIS = 1;
    
    /**
     * Vertical grid lines.
     */
    public static final int GRIDLINE_XAXIS = 2;
    
    /**
     * No grid lines.
     */
    public static final int GRIDLINE_NONE = 3;
    
    /**
     * Constructor
     */
    public GridLineControlProperty() {
        super(3100, "grid-line-control");
    }

    /**
     * Returns whether X axis grid lines are visible
     * @param flag grid lines visibility flag
     * @return true if X axis grid lines are visible
     */
    private boolean isVisibleX(int flag) {
        return flag == GRIDLINE_BOTH || flag == GRIDLINE_XAXIS;
    }
    
    /**
     * Returns whether Y axis grid lines are visible
     * @param flag grid lines visibility flag
     * @return true if Y axis grid lines are visible
     */
    private boolean isVisibleY(int flag) {
        return flag == GRIDLINE_BOTH || flag == GRIDLINE_YAXIS;
    }

    /**
     * {@inheritDoc}
     * Sets chart grid lines visibility
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        chart.getChart().showGridLines(isVisibleX(value), isVisibleY(value));
    }
}
