package gensym.charts.properties.hotspot;

import gensym.charts.IDataHotSpots;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>allow-subset-hot-spots</b> int property class.
 * This property controls whether subset legend items will be Hot-Spots.
 */
public class AllowSubsetHotSpotsProperty extends PropValueBase<Integer> {

    /**
     * Constructor
     */
    public AllowSubsetHotSpotsProperty() {
        super(2600, "allow-subset-hot-spots");
    }

    /**
     * {@inheritDoc}
     * This property controls whether subset legend items will be Hot-Spots.
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof IDataHotSpots) {
            ((IDataHotSpots) chart.getChart()).setAllowSeriesHotSpots(value != 0);
        }
    }
}
