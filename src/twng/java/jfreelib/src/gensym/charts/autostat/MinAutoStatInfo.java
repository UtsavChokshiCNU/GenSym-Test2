package gensym.charts.autostat;

/**
 * Minimum statistic
 */
public class MinAutoStatInfo extends AbstractAutoStatInfo {
    /**
     * Minimum value
     */
    private double minValue = Double.MAX_VALUE;
    
    /**
     * Constructor
     */
    public MinAutoStatInfo() {
        super("Min");
    }

    /**
     * {@inheritDoc}
     */
    public double calculate() {
        return minValue;
    }
    
    /**
     * {@inheritDoc}
     */
    public void add(double y) {
        super.add(y);
        minValue = Math.min(minValue, y);
    }
    
    /**
     * {@inheritDoc}
     */
    public void reset() {
        super.reset();
        minValue = Double.MAX_VALUE;
    }
}
