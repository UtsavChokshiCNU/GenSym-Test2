package gensym.charts.dialogs;

import java.awt.BorderLayout;

import gensym.charts.AbstractChart;

import javax.swing.BorderFactory;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;

import org.jfree.chart.JFreeChart;
import org.jfree.chart.editor.ChartEditor;
import org.jfree.chart.editor.DefaultChartEditorFactory;

/**
 * Chart properties panel 
 */
public class ChartPropertiesDialog extends JPanel implements ChartEditor {
    /**
     * Generated version UID 
     */
    private static final long serialVersionUID = 6113784811786161914L;

    /**
     * Chart editor
     */
    private ChartEditor chartEditor = null;

    /**
     * Default JFree chart editor
     */
    private ChartEditor defChartEditor = null;

    /**
     * Constructor
     * @param chart the chart
     */
    public ChartPropertiesDialog(AbstractChart chart) {
        defChartEditor = new DefaultChartEditorFactory().createEditor(chart.getChart());
        chartEditor = chart.makeChartEditor();

        JTabbedPane tabs = new JTabbedPane();

        if (defChartEditor instanceof JPanel) {
            tabs.addTab("Chart Properties", (JPanel) defChartEditor);
        }

        JPanel general = new JPanel(new BorderLayout());
        general.setBorder(BorderFactory.createTitledBorder(BorderFactory.createEtchedBorder(), chart.getName()));

        if (chartEditor instanceof JPanel) {
            general.add((JPanel) chartEditor, BorderLayout.NORTH);
            tabs.addTab("Additional Properties", general);
        }

        JPanel parts = new JPanel(new BorderLayout());
        parts.add(tabs, BorderLayout.NORTH);
        add(parts);
    }

    /**
     * {@inheritDoc}
     */
    public void updateChart(JFreeChart chart) {
        if (chart != null) {
            if (defChartEditor != null) {
                defChartEditor.updateChart(chart);
            }
            if (chartEditor != null) {
                chartEditor.updateChart(chart);
            }
            chart.fireChartChanged();
        }
    }
}
