package gensym.charts.autostat;

import org.jfree.data.general.DatasetChangeEvent;
import org.jfree.data.general.DatasetChangeListener;
import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

public class XYParetoDataset extends XYSeriesCollection implements DatasetChangeListener {
    /**
     * Serial version UID
     */
    private static final long serialVersionUID = 2171778628379054794L;
    
    /**
     * Ascending mode
     */
    private boolean ascending = true;
    
    /**
     * Events firing flag
     */
    boolean fireEvents = true;

    /**
     * Constructor
     */
    public XYParetoDataset(boolean ascending) {
        this.ascending = ascending;
    }
    
    /**
     * Makes series name
     * @param name main name
     * @return series name
     */
    private String makeName(String name) {
        return name + (ascending ? " Pareto ASC" : " Pareto DEC");
    }
    
    /**
     * Updates series
     * @param dataset source data set
     * @param series series index (zero based)
     */
    private void updateSeries(XYDataset dataset, int series) {
        XYSeries xySeries = null;
        if (series < getSeriesCount()) {
            xySeries = getSeries(series);
            xySeries.setKey(makeName((String) dataset.getSeriesKey(series)));
        } else {
            xySeries = new XYSeries(makeName((String) dataset.getSeriesKey(series)), false, false);
            addSeries(xySeries);
        }
        
        xySeries.clear();
        
        double value = 0.0;
        for (int item = 0; item < dataset.getItemCount(series); item++) {
            Number y = dataset.getY(series, item);
            if (y != null) {
                value += y.doubleValue();
            }
            
            xySeries.add(dataset.getX(series, item), value);
        }
        
        if (ascending) {
            for (int item = 0; item < xySeries.getItemCount(); item++) {
                xySeries.updateByIndex(item, xySeries.getY(item).doubleValue() / value);
            }
        } else {
            double newValue = 0.0;
            for (int item = dataset.getItemCount(series) - 1; item >= 0; item--) {
                Number y = dataset.getY(series, item);
                if (y != null) {
                    newValue += y.doubleValue();
                }
                
                xySeries.updateByIndex(item, newValue / value);
            }
        }
    }
    
    /**
     * Updates data set
     * @param dataset source data set
     */
    public void update(XYDataset dataset) {
        while (getSeriesCount() > dataset.getSeriesCount()) {
            removeSeries(getSeriesCount() - 1);
        }
        
        for (int series = 0; series < dataset.getSeriesCount(); series++) {
            updateSeries(dataset, series);
        }
    }

    /**
     * {@inheritDoc}
     */
    public void datasetChanged(DatasetChangeEvent event) {
        if (event.getDataset() instanceof XYDataset) {
            fireEvents = false;
            
            update((XYDataset) event.getDataset());
            
            fireEvents = true;
            fireDatasetChanged();
        }
    }
    
    /**
     * {@inheritDoc}
     */
    protected void fireDatasetChanged() {
        if (fireEvents) {
            super.fireDatasetChanged();
        }
    }
}
