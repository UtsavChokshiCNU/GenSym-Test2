package gensym.charts;

import java.awt.Graphics2D;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Rectangle2D;

import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.entity.EntityCollection;
import org.jfree.chart.plot.CrosshairState;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.PlotRenderingInfo;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.XYBubbleRenderer;
import org.jfree.chart.renderer.xy.XYItemRendererState;
import org.jfree.data.Range;
import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYZDataset;
import org.jfree.ui.RectangleEdge;

import gensym.charts.properties.bubble.BubbleSizeProperty;

/**
 * BubbleRenderer for GraphChart @see XYBubbleRenderer
 */
public class GraphBubbleRenderer extends XYBubbleRenderer {

    /**
     * RendererState for GraphBubbleRenderer class
     */
    static class XYZBubbleRendererState extends XYItemRendererState {

        /** Range of the z data */
        private final Range zRange;

        /**
         * Constructor
         * @param info plot rendering info
         * @param zRange range of the z data
         */
        public XYZBubbleRendererState(PlotRenderingInfo info, Range zRange) {
            super(info);
            this.zRange = zRange;
        }

        /**
         * Gets z range
         * @return range of the z data
         */
        public Range getZRange() {
            return zRange;
        }
    }

    /** Small comparative size */
    public static final int DIV_SMALL = 7;

    /** Medium comparative size */
    public static final int DIV_MEDIUM = 5;

    /** Large comparative size */
    public static final int DIV_LARGE = 3;

    /** Comparative size */
    private int div = DIV_MEDIUM;

    /**
     * Constructs a new renderer with the specified type of scaling.
     *
     * @param scaleType  the type of scaling (must be one of:
     *        {@link #SCALE_ON_BOTH_AXES}, {@link #SCALE_ON_DOMAIN_AXIS},
     *        {@link #SCALE_ON_RANGE_AXIS}).
     */
    public GraphBubbleRenderer(int scaleType) {
        super(scaleType);
    }

    /**
     * Sets bubble comparative size
     * @param size new size
     */
    public void setBubbleSize(int size) {
        switch(size) {
            case BubbleSizeProperty.SMALL:
                div = DIV_SMALL;
                break;

            case BubbleSizeProperty.MEDIUM:
                div = DIV_MEDIUM;
                break;

            case BubbleSizeProperty.LARGE:
                div = DIV_LARGE;
                break;
        }
    }

    /**
     * Gets bubble comparative size
     * @return comparative size
     */
    public int getBubbleSize() {
        return div;
    }

    /**
     * Gets range of the z data of the dataset
     * @param dataset XYDataset dataset
     * @return range of the z data
     */
    private static final Range getZRange(XYDataset dataset) {
        Range range = null;
        if (dataset instanceof XYZDataset) {
            XYZDataset xyzDataset = (XYZDataset) dataset;

            for (int series = 0; series < dataset.getSeriesCount(); series++) {
                int itemCount = dataset.getItemCount(series);
                for (int item = 0; item < itemCount; item++) {
                    double z = xyzDataset.getZValue(series, item);
                    range = Range.expandToInclude(range, z);
                }
            }
        }
        return range;
    }


    /**
     * {@inheritDoc}
     */
    public XYItemRendererState initialise(Graphics2D g2,
                                          Rectangle2D dataArea,
                                          XYPlot plot,
                                          XYDataset data,
                                          PlotRenderingInfo info) {

        return new XYZBubbleRendererState(info, getZRange(data));
    }

    /**
     * Gets z value (bubble radius).
     * @param state  the renderer state.
     * @param rangeAxis  the range (vertical) axis.
     * @param dataset  the dataset (an {@link XYZDataset} is expected).
     * @param series  the series index (zero-based).
     * @param item  the item index (zero-based).
     * @return z value
     */
    private double getZ(XYItemRendererState state, 
            ValueAxis rangeAxis, XYDataset dataset, int series, int item) {        
        double z = Double.NaN;
        if (dataset instanceof XYZDataset && state instanceof XYZBubbleRendererState) {
            XYZBubbleRendererState xyzState = (XYZBubbleRendererState) state;
            if (xyzState.getZRange() != null) {
                double factor = 0.5;
                XYZDataset xyzDataset = (XYZDataset) dataset;
                if (xyzState.getZRange().getLength() > 0) {
                    double delta = xyzDataset.getZValue(series, item)
                            - xyzState.getZRange().getLowerBound();
                    factor = delta / xyzState.getZRange().getLength();

                    if (factor - 0.1D < 1) {
                        factor += 0.1D;
                    }
                }
                if (xyzDataset.getZValue(series, item) != 0) {
                    z = factor * rangeAxis.getRange().getLength() / getBubbleSize();
                }
            }
        }
        return z;
    }

    /**
     * {@inheritDoc}
     */
    public void drawItem(Graphics2D g2, XYItemRendererState state,
            Rectangle2D dataArea, PlotRenderingInfo info, XYPlot plot,
            ValueAxis domainAxis, ValueAxis rangeAxis, XYDataset dataset,
            int series, int item, CrosshairState crosshairState, int pass) {

        // return straight away if the item is not visible
        if (!getItemVisible(series, item)) {
            return;
        }

        PlotOrientation orientation = plot.getOrientation();

        // get the data point...
        double x = dataset.getXValue(series, item);
        double y = dataset.getYValue(series, item);
        double z = getZ(state, rangeAxis, dataset, series, item);
        if (!Double.isNaN(z)) {
            RectangleEdge domainAxisLocation = plot.getDomainAxisEdge();
            RectangleEdge rangeAxisLocation = plot.getRangeAxisEdge();
            double transX = domainAxis.valueToJava2D(x, dataArea,
                    domainAxisLocation);
            double transY = rangeAxis.valueToJava2D(y, dataArea,
                    rangeAxisLocation);

            double transDomain = 0.0;
            double transRange = 0.0;
            double zero;

            switch (getScaleType()) {
                case SCALE_ON_DOMAIN_AXIS:
                    zero = domainAxis.valueToJava2D(0.0, dataArea,
                            domainAxisLocation);
                    transDomain = domainAxis.valueToJava2D(z, dataArea,
                            domainAxisLocation) - zero;
                    transRange = transDomain;
                    break;
                case SCALE_ON_RANGE_AXIS:
                    zero = rangeAxis.valueToJava2D(0.0, dataArea,
                            rangeAxisLocation);
                    transRange = zero - rangeAxis.valueToJava2D(z, dataArea,
                            rangeAxisLocation);
                    transDomain = transRange;
                    break;
                default:
                    double zero1 = domainAxis.valueToJava2D(0.0, dataArea,
                            domainAxisLocation);
                    double zero2 = rangeAxis.valueToJava2D(0.0, dataArea,
                            rangeAxisLocation);
                    transDomain = domainAxis.valueToJava2D(z, dataArea,
                            domainAxisLocation) - zero1;
                    transRange = zero2 - rangeAxis.valueToJava2D(z, dataArea,
                            rangeAxisLocation);
            }
            transDomain = Math.abs(transDomain);
            transRange = Math.abs(transRange);
            Ellipse2D circle = null;
            if (orientation == PlotOrientation.VERTICAL) {
                circle = new Ellipse2D.Double(transX - transDomain / 2.0,
                        transY - transRange / 2.0, transDomain, transRange);
            } else if (orientation == PlotOrientation.HORIZONTAL) {
                circle = new Ellipse2D.Double(transY - transRange / 2.0,
                        transX - transDomain / 2.0, transRange, transDomain);
            }
            g2.setPaint(getItemPaint(series, item));
            g2.fill(circle);
            g2.setStroke(getItemOutlineStroke(series, item));
            g2.setPaint(getItemOutlinePaint(series, item));
            g2.draw(circle);

            if (isItemLabelVisible(series, item)) {
                if (orientation == PlotOrientation.VERTICAL) {
                    drawItemLabel(g2, orientation, dataset, series, item,
                            transX, transY, false);
                } else if (orientation == PlotOrientation.HORIZONTAL) {
                    drawItemLabel(g2, orientation, dataset, series, item,
                            transY, transX, false);
                }
            }

            // add an entity if this info is being collected
            EntityCollection entities = null;
            if (info != null) {
                entities = info.getOwner().getEntityCollection();
                if (entities != null && circle.intersects(dataArea)) {
                    addEntity(entities, circle, dataset, series, item,
                            circle.getCenterX(), circle.getCenterY());
                }
            }

            int domainAxisIndex = plot.getDomainAxisIndex(domainAxis);
            int rangeAxisIndex = plot.getRangeAxisIndex(rangeAxis);
            updateCrosshairValues(crosshairState, x, y, domainAxisIndex,
                    rangeAxisIndex, transX, transY, orientation);
        }
    }
}
