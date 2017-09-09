package gensym.charts.properties;

import gensym.charts.JFreeChartHolder;

/**
 * <b>main-title</b> string property class.
 * Sets chart title
 */
public class MainTitleProperty extends PropValueBase<String> {
    /**
     * Constructor
     */
    public MainTitleProperty() {
        super(2105, "main-title");
    }

    /**
     * {@inheritDoc}
     * Sets chart title
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, String value) {
        // Make normal title
        String newTitle = value.replace("|", "                          ");
        chart.getChart().getChart().setTitle(newTitle);
    }
}
