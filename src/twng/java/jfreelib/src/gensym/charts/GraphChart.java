package gensym.charts;

import gensym.charts.annotations.ChartAnnotations;
import gensym.charts.annotations.table.ext.TableCellTitle;
import gensym.charts.autostat.AutoStatInfo;
import gensym.charts.autostat.XYAutoStatSeries;
import gensym.charts.autostat.XYParetoDataset;
import gensym.charts.axis.MultiAxesPlot;
import gensym.charts.axis.SeriesInfo;
import gensym.charts.axis.StringNumberFormat;
import gensym.charts.axis.TimeNumberFormat;
import gensym.charts.dialogs.tables.TableColorDialog;
import gensym.charts.scrolling.ChartScrolling;
import gensym.charts.scrolling.GraphSeriesScrolling;

import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.text.NumberFormat;
import java.text.SimpleDateFormat;
import java.util.*;

import org.jfree.chart.*;
import org.jfree.chart.axis.*;
import org.jfree.chart.entity.*;
import org.jfree.chart.plot.*;
import org.jfree.chart.renderer.xy.*;
import org.jfree.chart.title.TextTitle;
import org.jfree.data.Range;
import org.jfree.data.general.Series;
import org.jfree.data.xy.*;
import org.jfree.ui.*;

/**
 * Graph chart 
 */
public class GraphChart extends XYSeriesGraph implements IDataHotSpots {
    /**
     * Data set
     */
    private GraphXYZDataset dataset = new GraphXYZDataset();
    
    /**
     * Scrolling
     */
    private GraphSeriesScrolling scrolling = null;

    /**
     * Stat data set
     */
    private XYSeriesCollection statDataset = new XYSeriesCollection();
    
    /**
     * Data hot spot allowing property
     */
    private boolean allowDataHotSpots = false;
    
    /**
     * Point hot spot allowing property
     */
    private boolean allowPointHotSpots = false;
    
    /**
     * Series hot spot allowing property
     */
    private boolean allowSeriesHotSpots = false;

    /**
     * X axis labels format
     */
    private StringNumberFormat xAxisFormat = null;
    
    /**
     * Time title
     */
    private TextTitle timeTitle = null;
    
    /**
     * Annotations
     */
    private ChartAnnotations annotations;
    
    /**
     * Stacked data allowing flag
     */
    private boolean allowStackedData = false;

    /**
     * Horizontal stacked bars allowing flag
     */
    private boolean allowHorzBarStacked = false;
    
    /**
     * Ribbon plotting method allowing flag
     */
    private boolean allowRibbon = false;

    /**
     * Bubble plotting method allowing flag
     */
    private boolean allowBubble = false;

    /**
     * Step plotting method allowing flag
     */
    private boolean allowStep = false;

    /**
     * Constructor
     * @param title chart title
     */
    public GraphChart(String title) {
        super(createChart(title));

        getPlot().setPlotSeries(0, 15);

        scrolling = new GraphSeriesScrolling(-1, dataset);
        getPlot().setDataset(scrolling.getDataset());
        
        xAxisFormat = createAxisFormat();

        if (getChart().getXYPlot().getDomainAxis() instanceof NumberAxis) {
            NumberAxis axis = (NumberAxis) getChart().getXYPlot().getDomainAxis();
            axis.setNumberFormatOverride(xAxisFormat);
            Range range = new Range(-Double.MAX_VALUE, Double.MAX_VALUE);
            axis.setDefaultAutoRange(range);
        }
        
        annotations = new ChartAnnotations(this);
        
        initStatDatasets();
    }

    /**
     * Creates axis format
     * @return created format
     */
    private StringNumberFormat createAxisFormat() {
        return new StringNumberFormat(new StringNumberFormat.DataSource() {
            public int indexOf(double value) {
                if (getDataset().getSeriesCount() > 0) {
                    return getDataset().getSeries(0).indexOf(value);
                }
                return -1;
            }
            public Double getValue(int index) {
                if (getDataset().getSeriesCount() > 0 && getDataset().getItemCount(0) > index) {
                    return getDataset().getXValue(0, index);
                }

                return null;
            }
        });
    }
    
    /**
     * Creates graph chart
     * @param title chart title
     * @return created graph chart
     */
    private static JFreeChart createChart(String title) {
        NumberAxis xAxis = new NumberAxis();
        xAxis.setAutoRangeIncludesZero(false);
        MultiAxesPlot mainPlot = new MultiAxesPlot(xAxis);
        
        mainPlot.setRenderer(new XYLineAndShapeRenderer(true, false));

        JFreeChart chart = new JFreeChart(title, JFreeChart.DEFAULT_TITLE_FONT, mainPlot, false);
        ChartFactory.getChartTheme().apply(chart);
        return chart;
    }

    /**
     * Returns plot
     * @return plot
     */
    public MultiAxesPlot getPlot() {
        return (MultiAxesPlot) getChart().getPlot();
    }

    /**
     * Returns dataset
     * @return the dataset
     */
    public GraphXYZDataset getDataset() {
        return dataset;
    }

    /**
     * Initializes stat data sets
     */
    private void initStatDatasets() {
        XYPlot plot = getPlot().getCurrentPlot();

        plot.setDataset(1, statDataset);
        
        StandardXYItemRenderer renderer = new StandardXYItemRenderer();
        plot.setRenderer(1, renderer);
        plot.setRenderer(2, renderer);
        plot.setRenderer(3, renderer);
        plot.setDatasetRenderingOrder(DatasetRenderingOrder.FORWARD);
    }

    /**
     * Gets stat dataset
     * @return statDataset
     */
    public XYSeriesCollection getStatDataset() {
        return statDataset;
    }

    /**
     * {@inheritDoc}
     */
    public void setRenderer(XYItemRenderer renderer) {
        getChart().getXYPlot().setRenderer(renderer);
    }

    /**
     * {@inheritDoc}
     */
    public boolean isTableSupported() {
        return true;
    }

    /**
     * {@inheritDoc}
     */
    protected void addSeries(Series series) {
        dataset.addSeries((XYSeries) series);
        updateSeriesPoints(this.getSeriesCount() - 1);
    }

    /**
     * {@inheritDoc}
     */
    protected Series getSeries(int index) {
        return index < getSeriesCount() ? dataset.getSeries(index) : null;
    }

    /**
     * {@inheritDoc}
     */
    protected int getSeriesCount() {
        return dataset.getSeriesCount();
    }

    /**
     * {@inheritDoc}
     */
    protected void removeSeries(int index) {
        dataset.removeSeries(index);
    }

    /**
     * {@inheritDoc}
     */
    public void setSeriesLineType(int series, int lineType) {
        getPlot().setSeriesStroke(series, ChartLineTypes.makeBasicStroke(lineType));
    }

    /**
     * {@inheritDoc}
     * Returns X and Y axis
     */
   protected Axis[] getAxesList() {
       LinkedList<Axis> axes = new LinkedList<Axis>();
       axes.add(getPlot().getDomainAxis());
       for (Object obj : getPlot().getSubplots()) {
           XYPlot plot = (XYPlot) obj;
           for (int i = 0; i < plot.getRangeAxisCount(); i++) {
               axes.add(plot.getRangeAxis(i));
           }
       }
       return axes.toArray(new Axis[0]);
   }

   /**
    * {@inheritDoc}
    */
   public void setPointLabel(int point, String label) {
       xAxisFormat.setLabel(point, label);
   }
   
   /**
    * {@inheritDoc}
    */
   public void setAxisColor(Color color) {
       super.setAxisColor(color);
       
       XYPlot plot = getChart().getXYPlot();
       plot.setRangeGridlinePaint(color);
       plot.setDomainGridlinePaint(color);
   }
   
   /**
    * {@inheritDoc}
    */
   public void showGridLines(boolean showXAxis, boolean showYAxis) {
       XYPlot plot = getChart().getXYPlot();
       plot.setDomainGridlinesVisible(showXAxis);
       plot.setRangeGridlinesVisible(showYAxis);
   }
   
   /**
    * Sets grid line stroke
    * @param stroke
    */
   public void setGridStroke(Stroke stroke) {
       XYPlot plot = getChart().getXYPlot();
       plot.setDomainGridlineStroke(stroke);
       plot.setRangeGridlineStroke(stroke);
   }
   
   /**
     * Adds autostat subset
     * @param info auto stat info
     * @param forAllPoints
    */
   public void addAutoStatSubset(AutoStatInfo info, boolean forAllPoints) {
       if (info == null) {
           return;
       }
       
       XYAutoStatSeries series = new XYAutoStatSeries(info, forAllPoints);
       if (statDataset.indexOf(series.getKey()) == -1) {
           statDataset.addSeries(series);
           dataset.addChangeListener(series);
           series.updateData(dataset);
       }
   }
   
   /**
     * Adds Pareto autostat subset
     * @param ascending if true then there are used ascending accumulated percent line otherwise - descending
    */
   public void addParetoAutoStatSubset(boolean ascending) {
       XYPlot plot = getPlot().getCurrentPlot();
       int datasetIndex = ascending ? 2 : 3;
       if (plot.getDataset(datasetIndex) == null) {
           XYParetoDataset paretoDataset = new XYParetoDataset(ascending);
           plot.setDataset(datasetIndex, paretoDataset);
           
           NumberAxis axis = new NumberAxis("Pareto Percent");
           axis.setNumberFormatOverride(NumberFormat.getPercentInstance());
           plot.setRangeAxis(1, axis);
           plot.mapDatasetToRangeAxis(datasetIndex, 1);

           dataset.addChangeListener(paretoDataset);
           paretoDataset.update(dataset);
       }
   }
   
   /**
    * {@inheritDoc}
    */
   public void updateChart() {
       super.updateChart();
       annotations.update();
       getPlot().updateItems();
       getChart().fireChartChanged();
   }

   /**
    * {@inheritDoc}
    */
   public void chartMouseClicked(JFreeChartHolder holder, ChartMouseEvent paramChartMouseEvent) {
       ChartEntity entity = paramChartMouseEvent.getEntity();
       if (isDataHotSpotsAllowed() && entity instanceof XYItemEntity) {
           XYItemEntity xyEntity = (XYItemEntity) entity;
           XYSeries series = (XYSeries) getSeries(xyEntity.getSeriesIndex());
           XYDataItem item = series.getDataItem(xyEntity.getItem());
           double zValue = getDataset().getZValue(xyEntity.getSeriesIndex(), xyEntity.getItem());
           ChartServer.sendChartEvent("clicked", holder.getHandle(),
                   "x", item.getX(), "y", item.getY(), "z", zValue,
                   "subset", xyEntity.getSeriesIndex(), "point", xyEntity.getItem());
       } else if (entity instanceof TitleEntity) {
           TitleEntity titleEntity = (TitleEntity) entity;
           if (titleEntity.getTitle() instanceof TableCellTitle &&
                   paramChartMouseEvent.getTrigger().getClickCount() > 1) {
               TableCellTitle cellTitle = (TableCellTitle) titleEntity.getTitle();
               if (cellTitle.getTableColorSource() != null) {
                   TableColorDialog dialog = new TableColorDialog(null, cellTitle.getTableColorSource(), cellTitle.getRow(), cellTitle.getColumn());
                   dialog.setVisible(true);
               }
           }
       }

       super.chartMouseClicked(holder, paramChartMouseEvent);
   }

   /**
    * {@inheritDoc}
    */
   public void chartMouseMoved(JFreeChartHolder holder, ChartMouseEvent paramChartMouseEvent) {
       int cursorType = holder.getCursor().getType();
       int newCursotType = cursorType; 

       if (isDataHotSpotsAllowed() && paramChartMouseEvent.getEntity() instanceof XYItemEntity ||
               isPointHotSpotsAllowed() && paramChartMouseEvent.getEntity() instanceof TickLabelEntity ||
               isSeriesHotSpotsAllowed() && paramChartMouseEvent.getEntity() instanceof LegendItemEntity) {
           newCursotType = Cursor.HAND_CURSOR;
       } else {
           newCursotType = Cursor.DEFAULT_CURSOR;
       }
       
       if (cursorType != newCursotType) {
           holder.setCursor(new Cursor(newCursotType));
       }

       super.chartMouseMoved(holder, paramChartMouseEvent);
   }

   /**
    * {@inheritDoc}
    */
   public boolean isDataHotSpotsAllowed() {
       return allowDataHotSpots;
   }
   
   /**
    * {@inheritDoc}
    */
   public void setAllowDataHotSpots(boolean allow) {
       allowDataHotSpots = allow;
   }
   
   /**
    * {@inheritDoc}
    */
   public boolean isSeriesHotSpotsAllowed() {
       return allowSeriesHotSpots;
   }
   
   /**
    * {@inheritDoc}
    */
   public void setAllowSeriesHotSpots(boolean allow) {
       allowSeriesHotSpots = allow;
   }

   /**
    * {@inheritDoc}
    */
   public boolean isPointHotSpotsAllowed() {
       return allowPointHotSpots;
   }
   
   /**
    * {@inheritDoc}
    */
   public void setAllowPointHotSpots(boolean allow) {
       allowPointHotSpots = allow;
   }

   /**
    * Sets time format mode and display time if necessary
    * @param time true for time mode
    */
   public void setDateTimeAxisMode(boolean time) {
       if (time && timeTitle == null) {
           xAxisFormat.setDefaultNumberFormat(new TimeNumberFormat());

           timeTitle = new TextTitle(
                   (new SimpleDateFormat("dd E MMM yyyy")).format(new Date()));
           timeTitle.setHorizontalAlignment(HorizontalAlignment.LEFT);
           timeTitle.setVerticalAlignment(VerticalAlignment.TOP);
           timeTitle.setPosition(RectangleEdge.BOTTOM);
           getChart().addSubtitle(timeTitle);
       } else if (timeTitle != null) {
           getChart().removeSubtitle(timeTitle);
           timeTitle = null;
           xAxisFormat.setDefaultNumberFormat(null);
       }
   }
   
   /**
    * Returns chart annotations
    * @return the chart annotations
    */
   public ChartAnnotations getAnnotations() {
       return annotations;
   }
   
   /**
    * {@inheritDoc}
    */
   protected void updateSeriesPoints(int series) {
       SeriesInfo info = getPlot().getSeriesInfo(series);
       info.setShapeVisible(getMarkPoints());
       if (info.getShape() == null) {
           info.setShape(new Ellipse2D.Float(0, 0, 2.0F, 2.0F));
       }
   }

   /**
    * Sets series points shape
    * @param series series index
    * @param shape points shape
    * @param filled shape filling flag
    */
   public void setSeriesPointShape(int series, Shape shape, boolean filled) {
       SeriesInfo info = getPlot().getSeriesInfo(series);
       info.setShapeVisible(getMarkPoints());
       info.setShapeFilled(filled);
       info.setShape(shape);
   }
   
   /**
    * Tests if stacked data is allowed
    * @return true if stacked data is allowed
    */
   public boolean isStackedDataAllowed() {
       return allowStackedData;
   }
   
   /**
    * Sets stacked data allowing 
    * @param allowed the stacked data allowing flag
    */
   public void setStackedDataAllowed(boolean allowed) {
       allowStackedData = allowed;
   }

   /**
    * Tests if horizontal stacked bars are allowed
    * @return true if horizontal stacked bars are allowed
    */
   public boolean isHorzBarStackedAllowed() {
       return allowHorzBarStacked;
   }
   
   /**
    * Sets horizontal stacked bars allowing 
    * @param allowed the horizontal stacked bars allowing flag
    */
   public void setHorzBarStackedAllowed(boolean allowed) {
       allowHorzBarStacked = allowed;
   }
   
   /**
    * Tests if Ribbon plotting method is allowed
    * @return true if Ribbon plotting method is allowed
    */
   public boolean isRibbonAllowed() {
       return allowRibbon;
   }
   
   /**
    * Sets Ribbon plotting method  allowing 
    * @param allowed the Ribbon plotting method allowing flag
    */
   public void setRibbonAllowed(boolean allowed) {
       allowRibbon = allowed;
   }
   
   /**
    * Tests if Bubble plotting method is allowed
    * @return true if Bubble plotting method is allowed
    */
   public boolean isBubbleAllowed() {
       return allowBubble;
   }

   /**
    * Sets Bubble plotting method  allowing
    * @param allowed the Bubble plotting method allowing flag
    */
   public void setBubbleAllowed(boolean allowed) {
       allowBubble = allowed;
   }
   
   /**
    * Tests if Step plotting method is allowed
    * @return true if Step plotting method is allowed
    */
   public boolean isStepAllowed() {
       return allowStep;
   }
   
   /**
    * Sets Step plotting method  allowing 
    * @param allowed the Step plotting method allowing flag
    */
   public void setStepAllowed(boolean allowed) {
       allowStep = allowed;
   }

   /**
    * Sets the flag that controls whether the tick labels are displayed vertically.
    */
   public void showPointsVertically(boolean flag) {
       getPlot().getDomainAxis().setVerticalTickLabels(flag);
   }

   /**
    * {@inheritDoc}
    */
   protected void updatePaints(Map<Integer, Paint> paints) {
       getPlot().setSeriesPaints(new LinkedHashMap<Integer, Paint>(paints));
   }

   /**
    * {@inheritDoc}
    */
   public ChartScrolling getVerticalScrollingInterface() {
       return getSeriesScrolling();
   }
   
   /**
    * Returns series scrolling
    * @return the series scrolling
    */
   public GraphSeriesScrolling getSeriesScrolling() {
       return scrolling;
   }

   @Override
   protected boolean allowDuplicates() {
       return false;
   }
}
