package gensym.charts.scrolling;

import gensym.charts.j3d.Plot3D;

import java.util.LinkedList;
import java.util.List;

/**
 * Child of ChartScrolling interface, used by 3D charts
 */
public abstract class ChartScrolling3D implements ChartScrolling {

    /** Scroll items count*/
    private static final int count = 500;
    /** Current scroll value*/
    private int value = 0;
    /** Plot3D for rotation*/
    private Plot3D plot = null;
    /** Scrolling listener */
    private List<ScrollingListener> listeners = new LinkedList<ScrollingListener>();

    /**
     * Constructor
     * @param plot Plot3D for rotation
     * @param interval part of Pi number
     */
    public ChartScrolling3D(Plot3D plot) {
        this.plot = plot;
    }

    /**
     * Do rotation
     */
    public abstract void do3DRotation();

    /**
     * Gets Plot3D
     * @return Plot3D instance
     */
    synchronized public Plot3D getPlot() {
        return plot;
    }

    /**
     * Adds scrolling listener
     * @param listener the scrolling listener to be added
     */
    public void addListener(ScrollingListener listener) {
        listeners.add(listener);
    }

    /**
     * Removes scrolling listener
     * @param listener the scrolling listener to be removed
     */
    public void removeListener(ScrollingListener listener) {
        listeners.remove(listener);
    }

    /**
     * Gets all added listeners
     * @return list of ScrollingListener's
     */
    public List<ScrollingListener> getListeners() {
        return listeners;
    }

    /**
     * {@inheritDoc}
     */
    synchronized public int getScrollItemPos() {
        return value;
    }

    /**
     * {@inheritDoc}
     */
    synchronized public int getScrollItemsCount() {
        return count;
    }

    /**
     * {@inheritDoc}
     */
    synchronized public boolean isScrollingSupported() {
        return true;
    }

    /**
     * {@inheritDoc}
     */
    synchronized public void updateScrollingPos(int newValue) {
        if (isScrollingSupported()) {
            value = newValue;
            do3DRotation();
            
            for (ScrollingListener listener : getListeners()) {
                listener.itemsScrolled();
            }
        }
    }
}
