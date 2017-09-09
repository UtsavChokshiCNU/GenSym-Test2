package gensym.charts;

import gensym.charts.dialogs.tables.TableColorDialog;
import gensym.charts.dialogs.ChartPropertiesDialog;
import gensym.charts.scrolling.*;
import gensym.charts.tooltips.MultiLineToolTip;
import gensym.charts.tables.*;

import org.jfree.chart.*;
import org.jfree.chart.editor.*;
import org.jfree.ui.RectangleInsets;
import org.jfree.ui.RefineryUtilities;

import javax.swing.*;
import javax.swing.table.*;

import java.awt.*;
import java.awt.event.*;

import java.util.Map;
import java.util.LinkedHashMap;

/**
 * JFree charts proxy
 */
public class JFreeChartHolder extends JFrame {
    /**
     * Generated serial version UID 
     */
    private static final long serialVersionUID = -6090361621820377062L;

    /** Default chart height constant */
    public static final int DEFAULT_HEIGHT = 600;

    /** Default chart width constant */
    public static final int DEFAULT_WIDTH = 800;
    
    /**
     * Map of existing charts
     */
    static Map<Integer, JFreeChartHolder> holders = new LinkedHashMap<Integer, JFreeChartHolder>();

    /**
     * Makes new chart holder
     * @param handle chart handle
     * @return
     */
    public static JFreeChartHolder makeHolder(int handle) {
        JFreeChartHolder holder = new JFreeChartHolder(handle);
        holders.put(handle, holder);

        return holder;
    }

    /**
     * Returns chart holder by handle
     * @param handle chart handle
     * @return chart holder with specified handle of null
     */
    public static JFreeChartHolder getHolder(int handle) {
        return holders.get(handle);
    }

    /** Chart handle */
    private int handle = 0;

    /** Chart object */
    private AbstractChart chart = null;
    
    /** Chart table */
    private ColoredTable dataTable = null;

    /** Table panel */
    private JComponent tablePanel = null;
    
    /** Chart panel */
    private ChartPanel chartPanel = null;
    
    /** Chart pane */
    private JComponent chartPane = null;
    
    /** Chart vertical(east side) scroll bar */
    private JScrollBar scrollBarVertical = null;

    /** Chart horizontal(south side) scroll bar */
    private JScrollBar scrollBarHorizontal = null;

    /** Chart style */
    private ChartStyle style = null;
    
    /** Chart padding */
    private RectangleInsets padding = null;

    /**
     * Constructor
     * @param handle chart handle
     */
    public JFreeChartHolder(int handle) {
        this.handle = handle;
        setVisible(false);
    }

    /**
     * Returns chart handle
     * @return chart handle
     */
    public int getHandle() {
        return handle;
    }

    /**
     * Return chart object
     * @return chart
     */
    public AbstractChart getChart() {
        return chart;
    }

    /**
     * Returns chart style
     * @return chart style
     */
    public ChartStyle getStyle() {
        return style;
    }

    /**
     * Updates chart table model
     */
    private void updateTableView() {
        if (chart.isTableSupported()) {
            TableModel model = dataTable.getModel();
            if (model instanceof ChartTableModel) {
                ((ChartTableModel) model).updateData();
            }
        }
    }

    /**
     * Returns chart padding
     * @return chart padding
     */
    public RectangleInsets getPadding() {
        return padding;
    }

    /**
     * Sets chart padding
     * @param padding chart padding
     */
    public void setPadding(RectangleInsets padding) {
        this.padding = padding;
        updateChartPadding();
    }

    /**
     * Updates chart padding
     */
    private void updateChartPadding() {
        if (padding == null) {
            chart.getChart().setPadding(new RectangleInsets());
            return;
        }
        double dx = chartPanel.getWidth() / 10000.0;
        double dy = chartPanel.getHeight() / 10000.0;
        chart.getChart().setPadding(
                new RectangleInsets(padding.getTop() * dy, padding.getLeft() * dx,
                padding.getBottom() * dy, padding.getRight() * dy));
    }

    /**
     * Updating chart view
     */
    public void updateChartView() {
        updateChartStyle();
        updateChartPadding();
        updateScrolls();
    }

    /**
     * Updates all scrolls
     */
    public void updateScrolls() {
        updateScroll(scrollBarVertical, chart.getVerticalScrollingInterface());
        updateScroll(scrollBarHorizontal, chart.getHorizontalScrollingInterface());
    }
    
    /**
     * Updates scroll
     */
    public void updateScroll(JScrollBar bar, ChartScrolling scroll) {
        if (scroll != null && scroll.isScrollingSupported()) {
            bar.setVisible(true);
            bar.setValues(scroll.getScrollItemPos(), 1, 0, scroll.getScrollItemsCount());
            bar.setBlockIncrement(1);
            bar.setUnitIncrement(1);
        } else {
            bar.setVisible(false);
        }
    }

    /**
     * Updates chart style
     */
    public void updateChartStyle() {
        style.updateCharts(chartPanel.getChartRenderingInfo());
    }

    /**
     * Updates charts data
     */
    public void updateChartData() {
        updateTableView();
    }

    /**
     * Creates chart view
     * @param chart chart object
     * @param x chart x position
     * @param y chart y position
     * @param width chart width
     * @param height chart height 
     */
    public void createChartView(AbstractChart chart, int x, int y, int width, int height) {
        this.chart = chart;
        setTitle(chart.getChart().getTitle().getText());

        // Create chart view
        chartPanel = new ChartPanel(chart.getChart()) {
            private static final long serialVersionUID = -8132244206101747180L;
            public JToolTip createToolTip() {
	            MultiLineToolTip toolTip = new MultiLineToolTip();
	            toolTip.setComponent(this);
	            return toolTip;
	        }
        };
        
        chartPanel.setPreferredSize(new Dimension(width, height * 2 / 3));
        chartPane = new JPanel(new BorderLayout());
        chartPane.add(chartPanel, BorderLayout.CENTER);
        
        scrollBarVertical = new JScrollBar(JScrollBar.VERTICAL);
        chartPane.add(scrollBarVertical, BorderLayout.EAST);

        scrollBarHorizontal = new JScrollBar(JScrollBar.HORIZONTAL);
        chartPane.add(scrollBarHorizontal, BorderLayout.SOUTH);

        if (chart.getHorizontalScrollingInterface() instanceof ChartScrolling3D) {
            ChartScrolling3D scrolling3D = (ChartScrolling3D)chart.getHorizontalScrollingInterface();
            scrolling3D.addListener(new ScrollingListener() {
                public void itemsScrolled() {
                    updateScrolls();
                }
            });
        }

        createTableView(width, height);

        updateVisibility();
        pack();
        setPosition(x, y, width, height);

        setVisible(true);

        setAlwaysOnTop(true);
        setAlwaysOnTop(false);

        style = new ChartStyle(chart);
        updateChartView();

        initListeners();
    }

    /**
     * Initializes window events listeners
     */
    private void initListeners() {
        scrollBarVertical.addAdjustmentListener(new AdjustmentListener() {
            public void adjustmentValueChanged(AdjustmentEvent e) {
                ChartScrolling scroll = chart.getVerticalScrollingInterface();
                if (scroll!= null && scroll.isScrollingSupported()) {
                    scroll.updateScrollingPos(e.getValue());
                }
            }
        });

        scrollBarHorizontal.addAdjustmentListener(new AdjustmentListener() {
            public void adjustmentValueChanged(AdjustmentEvent e) {
                ChartScrolling scroll = chart.getHorizontalScrollingInterface();
                if (scroll!= null && scroll.isScrollingSupported()) {
                    scroll.updateScrollingPos(e.getValue());
                }
            }
        });

        MouseAdapter adapter = getChart().getMouseAdapter();
        if (adapter != null) {
            scrollBarVertical.addMouseListener(adapter);
            scrollBarHorizontal.addMouseListener(adapter);
        }

        // zooming
        chartPanel.addMouseWheelListener(new MouseWheelListener() {
            public void mouseWheelMoved(MouseWheelEvent e) {
                if (getChart() instanceof Chart3D) {
                    double zoom = e.getWheelRotation() > 0 ? 0.1 : -0.1;
                    ((Chart3D)getChart()).getPlot().zoom(zoom, true);
                }
            }
        });
        
        chartPanel.addComponentListener(new ComponentAdapter() {
            public void componentResized(ComponentEvent e) {
                updateChartPadding();
                updateChartStyle();
            }
        });

        final JFreeChartHolder this_ = this;
        chartPanel.addChartMouseListener(new ChartMouseListener() {
            public void chartMouseClicked(ChartMouseEvent paramChartMouseEvent) {
                getChart().chartMouseClicked(this_, paramChartMouseEvent);
            }
            public void chartMouseMoved(ChartMouseEvent paramChartMouseEvent) {
                getChart().chartMouseMoved(this_, paramChartMouseEvent);
            }
        });


        addComponentListener(new ComponentAdapter() {
            public void componentResized(ComponentEvent e) {
                ChartServer.sendChartEvent("resized", getHandle(), "width", getWidth(), "height", getHeight());
            }
        });

        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                dispose();
            }
            public void windowClosed(WindowEvent e) {
                ChartServer.sendChartEvent("closed", getHandle());
            }
        });
    }

    /**
     * {@inheritDoc}
     */
    public void dispose() {
        holders.remove(handle);
        super.dispose();
    }

    /**
     * Creates table view
     * @param width table width
     * @param height table height
     */
    private void createTableView(int width, int height) {
        dataTable = new ColoredTable();
        
        if (chart.isTableSupported() && chart instanceof GraphChart) {
            GraphChart graph = (GraphChart) chart;
            ChartTableModel model = new ChartTableModel(graph.getDataset());
            dataTable.setModel(model);
            
            if (chart.getVerticalScrollingInterface() instanceof GraphSeriesScrolling) {
                GraphSeriesScrolling scroll = (GraphSeriesScrolling) chart.getVerticalScrollingInterface();
                scroll.addListener(dataTable);
                scroll.addListener(model);
            }
        }

        final Frame frame = this;
        dataTable.addMouseListener(new MouseAdapter() {
            public void mouseClicked(MouseEvent e) {
                if (e.getClickCount() > 1) {
                    (new TableColorDialog(frame, dataTable,
                            dataTable.getSelectedRow(), dataTable.getSelectedColumn())).setVisible(true);
                }
            }
        });
        tablePanel = new JScrollPane(dataTable);
        tablePanel.setPreferredSize(new Dimension(width, height / 3));
        tablePanel.setVisible(false);
    }

    /**
     * Moves window to specified position
     * @param x window x position
     * @param y window y position
     * @param width window width
     * @param height window height
     */
    public void setPosition(int x, int y, int width, int height) {
        if (x <= 0 || y <= 0) {
            RefineryUtilities.centerFrameOnScreen(this);
            //setPreferredSize(new Dimension(width, height));
        } else {
            setBounds(x, y, width, height);
        }
    }

    /**
     * Set chart panel visibility
     * @param visible visibility flag
     */
    public void setChartVisible(boolean visible) {
        visible = visible || !chart.isTableSupported();
        if (chartPane.isVisible() != visible) {
            chartPane.setVisible(visible);
            updateVisibility();
        }
    }

    /**
     * Tests if chart is visible
     * @return true if chart is visible
     */
    public boolean isChartVisible() {
        return chartPane.isVisible();
    }

    /**
     * Set table panel visibility
     * @param visible visibility flag
     */
    public void setTableVisible(boolean visible) {
        visible = visible && chart.isTableSupported();
        if (tablePanel.isVisible() != visible) {
            tablePanel.setVisible(visible);
            updateTableView();
            updateVisibility();
        }
    }

    /**
     * Tests if table is visible
     * @return true if table is visible
     */
    public boolean isTableVisible() {
        return tablePanel.isVisible();
    }

    /**
     * Updates visibility
     */
    private void updateVisibility() {
        Container mainPane = null;
        if (!chartPane.isVisible()) {
            mainPane = tablePanel;
        } else if (!tablePanel.isVisible()) {
            mainPane = chartPane;
        } else {
            mainPane = new JSplitPane(JSplitPane.VERTICAL_SPLIT, chartPane, tablePanel);
        }
        mainPane.setVisible(true);
        setContentPane(mainPane);

        pack();
    }

    /**
     * Enable zooming flag
     * @param zoomable true enables zooming.
     */
    public void setZoomable(boolean zoomable) {
        chartPanel.setRangeZoomable(zoomable);
    }

    /**
     * Test zooming enabling
     * @return true if zooming is enabled.
     */
    public boolean isZoomable() {
        return chartPanel.isRangeZoomable();
    }

    /**
     * Register chart properties dialog
     */
    static {
        ChartEditorManager.setChartEditorFactory(new ChartEditorFactory() {
            public ChartEditor createEditor(JFreeChart chart) {
                for (JFreeChartHolder holder: holders.values()) {
                    if (holder.getChart().getChart() == chart) {
                        return new ChartPropertiesDialog(holder.getChart());
                    }
                }
                return new DefaultChartEditorFactory().createEditor(chart);
            }
        });
    }
    
    /**
     * Returns table
     * @return the table
     */
    public ColoredTable getTable() {
        return chart.isTableSupported() ? dataTable : null;
    }
}
