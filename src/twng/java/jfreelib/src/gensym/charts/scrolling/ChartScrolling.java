package gensym.charts.scrolling;

/**
 * Chart scrolling interface.
 */
public interface ChartScrolling {
    /**
     * Tests if scrolling feature is supported
     * @return true if scrolling feature is supported
     */
    boolean isScrollingSupported();
    
    /**
     * Returns count of scrolled items
     * @return count of scrolled items
     */
    public int getScrollItemsCount();
    
    /**
     * Returns current scroll position
     * @return the current scroll position
     */
    public int getScrollItemPos();
    
    /**
     * Updates scrolling position. Is called when scrolling position is changed
     * @param newValue new scroll value
     */
    public void updateScrollingPos(int newValue);
}
