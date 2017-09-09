package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;
import gensym.charts.PieChart;

/**
 * <b>show-pie-labels</b> int property class.
 * Shows pie chart labels
 */
public class ShowPieLablesProperty extends PropValueBase<Integer> {
    /**
     * Percent plus Label
     */
    public static final int SHOW_PERCENT_PLUS_LABEL = 0;
    
    /**
     * Percent Only
     */
    public static final int SHOW_PERCENT = 1;

    /**
     * Label Only
     */
    public static final int SHOW_LABEL = 2;

    /**
     * No Label
     */
    public static final int SHOW_NONE = 3;

    /**
     * Constructor
     */
    public ShowPieLablesProperty() {
        super(3921, "show-pie-labels");
    }

    /**
     * Test showing percents
     * @param flag showing flag
     * @return true if it needs to show percents 
     */
    private boolean showPercent(int flag) {
        return flag == SHOW_PERCENT_PLUS_LABEL || flag == SHOW_PERCENT;
    }
    
    /**
     * Test showing labels
     * @param flag showing flag
     * @return true if it needs to show labels 
     */
    private boolean showLabel(int flag) {
        return flag == SHOW_PERCENT_PLUS_LABEL || flag == SHOW_LABEL;
    }

    /**
     * {@inheritDoc}
     * Shows pie chart labels
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof PieChart) {
            PieChart pie = (PieChart) chart.getChart();
            pie.showPieLabels(showPercent(value), showLabel(value));
        }
    }
}
