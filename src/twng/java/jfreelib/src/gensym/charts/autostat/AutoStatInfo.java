package gensym.charts.autostat;

/**
 * Auto statistic info 
 */
public interface AutoStatInfo {
    /**
     * Resets state
     */
    void reset();
    
    /**
     * Add Y value
     * @param y Y value
     */
    void add(double y);
    
    /**
     * Calculates statistic
     * @return calculated value
     */
    double calculate();
    
    /**
     * Returns stat name
     * @return stat name
     */
    String getName();
}
