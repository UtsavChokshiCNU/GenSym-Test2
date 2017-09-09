package gensym.charts.properties.rotation;

import gensym.charts.Chart3D;
import gensym.charts.JFreeChartHolder;
import gensym.charts.j3d.renderers.Renderer3D;
import gensym.charts.properties.PropValueBase;

/**
 * <b>rotation-detail</b> int property class.
 * This property sets chart view during rotation.
 */
public class RotationDetailProperty extends PropValueBase<Integer> {

    /**
     * Constructor
     */
    public RotationDetailProperty() {
        super(4005, "rotation-detail");
    }

    /**
     * {@inheritDoc}
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof Chart3D) {
            if (value >= Renderer3D.DETAILS_WIREFRAME && value <= Renderer3D.DETAILS_FULL) {
                ((Chart3D) chart.getChart()).getPlot().setRotationDetail(value);
            }
        }
    }
}
