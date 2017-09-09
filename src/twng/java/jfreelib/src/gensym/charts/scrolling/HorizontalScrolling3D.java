package gensym.charts.scrolling;

import gensym.charts.j3d.Plot3D;

/**
 * Horizontal scrolling 3D do rotation around Z axis
 */
public class HorizontalScrolling3D extends ChartScrolling3D {

    /**
     * Constructor
     * @param plot for ChartScrolling3D constructor
     */
    public HorizontalScrolling3D(Plot3D plot) {
        super(plot);
    }

    /**
     * {@inheritDoc}
     */
    public void do3DRotation() {
        getPlot().rotateAroundZ(2 * Math.PI * getScrollItemPos() / getScrollItemsCount());
    }
}
