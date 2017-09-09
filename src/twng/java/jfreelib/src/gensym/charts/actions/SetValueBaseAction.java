package gensym.charts.actions;


import gensym.charts.ChartsCommon;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.IPropValue;
import gensym.charts.properties.factory.PropValueFactory;

import org.w3c.dom.Element;

/**
 * Base class for Set* actions.
 * Initializes Set* action common data, delegates delivered classes reading value operation and executes action by
 *  delegeting request to property object given by property id.
 * XML data tags:
 *  <b>property</b> - property id
 *  <b>i</b> and <b>j</b> PE charts <b>i</b> and <b>j</b> value
 *  <b>value</b> - property value 
 */
public abstract class SetValueBaseAction<PropType> implements IChartAction {

    /**
     * Action name
     */
    private String name;

    /** Property id */
    private int propId;

    /** PE chart i value */
    private int i;
    /** PE chart j value */
    private int j;

    /** Property value value */
    private PropType value;

    /**
     * Constructor
     * @param name action name
     */
    public SetValueBaseAction(String name) {
        this.name = name;
    }

    /**
     *  {@inheritDoc}
     */
    public void setData(Element data) throws ChartActionException {
        propId = ChartsCommon.getIntValue(data, "property");
        i = ChartsCommon.getIntValue(data, "i");
        j = ChartsCommon.getIntValue(data, "j");

        value = getValue(data);
    }

    /**
     * Reads and returns property value to be set
     * @param data XML data root element
     * @return property value to be set 
     * @throws ChartActionException
     */
    protected abstract PropType getValue(Element data) throws ChartActionException;

    /**
     * {@inheritDoc}
     * Gets property by id and delegates request to it.
     */
    public void execute(JFreeChartHolder chart) throws ChartActionException {
        IPropValue valType = PropValueFactory.makeValue(propId, name);

        if (valType == null) {
            throw new ChartActionException("Invalid property: " + propId);
        }
        
        valType.setValue(chart, i, j, value);
    }

    /**
     *  {@inheritDoc}
     */
    public Object clone() throws CloneNotSupportedException {
        return super.clone();
    }

    /**
     *  {@inheritDoc}
     */
    public String getName() {
        return name;
    }

    /**
     * {@inheritDoc}
     * Returns true.
     */
    public boolean isChartRequired() {
        return true;
    }
}
