package gensym.charts.scrolling;

import java.util.List;

/**
 * Series scrolling listener interface
 */
public interface SeriesScrollingListener {
    /**
     * Scrolled items callback
     * @param items list of visible items
     */
    public void itemsScrolled(List<Integer> items);
}
