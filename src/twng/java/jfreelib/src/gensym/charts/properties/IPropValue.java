package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

/**
 * IPropValue interface provides methods to apply PE chart properties to JFree charts.
 */
public interface IPropValue {
    /**
     * Returns corresponding PE chart property Id
     * @return property Id
     */
    public int getPropId();

    /**
     * Returns corresponding PE chart property name used in G2
     * @return property name
     */
    public String getPropName();

    /**
     * Apply PE chart property value to JFree chart
     * @param chart chart object
     * @param i i value of PE property
     * @param j j value of PE property
     * @param value PE property value 
     */
    public void setValue(JFreeChartHolder chart, int i, int j, Object value);
}
