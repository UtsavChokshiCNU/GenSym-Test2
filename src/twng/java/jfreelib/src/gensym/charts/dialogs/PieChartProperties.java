package gensym.charts.dialogs;

import java.awt.GridLayout;
import javax.swing.JCheckBox;
import javax.swing.JPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.editor.ChartEditor;
import org.jfree.chart.plot.PiePlot;
import org.jfree.chart.plot.Plot;

public class PieChartProperties extends JPanel implements ChartEditor {
    /**
     * Generated serial version UID
     */
    private static final long serialVersionUID = -772556865898030262L;

    /**
     * Show labels inside sections checkBox
     */
    private JCheckBox showLabelsInside = new JCheckBox("Show labels inside sections");
    
    /**
     * Return PiePlot for JFreeChart
     * @return PiePlot
     */
    public PiePlot getPlot(JFreeChart chart) {
    	if (chart != null) {
  	    Plot plot = chart.getPlot();
    	    if (plot instanceof PiePlot) {
                return (PiePlot) plot;
            }
    	}
        return null;
    }

    /**
     * Constructor
     */
    public PieChartProperties(JFreeChart chart) {
        setLayout(new GridLayout(1, 1));
        setOpaque(true);
        
        add(showLabelsInside);
        showLabelsInside.setSelected(getPlot(chart).getSimpleLabels());
    }

    /**
     * {@inheritDoc}
     */
    public void updateChart(JFreeChart chart) {
    	PiePlot pPlot = getPlot(chart);
    	if (pPlot != null) {
            pPlot.setSimpleLabels(showLabelsInside.isSelected());
        }
    }
}
