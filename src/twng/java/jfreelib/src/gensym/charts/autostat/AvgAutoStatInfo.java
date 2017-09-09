package gensym.charts.autostat;

/**
 * Average statistic 
 */
public class AvgAutoStatInfo extends AbstractAutoStatInfo {
    /**
     * Constructor
     */
    public AvgAutoStatInfo() {
        super("Avg");
    }

    /**
     * Constructor with class name
     * @param name
     */
    public AvgAutoStatInfo(String name) {
        super(name);
    }
    
    /**
     * {@inheritDoc}
     */
    public double calculate() {
        Double summ = 0.0; 
        for (Double y : getData()) {
            summ += y;
        }
        
        return getData().size() > 0 ? summ / getData().size() : 0.0;
    }
}
