package gensym.charts;

import gensym.charts.j3d.*;
import gensym.charts.j3d.renderers.BarRenderer3D;
import gensym.charts.j3d.renderers.Renderer3D;
import gensym.charts.scrolling.*;
import java.awt.Color;
import java.awt.Cursor;
import java.awt.Paint;
import java.awt.event.MouseAdapter;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import org.jfree.chart.ChartMouseEvent;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.*;

public class Chart3D extends AbstractChart implements IDataHotSpots {

    /** X data of dataset */
    private List<Double> valuesX = new LinkedList<Double>();
    
    /** Y data of dataset */
    private List<Double> valuesY = new LinkedList<Double>();
    
    /** Z data of dataset */
    private List<Double> valuesZ = new LinkedList<Double>();
    
    /** Plot of the chart */
    private Plot3D plot = null;
    
    /** Dataset of the chart */
    private Dataset3D dataset = null;
    
    /** Horizontal scroll interface */
    private ChartScrolling horizontalInterface = null;
    
    /** Vertical scroll interface */
    private ChartScrolling verticalInterface = null;
    
    /** Auto rotation element*/
    private AutoRotation3D rotation = null;
    
    /** Data hot spot allowing property */
    private boolean allowDataHotSpots = false;

    /** Is need to start/stop auto rotation*/
    private boolean startAutoRotation = false;
    
    /**
     * Constructor
     * @param title
     */
    public Chart3D(String title) {
        super(new JFreeChart(new Plot3D(new Dataset3D(), new Axis3D(), new Axis3D(), new Axis3D())));
        getChart().setTitle(title);

        plot = (Plot3D) getChart().getPlot();
        dataset = plot.getDataset();

        // Initialize by default values
        getPlot().getXAxis().setLabel("X Axis");
        getPlot().getYAxis().setLabel("Z Axis");
        getPlot().getZAxis().setLabel("Y Axis");

        // Initialize scrolling interfaces
        horizontalInterface = new HorizontalScrolling3D(getPlot());
        verticalInterface = new VerticalScrolling3D(getPlot());

        getPlot().rotateAroundY(Math.PI);

        rotation = new AutoRotation3D(horizontalInterface, plot);
    }

    /**
     * Sets auto rotation required
     * @param startAutoRotation true, if need to start
     */
    public void setAutoRotation(boolean startAutoRotation) {
        this.startAutoRotation = startAutoRotation;
    }

    /**
     * Gets is auto rotation started
     * @return true, if started
     */
    public boolean isAutoRotationDone() {
        return startAutoRotation == false;
    }

    /**
     * Gets auto rocation of the chart
     * @return AutoRotation3D class instance
     */
    public AutoRotation3D getAutoRotation() {
        return rotation;
    }

    /**
     * Gets chart plot
     * @return Plot3D
     */
    public final Plot3D getPlot() {
        return plot;
    }

    /**
     * {@inheritDoc}
     */
    public void setValuesX(List<Double> values) {
        valuesX = values;
    }

    /**
     * {@inheritDoc}
     */
    public void setValuesY(List<Double> values) {
        valuesZ = values;
    }

    /**
     * {@inheritDoc}
     */
    public void setValuesZ(List<Double> values) {
        valuesY = values;
    }

    /**
     * {@inheritDoc}
     */
    public void setSeriesCount(int count) {
        if (dataset.getSeriesCount() == 0) {
            for (int i = 0; i < count; i++) {
                dataset.addSeries(new Series3D("Series" + i));
            }
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
    protected Axis[] getAxesList() {
        return new Axis[]{getPlot().getXAxis(), getPlot().getYAxis(), getPlot().getZAxis()};
    }

    /**
     * {@inheritDoc}
     */
    public void showGridLines(boolean showXAxis, boolean showYAxis) {
        if (plot.getXAxis() != null) {
            plot.getXAxis().setGridLineVisible(showXAxis);
        }
        if (plot.getYAxis() != null) {
            plot.getYAxis().setGridLineVisible(showYAxis);
        }
    }

    /**
     * Updates data set if XYZ data are ready for use
     */
    private void updateDataset() {
        for (int series = 0; series < dataset.getSeriesCount(); series++) {
            Series3D series3D = dataset.getSeries3D(series);
            series3D.clear();
            
            for (int item = 0; item < getItemCount(); item++) {
                int position = series * getItemCount() + item;
                double x = position < valuesX.size() ? valuesX.get(position) : 0;
                double y = position < valuesY.size() ? valuesY.get(position) : 0;
                double z = position < valuesZ.size() ? valuesZ.get(position) : 0;
                series3D.addPoint3D(new Point3D(x, y, z));
            }
        }
    }

    /**
     * {@inheritDoc}
     */
    public ChartScrolling getVerticalScrollingInterface() {
        return verticalInterface;
    }

    /**
     * {@inheritDoc}
     */
    public ChartScrolling getHorizontalScrollingInterface() {
        return horizontalInterface;
    }

    /**
     * {@inheritDoc}
     */
    public void chartMouseClicked(JFreeChartHolder holder, ChartMouseEvent paramChartMouseEvent) {
        if (isDataHotSpotsAllowed() && paramChartMouseEvent.getEntity() instanceof XYZItemEntity) {
            XYZItemEntity entity = (XYZItemEntity) paramChartMouseEvent.getEntity();
            Point3D item = entity.getItem();
            ChartServer.sendChartEvent("clicked", holder.getHandle(),
                    "x", item.getX(), "y", item.getZ(), "z", item.getY(), 
                    "subset", entity.getSeries(), "point", entity.getPoint());
        }
        if (paramChartMouseEvent.getTrigger().getClickCount() > 1) {
            rotation.doAutoRotation3D(!rotation.isRunning());
        }
        super.chartMouseClicked(holder, paramChartMouseEvent);
    }

    /**
     * {@inheritDoc}
     */
    public void chartMouseMoved(JFreeChartHolder holder, ChartMouseEvent paramChartMouseEvent) {
        int cursorType = holder.getCursor().getType();
        int newCursotType = cursorType;

        if (isDataHotSpotsAllowed() && paramChartMouseEvent.getEntity() instanceof XYZItemEntity) {
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
    public void updateChart() {
        super.updateChart();

        if (startAutoRotation) {
            if (getAutoRotation().isRunning()) {
                getAutoRotation().doAutoRotation3D(false);
            }
            getAutoRotation().doAutoRotation3D(true);
            startAutoRotation = false;
        }

        updateDataset();
        getPlot().datasetChanged(null);
    }

    /**
     * {@inheritDoc}
     */
    protected void updatePaints(Map<Integer, Paint> paints) {
        Renderer3D renderer = getPlot().getRenderer();
        for (Integer series : paints.keySet()) {
            Paint paint = paints.get(series);
            renderer.setSeriesPaint(series, paint);
            renderer.setSeriesOutlinePaint(series, Color.BLACK);
        }
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
        return true;
    }

    /**
     * {@inheritDoc}
     */
    public void setAllowSeriesHotSpots(boolean allow) {
    }

    /**
     * {@inheritDoc}
     */
    public boolean isPointHotSpotsAllowed() {
        return true;
    }

    /**
     * {@inheritDoc}
     */
    public void setAllowPointHotSpots(boolean allow) {
    }

    /**
     * {@inheritDoc}
     */
    public MouseAdapter getMouseAdapter() {
        return new ScrollMouseAdapter3D(this);
    }

    /**
     * {@inheritDoc}
     */
    public void setPointLabel(int point, String label) {
        if (getPlot().getXAxis() != null) {
            getPlot().getXAxis().getLabelFormat().setLabel(point, label);
        }
    }

    /**
     * {@inheritDoc}
     */
    public void setSeriesLabel(int series, String label) {
        if (series < dataset.getSeriesCount()) {
            dataset.getSeries3D(series).setKey(label);
        }

        if (plot.getRenderer() instanceof BarRenderer3D && getPlot().getYAxis() != null) {
            getPlot().getYAxis().getLabelFormat().setLabel(series, label);
        }
    }
}
