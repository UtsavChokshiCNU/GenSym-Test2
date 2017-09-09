package gensym.charts.scrolling;

import java.util.LinkedList;
import java.util.List;

import gensym.charts.SourceXYZDataset;

public class GraphSeriesScrolling implements ChartScrolling {
    /**
     * Current scrolling position
     */
    private int scrollingPos = 0;
    
    /**
     * Count of items to scroll
     */
    private int itemsToScroll = 1;
    
    /**
     * Scrolling dataset
     */
    private ScrollingDataset dataset;
    
    /**
     * Scrolling listener
     */
    private List<SeriesScrollingListener> listeners = new LinkedList<SeriesScrollingListener>();
    
    /**
     * Constructor
     * @param items count of items to scroll
     * @param dataset the source dataset
     * @param plot the plot
     */
    public GraphSeriesScrolling(int items, SourceXYZDataset dataset) {
        itemsToScroll = items;
        this.dataset = new ScrollingDataset(dataset);
    }
    
    /**
     * Returns scrolling dataset
     * @return the scrolling dataset
     */
    public ScrollingDataset getDataset() {
        return dataset;
    }
    
    /**
     * Returns count of items to scroll
     * @return the count of items to scroll
     */
    public int getScrolledItems() {
        return itemsToScroll;
    }

    /**
     * Adds scrolling listener 
     * @param listener the scrolling listener to be added
     */
    public void addListener(SeriesScrollingListener listener) {
        listeners.add(listener);
    }
    
    /**
     * Removes scrolling listener 
     * @param listener the scrolling listener to be removed
     */
    public void removeListener(SeriesScrollingListener listener) {
        listeners.remove(listener);
    }

    /**
     * {@inheritDoc}
     */
    public int getScrollItemPos() {
        return scrollingPos;
    }

    /**
     * {@inheritDoc}
     */
    public int getScrollItemsCount() {
        if (isScrollingSupported()) {
            boolean addOne = dataset.getSeriesCount() % itemsToScroll > 0;
            return dataset.getSeriesCount() / itemsToScroll + (addOne ? 1 : 0);
        }
        return 0;
    }

    /**
     * {@inheritDoc}
     */
    public boolean isScrollingSupported() {
        return itemsToScroll > 0 && itemsToScroll < dataset.getSeriesCount();
    }

    /**
     * {@inheritDoc}
     */
    public void updateScrollingPos(int newValue) {
        if (isScrollingSupported()) {
            scrollingPos = newValue;
            int itemIndex = itemsToScroll * getScrollItemPos();
            if (itemIndex + itemsToScroll >= dataset.getSeriesCount()) {
                itemIndex = dataset.getSeriesCount() - itemsToScroll;
            }

            LinkedList<Integer> items = new LinkedList<Integer>();
            for (int index = 0; index < itemsToScroll; index++) {
                items.add(itemIndex + index);
            }
            dataset.setItems(items);
            
            updateListeners(items);
        }
    }
    
    /**
     * Updates listeners
     * @param items
     */
    protected void updateListeners(List<Integer> items) {
        for (SeriesScrollingListener listener : listeners) {
            listener.itemsScrolled(items);
        }
    }
    
    /**
     * Sets count of scrolling items
     * @param count the count of scrolling items
     */
    public void setScrollingItems(int count, boolean update) {
        itemsToScroll = count;
        if (update) {
            updateScrollingPos(0);
        }
    }
}
