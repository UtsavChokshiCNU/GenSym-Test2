package gensym.charts.autostat;

import org.jfree.data.general.DatasetChangeEvent;
import org.jfree.data.general.DatasetChangeListener;
import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeries;

/**
 *  Auto stat series for Graph chart
 */
public class XYAutoStatSeries extends XYSeries implements DatasetChangeListener {

    /**
     * Serial version UID
     */
    private static final long serialVersionUID = 5527210169643777753L;
    /**
     * Dataset event processing flag 
     */
    private boolean processEvents = true;
    /**
     * Auto statistic info 
     */
    private AutoStatInfo info = null;
    /**
     * All points statistic flag
     */
    private boolean forAll = false;

    /**
     * Constructor
     * @param info auto stat info
     * @param forAll
     */
    public XYAutoStatSeries(AutoStatInfo info, boolean forAll) {
        super(info.getName() + (forAll ? " AP" : " PP"), false, false);
        this.info = info;
        this.forAll = forAll;
    }

    /**
     * Gets AutoStatInfo
     * @return info
     */
    public AutoStatInfo getAutoStatInfo() {
        return info;
    }

    /**
     * Updates points
     * @param dataset
     */
    private void updatePoints(XYDataset dataset) {
        clear();
        for (int series = 0; series < dataset.getSeriesCount(); series++) {
            for (int x = 0; x < dataset.getItemCount(series); x++) {
                addOrUpdate(dataset.getXValue(series, x), 0.0);
            }
        }
    }

    /**
     * Updates series data
     * @param dataset XY dataset
     */
    public void updateData(XYDataset dataset) {
        if (dataset == null) {
            return;
        }

        updatePoints(dataset);

        if (forAll) {
            double value = getStat(dataset, 0);
            for (int i = 0; i < getItemCount(); i++) {
                updateByIndex(i, value);
            }
        } else {
            for (int i = 0; i < getItemCount(); i++) {
                updateByIndex(i, getStat(dataset, i));
            }
        }
    }

    /**
     * Collect statistic for specified point
     * @param point point
     * @return calculated statistic
     */
    private double getStat(XYDataset dataset, double point) {
        info.reset();

        for (int series = 0; series < dataset.getSeriesCount(); series++) {
            if (forAll) {
                for (int x = 0; x < dataset.getItemCount(series); x++) {
                    Number y = dataset.getY(series, x);
                    info.add(y != null ? y.doubleValue() : 0.0);
                }
            } else {
                int x = getIndex(series, point, dataset);
                if (x != -1) {
                    Number y = dataset.getY(series, x);
                    info.add(y != null ? y.doubleValue() : 0.0);
                }
            }
        }

        return info.calculate();
    }

    /**
     * Returns index of specified x value
     * @param series series index (zero based)
     * @param value x value
     * @param dataset data set
     * @return index of specified x value (zero based)
     */
    int getIndex(int series, double value, XYDataset dataset) {
        for (int x = 0; x < dataset.getItemCount(series); x++) {
            if (value == dataset.getXValue(series, x)) {
                return x;
            }
        }
        return -1;
    }

    /**
     * {@inheritDoc}
     */
    public void datasetChanged(DatasetChangeEvent event) {
        if (!processEvents) {
            return;
        }
        processEvents = false;
        setNotify(false);
        updateData(event.getDataset() instanceof XYDataset ? (XYDataset) event.getDataset() : null);
        setNotify(true);
        processEvents = true;
    }
}
