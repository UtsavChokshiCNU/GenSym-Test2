package gensym.charts.tables;

import java.awt.Color;
import java.awt.Component;
import java.awt.Font;
import java.util.List;

import gensym.charts.dialogs.tables.TableColorSource;
import gensym.charts.scrolling.SeriesScrollingListener;

import javax.swing.JLabel;
import javax.swing.JTable;
import javax.swing.border.LineBorder;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.TableCellRenderer;

import org.jfree.util.PaintUtilities;

public class ColoredTable extends JTable implements TableColorSource, SeriesScrollingListener {
    /**
     * Generated serial version UID
     */
    private static final long serialVersionUID = -7285228103906012469L;
    
    /**
     * Default cell font
     */
    public static Font DEFAULT_CELL_FONT = new Font(null, 0, 12);

    /**
     * Text colors
     */
    private TablePropertySet<Color> textColors = new TablePropertySet<Color>();

    /**
     * Outline colors
     */
    private TablePropertySet<Color> outlineColors = new TablePropertySet<Color>();

    /**
     * Text Font
     */
    private TablePropertySet<Font> textFont = new TablePropertySet<Font>();
    
    /**
     * Show all items flag
     */
    private boolean showAllItems = true;
    
    /**
     * Cell selection enabling flag
     */
    private boolean enableSelect = true;

    /**
     * Constructor
     */
    public ColoredTable() {
        // Set default cell settings
        textColors.setData(-1, -1, getForeground());
        outlineColors.setData(-1, -1, getGridColor());
        textFont.setData(-1, -1, DEFAULT_CELL_FONT);
    }
    
    /**
     * {@inheritDoc}
     */
    public TableCellRenderer getCellRenderer(int row, int column) {
        return new DefaultTableCellRenderer() {
            private static final long serialVersionUID = -3653643710289204359L;

            public Component getTableCellRendererComponent(JTable table, Object value,
                         boolean isSelected, boolean hasFocus, int row, int column) {
                
                Component comp = super.getTableCellRendererComponent(table, value,
                        getEnableSelect() && isSelected, getEnableSelect() && hasFocus, row, column);
                if (comp instanceof JLabel) {
                    JLabel label = (JLabel) comp;

                    if (getTextColor(row, column) != null) {
                        label.setForeground(getTextColor(row, column));
                    }
                    if (!(getEnableSelect() && hasFocus) && getOutlineColor(row, column) != null) {
                        label.setBorder(new LineBorder(getOutlineColor(row, column)));
                    }
                    if (textFont.getData(row, column) != null) {
                        label.setFont(textFont.getData(row, column));
                    }
                    label.setHorizontalAlignment(CENTER);
                }

                return comp;
            }
        };
    }

    /**
     * {@inheritDoc}
     */
    public Color getOutlineColor(int row, int column) {
        return outlineColors.getData(row, column);
    }

    /**
     * {@inheritDoc}
     */
    public Color getTextColor(int row, int column) {
        return textColors.getData(row, column);
    }

    /**
     * {@inheritDoc}
     */
    public void setOutlineColor(int row, int column, Color color) {
        Color oldColor = getOutlineColor(row, column);
        if (!PaintUtilities.equal(color, oldColor)) {
            outlineColors.setData(row, column, color);
            updateUI();
        }
    }

    /**
     * {@inheritDoc}
     */
    public void setTextColor(int row, int column, Color color) {
        Color oldColor = getTextColor(row, column);
        if (!PaintUtilities.equal(color, oldColor)) {
            textColors.setData(row, column, color);
            updateUI();
        }
    }

    /**
     * {@inheritDoc}
     */
    public void itemsScrolled(List<Integer> items) {
        textFont.clear();
        textFont.setData(-1, -1, DEFAULT_CELL_FONT);
        if (getShowAllItems()) {
            Font bold = DEFAULT_CELL_FONT.deriveFont(Font.BOLD);
            for (Integer item : items) {
                textFont.setData(item, -1, bold);
            }
        }
        repaint();
    }
    
    /**
     * Sets show all items flag
     * @param show new showing state
     */
    public void setShowAllItems(boolean show) {
        showAllItems = show;
        if (getModel() instanceof ChartTableModel) {
            ((ChartTableModel) getModel()).setShowAllItems(show);
        }
    }
    
    /**
     * Returns show all items flag
     * @return the show all items flag
     */
    public boolean getShowAllItems() {
        return showAllItems;
    }
    
    /**
     * Sets selection enabling flag
     * @param show new selection enabling state
     */
    public void setEnableSelect(boolean enable) {
        enableSelect = enable;
        repaint();
    }
    
    /**
     * Returns selection enabling flag
     * @return the selection enabling flag
     */
    public boolean getEnableSelect() {
        return enableSelect;
    }
}
