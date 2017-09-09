package gensym.charts.actions;

import gensym.charts.ChartsCommon;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

import java.util.List;
import java.util.ArrayList;

/**
 * Set* actions initializer
 */
public class SetValueActions {
    /**
     * Register all known Set* actions
     */
    public static void register() {
        ChartActionsFactory.registerAction(new SetIntValueAction());
        ChartActionsFactory.registerAction(new SetDoubleValueAction());
        ChartActionsFactory.registerAction(new SetDoubleArrayValueAction());
        ChartActionsFactory.registerAction(new SetStringValueAction());
    }

    /** Action name SetInt */
    public final static String SetInt = "SetInt";

    /** Action name SetDouble */
    public final static String SetDouble = "SetDouble";

    /** Action name SetDoubleArray */
    public final static String SetDoubleArray = "SetDoubleArray";

    /** Action name SetString */
    public final static String SetString = "SetString";
}

/**
 * SetInt action
 */
class SetIntValueAction extends SetValueBaseAction<Integer> {
    /**
     * Constructor
     */
    public SetIntValueAction() {
        super(SetValueActions.SetInt);
    }

    /**
     * {@inheritDoc}
     */
    protected Integer getValue(Element data) throws ChartActionException {
        return ChartsCommon.getIntValue(data, "value");
    }
}

/**
 * SetDouble action
 */
class SetDoubleValueAction extends SetValueBaseAction<Double> {
    /**
     * Constructor
     */
    public SetDoubleValueAction() {
        super(SetValueActions.SetDouble);
    }

    /**
     * {@inheritDoc}
     */
    protected Double getValue(Element data) throws ChartActionException {
        return ChartsCommon.getDoubleValue(ChartsCommon.getElementValue(data, "value"));
    }
}

/**
 * SetDoubleArray action
 */
class SetDoubleArrayValueAction extends SetValueBaseAction<List<Double>> {
    /**
     * Constructor
     */
    public SetDoubleArrayValueAction() {
        super(SetValueActions.SetDoubleArray);
    }

    /**
     * {@inheritDoc}
     */
    protected List<Double> getValue(Element data) throws ChartActionException {
        NodeList values = ChartsCommon.getChildElement(data, "value").getElementsByTagName("item");

        List<Double> value = new ArrayList<Double>(values.getLength());

        for (int index = 0; index < values.getLength(); index++) {
            value.add(ChartsCommon.getDoubleValue(values.item(index).getFirstChild().getNodeValue()));
        }

        return value;
    }
}

/**
 * SetString action
 */
class SetStringValueAction extends SetValueBaseAction<String> {
    /**
     * Constructor
     */
    public SetStringValueAction() {
        super(SetValueActions.SetString);
    }

    /**
     * {@inheritDoc}
     */
    protected String getValue(Element data) throws ChartActionException {
        return ChartsCommon.getElementValue(data, "value");
    }
}