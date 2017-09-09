package gensym.charts.actions;

import gensym.charts.JFreeChartHolder;
import org.w3c.dom.Element;

/**
 * Chart Action interface.
 */
public interface IChartAction extends Cloneable {
    /**
     * Chart action exception class
     */
    public static class ChartActionException extends Exception {
        /**
         * Generated serial version UID
         */
        private static final long serialVersionUID = -5880724105467530463L;

        /**
         * Constructor
         * @param message error message
         */
        public ChartActionException(String message) {
            super(message);
        }
    }

    /**
     * Initializes action by data from XML
     * @param data root XML element containing necessary data
     * @throws ChartActionException
     */
    public void setData(Element data) throws ChartActionException;

    /**
     * Execute action
     * @param chart chart object
     * @throws ChartActionException
     */
    public void execute(JFreeChartHolder chart) throws ChartActionException;

    /**
     * Clones action
     * @return copy of action object
     * @throws CloneNotSupportedException
     */
    public Object clone() throws CloneNotSupportedException;

    /**
     * Returns action name
     * @return action name
     */
    public String getName();

    /**
     * Returns whether chart has to be created for action before executing
     * @return
     */
    public boolean isChartRequired();
}
