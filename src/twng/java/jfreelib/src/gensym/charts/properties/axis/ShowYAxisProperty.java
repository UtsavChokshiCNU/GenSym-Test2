package gensym.charts.properties.axis;

import org.jfree.chart.axis.ValueAxis;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>show-y-axis</b> int property class.
 * Shows Y axis
 */
public class ShowYAxisProperty extends PropValueBase<Integer> {
    /**
     * Grid, grid numbers and axis labels
     */
    public static final int PESA_ALL = 0;
    
    /**
     * Grid and axis labels
     */
    public static final int PESA_AXIS_LABELS = 1;

    /**
     * Grid and grid numbers
     */
    public static final int PESA_GRIDNUMBERS = 2;

    /**
     * Grid only
     */
    public static final int PESA_NONE = 3;

    /**
     * Label only
     */
    public static final int PESA_LABELONLY = 4;

    /**
     * Empty axis
     */
    public static final int PESA_EMPTY = 5;

    /**
     * Constructor
     */
    public ShowYAxisProperty() {
        super(3027, "show-y-axis");
    }

    /**
     * {@inheritDoc}
     * Shows Y axis
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            ValueAxis axis = graph.getPlot().getCurrentAxis();
            if (axis != null) {
                switch (value) {
                case PESA_ALL:
                case PESA_GRIDNUMBERS:
                    axis.setTickLabelsVisible(true);
                    axis.setTickMarksVisible(true);
                    break;
                case PESA_AXIS_LABELS:
                case PESA_NONE:
                    axis.setTickLabelsVisible(true);
                    axis.setTickMarksVisible(false);
                    break;
                case PESA_LABELONLY:
                case PESA_EMPTY:
                    axis.setTickLabelsVisible(false);
                    axis.setTickMarksVisible(false);
                    break;
                }
            }
        }
    }
}
