package gensym.charts.tests.annotations;

import gensym.charts.tests.TestChartBase;
import gensym.charts.annotations.table.*;
import gensym.charts.annotations.table.ext.*;
import gensym.charts.GraphChart;
import gensym.charts.actions.CreateChartAction;
import gensym.charts.ChartsCommon;
import gensym.charts.properties.annotations.table.*;
import gensym.charts.dialogs.tables.TableColorSource;

import java.awt.*;

import org.jfree.chart.block.BlockContainer;
import org.jfree.chart.JFreeChart;
import org.jfree.ui.HorizontalAlignment;

/**
 * Table annotations test
 */
public class TableAnnotationsTest extends TestChartBase {
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
     * Test factory
     */
    public void testFactory() {
        TableAnnotationsFactory factory = new TableAnnotationsFactory(createChart());

        int size = 10;
        for (int i = 0; i < size; i++) {
            factory.get(i);
        }

        assertEquals(size, factory.getItems().length);
    }

    /**
     * Tests TableCellTitle class
     */
    public void testTableCellTitle() {
        TableColorSource source = new TableColorSource() {
            public Color getTextColor(int row, int column) { return null; }
            public void setTextColor(int row, int column, Color color) {}
            public Color getOutlineColor(int row, int column) { return null; }
            public void setOutlineColor(int row, int column, Color color) {}
        };

        int row = 10;
        int column = 20;
        String text = "test";
        TableCellTitle title = new TableCellTitle(text, row, column, source);

        assertEquals(row, title.getRow());
        assertEquals(column, title.getColumn());
        assertEquals(text, title.getText());
        assertEquals(source, title.getTableColorSource());

        assertEquals(" ", new TableCellTitle(null, row, column, source).getText());
        assertEquals(" ", new TableCellTitle("", row, column, source).getText());
    }

    /**
     * Tests TableTitle class
     */
    public void testTableTitle() {
        TableAnnotation annotation = new TableAnnotation(createChart());
        TableTitle title = new TableTitle(annotation);
        annotation.setRowsCount(2);
        annotation.setColumnsCount(1);

        title.update();
        assertEquals(1, title.getContainer().getBlocks().size());
        assertTrue(title.getContainer().getBlocks().get(0) instanceof BlockContainer);
        BlockContainer block = (BlockContainer) title.getContainer().getBlocks().get(0);
        assertEquals(annotation.getColumnsCount() * annotation.getRowsCount(), block.getBlocks().size());

        title.update(2);
        assertEquals(3, title.getContainer().getBlocks().size());
        assertTrue(title.getContainer().getBlocks().get(0) instanceof BlockContainer);
        block = (BlockContainer) title.getContainer().getBlocks().get(0);
        assertEquals(1, block.getBlocks().size());

        assertTrue(title.getContainer().getBlocks().get(1) instanceof BlockContainer);
        block = (BlockContainer) title.getContainer().getBlocks().get(1);
        assertEquals(1, block.getBlocks().size());

        assertTrue(title.getContainer().getBlocks().get(2) instanceof BlockContainer);
        block = (BlockContainer) title.getContainer().getBlocks().get(2);
        assertEquals(annotation.getColumnsCount() * annotation.getRowsCount(), block.getBlocks().size());
    }

    /**
     * Tests table annotation
     */
    public void testAnnotation() {
        TableAnnotation annotation = new TableAnnotation(createChart());

        int rows = 20;
        annotation.setRowsCount(rows);
        assertEquals(rows, annotation.getRowsCount());

        int columns = 10;
        annotation.setColumnsCount(columns);
        assertEquals(columns, annotation.getColumnsCount());

        String text = "test";
        int row = 4;
        int column = 5;
        annotation.setCellText(row, column, text);
        assertEquals(text, annotation.getCellText(row, column));

        Color color = Color.GREEN;
        annotation.setCellTextColor(row, -1, color);
        assertEquals(color, annotation.getCellTextPaint(row, column));

        Color backColor = Color.RED;
        annotation.setCellBackColor(-1, -1, backColor);

        assertEquals(backColor, annotation.getCellPaint(row, column));
        annotation.setHeaderColumns(1);
        assertNull(annotation.getCellPaint(row, 0));

        annotation.setHeaderRows(1);
        assertNull(annotation.getCellPaint(0, column));

        annotation.setShowVerticalLines(true);
        assertTrue(annotation.getShowVerticalLines());
        annotation.setShowVerticalLines(false);
        assertFalse(annotation.getShowVerticalLines());

        annotation.setShowHorizontalLines(true);
        assertTrue(annotation.getShowHorizontalLines());
        annotation.setShowHorizontalLines(false);
        assertFalse(annotation.getShowHorizontalLines());

        int borderWidth = 2;
        annotation.setBorderWidth(borderWidth);
        assertEquals(borderWidth, annotation.getBorderWidth());

        Color borderColor = Color.CYAN;
        annotation.setCellBorderColor(-1, -1, borderColor);
        assertEquals(borderColor, annotation.getCellBorderPaint(row, column));

        Color cellBorderColor = Color.CYAN;
        annotation.setCellBorderColor(row, column, cellBorderColor);
        assertEquals(cellBorderColor, annotation.getCellBorderPaint(row, column));

        Font oldFont = annotation.getCellFont(-1, -1);
        annotation.setTextSize(50);
        assertNotSame(oldFont, annotation.getCellFont(-1, -1));

        int columnWidth = 12;
        annotation.setColumnWidth(column, columnWidth);
        assertEquals(columnWidth, annotation.getColumnWidth(column));

        HorizontalAlignment alignment = HorizontalAlignment.LEFT;
        annotation.setAlignment(-1, -1, alignment);
        assertEquals(alignment, annotation.getAlignment(-1, column));

        Color textColor = Color.DARK_GRAY;
        annotation.setTextColor(-1, -1, textColor);
        assertEquals(textColor, annotation.getTextColor(row, column));

        Color outlineColor = Color.BLUE;
        annotation.setOutlineColor(-1, -1, outlineColor);
        assertEquals(outlineColor, annotation.getOutlineColor(row, column));

        assertEquals(annotation, annotation.getColorSource());
    }

    /**
     * Test annotations positions
     */
    public void testAnotationPositions() {
        for (int i = TableAnnotation.PETAL_TOP_CENTER; i <= TableAnnotation.PETAL_INSIDE_TOP_RIGHT; i++) {
            doTestPosition(i, i >= TableAnnotation.PETAL_INSIDE_TOP_CENTER);
        }
        doTestPosition(TableAnnotation.PETAL_INSIDE_AXIS, true);

        // axis location
        JFreeChart chart = createChart().getChart();
        chart.clearSubtitles();
        chart.getXYPlot().clearAnnotations();
        TableAnnotation annotation = new TableAnnotation(createChart());
        annotation.setRowsCount(10);
        annotation.setColumnsCount(10);

        annotation.setPosition(-1);
        assertEquals(0, chart.getXYPlot().getAnnotations().size());
        assertTrue(chart.getSubtitle(0).isVisible());

        annotation.setPosition(TableAnnotation.PETAL_INSIDE_AXIS);

        for (int pos = 100; pos < 111; pos++) {
            annotation.setAxisLocation(pos);
            assertEquals(1, chart.getXYPlot().getAnnotations().size());
            assertFalse(chart.getSubtitle(0).isVisible());
        }

        annotation.update(false);
        assertFalse(chart.getSubtitle(0).isVisible());
        assertEquals(0, chart.getXYPlot().getAnnotations().size());
        annotation.setAxisLocation(0);
        assertFalse(chart.getSubtitle(0).isVisible());
        assertEquals(1, chart.getXYPlot().getAnnotations().size());

        annotation.update(true);
        annotation.setPosition(TableAnnotation.PETAL_BOTTOM_LEFT);
        assertTrue(chart.getSubtitle(0).isVisible());
        assertEquals(0, chart.getXYPlot().getAnnotations().size());
    }

    /**
     * Tests table position
     * @param position table position
     * @param showAnnotation annotation shpwing flag
     */
    private void doTestPosition(int position, boolean showAnnotation) {
        JFreeChart chart = createChart().getChart();
        chart.clearSubtitles();
        chart.getXYPlot().clearAnnotations();

        TableAnnotation annotation = new TableAnnotation(createChart());
        annotation.setRowsCount(10);
        annotation.setColumnsCount(10);

        annotation.setPosition(position);
        assertEquals(1, chart.getSubtitleCount());
        
        annotation.update(true);
        assertEquals(showAnnotation ? 1 : 0, chart.getXYPlot().getAnnotations().size());
        assertEquals(showAnnotation, !chart.getSubtitle(0).isVisible());

        annotation.update(false);
        assertFalse(chart.getSubtitle(0).isVisible());
        assertEquals(0, chart.getXYPlot().getAnnotations().size());
    }

    /**
     * Tests table properties
     */
    public void testProperties() {
        GraphChart graph = createChart();
        JFreeChart chart = graph.getChart();

        graph.getAnnotations().setAnnotationVisible(true);
        chart.clearSubtitles();
        chart.getXYPlot().clearAnnotations();

        try {
            // working-table
            int table = 1;
            runAction("SetInt", "property", 2977, "i", 0, "j", 0, "value", table);
            assertNotNull(graph.getAnnotations().getCurrentTableAnnotation());

            // tacolumns
            int columns = 10;
            runAction("SetInt", "property", 2952, "i", 0, "j", 0, "value", columns);
            assertEquals(columns, graph.getAnnotations().getCurrentTableAnnotation().getColumnsCount());

            // tarows
            int rows = 10;
            runAction("SetInt", "property", 2951, "i", 0, "j", 0, "value", rows);
            assertEquals(rows, graph.getAnnotations().getCurrentTableAnnotation().getRowsCount());

            Color backColor = Color.GREEN;
            // taheader-rows
            graph.getAnnotations().getCurrentTableAnnotation().setCellBackColor(-1, -1, backColor);
            int headerRows = 2;
            for (int i = 0; i < headerRows; i++) {
                assertEquals(backColor, graph.getAnnotations().getCurrentTableAnnotation().getCellPaint(i, -1));
            }
            runAction("SetInt", "property", 2957, "i", 0, "j", 0, "value", headerRows);
            for (int i = 0; i < headerRows; i++) {
                assertNull(graph.getAnnotations().getCurrentTableAnnotation().getCellPaint(i, -1));
            }

            // taheader-column
            assertEquals(backColor, graph.getAnnotations().getCurrentTableAnnotation().getCellPaint(-1, 0));
            runAction("SetInt", "property", 2958, "i", 0, "j", 0, "value", 0);
            assertEquals(backColor, graph.getAnnotations().getCurrentTableAnnotation().getCellPaint(-1, 0));

            runAction("SetInt", "property", 2958, "i", 0, "j", 0, "value", 1);
            assertNull(graph.getAnnotations().getCurrentTableAnnotation().getCellPaint(-1, 0));

            // tatext
            int row = 3;
            int column = 2;
            String text = "cell text";
            runAction("SetString", "property", 2954, "i", row, "j", column, "value", text);
            assertEquals(text, graph.getAnnotations().getCurrentTableAnnotation().getCellText(row, column));

            text = "new text";
            runAction("SetString", "property", 2954, "i", column, "j", -1, "value", text);
            assertEquals(text, graph.getAnnotations().getCurrentTableAnnotation().getCellText(0, column));

            // tatext-size
            int textSize = 60;
            Font font = graph.getAnnotations().getCurrentTableAnnotation().getCellFont(-1, -1);
            runAction("SetInt", "property", 2965, "i", 0, "j", 0, "value", textSize);
            assertNotSame(font, graph.getAnnotations().getCurrentTableAnnotation().getCellFont(-1, -1));

            // tajustification
            runAction("SetInt", "property", 2969, "i", row, "j", column, "value", TaJustificationProperty.PETAJ_RIGHT);
            assertEquals(HorizontalAlignment.RIGHT, graph.getAnnotations().getCurrentTableAnnotation().getAlignment(row, column));
            runAction("SetInt", "property", 2969, "i", row, "j", column, "value", TaJustificationProperty.PETAJ_LEFT);
            assertEquals(HorizontalAlignment.LEFT, graph.getAnnotations().getCurrentTableAnnotation().getAlignment(row, column));
            runAction("SetInt", "property", 2969, "i", row, "j", column, "value", TaJustificationProperty.PETAJ_CENTER);
            assertEquals(HorizontalAlignment.CENTER, graph.getAnnotations().getCurrentTableAnnotation().getAlignment(row, column));

            // ta-grid-line-control
            runAction("SetInt", "property", 2967, "i", 0, "j", 0, "value", TaGridLineControlProperty.SHOW_NONE);
            assertFalse(graph.getAnnotations().getCurrentTableAnnotation().getShowHorizontalLines());
            assertFalse(graph.getAnnotations().getCurrentTableAnnotation().getShowVerticalLines());

            runAction("SetInt", "property", 2967, "i", 0, "j", 0, "value", TaGridLineControlProperty.SHOW_HORIZONTAL);
            assertTrue(graph.getAnnotations().getCurrentTableAnnotation().getShowHorizontalLines());
            assertFalse(graph.getAnnotations().getCurrentTableAnnotation().getShowVerticalLines());

            runAction("SetInt", "property", 2967, "i", 0, "j", 0, "value", TaGridLineControlProperty.SHOW_VERTICAL);
            assertFalse(graph.getAnnotations().getCurrentTableAnnotation().getShowHorizontalLines());
            assertTrue(graph.getAnnotations().getCurrentTableAnnotation().getShowVerticalLines());

            runAction("SetInt", "property", 2967, "i", 0, "j", 0, "value", TaGridLineControlProperty.SHOW_BOTH);
            assertTrue(graph.getAnnotations().getCurrentTableAnnotation().getShowHorizontalLines());
            assertTrue(graph.getAnnotations().getCurrentTableAnnotation().getShowVerticalLines());

            // tacolumn-width
            int width = 20;
            runAction("SetInt", "property", 2959, "i", column, "j", 0, "value", width);
            assertEquals(width, graph.getAnnotations().getCurrentTableAnnotation().getColumnWidth(column));

            // tacolor
            Color textColor = Color.ORANGE;
            int bgr = ChartsCommon.convertBGRtoRGB(textColor.getRGB() & 0xFFFFFF); 
            runAction("SetInt", "property", 2955, "i", row, "j", column, "value", bgr);
            assertEquals(textColor, graph.getAnnotations().getCurrentTableAnnotation().getCellTextPaint(row, column));

            // ta-border
            runAction("SetInt", "property", 2962, "i", row, "j", column, "value", TaBorderProperty.PETAB_DROP_SHADOW);
            assertEquals(1, graph.getAnnotations().getCurrentTableAnnotation().getBorderWidth());

            runAction("SetInt", "property", 2962, "i", row, "j", column, "value", TaBorderProperty.PETAB_INSET);
            assertEquals(1, graph.getAnnotations().getCurrentTableAnnotation().getBorderWidth());

            runAction("SetInt", "property", 2962, "i", row, "j", column, "value", TaBorderProperty.PETAB_NO_BORDER);
            assertEquals(0, graph.getAnnotations().getCurrentTableAnnotation().getBorderWidth());

            runAction("SetInt", "property", 2962, "i", row, "j", column, "value", TaBorderProperty.PETAB_SINGLE_LINE);
            assertEquals(1, graph.getAnnotations().getCurrentTableAnnotation().getBorderWidth());

            runAction("SetInt", "property", 2962, "i", row, "j", column, "value", TaBorderProperty.PETAB_THICK_LINE);
            assertEquals(2, graph.getAnnotations().getCurrentTableAnnotation().getBorderWidth());

            // taback-color
            backColor = Color.BLUE;
            bgr = ChartsCommon.convertBGRtoRGB(backColor.getRGB() & 0xFFFFFF);
            runAction("SetInt", "property", 2963, "i", row, "j", column, "value", bgr);
            assertEquals(backColor, graph.getAnnotations().getCurrentTableAnnotation().getCellPaint(row, column));

            // talocation and taaxis-location
            runAction("SetInt", "property", 2961, "i", 0, "j", 0, "value", TableAnnotation.PETAL_INSIDE_AXIS);
            runAction("SetInt", "property", 2966, "i", 0, "j", 0, "value", 5);
            runAction("Update");
            assertEquals(1, chart.getXYPlot().getAnnotations().size());
            assertFalse(chart.getSubtitle(0).isVisible());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
}
