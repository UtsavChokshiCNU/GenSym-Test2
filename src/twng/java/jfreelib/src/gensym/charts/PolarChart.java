package gensym.charts;

import gensym.charts.hatching.HatchedPaint;

import java.awt.*;
import java.awt.geom.Rectangle2D;
import java.util.List;
import java.util.Map;

import org.jfree.chart.*;
import org.jfree.chart.axis.Axis;
import org.jfree.chart.plot.PolarPlot;
import org.jfree.chart.renderer.DefaultPolarItemRenderer;
import org.jfree.data.general.Series;
import org.jfree.data.xy.*;

/**
 * Polar chart class
 */
public class PolarChart extends XYSeriesGraph {
    /*
     * Data set
     */
    private XYSeriesCollection dataset = null;

    /**
     * Constructor
     * @param title chart title
     */
    public PolarChart(String title) {
        super(ChartFactory.createPolarChart(title, new XYSeriesCollection(), false, false, false));
        getPlot().setRenderer(new DefaultPolarItemRenderer());
        dataset = (XYSeriesCollection) getPlot().getDataset();
    }

    /**
     * {@inheritDoc}
     */
    protected void addSeries(Series series) {
        dataset.addSeries((XYSeries)series);
    }

    /**
     * {@inheritDoc}
     */
    protected XYSeries getSeries(int index) {
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
     * Returns plot
     * @return plot
     */
    private PolarPlot getPlot() {
        return (PolarPlot) getChart().getPlot();
    }
    
    /**
     * Returns Polar chart renderer
     * @return renderer
     */
    private DefaultPolarItemRenderer getRenderer() {
        return (DefaultPolarItemRenderer) getPlot().getRenderer();
    }
    /**
     * {@inheritDoc}
     */
    public void setSeriesLineType(int series, int lineType) {
        getRenderer().setSeriesStroke(series, ChartLineTypes.makeBasicStroke(lineType));
    }

    /**
     * {@inheritDoc}
     */
    protected void updatePaints(Map<Integer, Paint> paints) {
        DefaultPolarItemRenderer renderer = getRenderer();
        if (renderer != null) {
            for (Integer series : paints.keySet()) {
                Paint paint = paints.get(series);
                
                if (paint instanceof HatchedPaint) {
                    HatchedPaint hatched = (HatchedPaint) paint;
                    paint = hatched.getForegroundColor();
                }

                renderer.setSeriesPaint(series, paint);
            }
        }
    }

    /**
     * {@inheritDoc}
     * JFree chart does not work correctly with negative Y values, so they are converted to
     *  non negative: (x, y) => (x + 180 degree, -y).
     */
    protected void updatePoints(List<XYDataItem> points) {
        int index = 0;
        boolean isPrevNegative = points.isEmpty() || points.get(0).getYValue() < 0.0;
        for (XYDataItem item : points) {
            XYSeries series = getSeries(index++ / getItemCount());

            if (series == null) {
                break;
            }

            if (item.getYValue() < 0.0) {
                if (!isPrevNegative) {
                    series.add(0, 0);
                    isPrevNegative = true;
                }
                double newX = item.getXValue();
                newX = newX < 180.0 ? 180.0 + newX : newX - 180.0;   
                series.add(newX, -item.getYValue());
            } else {
                if (isPrevNegative) {
                    series.add(0, 0);
                    isPrevNegative = false;
                }
                series.add(item);
            }
        }
    }

    /**
     * {@inheritDoc}
     */
    protected boolean allowDuplicates() {
        return true;
    }
    
    /**
     * {@inheritDoc}
     */
    public Paint getBackgroundPaint(Color color1, Color color2, ChartRenderingInfo info) {
        Rectangle2D rect = info.getPlotInfo().getPlotArea();
        if (rect == null) {
            return null;
        }
        float radius = (float) Math.sqrt(rect.getHeight() * rect.getHeight() + rect.getWidth() * rect.getWidth()); 
        return new RadialGradientPaint((float)rect.getCenterX(), (float)rect.getCenterY(), radius, new float[]{0.0f, 1.0f}, new Color[]{color1, color2});
    }
    
    /**
     * {@inheritDoc}
     */
   protected Axis[] getAxesList() {
       return new Axis[] {getPlot().getAxis()}; 
   }
   
   /**
    * {@inheritDoc}
    */
   public void setAxisColor(Color color) {
       super.setAxisColor(color);
       
       getPlot().setAngleGridlinePaint(color);
       getPlot().setAngleLabelPaint(color);
       getPlot().setRadiusGridlinePaint(color);
   }
   
   /**
    * {@inheritDoc}
    */
   public void showGridLines(boolean showXAxis, boolean showYAxis) {
       getPlot().setAngleGridlinesVisible(showXAxis);
       getPlot().setRadiusGridlinesVisible(showYAxis);
   }

   @Override
   protected void updateSeriesPoints(int series) {
   }
}
