package gensym.charts.autostat;

import java.util.LinkedList;
import java.util.List;

/**
 * Abstract class implements AutoStatInfo interface.
 * delivered classes have to implement AutoStatInfo.calculate() method.
 */
public abstract class AbstractAutoStatInfo implements AutoStatInfo {
    /**
     * Name
     */
    String name = null;
    
    /**
     * Statistic data
     */
    private List<Double> data = new LinkedList<Double>(); 

    /**
     * Constructor
     * @param name statistic name
     */
    public AbstractAutoStatInfo(String name) {
        this.name = name;
    }

    /**
     * {@inheritDoc}
     */
    public void add(double y) {
        data.add(y);
    }

    /**
     * {@inheritDoc}
     */
    public void reset() {
        data.clear();
    }

    /**
     * {@inheritDoc}
     */
    protected List<Double> getData() {
        return data;
    }
    
    /**
     * {@inheritDoc}
     */
    public String getName() {
        return name;
    }
}
