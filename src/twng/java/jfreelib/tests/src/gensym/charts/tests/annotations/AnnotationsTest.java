package gensym.charts.tests.annotations;

import gensym.charts.tests.TestChartBase;
import gensym.charts.GraphChart;
import gensym.charts.actions.CreateChartAction;
import gensym.charts.annotations.ChartAnnotations;
import gensym.charts.annotations.line.LineAnnotation;
import gensym.charts.annotations.graph.AbstractBuilder;
import gensym.charts.annotations.graph.AnnotationBuildersFactory;
import gensym.charts.annotations.graph.AnnotationInfo;
import gensym.charts.annotations.graph.AnnotationWithAxis;
import gensym.charts.annotations.table.TableAnnotation;

import org.jfree.chart.JFreeChart;
import org.jfree.ui.Layer;

import java.util.Collection;

/**
 * Annotations test
 */
public class AnnotationsTest extends TestChartBase {
    /**
     * Creates chart object
     * @return created chart
     */
    private GraphChart createChart() {
        if (getChart() == null) {
            doCreateAction(CreateChartAction.PE_GRAPH_CHART);
            assertNotNull(getChart());
            assertEquals(GraphChart.class, getChart().getClass());
        }
        return (GraphChart) getChart();
    }

    /**
     * Tests annotations visibility
     */
    public void testVisibility() {
        ChartAnnotations annotations = new ChartAnnotations(createChart());

        annotations.setAnnotationVisible(false);
        assertFalse(annotations.isAnnotationVisible());
        annotations.setAnnotationVisible(true);
        assertTrue(annotations.isAnnotationVisible());

        // graph
        annotations.setAnnotationVisible(false);
        annotations.setGraphAnnotationsVisible(false);
        assertFalse(annotations.isGraphAnnotationsVisible());

        annotations.setGraphAnnotationsVisible(true);
        assertTrue(annotations.isGraphAnnotationsVisible());

        annotations.setGraphAnnotationsVisible(false);
        annotations.setAnnotationVisible(true);
        assertTrue(annotations.isGraphAnnotationsVisible());

        annotations.setGraphAnnotationsVisible(true);
        assertTrue(annotations.isGraphAnnotationsVisible());

        // table
        annotations.setAnnotationVisible(false);
        annotations.setTableAnnotationsVisible(false);
        assertFalse(annotations.isTableAnnotationsVisible());

        annotations.setTableAnnotationsVisible(true);
        assertTrue(annotations.isTableAnnotationsVisible());

        annotations.setTableAnnotationsVisible(false);
        annotations.setAnnotationVisible(true);
        assertTrue(annotations.isTableAnnotationsVisible());

        annotations.setTableAnnotationsVisible(true);
        assertTrue(annotations.isTableAnnotationsVisible());

        // line
        annotations.setAnnotationVisible(false);
        annotations.setLineAnnotationsVisible(false);
        assertFalse(annotations.isLineAnnotationsVisible());

        annotations.setLineAnnotationsVisible(true);
        assertTrue(annotations.isLineAnnotationsVisible());

        annotations.setLineAnnotationsVisible(false);
        annotations.setAnnotationVisible(true);
        assertTrue(annotations.isLineAnnotationsVisible());

        annotations.setLineAnnotationsVisible(true);
        assertTrue(annotations.isLineAnnotationsVisible());
    }

    /**
     * Tests table annotations
     */
    public void testTables() {
        GraphChart graph = createChart();
        JFreeChart chart = graph.getChart();

        chart.clearSubtitles();
        chart.getXYPlot().clearAnnotations();

        ChartAnnotations annotations = new ChartAnnotations(graph);
        annotations.setAnnotationVisible(false);

        annotations.setCurrentTableAnnotation(1);
        TableAnnotation table = annotations.getCurrentTableAnnotation();
        table.setRowsCount(3);
        table.setColumnsCount(3);

        annotations.setTableAnnotationsVisible(true);
        annotations.updateTableAnnotations();
        assertEquals(1, chart.getSubtitleCount());
        assertTrue(chart.getSubtitle(0).isVisible());

        annotations.setTableAnnotationsVisible(false);
        annotations.updateTableAnnotations();
        assertEquals(1, chart.getSubtitleCount());
        assertFalse(chart.getSubtitle(0).isVisible());
    }

    /**
     * Tests graph annotations
     */
    public void testGraph() {
        GraphChart graph = createChart();
        JFreeChart chart = graph.getChart();

        chart.getXYPlot().clearAnnotations();

        ChartAnnotations annotations = new ChartAnnotations(graph);
        annotations.setAnnotationVisible(false);

        AnnotationInfo info = annotations.getGraphAnnotations().getInfo(1);
        info.setType(AnnotationBuildersFactory.PEGAT_SMALLCROSS);
        info.setX(100);
        info.setY(120);
        info.setText("small cross");

        annotations.setGraphAnnotationsVisible(true);
        annotations.updateGraphAnnotations();
        assertEquals(2, chart.getXYPlot().getAnnotations().size()); // cross + text

        annotations.setGraphAnnotationsVisible(false);
        annotations.updateGraphAnnotations();
        assertEquals(0, chart.getXYPlot().getAnnotations().size());

        AbstractBuilder builder = AnnotationBuildersFactory.createBuilder(info);
        assertEquals(0, builder.getAxis());
        builder.setAxis(1);
        assertEquals(1, builder.getAxis());
        assertEquals(2, builder.build().length);

        try {
            new AnnotationWithAxis(null, 1);
        } catch (IllegalArgumentException e) {
            //right
        } catch (Exception e) {
            fail("Wrong exception.");
        }
    }

    /**
     * Tests line annotations
     */
    public void testLines() {
        GraphChart graph = createChart();
        JFreeChart chart = graph.getChart();

        chart.getXYPlot().clearRangeMarkers();

        ChartAnnotations annotations = new ChartAnnotations(graph);
        annotations.setAnnotationVisible(false);

        LineAnnotation line = annotations.getHorizontalLineAnnotations().get(1);
        line.setPosition(150);
        line.setText("line");

        annotations.setLineAnnotationsVisible(true);
        annotations.updateHorLineAnnotations();
        assertNotNull(chart.getXYPlot().getRangeMarkers(Layer.FOREGROUND));
        assertEquals(1, chart.getXYPlot().getRangeMarkers(Layer.FOREGROUND).size());

        annotations.setLineAnnotationsVisible(false);
        annotations.updateHorLineAnnotations();
        Collection<?> markers = chart.getXYPlot().getRangeMarkers(Layer.FOREGROUND);
        assertEquals(0, markers == null ? 0 : markers.size());
    }

    /**
     * Tests properties
     */
    public void testProperties() {
        GraphChart graph = createChart();
        ChartAnnotations annotations = graph.getAnnotations();

        try {
            // show-annotations
            runAction("SetInt", "property", 3290, "i", 0, "j", 0, "value", 0);
            assertFalse(annotations.isAnnotationVisible());
            runAction("SetInt", "property", 3290, "i", 0, "j", 0, "value", 1);
            assertTrue(annotations.isAnnotationVisible());

            annotations.setAnnotationVisible(false);

            // show-graph-annotations
            runAction("SetInt", "property", 3223, "i", 0, "j", 0, "value", 0);
            assertFalse(annotations.isGraphAnnotationsVisible());
            runAction("SetInt", "property", 3223, "i", 0, "j", 0, "value", 1);
            assertTrue(annotations.isGraphAnnotationsVisible());

            // show-horz-line-annotations
            runAction("SetInt", "property", 3227, "i", 0, "j", 0, "value", 0);
            assertFalse(annotations.isLineAnnotationsVisible());
            runAction("SetInt", "property", 3227, "i", 0, "j", 0, "value", 1);
            assertTrue(annotations.isLineAnnotationsVisible());

            // show-table-annotation
            runAction("SetInt", "property", 2968, "i", 0, "j", 0, "value", 0);
            assertFalse(annotations.isTableAnnotationsVisible());
            runAction("SetInt", "property", 2968, "i", 0, "j", 0, "value", 1);
            assertTrue(annotations.isTableAnnotationsVisible());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
}
