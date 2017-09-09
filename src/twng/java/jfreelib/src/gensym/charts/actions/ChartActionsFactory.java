package gensym.charts.actions;

import java.util.Map;
import java.util.LinkedHashMap;

/**
 * Charts action factory.
 * Use registerAction() to register action and makeAction() to get it.
 */
public class ChartActionsFactory {
    /**
     * Actions factory exception
     */
    public static class ChartActionsFactoryException extends Exception {
        /**
         * Generated serial version UID
         */
        private static final long serialVersionUID = -227882911974975838L;

        /**
         * Constructor
         * @param message error message
         */
        public ChartActionsFactoryException(String message) {
            super(message);
        }
    }

    /**
     * Actions map
     */
    private static Map<String, IChartAction> actions = new LinkedHashMap<String, IChartAction>();


    /**
     * Gets action object by name
     * @param actionName action name
     * @return action
     * @throws ChartActionsFactoryException if there is not action named by name
     */
    public static IChartAction makeAction(String actionName) throws ChartActionsFactoryException {
        IChartAction action = actions.get(actionName);

        if (action == null) {
            throw new ChartActionsFactoryException("Unknown action type: " + actionName);
        }

        try {
            return (IChartAction) action.clone();
        } catch (CloneNotSupportedException e) {
            throw new ChartActionsFactoryException("Cant make action");
        }
    }

    /**
     * Registers action object
     * @param action action object
     */
    public static void registerAction(IChartAction action) {
        actions.put(action.getName(), action);
    }

    /**
     * Register known actions
     */
    static {
        SetValueActions.register();

        registerAction(new CreateChartAction());
        registerAction(new TestChartAction());
        registerAction(new UpdateChartAction());
        registerAction(new CopyChartAction());
        registerAction(new DestroyChartAction());
        registerAction(new PrintChartAction());
        registerAction(new ExportChartAction());
    }
}
