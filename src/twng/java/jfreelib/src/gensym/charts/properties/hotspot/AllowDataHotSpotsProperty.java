package gensym.charts.properties.hotspot;

import gensym.charts.JFreeChartHolder;
import gensym.charts.IDataHotSpots;
import gensym.charts.properties.PropValueBase;

/**
 * <b>allow-data-hot-spots</b> int property class.
 * This property controls whether data-points will be Hot-Spots.
 */
public class AllowDataHotSpotsProperty extends PropValueBase<Integer> {

    /**
     * Constructor
     */
    public AllowDataHotSpotsProperty() {
        super(3210, "allow-data-hot-spots");
    }

    /**
     * {@inheritDoc}
     * Sets allow data-points hot-spots.
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof IDataHotSpots) {
            ((IDataHotSpots) chart.getChart()).setAllowDataHotSpots(value != 0);
        }
    }
}
