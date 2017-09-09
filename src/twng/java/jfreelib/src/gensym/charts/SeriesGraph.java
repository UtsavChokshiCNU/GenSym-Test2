package gensym.charts;

import org.jfree.chart.JFreeChart;
import org.jfree.data.general.Series;

/**
 * Series graph chart
 */
public abstract class SeriesGraph extends AbstractChart {

    /**
     * Points marking flag
     */
    private boolean markPoints = true;

    /**
     * Constructor
     * @param chart the chart
     */
    public SeriesGraph(JFreeChart chart) {
        super(chart);
    }

    /**
     * {@inheritDoc}
     */
    public void setSeriesLabel(int series, String label) {
        if (series < getSeriesCount()) {
            getSeries(series).setKey(label);
        }
    }

    /**
     * Indicates whether graph supports duplicates
     * @return true if graph supports duplicates
     */
    protected abstract boolean allowDuplicates();

    /**
     * Update points for current series
     * @param series current series
     */
    protected abstract void updateSeriesPoints(int series);

    /**
     * Sets visualization for each point n each series
     * @param mark points visualization flag
     */
    public void setMarkDataPoints(boolean mark) {
        markPoints = mark;
        for (int i = 0; i < getSeriesCount(); i++) {
            updateSeriesPoints(i);
        }
    }

    /**
     * Returns marking points flag
     * @return true 
     */
    public boolean getMarkPoints() {
        return markPoints;
    }

    /**
     * Returns series by index
     * @param index series number (zero based)
     * @return series with specified index
     */
    protected abstract Series getSeries(int index);

    /**
     * Returns series count
     * @return series count
     */
    protected abstract int getSeriesCount();

    /**
     * Adds new series
     * @param series series to add
     */
    protected abstract void addSeries(Series series);

    /**
     * Removes series by index
     * @param index series number (zero based)
     */
    protected abstract void removeSeries(int index);

    /**
     * Creates series if dataset does not contain any ones
     */
    protected abstract void createSeriesIfNeeds();
}
