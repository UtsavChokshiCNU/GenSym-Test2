package gensym.charts.properties.hotspot;

import gensym.charts.IDataHotSpots;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>allow-point-hot-spots</b> int property class.
 * This property controls whether point labels will be Hot-Spots.
 */
public class AllowPointHotSpotsProperty extends PropValueBase<Integer> {

    /**
     * Constructor
     */
    public AllowPointHotSpotsProperty() {
        super(2605, "allow-point-hot-spots");
    }

    /**
     * {@inheritDoc}
     * This property controls whether point labels will be Hot-Spots.
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof IDataHotSpots) {
            ((IDataHotSpots) chart.getChart()).setAllowPointHotSpots(value != 0);
        }
    }
}
