package gensym.charts.properties.legends;

import gensym.charts.properties.*;
import gensym.charts.JFreeChartHolder;

import org.jfree.chart.title.LegendTitle;
import org.jfree.ui.RectangleEdge;

/**
 * <b>legend-location</b> int property class.
 * Sets legend location 
 */
public class LegendLocationProperty extends PropValueBase<Integer> {

    /** Legends on Top */
    public static final int LOCATION_TOP = 0;
    
    /** Legends on Bottom */
    public static final int LOCATION_BOTTOM = 1;

    /** Legends on Left */
    public static final int LOCATION_LEFT = 2;

    /** Legends on Right */
    public static final int LOCATION_RIGHT = 3;

    /**
     * Constructor
     */
    public LegendLocationProperty() {
        super(3082, "legend-location");
    }

    /**
     * Returns position by location flag
     * @return position
     */
    private RectangleEdge getPosition(int location) {
        switch (location) {
            case LOCATION_TOP:
                return RectangleEdge.TOP;
            case LOCATION_LEFT:
                return RectangleEdge.LEFT;
            case LOCATION_RIGHT:
                return RectangleEdge.RIGHT;
        }

        return RectangleEdge.BOTTOM;
    }

    /**
     * {@inheritDoc}
     * Sets legend location
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        LegendTitle legend = chart.getChart().getChart().getLegend();
        if (legend != null) {
            legend.setPosition(getPosition(value));
        }
    }
}
