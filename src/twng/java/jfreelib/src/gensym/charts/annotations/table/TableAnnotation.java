package gensym.charts.annotations.table;

import java.awt.Color;
import java.awt.Font;
import java.awt.Paint;
import java.util.LinkedHashMap;
import java.util.Map;

import org.jfree.chart.annotations.XYTitleAnnotation;
import org.jfree.chart.plot.XYPlot;
import org.jfree.ui.HorizontalAlignment;
import org.jfree.ui.RectangleAnchor;
import org.jfree.ui.RectangleEdge;
import org.jfree.ui.VerticalAlignment;

import gensym.charts.GraphChart;
import gensym.charts.annotations.table.ext.TableTitle;
import gensym.charts.annotations.table.ext.TableTitleSource;
import gensym.charts.dialogs.tables.TableColorSource;
import gensym.charts.tables.TableCellData;
import gensym.charts.tables.TablePropertySet;

/**
 * Table annotation class
 */
public class TableAnnotation implements TableTitleSource, TableColorSource {
    /**
     * Max font size
     */
    private static final int MAX_FONT_SIZE = 14;
    
    /**
     * Transparent color
     */
    private static final Color TRANSPARENT_COLOR = new Color(0x000001);
    
    /**
     * Top Center position
     */
    public static final int PETAL_TOP_CENTER = 0;
    
    /**
     * Top Left position
     */
    public static final int PETAL_TOP_LEFT = 1;

    /**
     * Left Center position
     */
    public static final int PETAL_LEFT_CENTER = 2;

    /**
     * Bottom Left position
     */
    public static final int PETAL_BOTTOM_LEFT = 3;

    /**
     * Bottom Center position
     */
    public static final int PETAL_BOTTOM_CENTER = 4;
    
    /**
     * Bottom Right position
     */
    public static final int PETAL_BOTTOM_RIGHT = 5;

    /**
     * Right Center position
     */
    public static final int PETAL_RIGHT_CENTER = 6;
    
    /**
     * Top Right position
     */
    public static final int PETAL_TOP_RIGHT = 7;

    /**
     * Inside Top Center position
     */
    public static final int PETAL_INSIDE_TOP_CENTER = 8;
    
    /**
     * Inside Top Left position
     */
    public static final int PETAL_INSIDE_TOP_LEFT = 9;

    /**
     * Inside Left Center position
     */
    public static final int PETAL_INSIDE_LEFT_CENTER = 10;

    /**
     * Inside Bottom Left position
     */
    public static final int PETAL_INSIDE_BOTTOM_LEFT = 11;

    /**
     * Inside Bottom Center position
     */
    public static final int PETAL_INSIDE_BOTTOM_CENTER = 12;
    
    /**
     * Inside Bottom Right position
     */
    public static final int PETAL_INSIDE_BOTTOM_RIGHT = 13;

    /**
     * Inside Right Center position
     */
    public static final int PETAL_INSIDE_RIGHT_CENTER = 14;
    
    /**
     * Inside Top Right position
     */
    public static final int PETAL_INSIDE_TOP_RIGHT = 15;

    /**
     * Inside Axis position
     */
    public static final int PETAL_INSIDE_AXIS = 100;
    
    /**
     * Annotation location
     */
    private int location = PETAL_BOTTOM_CENTER;
    
    /**
     * Count of rows to skip
     */
    private int skipRows = 0;

    /**
     * Cells text
     */
    private TableCellData<String> cellText = new TableCellData<String>();
    
    /**
     * Cells text alignment
     */
    private TablePropertySet<HorizontalAlignment> textAlignment = new TablePropertySet<HorizontalAlignment>();

    /**
     * Cell text colors
     */
    private TablePropertySet<Color> textColors = new TablePropertySet<Color>();

    /**
     * Cell back colors
     */
    private TablePropertySet<Color> backColors = new TablePropertySet<Color>();

    /**
     * Cell back colors
     */
    private TablePropertySet<Color> borderColors = new TablePropertySet<Color>();

    /**
     * Columns width map (column => width)
     */
    private Map<Integer, Integer> columnsWidth = new LinkedHashMap<Integer, Integer>();

    /**
     * Chart
     */
    private GraphChart chart = null;
    
    /**
     * Rows count
     */
    private int rows = 0;
    
    /**
     * Header rows
     */
    private int headerRows = 0;
    
    /**
     * Columns count
     */
    private int columns = 0;

    /**
     * Header columns
     */
    private int headerColumns = 0;

    /**
     * Table title
     */
    private TableTitle title = null;
    
    /**
     * Annotation
     */
    private XYTitleAnnotation annotation = null;
    
    /**
     * Show horizontal lines flag
     */
    private boolean showHorizontalLines = true;
    
    /**
     * Show vertical lines flag
     */
    private boolean showVerticalLines = true;
    
    /**
     * Border width
     */
    private int borderWidth = 1;
    
    /**
     * Text font
     */
    private Font font = new Font("SansSerif", Font.PLAIN, MAX_FONT_SIZE);

    /**
     * Plot containing annotation
     */
    private XYPlot plot;

    /**
     * Constructor
     * @param chart the chart
     */
    public TableAnnotation(GraphChart chart) {
        this.chart = chart;
        
        title = new TableTitle(this);
        chart.getChart().addSubtitle(title);
        setPosition(location);
        
        textAlignment.setData(-1, -1, HorizontalAlignment.CENTER);
    }
    
    /**
     * {@inheritDoc}
     */
    public String getCellText(int row, int column) {
        return cellText.get(row, column);
    }
    
    /**
     * Sets cell text
     * @param row row index
     * @param column column index
     * @param text the new cell text
     */
    public void setCellText(int row, int column, String text) {
        cellText.setCellData(row, column, text);
    }

    /**
     * {@inheritDoc}
     */
    public Paint getCellTextPaint(int row, int column) {
        return getTextColor(row, column);
    }
    
    /**
     * Sets cell text color
     * @param row row index
     * @param column column index
     * @param color the new cell text color
     */
    public void setCellTextColor(int row, int column, Color color) {
        textColors.setData(row, column, color);
    }

    /**
     * {@inheritDoc}
     */
    public Paint getCellPaint(int row, int column) {
        Color color = backColors.getData(row, column);
        return color != TRANSPARENT_COLOR ? color : null;
    }

    /**
     * Sets cell back color
     * @param row row index
     * @param column column index
     * @param color the new cell back color
     */
    public void setCellBackColor(int row, int column, Color color) {
        backColors.setData(row, column, color);
        if (row == -1 && column == -1) {
            updateHeaderColors();
        }
    }
    
    /**
     * Updates header colors
     */
    private void updateHeaderColors() {
        for (int i = 0; i < headerColumns; i++) {
            backColors.setData(-1, i, TRANSPARENT_COLOR);
        }
        for (int i = 0; i < headerRows; i++) {
            backColors.setData(i, -1, TRANSPARENT_COLOR);
        }
    }

    /**
     * {@inheritDoc}
     */
    public int getColumnsCount() {
        return columns;
    }
    
    /**
     * Sets columns count
     * @param count the new columns count
     */
    public void setColumnsCount(int count) {
        columns = count;
    }

    /**
     * Sets header columns count
     * @param count the header columns count
     */
    public void setHeaderColumns(int count) {
        headerColumns = count;
        updateHeaderColors();
    }

    /**
     * {@inheritDoc}
     */
    public int getRowsCount() {
        return rows;
    }
    
    /**
     * Sets rows count
     * @param count the new rows count
     */
    public void setRowsCount(int count) {
        rows = count;
        updateHeaderColors();
    }

    /**
     * Sets header rows count
     * @param count the header rows count
     */
    public void setHeaderRows(int count) {
        headerRows = count;
        updateHeaderColors();
    }

    /**
     * {@inheritDoc}
     */
    public boolean getShowVerticalLines() {
        return showVerticalLines;
    }
    
    /**
     * Shows vertical grid lines
     * @param show showing flag
     */
    public void setShowVerticalLines(boolean show) {
        showVerticalLines = show;
    }
    
    /**
     * {@inheritDoc}
     */
    public boolean getShowHorizontalLines() {
        return showHorizontalLines;
    }
    
    /**
     * Shows horizontal grid lines
     * @param show showing flag
     */
    public void setShowHorizontalLines(boolean show) {
        showHorizontalLines = show;
    }
    
    /**
     * {@inheritDoc}
     */
    public int getBorderWidth() {
        return borderWidth;
    }

    /**
     * Sets border width
     * @param width the border width
     */
    public void setBorderWidth(int width) {
        borderWidth = width;
    }
    
    /**
     * {@inheritDoc}
     */
    public Paint getCellBorderPaint(int row, int column) {
        return getOutlineColor(row, column);
    }
    
    /**
     * Sets cell border color
     * @param row row index
     * @param column column index
     * @param color the new cell border color
     */
    public void setCellBorderColor(int row, int column, Color color) {
        borderColors.setData(row, column, color);
    }
    
    /**
     * {@inheritDoc}
     */
    public Font getCellFont(int row, int column) {
        return font;
    }
    
    /**
     * Sets text size
     * @param size the new text size
     */
    public void setTextSize(int size) {
        float newSize = MAX_FONT_SIZE * size / 100;
        font = font.deriveFont(newSize);
    }
    
    /**
     * {@inheritDoc}
     */
    public int getColumnWidth(int column) {
        Integer width = columnsWidth.get(column);
        return width != null ? width.intValue() : 0;
    }

    /**
     * Sets column width
     * @param column column index
     * @param width the new column width
     */
    public void setColumnWidth(int column, int width) {
        columnsWidth.put(column, width);
    }
    
    /**
     * {@inheritDoc}
     */
    public HorizontalAlignment getAlignment(int row, int column) {
        return textAlignment.getData(row, column);
    }

    /**
     * Sets cell text horizontal alignment
     * @param row row index
     * @param column column index
     * @param alignment the horizontal alignment
     */
    public void setAlignment(int row, int column, HorizontalAlignment alignment) {
        textAlignment.setData(row, column, alignment);
    }

    /**
     * Updates view
     */
    public void update(boolean visible) {
        if (visible) {
            title.update(skipRows);
            if (annotation != null) {
                if (plot != null) {
                    plot.removeAnnotation(annotation, false);
                }
                plot = chart.getPlot().getCurrentPlot();
                if (plot != null) {
                    plot.addAnnotation(annotation, false);
                }
                title.setVisible(false);
            } else {
                title.setVisible(true);
            }
        } else {
            if (annotation != null && plot != null) {
                plot.removeAnnotation(annotation, false);
            }
            title.setVisible(false);
        }
    }
    
    /**
     * Sets position
     * @param position the new position
     */
    public final void setPosition(int position) {
        if ((position < PETAL_TOP_CENTER || position > PETAL_INSIDE_TOP_RIGHT) && position != PETAL_INSIDE_AXIS) {
            return;
        }
        
        location = position;
        
        if (annotation != null) {
            if (plot != null) {
                plot.removeAnnotation(annotation, false);
            }
            annotation = null;
        }
        
        RectangleEdge rectEdge = null;
        VerticalAlignment vAlign = null;
        HorizontalAlignment hAlign = null;
        
        double x = 0;
        double y = 0;
        RectangleAnchor anchor = null;
        
        switch (position) {
        case PETAL_TOP_CENTER:
            rectEdge = RectangleEdge.TOP;
            hAlign = HorizontalAlignment.CENTER;
            break;
        case PETAL_TOP_LEFT:
            rectEdge = RectangleEdge.TOP;
            hAlign = HorizontalAlignment.LEFT;
            break;
        case PETAL_LEFT_CENTER:
            rectEdge = RectangleEdge.LEFT;
            vAlign = VerticalAlignment.CENTER;
            break;
        case PETAL_BOTTOM_LEFT:
            rectEdge = RectangleEdge.BOTTOM;
            hAlign = HorizontalAlignment.LEFT;
            break;
        case PETAL_BOTTOM_CENTER:
            rectEdge = RectangleEdge.BOTTOM;
            hAlign = HorizontalAlignment.CENTER;
            break;
        case PETAL_BOTTOM_RIGHT:
            rectEdge = RectangleEdge.BOTTOM;
            hAlign = HorizontalAlignment.RIGHT;
            break;
        case PETAL_RIGHT_CENTER:
            rectEdge = RectangleEdge.RIGHT;
            vAlign = VerticalAlignment.CENTER;
            break;
        case PETAL_TOP_RIGHT:
            rectEdge = RectangleEdge.TOP;
            hAlign = HorizontalAlignment.RIGHT;
            break;
            
        case PETAL_INSIDE_TOP_CENTER:
            y = 0.98;
            x = 0.35;
            anchor = RectangleAnchor.TOP;
            break;
        case PETAL_INSIDE_TOP_LEFT:
        case PETAL_INSIDE_AXIS:
        case PETAL_INSIDE_AXIS + 1:
        case PETAL_INSIDE_AXIS + 2:
        case PETAL_INSIDE_AXIS + 3:
            y = 0.98;
            x = 0.01;
            anchor = RectangleAnchor.TOP_LEFT;
            break;
        case PETAL_INSIDE_LEFT_CENTER:
            y = 0.35;
            x = 0.01;
            anchor = RectangleAnchor.LEFT;
            break;
        case PETAL_INSIDE_BOTTOM_LEFT:
            y = 0.01;
            x = 0.01;
            anchor = RectangleAnchor.BOTTOM_LEFT;
            break;
        case PETAL_INSIDE_BOTTOM_CENTER:
            y = 0.01;
            x = 0.35;
            anchor = RectangleAnchor.BOTTOM;
            break;
        case PETAL_INSIDE_BOTTOM_RIGHT:
            y = 0.01;
            x = 0.85;
            anchor = RectangleAnchor.BOTTOM_RIGHT;
            break;
        case PETAL_INSIDE_RIGHT_CENTER:
            y = 0.35;
            x = 0.85;
            anchor = RectangleAnchor.RIGHT;
            break;
        case PETAL_INSIDE_TOP_RIGHT:
            y = 0.98;
            x = 0.85;
            anchor = RectangleAnchor.TOP_RIGHT;
            break;
        }
        
        if (position < PETAL_INSIDE_TOP_CENTER) {
            title.setPosition(rectEdge);
            
            if (vAlign != null) {
                title.setVerticalAlignment(vAlign);
            }
            if (hAlign != null) {
                title.setHorizontalAlignment(hAlign);
            }
            title.setVisible(true);
        } else {
            annotation = new XYTitleAnnotation(x, y, title, anchor);
            if (position >= PETAL_INSIDE_AXIS) {
                plot = chart.getPlot().getPlot(position - PETAL_INSIDE_AXIS);
            } else {
                plot = chart.getPlot().getPlot(0);
            }
            if (plot != null) {
                plot.addAnnotation(annotation, false);
            }
            title.setVisible(false);
        }
    }
    
    /**
     * Sets axis location
     * @param axisLocation
     */
    public void setAxisLocation(int axisLocation) {
        if (location >= PETAL_INSIDE_AXIS && annotation != null) {
            double x = 0;
            double y = 0;
            RectangleAnchor anchor = null;
            
            int PETAAL_NEW_ROW = 100;
            
            switch (axisLocation % PETAAL_NEW_ROW) {
            case 0: // PETAAL_TOP_FULL_WIDTH
            case 2: // PETAAL_TOP_CENTER
            case 8: // PETAAL_TOP_TABLE_SPACED
                y = 0.98;
                x = 0.35;
                anchor = RectangleAnchor.TOP;
                break;
            case 4: // PETAAL_BOTTOM_FULL_WIDTH
            case 6: // PETAAL_BOTTOM_CENTER
            case 9: // PETAAL_BOTTOM_TABLE_SPACED
                y = 0.01;
                x = 0.35;
                anchor = RectangleAnchor.BOTTOM;
                break;
            case 1: // PETAAL_TOP_LEFT
                y = 0.98;
                x = 0.01;
                anchor = RectangleAnchor.TOP_LEFT;
                break;
            case 3: // PETAAL_TOP_RIGHT
                y = 0.98;
                x = 0.85;
                anchor = RectangleAnchor.TOP_RIGHT;
                break;
            case 5: // PETAAL_BOTTOM_LEFT
                y = 0.01;
                x = 0.01;
                anchor = RectangleAnchor.BOTTOM_LEFT;
                break;
            case 7: // PETAAL_BOTTOM_RIGHT
                y = 0.01;
                x = 0.85;
                anchor = RectangleAnchor.BOTTOM_RIGHT;
                break;
            }
            
            if (anchor != null) {
                skipRows = axisLocation / PETAAL_NEW_ROW;
                if (skipRows > 0) {
                    title.update(skipRows);
                }

                if (plot != null) {
                    plot.removeAnnotation(annotation, false);
                    annotation = new XYTitleAnnotation(x, y, title, anchor);
                    plot.addAnnotation(annotation, false);
                }
            }
        }
    }

    /**
     * {@inheritDoc}
     */
    public Color getOutlineColor(int row, int column) {
        return borderColors.getData(row, column);
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
        borderColors.setData(row, column, color);
        title.update(skipRows);
        chart.getChart().fireChartChanged();
    }

    /**
     * {@inheritDoc}
     */
    public void setTextColor(int row, int column, Color color) {
        textColors.setData(row, column, color);
        title.update(skipRows);
        chart.getChart().fireChartChanged();
    }
    
    /**
     * {@inheritDoc}
     */
    public TableColorSource getColorSource() {
        return this;
    }
}
