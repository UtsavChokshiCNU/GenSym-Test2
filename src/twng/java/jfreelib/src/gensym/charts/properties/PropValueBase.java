package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

/**
 * Base class for properties adapters, implements the main methods of IPropValue.
 * Delivered classes have to implement just setValueImpl() method that is abstract.
 */
public abstract class PropValueBase<PropType> implements IPropValue {
    /**
     * Property Id
     */
    private int id;

    /**
     * Property name
     */
    private String name;
    
    /**
     * Constructor
     * @param id property id
     * @param name property name
     */
    public PropValueBase(int id, String name) {
        this.id = id;
        this.name = name;
    }

    /**
     * {@inheritDoc}
     */
    public int getPropId() {
        return id;
    }

    /**
     * {@inheritDoc}
     */
    public String getPropName() {
        return name;
    }

    /**
     * Apply PE chart property value to JFree chart.
     * Is called from setValue() by casting last parameter to PropType. 
     * @param chart chart object
     * @param i i value of PE property
     * @param j j value of PE property
     * @param value PE property value
     */
    protected abstract void setValueImpl(JFreeChartHolder chart, int i, int j, PropType value);

    /**
     * {@inheritDoc}
     * Calls setValueImpl() by casting last parameter to PropType. 
     */
    public void setValue(JFreeChartHolder chart, int i, int j, Object value) {
        setValueImpl(chart, i, j, (PropType) value);
    }
}
