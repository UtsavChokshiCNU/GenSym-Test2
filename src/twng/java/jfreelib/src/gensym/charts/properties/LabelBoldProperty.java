package gensym.charts.properties;

import gensym.charts.*;

import gensym.charts.j3d.Axis3D;
import gensym.charts.j3d.Plot3D;
import java.awt.Font;

import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.Plot;
import org.jfree.chart.title.*;

/**
 * <b>label-bold</b> int property class.
 * Sets label bold
 */
public class LabelBoldProperty extends PropValueBase<Integer> {
    /**
     * Constructor
     */
    public LabelBoldProperty() {
        super(2530, "label-bold");
    }

    /**
     * {@inheritDoc}
     * Sets label bold
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        for (JFreeChart jchart : chart.getChart().getCharts()) {
            for (Object obj : jchart.getSubtitles()) {
                Title title  = (Title) obj;
                if (title instanceof LegendTitle) {
                    LegendTitle legendTitle = (LegendTitle) title;
                    legendTitle.setItemFont(ChartsCommon.deriveFont(legendTitle.getItemFont(), Font.BOLD, value != 0));
                }
            }
        }
        Plot plot = chart.getChart().getChart().getPlot();
        if (plot instanceof Plot3D) {
            updateAxis3D(((Plot3D)plot).getXAxis(), value);
            updateAxis3D(((Plot3D)plot).getYAxis(), value);
            updateAxis3D(((Plot3D)plot).getZAxis(), value);
        }
    }

    /**
     * Update label font for in given Axis3D
     * @param axis Axis3D
     * @param value 1 - bold, 0 - simple
     */
    private void updateAxis3D(Axis3D axis, Integer value) {
        Font font = axis.getLabelFont();
        axis.setLabelFont(ChartsCommon.deriveFont(font, Font.BOLD, value != 0));
    }
}
