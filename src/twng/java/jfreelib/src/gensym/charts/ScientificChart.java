package gensym.charts;

import org.jfree.data.xy.XYSeries;
import java.util.List;

/**
 * Scientific chart class
 */
public class ScientificChart extends GraphChart {
    /**
     * Constructor
     * @param title of chart
     */
    public ScientificChart(String title) {
        super(title);
    }

    /**
     * Append X values into the series
     * @param values to append
     */
    public void appendValuesX(List<Double> values) {
        createSeriesIfNeeds();
        for (int index = 0; index < getSeriesCount() && index < values.size(); index++) {
            XYSeries series = (XYSeries) getSeries(index);
            series.setMaximumItemCount(getItemCount());
            double y = series.getItemCount() > 0 ? series.getY(series.getItemCount() - 1).doubleValue() : 0;
            series.add((double) values.get(index), y);
        }
    }

    /**
     * Append Y values into the series
     * @param values to append
     */
    public void appendValuesY(List<Double> values) {
        for (int index = 0; index < getSeriesCount() && index < values.size(); index++) {
            XYSeries series = (XYSeries)getSeries(index);
            series.updateByIndex(series.getItemCount() - 1, values.get(index));
        }
    }
}
