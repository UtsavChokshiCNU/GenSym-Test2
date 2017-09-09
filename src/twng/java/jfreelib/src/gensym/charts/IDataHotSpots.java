package gensym.charts;

/**
 * Hot spots data interface
 */
public interface IDataHotSpots {

    /**
     * Returns allowing data hot spot flag
     * @return true if allowing data hot spot is enabled
     */
    public boolean isDataHotSpotsAllowed();

    /**
     * Sets allow data-points hot-spots.
     * @param allow true or false (allow or not)
     */
    public void setAllowDataHotSpots(boolean allow);

    /**
     * Returns allowing series hot spot flag
     * @return true if allowing series hot spot is enabled
     */
    public boolean isSeriesHotSpotsAllowed();

    /**
     * Sets allowing series hot spot flag
     * @param allow hot spot allowing flag
     */
    public void setAllowSeriesHotSpots(boolean allow);

    /**
     * Returns allowing point hot spot flag
     * @return true if allowing point hot spot is enabled
     */
    public boolean isPointHotSpotsAllowed();

    /**
     * Sets allowing point hot spot flag
     * @param allow hot spot allowing flag
     */
    public void setAllowPointHotSpots(boolean allow);
}
