package gensym.charts.properties.contour;

import gensym.charts.Chart3D;
import gensym.charts.JFreeChartHolder;
import gensym.charts.j3d.renderers.SurfaceRenderer3D;
import gensym.charts.properties.PropValueBase;

/**
 * <b>manual-contour-line</b> int property class.
 * Sets delta z value for 3D chart, if renderer is SurfaceRenderer3D
 */
public class ManualContourLineProperty extends PropValueBase<Double> {

    /** Min value of this property */
    public static final int minValue = 20;
    
    /**
     * Constructor
     */
    public ManualContourLineProperty() {
        super(4027, "manual-contour-line");
    }

    /**
     * {@inheritDoc}
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Double value) {
        if (value > 0) {
            if (chart.getChart() instanceof Chart3D) {
                Chart3D chart3d = (Chart3D)chart.getChart();
                if (chart3d.getPlot().getRenderer() instanceof SurfaceRenderer3D) {
                    SurfaceRenderer3D renderer = (SurfaceRenderer3D)chart3d.getPlot().getRenderer();
                    renderer.setDeltaZ(value.intValue() > minValue ? value.intValue() : minValue);
                }
            }
        }
    }    
}
