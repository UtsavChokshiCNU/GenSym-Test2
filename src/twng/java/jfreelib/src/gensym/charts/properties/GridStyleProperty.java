package gensym.charts.properties;

import gensym.charts.*;

/**
 * <b>grid-style</b> int property class.
 * Sets chart grid style
 */
public class GridStyleProperty extends PropValueBase<Integer> {
    /**
     * Thin solid line
     */
    public static final int PEGS_THIN = 0;
    
    /**
     * Thick solid line
     */
    public static final int PEGS_THICK = 1;

    /**
     * Dotted line
     */
    public static final int PEGS_DOT = 2;

    /**
     * Dashed line
     */
    public static final int PEGS_DASH = 3;

    /**
     * Constructor
     */
    public GridStyleProperty() {
        super(3032, "grid-style");
    }

    /**
     * {@inheritDoc}
     * Sets chart grid style
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            
            int lineType = ChartLineTypes.LINE_THINSOLID;
            switch (value) {
            case PEGS_THICK:
                lineType = ChartLineTypes.LINE_THICKSOLID;
                break;
            case PEGS_DOT:
                lineType = ChartLineTypes.LINE_DOT;
                break;
            case PEGS_DASH:
                lineType = ChartLineTypes.LINE_DASH;
                break;
            }
            
            graph.setGridStroke(ChartLineTypes.makeBasicStroke(lineType));
        }
    }
}
