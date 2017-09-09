package gensym.charts.properties.axis;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>date-time-mode</b> int property class.
 * This property enables the Graph and Scientific Graph
 * to treat X Axis data as serially formatted date/time data.
 */
public class DateTimeModeProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public DateTimeModeProperty() {
        super(3018, "date-time-mode");
    }

    /**
     * {@inheritDoc}
     * Sets formatted date/time data
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart sChart = (GraphChart) chart.getChart();
            sChart.setDateTimeAxisMode(value != 0);
        }
    }
}
