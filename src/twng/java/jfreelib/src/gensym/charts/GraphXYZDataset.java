package gensym.charts;

import java.util.ArrayList;
import java.util.List;

import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

/**
 * XYZ dataset for GraphChart
 */
public class GraphXYZDataset extends XYSeriesCollection implements SourceXYZDataset {

    /** List of the z values of XYZ dataset */
    List<Double> zValues = new ArrayList<Double>();

    /**
     * Constructs an empty dataset.
     */
    public GraphXYZDataset() {
        super();
    }

    /**
     * Constructs a dataset and populates it with a single series.
     *
     * @param series  the series (<code>null</code> ignored).
     */
    public GraphXYZDataset(XYSeries series) {
        super(series);
    }

    /**
     * Sets z values
     * @param zValues new z values
     */
    public void setValuesZ(List<Double> zValues) {
        this.zValues = new ArrayList<Double>(zValues);
    }

    /**
     * {@inheritDoc}
     */
    public Number getZ(int series, int item) {
        int index = item;

        // add to index all counts
        for (int i = 0; i < series; i++) {
            index += getItemCount(i);
        }
        
        if ((index < 0) || (index >= zValues.size())) {
            return 0;
        }

        return zValues.get(index);
    }

    /**
     * {@inheritDoc}
     */
    public double getZValue(int series, int item) {
        return getZ(series, item).doubleValue();
    }
}
