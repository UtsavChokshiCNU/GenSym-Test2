package gensym.charts.autostat;

/**
 * Maximum statistic
 */
public class MaxAutoStatInfo extends AbstractAutoStatInfo {
    /**
     * Maximum value
     */
    private double maxValue = Double.MIN_VALUE;
    
    /**
     * Constructor
     */
    public MaxAutoStatInfo() {
        super("Max");
    }

    /**
     * {@inheritDoc}
     */
    public double calculate() {
        return maxValue;
    }
    
    /**
     * {@inheritDoc}
     */
    public void add(double y) {
        super.add(y);
        maxValue = Math.max(maxValue, y);
    }
    
    /**
     * {@inheritDoc}
     */
    public void reset() {
        super.reset();
        maxValue = Double.MIN_VALUE;
    }
}
