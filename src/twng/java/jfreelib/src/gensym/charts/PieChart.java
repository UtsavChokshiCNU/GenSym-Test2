package gensym.charts;

import gensym.charts.hatching.HatchedPaint;
import gensym.charts.dialogs.PieChartProperties;
import gensym.charts.scrolling.ChartScrolling;

import java.awt.Paint;
import java.awt.Color;
import java.awt.event.MouseEvent;
import java.util.*;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartMouseEvent;
import org.jfree.chart.axis.Axis;
import org.jfree.chart.labels.PieSectionLabelGenerator;
import org.jfree.chart.labels.StandardPieSectionLabelGenerator;
import org.jfree.chart.editor.ChartEditor;
import org.jfree.chart.entity.ChartEntity;
import org.jfree.chart.entity.PieSectionEntity;
import org.jfree.chart.labels.*;
import org.jfree.chart.plot.*;
import org.jfree.util.TableOrder;
import org.jfree.data.category.CategoryToPieDataset;

/**
 * Pie chart class
 */
public class PieChart extends AbstractChart {
    /**
     * Item count
     */
    private int itemCount = 0;
    
    /**
     * Set of exploded items
     */
    private Set<Integer> explodedItems = new HashSet<Integer>();
    
    /** 
     * Slice hatching flag 
     */
    protected boolean sliceHatching = false;
    
    /**
     * Current pie chart index
     */
    private int currentPieIndex = -1;

    /**
     * Disable automatic slice exploding
     */
    public static final int AUTO_EXPLODE_NONE = 0;
    
    /**
     * Pie data set
     */
    private PieCategoryDataset dataset = new PieCategoryDataset();
    
    /**

     * Enable automatic slice exploding. Slices are exploded for all subsets
     */
    public static final int AUTO_EXPLODE_ALLSUBSETS = 1;

    /**
     * Enable automatic slice exploding. Slices are exploded for individual subsets only
     */
    public static final int AUTO_EXPLODE_INDSUBSETS = 2;
    
    /**
     * Slices auto-explode flag to set
     */
    private int slicesAutoExplode = AUTO_EXPLODE_NONE;

    /**
     * Constructor
     * @param title chart title
     */
    public PieChart(String title) {
        super(ChartFactory.createPieChart(title, null, false, false, false));

        name = "Pie chart";
        
        setCurrentPie(0);
        getPlot().setShadowPaint(Color.DARK_GRAY);
        getPlot().setIgnoreZeroValues(true);
        
        setDataShadows(true, false);
        showPieLabels(true, true);
        showLegend(false);
    }
    
    /**
     * Returns pie plot
     * @return pie plot
     */
    private PiePlot getPlot() {
        return (PiePlot) getChart().getPlot();
    }
    
    /**
     * Returns pie chart data set
     * @return pie chart data set
     */
    public PieCategoryDataset getDataset() {
        return dataset;
    }
    
    /**
     * {@inheritDoc}
     */
    protected Axis[] getAxesList() {
        return new Axis[0];
    }

    /**
     * {@inheritDoc}
     */
    public int getItemCount() {
        return itemCount;
    }

    /**
     * {@inheritDoc}
     */
    public void setItemCount(int count) {
        itemCount = count;
        getDataset().setRowsCount(count);
    }

    /**
     * {@inheritDoc}
     */
    public void setNullDataValueX(double x) {
    }

    /**
     * {@inheritDoc}
     */
    public void setNullDataValueY(double y) {
    }

    /**
     * {@inheritDoc}
     */
    public void setSeriesCount(int count) {
        getDataset().setColumnsCount(count);
    }

    /**
     * {@inheritDoc}
     */
    public void updateChart() {
        super.updateChart();
        
        updateExplodedItems();
    }
    
    /**
     * {@inheritDoc}
     */
    public void setPointLabel(int point, String label) {
        if (point < getDataset().getRowCount()) {
            getDataset().setRowKey(point, label);
        }
    }

    /**
     * {@inheritDoc}
     */
    public void setSeriesLabel(int series, String label) {
        if (series < getDataset().getColumnCount()) {
            getDataset().setColumnKey(series, label);
        }
    }

    /**
     * {@inheritDoc}
     */
    public void setSeriesLineType(int series, int lineType) {
    }

    /**
     * {@inheritDoc}
     */
    public void setValuesX(List<Double> values) {
        PieCategoryDataset dataset = getDataset();
        dataset.setEventsAllowed(false);
        
        int index = 0;
        for (double x : values) {
            int column = index / itemCount;
            
            if (column >= dataset.getColumnCount()) {
                break;
            }
            
            dataset.setValue(x, index++ % itemCount, column);
        }
        
        dataset.setEventsAllowed(true);
    }

    /**
     * {@inheritDoc}
     */
    public void setValuesY(List<Double> values) {
        explodedItems.clear();
        
        int index = 0;
        for (double y : values) {
            if (Math.abs(y - 1.0) < 0.01) {
                explodedItems.add(index);
            }
            index++;
        }
    }
    
    /**
     * Updates exploded items
     */
    private void updateExplodedItems() {
        for (int index = 0; index < itemCount; index++) {
            updateExplodedItem(index);
        }
    }

    /**
     * Updates exploded item
     * @param index item index (zero based)
     */
    private void updateExplodedItem(int index) {
        getPlot().setExplodePercent(getDataset().getRowKey(index), explodedItems.contains(index) ? 0.30 : 0.0);
    }

    /**
     * {@inheritDoc}
     */
    public void showGridLines(boolean showXAxis, boolean showYAxis) {
    }
    
    /**
     * {@inheritDoc}
     */
    public final void setDataShadows(boolean shadow, boolean shadow3d) {
        getPlot().setShadowXOffset(shadow ? 4.0 : 0.0);
        getPlot().setShadowYOffset(shadow ? 4.0 : 0.0);
    }

    /**
     * {@inheritDoc}
     */
    public void showPieZeroData(boolean show) {
        getPlot().setIgnoreZeroValues(!show);
    }
	
    /**
     * {@inheritDoc}
     */
    public boolean isShowPieZeroData() {
        return !getPlot().getIgnoreZeroValues();
    }
    
    /**
     * Show pie chart labels
     * @param percent show percent?
     * @param label show labels?
     */
    public final void showPieLabels(boolean percent, boolean label) {
        PieSectionLabelGenerator lableGenerator = null;
        if (percent && label) {
            lableGenerator = new StandardPieSectionLabelGenerator("{2} - {0}");
        } else if (percent) {
            lableGenerator = new StandardPieSectionLabelGenerator("{2}");
        }  else if (label) {
            lableGenerator = new StandardPieSectionLabelGenerator("{0}");
        }
        getPlot().setLabelGenerator(lableGenerator);
    }
    
    /**
     * Test enable toolTips showing
     * @return true if toolTips showing enabled 
     */
    public boolean isTooltipsEnabled() {
        return (getPlot().getToolTipGenerator() != null);
    }
    
    /**
     * Enable showing toolTips
     */
    public void setTooltipsEnabled(boolean enable) {
    	String format = "Section: {0}\r\nAbsolute value: {1}\r\nPercent value: {2}";
        getPlot().setToolTipGenerator(enable ? new StandardPieToolTipGenerator(format) : null);
    }

    /**
     * Test showing labels inside of chart
     * @return true if labels show inside pie sectors 
     */
    public boolean isShowLabelsInsideOfChart() {
        return getPlot().getSimpleLabels();
    }
   
    /**
     * Show labels inside of chart
     */
    public void setShowLabelsInsideOfChart(boolean showInside) {
        getPlot().setSimpleLabels(showInside);
    }

    /**
     * {@inheritDoc}
     */
    public ChartEditor makeChartEditor() {
    	return new PieChartProperties(getChart());
    }
    
    /**
     * {@inheritDoc}
     */
    public ChartScrolling getVerticalScrollingInterface() {
        return new ChartScrolling() {
            public int getScrollItemPos() {
                return currentPieIndex;
            }
            public int getScrollItemsCount() {
                return dataset.getColumnCount();
            }
            public boolean isScrollingSupported() {
                return dataset.getColumnCount() > 1;
            }
            public void updateScrollingPos(int newValue) {
                if (isScrollingSupported()) {
                    setCurrentPie(newValue);
                }
            }
        };
    }
    
    /**
     * Sets current pie
     * @param index the pie index
     */
    private final void setCurrentPie(int index) {
        if (currentPieIndex != index) {
            currentPieIndex = index;
            getPlot().setDataset(new CategoryToPieDataset(getDataset(), TableOrder.BY_COLUMN, currentPieIndex));
        }
    }

    /**
     * @return the sliceHatching
     */
    public boolean isSliceHatching() {
        return sliceHatching;
    }
    
    /**
     * Sets hatching slice type
     */
    public void setSliceHatching(boolean value) {
        sliceHatching = value;
    }

    /**
     * {@inheritDoc}
     */
    public void chartMouseClicked(JFreeChartHolder holder, ChartMouseEvent paramChartMouseEvent) {
        MouseEvent me = paramChartMouseEvent.getTrigger();
        if ((me.getButton() == MouseEvent.BUTTON1) && (me.getClickCount() > 1)) { 
            ChartEntity entity = paramChartMouseEvent.getEntity();
            if (entity instanceof PieSectionEntity) {
                PieSectionEntity pe = (PieSectionEntity) entity;
                if (isRevertExplodingAllowed(pe.getPieIndex())) {
                    revertExploding(pe.getSectionIndex());
                }
            }
        }
        super.chartMouseClicked(holder, paramChartMouseEvent);
    }
    
    /**
     * Sets slices auto-explode flag
     * @param saeFlag the slicesAutoExplode flag to set
     */
    public void setSlicesAutoExplode(int saeFlag) {
        slicesAutoExplode = saeFlag;
    }

    /**
     * Check is revert exploding allowed
     * @param pieIndex the pie index need in case if auto-explode flag sets to 'individual subsets'
     * @return the true if auto-explode flag seted to 'all subsets' 
     *                  or auto-explode flag seted to 'individual subsets' and pie index == 0 
     */
    private boolean isRevertExplodingAllowed(int pieIndex) {
        return (slicesAutoExplode == AUTO_EXPLODE_ALLSUBSETS) 
           || ((slicesAutoExplode == AUTO_EXPLODE_INDSUBSETS) && (pieIndex == 0));
    }

    /**
     * Revert exploding for item with specified index
     * @param index  the item index
     */
    private void revertExploding(int index) {
        if (!explodedItems.contains(index)) {
            explodedItems.add(index);
        } else {
            explodedItems.remove(index);
        }
        updateExplodedItem(index);
    }
    
    /**
     * {@inheritDoc}
     */
    protected void updatePaints(Map<Integer, Paint> paints) {
        for (Map.Entry<Integer, Paint> entry : paints.entrySet()) {
            Comparable<?> key = getDataset().getRowKey(entry.getKey());
            if (key != null) {
                Paint paint = entry.getValue();
                if (paint instanceof HatchedPaint && !isSliceHatching()) {
                    HatchedPaint hatched = (HatchedPaint) paint;
                    paint = hatched.getForegroundColor();
                }
                getPlot().setSectionPaint(key, paint);
            }
        }
    }
}
