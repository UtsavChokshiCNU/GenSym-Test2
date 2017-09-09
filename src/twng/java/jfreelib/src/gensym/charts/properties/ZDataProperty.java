package gensym.charts.properties;

import gensym.charts.Chart3D;
import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;

import java.util.List;

/**
 * <b>zdata</b> double array property class.
 * Sets Z points value.
 */
public class ZDataProperty extends PropValueBase<List<Double>> {

    /**
     * Constructor
     */
    public ZDataProperty() {
        super(2900, "zdata");
    }

    /**
     * {@inheritDoc}
     * Sets Z points value.
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, List<Double> value) {
        if ( chart.getChart() instanceof Chart3D ) {
            ((Chart3D)chart.getChart()).setValuesZ(value);
            chart.updateChartData();
        } else if (chart.getChart() instanceof GraphChart) {
            GraphChart graphChart = (GraphChart) chart.getChart();
            graphChart.getDataset().setValuesZ(value);
            chart.updateChartData();
        }
    }
}
