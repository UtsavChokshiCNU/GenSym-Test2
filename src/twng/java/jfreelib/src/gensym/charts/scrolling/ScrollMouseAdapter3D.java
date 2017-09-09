package gensym.charts.scrolling;

import gensym.charts.Chart3D;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

/**
 * Mouse Adapter for 3D scrolling
 */
public class ScrollMouseAdapter3D extends MouseAdapter {

    /** Chart3D chart */
    private Chart3D chart;

    /**
     * Constructor
     * @param pane demo pane
     */
    public ScrollMouseAdapter3D(Chart3D chart) {
        this.chart = chart;
    }

    /**
     * {@inheritDoc}
     */
    public void mousePressed(MouseEvent e) {
        if (e.getClickCount() == 1 && !chart.getAutoRotation().isRunning()) {
            chart.getPlot().setRotationMode();
        }
    }

    /**
     * {@inheritDoc}
     */
    public void mouseReleased(MouseEvent e) {
        if ( !chart.getAutoRotation().isRunning() ) {
            chart.getPlot().leaveRotationMode();
        }
    }
}
