package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

/**
 * <b>graph-plus-table</b> int property class.
 * Sets graph view mode: graph, table of both.
 */
public class GraphPlusTableProperty extends PropValueBase<Integer> {

    /**
     * PE chart view mode constants
     */
    public final static int PEGPT_GRAPH = 0;
    public final static int PEGPT_TABLE = 1;
    public final static int PEGPT_BOTH = 2;

    /**
     * Constructor
     */
    public GraphPlusTableProperty() {
        super(3355, "graph-plus-table");
    }

    /**
     * {@inheritDoc}
     * Sets graph view mode: graph, table of both.
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        chart.setChartVisible(value != PEGPT_TABLE);
        chart.setTableVisible(value != PEGPT_GRAPH);
    }
}
