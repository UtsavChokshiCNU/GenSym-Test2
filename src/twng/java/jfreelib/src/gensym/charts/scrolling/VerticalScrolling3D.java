package gensym.charts.scrolling;

import gensym.charts.j3d.Plot3D;

/**
 * Vertical scrolling 3D do rotation around X axis
 */
public class VerticalScrolling3D extends ChartScrolling3D {

    /**
     * Constructor
     * @param plot for ChartScrolling3D constructor
     */
    public VerticalScrolling3D(Plot3D plot) {
        super(plot);
    }

    /**
     * {@inheritDoc}
     */
    public void do3DRotation() {
        getPlot().rotateAroundX(Math.PI * (getScrollItemsCount() -
                getScrollItemPos()) / getScrollItemsCount());
    }
}
