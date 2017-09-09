package gensym.charts.tests;

import gensym.charts.actions.CreateChartAction;
import gensym.charts.GraphChart;
import gensym.charts.autostat.AvgAutoStatInfo;
import gensym.charts.autostat.AvgWithStdDevs;
import gensym.charts.autostat.MaxAutoStatInfo;
import gensym.charts.autostat.MinAutoStatInfo;
import gensym.charts.autostat.SumAutoStatInfo;
import gensym.charts.autostat.XYAutoStatSeries;
import gensym.charts.autostat.XYParetoDataset;
import gensym.charts.properties.AutoStatSubsetsProperty;

import org.jfree.data.general.DatasetChangeEvent;
import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

/**
 * Tests Autostat
 */
public class AutoStatTest extends TestChartBase {

    /**
     * Tests auto-stat-subsets prop for one passed value
     * @param type of the AutoStat
     * @param nameToCheck class name of AutoStat
     */
    private void checkOneAutoStat(int type, Class<?> nameToCheck) {
        assertNotNull(getChart());
        assertEquals(GraphChart.class, getChart().getClass());
        GraphChart chart = (GraphChart) getChart();
        try {
            runAction("SetInt", "property", 3300, "i", 0, "j", 0, "value", type);
            assertNotNull(chart.getStatDataset());
            XYSeriesCollection collection = chart.getStatDataset();
            int index = collection.getSeriesCount() - 1;
            assertEquals(XYAutoStatSeries.class, collection.getSeries(index).getClass());
            XYAutoStatSeries series = (XYAutoStatSeries) collection.getSeries(index);
            assertEquals(series.getAutoStatInfo().getClass(), nameToCheck);
            assertNotNull(series.getAutoStatInfo().getName());
            series.getAutoStatInfo().reset();
            series.getAutoStatInfo().add(1);
            series.getAutoStatInfo().add(2);
            assertNotNull(series.getAutoStatInfo().calculate());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Checks pareto autostat
     * @param type of pareto
     */
    private void checkPareto(int type) {
        assertTrue(getChart() instanceof GraphChart);
        GraphChart chart = (GraphChart) getChart();
        try {
            runAction("SetInt", "property", 3300, "i", 0, "j", 0, "value", type);
            int datasetIndex = type == AutoStatSubsetsProperty.PEAS_PARETO_ASC ? 2 : 3;
            
            assertNotNull(chart.getPlot().getCurrentPlot());

            XYDataset xyDataet = chart.getPlot().getCurrentPlot().getDataset(datasetIndex);
            assertTrue(xyDataet instanceof XYParetoDataset);
            XYParetoDataset dataset = (XYParetoDataset) xyDataet;
            dataset.update(getXYSeriesCollection("Subset 1", "Subset 2"));
            assertNotNull(chart.getPlot().getCurrentPlot().getDataset(datasetIndex));
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Create and return dataset
     * @param name1 name of the first Series
     * @param name2 name of the second Series
     * @return created dataset
     */
    private XYSeriesCollection getXYSeriesCollection(String name1, String name2) {
        XYSeriesCollection dataset = new XYSeriesCollection();
        XYSeries series1 = new XYSeries(name1, false, false);
        XYSeries series2 = new XYSeries(name2, false, false);
        for (int i = 21; i < 56; i += 2) {
            series1.add(i, i + 1);
            series2.add(i, i - 1);
        }
        dataset.addSeries(series1);
        dataset.addSeries(series2);
        return dataset;
    }

    /**
     * Checks XYParetoDataset
     */
    private void checkParetoDataset() {
        assertTrue(getChart() instanceof GraphChart);
        GraphChart chart = (GraphChart) getChart();
        assertNotNull(chart.getPlot().getCurrentPlot());

        int type = AutoStatSubsetsProperty.PEAS_PARETO_DEC;
        int datasetIndex = type == AutoStatSubsetsProperty.PEAS_PARETO_ASC ? 2 : 3;
        try {
            runAction("SetInt", "property", 3300, "i", 0, "j", 0, "value", type);
            
            XYDataset xyDataet = chart.getPlot().getCurrentPlot().getDataset(datasetIndex);
            assertTrue(xyDataet instanceof XYParetoDataset);
            XYParetoDataset dataset = (XYParetoDataset) xyDataet;

            DatasetChangeEvent event = new DatasetChangeEvent(chart, dataset);
            dataset.datasetChanged(event);
            assertNotNull(chart.getPlot().getCurrentPlot().getDataset(datasetIndex));
            dataset.update(new XYSeriesCollection());
            assertNotNull(chart.getPlot().getCurrentPlot().getDataset(datasetIndex));
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Checks XYAutoStatSeries
     */
    private final void checkXYAutoStatSeries() {
        assertNotNull(getChart());
        assertEquals(GraphChart.class, getChart().getClass());
        GraphChart chart = (GraphChart) getChart();

        XYAutoStatSeries autoSeries1 = new XYAutoStatSeries(new AvgAutoStatInfo(), false);
        XYAutoStatSeries autoSeries2 = new XYAutoStatSeries(new AvgAutoStatInfo(), true);
        assertNotNull(autoSeries1);
        assertNotNull(autoSeries2);

        int size1 = autoSeries1.getItemCount();
        int size2 = autoSeries2.getItemCount();
        autoSeries1.updateData(null);
        autoSeries2.updateData(null);
        assertEquals(autoSeries1.getItemCount(), size1);
        assertEquals(autoSeries2.getItemCount(), size2);

        int newSize = 18;
        autoSeries1.updateData(getXYSeriesCollection("s1", "s2"));
        autoSeries2.updateData(getXYSeriesCollection("s3", "s4"));
        assertEquals(autoSeries1.getItemCount(), newSize);
        assertEquals(autoSeries2.getItemCount(), newSize);

        DatasetChangeEvent event = new DatasetChangeEvent(chart, getXYSeriesCollection("s5", "s6"));
        autoSeries1.datasetChanged(event);
        assertEquals(autoSeries1.getItemCount(), newSize);
    }

    /**
     * Tests all posible values for auto-stat-subsets
     */
    public final void testAutoStat() {
        doCreateAction(CreateChartAction.PE_GRAPH_CHART);

        checkOneAutoStat(AutoStatSubsetsProperty.PEAS_MINAP, MinAutoStatInfo.class);
        checkOneAutoStat(AutoStatSubsetsProperty.PEAS_MINPP, MinAutoStatInfo.class);

        checkOneAutoStat(AutoStatSubsetsProperty.PEAS_MAXAP, MaxAutoStatInfo.class);
        checkOneAutoStat(AutoStatSubsetsProperty.PEAS_MAXPP, MaxAutoStatInfo.class);

        checkOneAutoStat(AutoStatSubsetsProperty.PEAS_AVGAP, AvgAutoStatInfo.class);
        checkOneAutoStat(AutoStatSubsetsProperty.PEAS_AVGPP, AvgAutoStatInfo.class);

        checkOneAutoStat(AutoStatSubsetsProperty.PEAS_SUMPP, SumAutoStatInfo.class);

        checkOneAutoStat(AutoStatSubsetsProperty.PEAS_P1SDAP, AvgWithStdDevs.class);
        checkOneAutoStat(AutoStatSubsetsProperty.PEAS_P1SDPP, AvgWithStdDevs.class);
        checkOneAutoStat(AutoStatSubsetsProperty.PEAS_P2SDAP, AvgWithStdDevs.class);
        checkOneAutoStat(AutoStatSubsetsProperty.PEAS_P2SDPP, AvgWithStdDevs.class);
        checkOneAutoStat(AutoStatSubsetsProperty.PEAS_P3SDAP, AvgWithStdDevs.class);
        checkOneAutoStat(AutoStatSubsetsProperty.PEAS_P3SDPP, AvgWithStdDevs.class);
        checkOneAutoStat(AutoStatSubsetsProperty.PEAS_M1SDAP, AvgWithStdDevs.class);
        checkOneAutoStat(AutoStatSubsetsProperty.PEAS_M1SDPP, AvgWithStdDevs.class);
        checkOneAutoStat(AutoStatSubsetsProperty.PEAS_M2SDPP, AvgWithStdDevs.class);
        checkOneAutoStat(AutoStatSubsetsProperty.PEAS_M3SDAP, AvgWithStdDevs.class);
        checkOneAutoStat(AutoStatSubsetsProperty.PEAS_M3SDPP, AvgWithStdDevs.class);

        checkOneAutoStat(AutoStatSubsetsProperty.PEAS_M3SDAP, AvgWithStdDevs.class);
        checkOneAutoStat(AutoStatSubsetsProperty.PEAS_M3SDPP, AvgWithStdDevs.class);

        checkPareto(AutoStatSubsetsProperty.PEAS_PARETO_ASC);
        checkPareto(AutoStatSubsetsProperty.PEAS_PARETO_DEC);

        checkParetoDataset();
        checkXYAutoStatSeries();
    }
}
