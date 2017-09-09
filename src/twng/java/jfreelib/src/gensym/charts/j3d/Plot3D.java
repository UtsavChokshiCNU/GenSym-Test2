package gensym.charts.j3d;

import java.awt.*;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;

import org.jfree.chart.LegendItem;
import org.jfree.chart.LegendItemCollection;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.Plot;
import org.jfree.chart.plot.PlotRenderingInfo;
import org.jfree.chart.plot.PlotState;
import org.jfree.chart.plot.ValueAxisPlot;
import org.jfree.data.Range;
import org.jfree.data.general.DatasetChangeEvent;
import org.jfree.ui.RectangleInsets;

import gensym.charts.axis.StringNumberFormat;
import gensym.charts.axis.StringNumberFormat.DataSource;
import gensym.charts.j3d.primitives.*;
import gensym.charts.j3d.renderers.*;

/**
 * Simple plot 3D class
 */
public class Plot3D extends Plot implements ValueAxisPlot {
    
    /** Generated serial version UID */
    private static final long serialVersionUID = 2557158082193805005L;
    
    /** The DataSet instance */
    private Dataset3D dataset;
    
    /** The X Axis instance */
    private Axis3D xAxis;
    
    /** The Y Axis instance */
    private Axis3D yAxis;
    
    /** The Z Axis instance */
    private Axis3D zAxis;
    
    /** Data renderer*/
    private Renderer3D renderer = new LineAndShapeRenderer3D();
    
    /** 3D object */
    private Object3D object = null;
    
    /** View point */
    private ViewPoint viewPoint = new ViewPoint();
    
    /** Sun point */
    private Point3D sunPoint = new Point3D(-1 / Math.sqrt(3), -1 / Math.sqrt(3), 1 / Math.sqrt(3));

    /** Axis background paint */
    private Paint axisBackgroundPaint = Color.GRAY;

    /** Response for chart contour visibility */
    private boolean isContourVisible = false;

    /** Plotting method of the chart*/
    private int plottingMethod = 2;

    /** Plotting details of the chart*/
    private int plottingDetails = Renderer3D.DETAILS_FULL;

    /** Rotation detail value of the chart*/
    private int rotationDetail = Renderer3D.DETAILS_WIREFRAME;


    /**
     * Constructor with the specified dataset, x axis, y axis and z axis.  
     * 
     * @param dataset Dataset3D object (<code>null</code> not permitted).
     * @param xAxis the Axis3D object (<code>null</code> not permitted).
     * @param yAxis the Axis3D object (<code>null</code> not permitted).
     * @param zAxis the Axis3D object (<code>null</code> not permitted).
     */
    public Plot3D(Dataset3D dataset, Axis3D xAxis, Axis3D yAxis, Axis3D zAxis) {
        setDataset(dataset);
        setXAxis(xAxis);
        setYAxis(yAxis);
        setZAxis(zAxis);
    }

    /**
     * Sets new rotation detail
     * @param rotationDetail new rotation detail
     */
    public void setRotationDetail(int rotationDetail) {
        this.rotationDetail = rotationDetail;
    }

    /**
     * Gets rotation detail
     * @return rotation detail
     */
    public int getRotationDetail() {
        return this.rotationDetail;
    }
    
    /**
     * Sets plotting method
     * @param plottingMethod new plotting method
     */
    public void setPlottingMethod(int plottingMethod) {
        if (this.plottingMethod != plottingMethod) {
        this.plottingMethod = plottingMethod;
            datasetChanged(null);
        }
    }

    /**
     * Gets plotting method
     * @return plotting method of the 
     */
    public int getPlottingMethod() {
        return plottingMethod;
    }

    /**
     * Sets plotting details
     * @param plottingDetails new plotting details
     */
    public void setPlottingDetails(int plottingDetails) {
        if (this.plottingDetails != plottingDetails) {
            this.plottingDetails = plottingDetails;
            datasetChanged(null);
        }
    }

    /**
     * Gets plotting details
     * @return plotting details
     */
    public int getPlottingDetails() {
        return plottingDetails;
    }

    /**
     * Sets contour visibility
     * @param visibility of the contour
     */
    public void setContourVisible(boolean isContourVisible) {
        this.isContourVisible = isContourVisible;
    }

    /**
     * Gets contour visibility
     * @return visibility of axis contour
     */
    public boolean isContourVisible() {
        return isContourVisible;
    }

    /**
     * Do rotation around X axis.
     * @param phi new angle
     */
    public void rotateAroundX(double phi) {
        viewPoint.setPhi(phi);
        fireChangeEvent();
    }
    
    /**
     * Returns angle of rotation around X axis
     * @return the angle of rotation around X
     */
    public double getXAngle() {
       return viewPoint.getPhi();
    }

    /**
     * Do rotation around Y axis.
     * @param xi new angle
     */
    public void rotateAroundY(double xi) {
        viewPoint.setXi(xi);
        fireChangeEvent();
    }

    /**
     * Returns angle of rotation around Y axis
     * @return the angle of rotation around Y
     */
    public double getYAngle() {
       return viewPoint.getXi();
    }

    /**
     * Do rotation around Z axis.
     * @param rho new angle
     */
    public void rotateAroundZ(double rho) {
        viewPoint.setRho(rho);
        fireChangeEvent();
    }

    /**
     * Returns angle of rotation around Z axis
     * @return the angle of rotation around Z
     */
    public double getZAngle() {
       return viewPoint.getRho();
    }

    /** 
     * Checks object for nullable and throw exception if true
     * 
     * @param obj the object
     * @param str the object description
     */
    private void checkNullable(Object obj, String str) {
        if (obj == null) {
            throw new IllegalArgumentException("The '" + str + "' cannot be null.");
        }
    }

    /** 
     * Gets the saves instance of DataSet
     * 
     * @return the Dataset3D object or null.
     */
    public Dataset3D getDataset() {
        return dataset;
    }

    /**
     * Gets renderer
     * @return renderer instance
     */
    public Renderer3D getRenderer() {
        return renderer;
    }

    /**
     * Sets renderer
     * @param rend new renderer
     */
    public void setRenderer(Renderer3D rend) {
        renderer = rend;
    }

    /**
     * Sets DataSet and send change event (<code>null</code> permitted).
     * 
     * @param dataset the Dataset3D object
     */
    public final void setDataset(Dataset3D dataset) {
        if (this.dataset != null) {
            this.dataset.removeChangeListener(this);
        }
        this.dataset = dataset;
        if (this.dataset != null) {
            this.dataset.addChangeListener(this);
        }
        fireChangeEvent();
    }

    /**
     * Returns the saves instance of Y axis object
     *  
     * @return the Axis3D object
     */
    public Axis3D getXAxis() {
        return xAxis;
    }

    /**
     * Sets X axis and send change event (<code>null</code> not permitted).
     *  
     * @param axis the Axis3D object
     */
    public final void setXAxis(Axis3D axis) {
        checkNullable(axis, "X Axis");
        xAxis = axis;
        xAxis.setPlot(this);
        xAxis.getLabelFormat().setSource(createAxisFormat());
        fireChangeEvent();
    }

    /**
     * Creates format
     * @return created format
     */
    private DataSource createAxisFormat() {
        return new StringNumberFormat.DataSource() {
            public int indexOf(double value) {
                return -1;
            }
            public Double getValue(int index) {
                return (double) index + 1;
            }
        };
    }

    /**
     * Returns the saves instance of Y axis object
     *  
     * @return the Axis3D object
     */
    public Axis3D getYAxis() {
        return yAxis;
    }

    /**
     * Sets Y axis and send change event (<code>null</code> not permitted).
     *  
     * @param axis the Axis3D object
     */
    public final void setYAxis(Axis3D axis) {
        checkNullable(axis, "Y Axis");
        yAxis = axis;
        yAxis.setPlot(this);
        yAxis.getLabelFormat().setSource(createAxisFormat());
        fireChangeEvent();
    }

    /**
     * Returns the saves instance of Z Axis object
     *  
     * @return the Axis3D object
     */
    public Axis3D getZAxis() {
        return zAxis;
    }

    /**
     * Sets Z axis and send change event (<code>null</code> not permitted).
     *  
     * @param axis the Axis3D object
     */
    public final void setZAxis(Axis3D axis) {
        checkNullable(axis, "Z Axis");
        zAxis = axis;
        zAxis.setPlot(this);
        fireChangeEvent();
    }

    /**
     * Returns the zoom value
     *  
     * @return the double value
     */
    public double getZoom() {
        return viewPoint.getZoom();
    }

    /**
     * Returns screen moving
     * @return screen moving
     */
    public Point2D getScreenMoving() {
        return viewPoint.getScreenMoving();
    }

    /**
     * {@inheritDoc}
     */
    public void draw(Graphics2D g2, Rectangle2D area, Point2D anchor,
            PlotState parentState, PlotRenderingInfo info) {

        if (area.getWidth() <= MINIMUM_WIDTH_TO_DRAW || area.getHeight() <= MINIMUM_HEIGHT_TO_DRAW) {
            return;
        }

        if (info != null) {
            info.setPlotArea(area);
        }

        // adjust the drawing area for the plot insets
        RectangleInsets insets = getInsets();
        insets.trim(area);

        if (info != null) {
            info.setDataArea(area);
        }

        drawBackground(g2, area);
        
        if (object == null) {
            object = createObject();
        }
        
        // draw object
        centerImage();
        
        boolean isXVisible = getXAxis().isVisible();
        boolean isYVisible = getYAxis().isVisible();
        boolean isZVisible = getZAxis().isVisible();

        Shape clip = g2.getClip();
        g2.setClip(area);
        
        Range[] ranges = object.getBounds();
        double dx = ranges.length > 0 && ranges[0] != null ? ranges[0].getLength() : 0;
        double dy = ranges.length > 1 && ranges[1] != null ? ranges[1].getLength() : 0;
        double dz = ranges.length > 2 && ranges[2] != null ? ranges[2].getLength() : 0;
        
        viewPoint.fitIntoArea(dx, dy, dz, area);

        object.draw(g2, sunPoint, viewPoint, info);
        
        g2.setClip(clip);
        
        drawOutline(g2, area);

        getXAxis().setVisible(isXVisible);
        getYAxis().setVisible(isYVisible);
        getZAxis().setVisible(isZVisible);
    }

    /**
     * {@inheritDoc}
     */
    public String getPlotType() {
        return "Plot3D";
    }
    
    /**
     * Get data range of X axis
     *  
     * @return double
     */
    private Range getXRange() {
        double minValue = Double.POSITIVE_INFINITY;
        double maxValue = Double.NEGATIVE_INFINITY;

        if (dataset != null) {
            for (int series = 0; series < dataset.getSeriesCount(); series++) {
                for (int item = 0; item < dataset.getItemCount(series); item++) {
                    double curValue = dataset.getXValue(series, item);
                    minValue = Math.min(minValue, curValue);
                    maxValue = Math.max(maxValue, curValue);
                }
            }
        }
        return new Range(Math.min(minValue, maxValue), Math.max(minValue, maxValue));
    }
    
    /**
     * Get data range of Y axis
     *  
     * @return double
     */
    private Range getYRange() {
        double minValue = Double.POSITIVE_INFINITY;
        double maxValue = Double.NEGATIVE_INFINITY;

        if (dataset != null) {
            for (int series = 0; series < dataset.getSeriesCount(); series++) {
                for (int item = 0; item < dataset.getItemCount(series); item++) {
                    double curValue = dataset.getYValue(series, item);
                    minValue = Math.min(minValue, curValue);
                    maxValue = Math.max(maxValue, curValue);
                }
            }
        }
        return new Range(Math.min(minValue, maxValue), Math.max(minValue, maxValue));
    }
    
    /**
     * Get data range of Z axis
     *  
     * @return double
     */
    private Range getZRange() {
        double minValue = Double.POSITIVE_INFINITY;
        double maxValue = Double.NEGATIVE_INFINITY;

        if (dataset != null) {
            
            for (int series = 0; series < dataset.getSeriesCount(); series++) {
                for (int item = 0; item < dataset.getItemCount(series); item++) {
                    double curValue = dataset.getZValue(series, item);
                    minValue = Math.min(minValue, curValue);
                    maxValue = Math.max(maxValue, curValue);
                }
            }
        }
        return new Range(Math.min(minValue, maxValue), Math.max(minValue, maxValue));
    }
    
    /**
     * {@inheritDoc}
     */
    public Range getDataRange(ValueAxis axis) {
        checkNullable(axis, "axis");
        
        if (dataset != null) {
            if (getXAxis() == axis) {
                return getXRange();
            } else if (getYAxis() == axis) {
                return getYRange();
            } else if (getZAxis() == axis) {
                return getZRange();
            }
            throw new IllegalArgumentException("The 'axis' does not belong to this plot");
        }
        return null;
    }

    /**
     * {@inheritDoc}
     */
    public void datasetChanged(DatasetChangeEvent event) {
        object = null;
        updateAxes();
        super.datasetChanged(event);
    }
    
    /**
     * Updates axes
     */
    private void updateAxes() {
        updateAxis(getXAxis());
        updateAxis(getYAxis());
        updateAxis(getZAxis());
    }
    
    /**
     * Updates axis
     * @param axis the axis to be updated
     */
    private void updateAxis(Axis3D axis) {
        if (axis != null) {
            axis.configure();
        }
    }

    /**
     * Centers image
     */
    private void centerImage() {
        if (object == null) {
            return;
        }
        Range[] ranges = object.getBounds();
        if (ranges.length > 0 && ranges[0] != null) {
            viewPoint.moveToX(ranges[0].getCentralValue());
        }
        if (ranges.length > 1 && ranges[1] != null) {
            viewPoint.moveToY(ranges[1].getCentralValue());
        }
        if (ranges.length > 2 && ranges[2] != null) {
            viewPoint.moveToZ(ranges[2].getCentralValue());
        }
    }

    /**
     * {@inheritDoc}
     */
    public void zoom(double v) {
        zoom(v, false);
    }

    /**
     * Set plot zoom factor
     * @param v zoom value
     * @param accumulate zoom accumulation flag
     */
    public void zoom(double v, boolean accumulate) {
        if (accumulate) {
            if (v > 0 || viewPoint.getZoom() > -v) {
                viewPoint.setZoom(viewPoint.getZoom() + v);
            }
        } else {
            viewPoint.setZoom(v);
        }
        fireChangeEvent();
    }
    
    /**
     * Returns 3D object
     * @return the contained 3D object
     */
    public Object3D getObject3D() {
        return object;
    }

    /**
     * Moves screen
     * @param dx x moving length
     * @param dy y moving length
     * @param accumulate moving accumulation flag
     */
    public void moveScreen(double dx, double dy, boolean accumulate) {
        if (accumulate) {
            Point2D moving = viewPoint.getScreenMoving();
            viewPoint.moveScreen(moving.getX() + dx, moving.getY() + dy);
        } else {
            viewPoint.moveScreen(dx, dy);
        }

        fireChangeEvent();
    }

    /**
     * Creates 3D object
     * @return created 3D object
     */
    private Object3D createObject() {
        Object3D obj = renderer.createObject3D(
                getDataset(), getPlottingMethod(), getPlottingDetails());

        // add axis planes
        Range[] ranges = obj.getBounds();
        Range rx = ranges.length > 0 && ranges[0] != null ? ranges[0] : new Range(0, 1);
        Range ry = ranges.length > 1 && ranges[1] != null ? ranges[1] : new Range(0, 1);
        Range rz = ranges.length > 2 && ranges[2] != null ? ranges[2] : new Range(0, 1);

        double dx = rx.getLength() * 0.05;
        double dy = ry.getLength() * 0.05;
        double dz = rz.getLength() * 0.05;

        Point3D a = new Point3D(rx.getLowerBound() - dx, ry.getLowerBound() - dy, rz.getLowerBound() - dz);
        Point3D b = new Point3D(rx.getUpperBound() + dx, ry.getLowerBound() - dy, rz.getLowerBound() - dz);
        Point3D c = new Point3D(rx.getUpperBound() + dx, ry.getLowerBound() - dy, rz.getUpperBound() + dz);
        Point3D d = new Point3D(rx.getLowerBound() - dx, ry.getLowerBound() - dy, rz.getUpperBound() + dz);
        Point3D a1 = new Point3D(rx.getLowerBound() - dx, ry.getUpperBound() + dy, rz.getLowerBound() - dz);
        Point3D b1 = new Point3D(rx.getUpperBound() + dx, ry.getUpperBound() + dy, rz.getLowerBound() - dz);
        Point3D c1 = new Point3D(rx.getUpperBound() + dx, ry.getUpperBound() + dy, rz.getUpperBound() + dz);
        Point3D d1 = new Point3D(rx.getLowerBound() - dx, ry.getUpperBound() + dy, rz.getUpperBound() + dz);

        if (getPlottingDetails() == Renderer3D.DETAILS_FULL) {
            // 1st Z axis plain
            addAxisPlane(obj, a, b, c, d, new Point3D(0, -1, 0), getZAxis(), null);
            // 2nd Z axis plain
            addAxisPlane(obj, a1, a, d, d1, new Point3D(-1, 0, 0), getZAxis(), null);
            // 3rd Z axis plain
            addAxisPlane(obj, b1, a1, d1, c1, new Point3D(0, 1, 0), getZAxis(), null);
            // 4th Z axis plain
            addAxisPlane(obj, b1, b, c, c1, new Point3D(1, 0, 0), getZAxis(), null);

            // 1st XY axis plane
            addAxisPlane(obj, a, a1, b1, b, new Point3D(0, 0, -1), getXAxis(), getYAxis());
            // 2nd XY axis plane
           addAxisPlane(obj, d, d1, c1, c, new Point3D(0, 0, 1), getXAxis(), getYAxis());
       }

        if (isContourVisible()) {
            obj.addPrimitive(new Contour3DPrimitive(a, b, c, d, new Point3D(0, -1, 0)));
            obj.addPrimitive(new Contour3DPrimitive(a, a1, d1, d, new Point3D(-1, 0, 0)));
            obj.addPrimitive(new Contour3DPrimitive(a1, b1, c1, d1, new Point3D(0, 1, 0)));
            obj.addPrimitive(new Contour3DPrimitive(c, c1, b1, b, new Point3D(1, 0, 0)));
            obj.addPrimitive(new Contour3DPrimitive(a, a1, b1, b, new Point3D(0, 0, -1)));
            obj.addPrimitive(new Contour3DPrimitive(d, d1, c1, c, new Point3D(0, 0, 1)));
        }

       return obj;
    }

    /**
     * Adds axis plane.
     * @param obj the 3D object
     * @param a the A plane point
     * @param b the A plane point
     * @param c the B plane point
     * @param d the C plane point
     * @param normal axis plane normal
     * @param axis1 the horizontal axis
     * @param axis2 the vertical axis
     */
    private void addAxisPlane(Object3D obj, Point3D a, Point3D b, Point3D c, Point3D d, Point3D normal, Axis3D axis1, Axis3D axis2) {
        AxisPlane3DPrimitive plane = new AxisPlane3DPrimitive(a, b, c, d, normal);
        plane.setPaint(axisBackgroundPaint);
        plane.setOutlinePaint(Color.BLACK);
        plane.setHorizontalAxis(axis1);
        plane.setVerticalAxis(axis2);
        obj.addPrimitive(plane);
    }

    /**
     * {@inheritDoc}
     */
    public LegendItemCollection getLegendItems() {
        LegendItemCollection legends = new LegendItemCollection();
        for (int series = 0; series < dataset.getSeriesCount(); series++) {
            LegendItem item = renderer.getLegendItem(dataset.getSeriesKey(series).toString(), series);
            if (item != null) {
                item.setDataset(dataset);
                item.setDatasetIndex(0);
                item.setSeriesIndex(series);
                item.setSeriesKey(dataset.getSeriesKey(series));
                legends.add(item);
            }
        }
        return legends;
    }

    /**
     * Sets rotation mode
     */
    synchronized public void setRotationMode() {
        boolean changesDone = false;
        if (getPlottingDetails() != getRotationDetail()) {
            setPlottingDetails(getRotationDetail());
            changesDone = true;
        }

        if (!isContourVisible()) {
            setContourVisible(true);
            changesDone = true;
        }

        if (changesDone) {
            datasetChanged(null);
        }

    }

    /**
     * Leaves rotation mode
     */
    synchronized public void leaveRotationMode() {
        setPlottingDetails(Renderer3D.DETAILS_FULL);
        setContourVisible(false);
        datasetChanged(null);
    }
}
