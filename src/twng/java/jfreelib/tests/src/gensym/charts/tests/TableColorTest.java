package gensym.charts.tests;

import junit.framework.TestCase;
import java.awt.*;
import javax.swing.*;

import gensym.charts.dialogs.tables.*;
import gensym.charts.tables.ColoredTable;
import java.awt.event.ActionEvent;
import java.awt.image.BufferedImage;
import java.util.LinkedList;

import javax.swing.border.Border;
import javax.swing.border.LineBorder;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellRenderer;

/**
 * Test case for TableColor* classes
 */
public class TableColorTest extends TestCase {

    /**
     * Tests Radio button of select color dialog
     */
    public final void testTableColorRButton() {
        int row = 43, column = 3523;
        TableColorRButton button = new TableColorRButton("Hello World", true, row, column);
        assertEquals(button.getRow(), row);
        assertEquals(button.getColumn(), column);
    }

    /**
     * Tests Select color button class
     */
    public final void testTableColorButton() {
        Color cl = Color.BLACK;
        int width = 34;
        int height = 12;
        TableColorButton button = new TableColorButton(Color.BLUE, width, height);
        button.setColor(cl);
        assertEquals(button.getColor(), cl);
        assertEquals(button.getIconWidth(), width);
        assertEquals(button.getIconHeight(), height);

        int x = 10;
        int y = 10;
        BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
        Graphics g2 = image.getGraphics();
        g2.setColor(cl);
        button.paintIcon(null, g2, x, y);
        assertEquals(g2.getColor(), cl);

        button.setVisible(false);
    }

    /**
     * Tests select color dialog
     */
    public final void testTableColorDialog() {
        JFrame frame = new JFrame();
        TableColorSource source = new ColoredTable();
        source.setTextColor(-1, -1, Color.GRAY);
        Color cl = source.getTextColor(-1, -1);
        TableColorDialog dialog = new TableColorDialog(frame, source, 1, 1);
        source.setTextColor(-1, -1, Color.LIGHT_GRAY);
        dialog.actionPerformed(new ActionEvent(dialog, 0, "ok", 0, 0));
        assertNotNull(dialog);
        assertEquals(source.getTextColor(1, 1), cl);
    }

    /**
     * Tests ColoredTable class
     */
    public final void testColoredTable() {
        doSimpleTest(-1, -1, Color.BLACK);
        doSimpleTest(0, 0, Color.BLACK);
        doSimpleTest(-1, 0, Color.BLACK);
        doSimpleTest(0, -1, Color.BLACK);

        doTestDuplicates(0, 0, Color.BLACK);
        doTestDuplicates(0, -1, Color.BLACK);
        doTestDuplicates(-1, 0, Color.BLACK);

        TableColorSource source = new ColoredTable();
        Color cl = Color.RED;
        source.setOutlineColor(0, 0, cl);
        source.setTextColor(0, 0, cl);

        cl = Color.GRAY;
        source.setOutlineColor(-1, 0, cl);
        source.setTextColor(0, -1, cl);

        assertEquals(source.getOutlineColor(0, 0), cl);
        assertEquals(source.getTextColor(0, 0), cl);
    }

    /**
     * Tests cell renderer
     */
    public final void testCellRenderer() {
        ColoredTable table = new ColoredTable();
        table.setModel(new DefaultTableModel(5, 5));

        table.setEnableSelect(false);
        assertFalse(table.getEnableSelect());
        table.setEnableSelect(true);
        assertTrue(table.getEnableSelect());

        int row = 1;
        int column = 1;
        Color color = Color.YELLOW;
        table.setTextColor(row, column, color);
        table.setOutlineColor(row, column, color);
        TableCellRenderer renderer = table.getCellRenderer(row, column);
        assertNotNull(renderer);
        Component comp = renderer.getTableCellRendererComponent(table, "Test", false, true, row, column);
        assertTrue(comp instanceof JLabel);
        assertEquals(((JLabel) comp).getForeground(), color);
        
        Color outline = Color.CYAN;
        table.setOutlineColor(-1, -1, outline);
        table.setEnableSelect(false);
        assertFalse(table.getEnableSelect());
        comp = renderer.getTableCellRendererComponent(table, "Test", false, true, row, column);
        assertTrue(comp instanceof JLabel);
        Border border = ((JLabel) comp).getBorder();
        assertTrue(border instanceof LineBorder);
        assertEquals(((LineBorder) border).getLineColor(), outline);

        table.setEnableSelect(true);
        assertTrue(table.getEnableSelect());
    }

    /**
     * Tests simple get\set colors
     */
    private void doSimpleTest(int row, int column, Color cl) {
        TableColorSource source = new ColoredTable();
        source.setOutlineColor(row, column, cl);
        source.setTextColor(row, column, cl);
        assertEquals(source.getOutlineColor(row, column), cl);
        assertEquals(source.getTextColor(row, column), cl);
    }

    /**
     * Additional test for color duplicates
     */
    private void doTestDuplicates(int row, int column, Color cl) {
        TableColorSource source = new ColoredTable();
        source.setOutlineColor(-1, -1, cl);
        source.setTextColor(-1, -1, cl);
        source.setOutlineColor(row, column, Color.RED);
        source.setTextColor(row, column, Color.RED);
        source.setOutlineColor(row, column, cl);
        source.setTextColor(row, column, cl);
        assertEquals(source.getOutlineColor(row, column), cl);
        assertEquals(source.getTextColor(row, column), cl);
    }
    
    /**
     * Tests scrolling functionality
     */
    public void testScrolling() {
        ColoredTable table = new ColoredTable();
        table.setModel(new DefaultTableModel(5, 5));
        
        LinkedList<Integer> items = new LinkedList<Integer>();
        int row1 = 1;
        int row2 = 3;
        items.add(row1); items.add(row2);

        table.setShowAllItems(false);
        assertFalse(table.getShowAllItems());
        table.itemsScrolled(items);
        Component comp =
            table.getCellRenderer(row1, 0).getTableCellRendererComponent(table, 1, false, false, row1, -1);
        assertTrue(comp instanceof JLabel);
        JLabel label = (JLabel) comp;
        assertEquals(ColoredTable.DEFAULT_CELL_FONT, label.getFont());
        
        table.setShowAllItems(true);
        assertTrue(table.getShowAllItems());
        table.itemsScrolled(items);
        comp = table.getCellRenderer(row1, 0).getTableCellRendererComponent(table, 1, false, false, row1, -1);
        assertTrue(comp instanceof JLabel);
        label = (JLabel) comp;
        assertNotSame(ColoredTable.DEFAULT_CELL_FONT, label.getFont());
        assertEquals(ColoredTable.DEFAULT_CELL_FONT.deriveFont(Font.BOLD), label.getFont());
    }
}
