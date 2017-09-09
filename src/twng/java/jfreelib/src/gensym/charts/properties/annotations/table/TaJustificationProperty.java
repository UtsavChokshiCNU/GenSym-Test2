package gensym.charts.properties.annotations.table;

import org.jfree.ui.HorizontalAlignment;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.properties.PropValueBase;

/**
 * <b>tajustification</b> int property class.
 * Sets cell text justification of current table annotation
 */
public class TaJustificationProperty extends PropValueBase<Integer> {
    /**
     * Left
     */
    public static final int PETAJ_LEFT = 0;

    /**
     * Left
     */
    public static final int PETAJ_CENTER = 1;

    /**
     * Left
     */
    public static final int PETAJ_RIGHT = 2;

    /**
     * Constructor
     */
    public TaJustificationProperty() {
        super(2969, "tajustification");
    }

    /**
     * {@inheritDoc}
     * Sets cell text justification of current table annotation
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
        if (chart.getChart() instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart.getChart();
            HorizontalAlignment alignment = HorizontalAlignment.CENTER;
            if (value == PETAJ_LEFT) {
                alignment = HorizontalAlignment.LEFT;
            } else if (value == PETAJ_RIGHT) {
                alignment = HorizontalAlignment.RIGHT;
            }

            graph.getAnnotations().getCurrentTableAnnotation().setAlignment(i, j, alignment);
        }
    }
}
