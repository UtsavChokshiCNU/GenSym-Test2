package gensym.charts.properties;

import gensym.charts.Chart3D;
import gensym.charts.JFreeChartHolder;

import gensym.charts.j3d.renderers.*;

/**
 * <b>poly-mode</b> int property class.
 * This property controls several modes of the 3D chart
 */
public class PolyModeProperty extends PropValueBase<Integer> {

    /**
     * Polygon modes constants
     */
    public static final int PEPM_SURFACEPOLYGONS = 1;
    public static final int PEPM_3DBAR = 2;
    public static final int PEPM_POLYGONDATA = 3;
    public static final int PEPM_SCATTER = 4;

    /**
     * Constructor
     */
    public PolyModeProperty() {
        super(4013, "poly-mode");
    }

    /**
     * {@inheritDoc}
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof Chart3D) {
            Renderer3D renderer = ((Chart3D) chart.getChart()).getPlot().getRenderer();

            switch (value) {
                case PEPM_SURFACEPOLYGONS:
                case PEPM_POLYGONDATA:
                    renderer = new SurfaceRenderer3D(renderer);
                    break;

                case PEPM_3DBAR:
                    renderer = new BarRenderer3D(renderer);
                    break;

                case PEPM_SCATTER:
                    renderer = new LineAndShapeRenderer3D(renderer);
                    break;

                default:
                    renderer = null;
                    break;
            }

            if (renderer != null) {
                ((Chart3D) chart.getChart()).getPlot().setRenderer(renderer);
            }
        }
    }
}
