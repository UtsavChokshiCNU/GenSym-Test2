package gensym.charts;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

import org.jfree.chart.JFreeChart;
import org.jfree.data.xy.*;

/*
 * AbstractChart implementation class working with XYSeries.
 */
public abstract class XYSeriesGraph extends SeriesGraph {
    /**
     * Start time
     */
    private double startTime = 0;
    
    /**
     * Delta X
     */
    private int deltaX = 0;

    /**
     * Deltas per day
     */
    private int deltasPerDay = 0;

    /**
     * Constructor
     * @param chart JFree chart
     */
     public XYSeriesGraph(JFreeChart chart) {
         super(chart);
     }
     
     /**
      * {@inheritDoc}
      */
     public void setSeriesCount(int count) {
         // Add additional series
         while (getSeriesCount() < count) {
             addSeries(new XYSeries("Subset " + (getSeriesCount() + 1), false, allowDuplicates()));
         }

         // Remove odd series
         while (getSeriesCount() > count) {
             removeSeries(getSeriesCount() - 1);
         }
     }

     /**
      * {@inheritDoc}
      */
     public void setValueX(int series, int index, double value) {
         if (index >= getItemCount()) {
             return;
         }
         if (getSeriesCount() < series) {
             setSeriesCount(series);
         }
         XYSeries xySeries = (XYSeries) getSeries(series);
         
         if (xySeries.indexOf(value) != -1 && !allowDuplicates()) {
             return;
         }

         if (xySeries.getItemCount() <= index) {
             while (xySeries.getItemCount() <= index) {
                 xySeries.add(value, null);
             }
         } else {
             List<XYDataItem> points = new ArrayList<XYDataItem>(xySeries.getItemCount());
             for (int point = 0; point < xySeries.getItemCount(); point ++) {
                 XYDataItem item = xySeries.getDataItem(point);
                 if (point == index) {
                     item = new XYDataItem(value, item.getYValue());
                 }
                 points.add(item);
             }
             
             xySeries.setNotify(false);
             xySeries.clear();
             for (XYDataItem item : points) {
                 xySeries.add(item);
             }
             xySeries.setNotify(true);
         }
     }
     
     /**
      * {@inheritDoc}
      */
     public void setValueY(int series, int index, double value) {
         if (index >= getItemCount()) {
             return;
         }
         if (getSeriesCount() < series) {
             setSeriesCount(series);
         }
         XYSeries xySeries = (XYSeries) getSeries(series);
         Double y = isNullY(value) ? null : new Double(value);

         if (xySeries.getItemCount() <= index) {
             while (xySeries.getItemCount() <= index) {
                 Number x = null;
                 if (xySeries.getItemCount() > 0) {
                     x = xySeries.getX(xySeries.getItemCount() - 1);
                 } else {
                     x = xySeries.getItemCount();
                 }
                 xySeries.add(x.doubleValue() + 1, y);
             }
         } else {
             xySeries.updateByIndex(index, y);
         }
     }

     /**
      * {@inheritDoc}
      */
     public void setValuesY(List<Double> values) {
         createSeriesIfNeeds();
         
         List<XYDataItem> points = new ArrayList<XYDataItem>(values.size());

         int x = 0;
         for (Double y : values) {
             XYSeries series = (XYSeries)getSeries(x / getItemCount());
             
             if (series == null) {
                 break;
             }
             
             int xx = x % getItemCount();
             Number oldX = null;
             if (xx < series.getItemCount()) {
                 oldX = series.getX(xx);
             } else if (series.getItemCount() > 0) {
                 oldX = series.getX(series.getItemCount() - 1);
             } else {
                 oldX = new Double(xx);
             }
             if (isNullY(y)) {
                 y = null;
             }
             points.add(new XYDataItem(oldX, y));
             x++;
         }
         doUpdatePoints(points);
     }

     /**
      * Updates points
      * @param points new series points
      */
     protected void updatePoints(List<XYDataItem> points) {
         int index = 0;
         for (XYDataItem item : points) {
            XYSeries series = (XYSeries)getSeries(index++ / getItemCount());
             if (series == null) {
                 break;
             }

             if (allowDuplicates()) {
                 series.add(item);
             } else {
                 series.addOrUpdate(item.getX(), item.getY());
             }
         }
     }
     
     /**
      * Updates points
      * @param points points list
      */
     private void doUpdatePoints(List<XYDataItem> points) {
         for (int series = 0; series < getSeriesCount(); series++) {
             getSeries(series).setNotify(false);
         }
         updatePoints(points);
         for (int series = 0; series < getSeriesCount(); series++) {
             getSeries(series).setNotify(true);
         }
     }
     
     /**
      * {@inheritDoc}
      */
     public void setValuesX(List<Double> values) {
        createSeriesIfNeeds();
        
        List<XYDataItem> points = new ArrayList<XYDataItem>(values.size());
        
        int y = 0;
        for (Double x : values) {
            XYSeries series = (XYSeries)getSeries(y / getItemCount());
            
            if (series == null) {
                break;
            }
            
            int yy = y % getItemCount();
            Number oldY = null;
            if (yy < series.getItemCount()) {
                oldY = series.getY(yy);
            } else {
                oldY = 0.0;
            }
            points.add(new XYDataItem(x, oldY));
            y++;
        }
        
        doUpdatePoints(points);
    }
     
     /**
      * {@inheritDoc}
      */
    protected void createSeriesIfNeeds() {
        if (getSeriesCount() == 0) {
            addSeries(new XYSeries("Subset 1", false, allowDuplicates()));
        }
    }
    
    /**
     * {@inheritDoc}
     */
    public void updateChart() {
        super.updateChart();
        updateNullValues();
    }
    
    /**
     * Updates null values
     */
    private void updateNullValues() {
        for (int series = 0; series < getSeriesCount(); series++) {
            XYSeries xySeries = (XYSeries) getSeries(series);
            
            List<Number> itemsToRemove = new LinkedList<Number>();
            for (Object obj : xySeries.getItems()) {
                XYDataItem item = (XYDataItem) obj;
                if (isNullX(item.getXValue()) || item.getY() == null || isNullY(item.getYValue())) {
                    if (!isNullX(item.getXValue()) && isNullDataGaps()) {
                        item.setY(null);
                    } else {
                        itemsToRemove.add(item.getX());
                    }
                }
            }
            
            if (itemsToRemove.size() > 0) {
                xySeries.setNotify(false);
                for (Number item : itemsToRemove) {
                    xySeries.remove(item);
                }
                xySeries.setNotify(true);
            }
        }
    }
    
    /**
     * Sets start time
     * @param time start time
     */
    public void setStartTime(double time) {
        startTime = time;
        doUpdateTime();
    }

    /**
     * Gets start time
     * @return startTime value
     */
    public double getStartTime() {
        return startTime;
    }

    /**
     * Sets delta X
     * @param delta delta X value
     */
    public void setDeltaX(int delta) {
        deltaX = delta;
        doUpdateTime();
    }

    /**
     * Gets delta X
     * @return deltaX value
     */
    public int getDeltaX() {
        return deltaX;
    }

    /**
     * Sets deltas per day
     * @param delta deltas per day value
     */
    public void setDeltasPerDay(int delta) {
        deltasPerDay = delta;
        doUpdateTime();
    }

    /**
     * Gets deltas per day
     * @return deltasPerDay value
     */
    public int getDeltasPerDay() {
        return deltasPerDay;
    }
    
    /**
     * Updates time according to set start time, delta X and delta per day values
     */
    private void doUpdateTime() {
        double delta = 0;
        switch (deltaX) {
        case -1: // 1 day
            delta = 24 * 60;
            break;
        case -2: // 1 week
            delta = 7 * 24 * 60;
            break;
        case -3: // month
            delta = 30 * 24 * 60;
            break;
        default:
            if (deltaX < 0 || deltasPerDay <= 0) {
                return;
            }
            delta = 24 * 60 / deltasPerDay;
        }
            
        // convert unix time
        delta *= 60;
        delta /= 86400.0;
        
        // update X values
        for (int series = 0; series < getSeriesCount(); series++) {
            XYSeries xySeries = (XYSeries) getSeries(series);
            
            List<XYDataItem> points = new ArrayList<XYDataItem>(xySeries.getItemCount());
            double start = startTime;
            for (Object obj : xySeries.getItems()) {
                XYDataItem item = (XYDataItem) obj;
                points.add(new XYDataItem(start, item.getYValue()));
                start += delta;
            }
            
            xySeries.setNotify(false);
            xySeries.clear();
            for (XYDataItem item : points) {
                xySeries.add(item, false);
            }
            xySeries.setNotify(true);
        }
    }
}
