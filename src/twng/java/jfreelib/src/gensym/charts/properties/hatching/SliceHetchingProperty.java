package gensym.charts.properties.hatching;

import gensym.charts.JFreeChartHolder;
import gensym.charts.PieChart;
import gensym.charts.properties.PropValueBase;

/**
 * <b>slice-hatching</b> int property class.
 * Sets slice hatching type
 */
public class SliceHetchingProperty extends PropValueBase<Integer> {
    
    /** PE constant: Only Monochrome gets hatched */
    public static final int PESH_MONOCHROME = 0;
    /** PE constant: Both Monochrome and color images get hatched */
    public static final int PESH_BOTH = 1;
    
    /**
     * Constructor
     */
    public SliceHetchingProperty() {
        super(3923, "slice-hatching");
    }

    /**
     * {@inheritDoc}
     * Sets series color
     */
    protected void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof PieChart) {
            ((PieChart) chart.getChart()).setSliceHatching(value == PESH_BOTH);
        }
        
    }

}
