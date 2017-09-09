package gensym.charts.properties.annotations.table;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>ta-border</b> int property class.
 * Sets current border style of table annotation
 */
public class TaBorderProperty extends PropValueBase<Integer> {
    /**
     * Drop shadow effect (not supported)
     */
    public static final int PETAB_DROP_SHADOW = 0;

    /**
     * Simple line border
     */
    public static final int PETAB_SINGLE_LINE = 1;

    /**
     * No border
     */
    public static final int PETAB_NO_BORDER = 2;

    /**
     * 3D inset style (not supported)
     */
    public static final int PETAB_INSET = 3;

    /**
     * Thick line border
     */
    public static final int PETAB_THICK_LINE = 4;

    /**
     * Constructor
     */
    public TaBorderProperty() {
        super(2962, "ta-border");
    }

    /**
     * {@inheritDoc}
     * Sets current border style of table annotation
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();

            int border = 1;
            if (value == PETAB_NO_BORDER) {
                border = 0;
            } else if (value == PETAB_THICK_LINE) {
                border = 2;
            }
            graph.getAnnotations().getCurrentTableAnnotation().setBorderWidth(border);
        }
    }
}
