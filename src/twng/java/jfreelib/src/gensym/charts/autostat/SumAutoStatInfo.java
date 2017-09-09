package gensym.charts.autostat;

public class SumAutoStatInfo extends AbstractAutoStatInfo {
    /**
     * Constructor
     */
    public SumAutoStatInfo() {
        super("Sum");
    }
    
    /**
     * {@inheritDoc}
     */
    public double calculate() {
        Double summ = 0.0; 
        for (Double y : getData()) {
            summ += y;
        }
        
        return summ;
    }
}
