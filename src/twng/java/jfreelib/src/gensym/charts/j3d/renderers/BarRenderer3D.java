package gensym.charts.j3d.renderers;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Paint;
import java.awt.Shape;
import java.awt.Stroke;
import java.awt.geom.Rectangle2D;

import org.jfree.chart.LegendItem;
import org.jfree.data.Range;

import gensym.charts.j3d.Dataset3D;
import gensym.charts.j3d.EntityData3D;
import gensym.charts.j3d.Object3D;
import gensym.charts.j3d.Point3D;
import gensym.charts.j3d.primitives.*;

/**
 * Renderer for bars
 */
public class BarRenderer3D extends Renderer3D {

    /** Base Z value factor */
    public static final double BASE_Z_VALUE_FACTOR = 0.1;

    /** Legend bar shape */
    public static final Shape LEGEND_BAR = new Rectangle2D.Double(-3.0, -5.0, 6.0, 10.0);
    
    /** Legend stroke */
    public static final Stroke LEGEND_STROKE = new BasicStroke(1.0f);;

    /** Plotting method value: display just bar wire frame */
    public static final int BAR_WIRE_FRAME = 0;

    /** Plotting method value: display bar surface without shades */
    public static final int BAR_SURFACE = 1;

    /** Plotting method value: display bar surface with shades */
    public static final int BAR_SURFACE_AND_SHADING = 2;

    /** Plotting method value: display only bar main pixels */
    public static final int BAR_SURFACE_AS_PIXELS = 3;

    /** Bar width and height */
    public static double BAR_WIDTH_HEIGHT = 0.35;

    /** Legend supporting flag */
    protected boolean isLegendSupported = false;

    /**
     * Constructor
     * @param w width of the bar
     * @param h height of the bar
     */
    public BarRenderer3D() {
        super();
    }

    /**
     * Copy constructor
     */
    public BarRenderer3D(Renderer3D renderer) {
        super(renderer);
    }

    /**
     * Tests whether legend is supported
     * @return true if legend is supported
     */
    public boolean isLegendSupported() {
        return isLegendSupported;
    }

    /**
     * Sets legend supporting flag
     * @param supported the new legend supporting flag
     */
    public void setLegendSupported(boolean supported) {
        isLegendSupported = supported;
    }

    /**
     * {@inheritDoc}
     */
    public Object3D createObject3D(Dataset3D dataset, int plottingMethod, int plottingDetails) {
        Object3D obj = new Object3D();
        double baseZ = getBaseZValue(dataset);
        for (int series = 0; series < dataset.getSeriesCount(); series++) {
            for (int item = 0; item < dataset.getSeries3D(series).getItemCount(); item++) {
                doPrimitivesFromPoint(obj, dataset.getSeries3D(series).getPoint3D(item),
                        series, item, plottingMethod, plottingDetails, baseZ);
            }
        }
        return obj;
    }

    /**
     * Calculates data range
     * @param dataset the dataset
     * @return bar data range
     */
    protected Range getBarRange(Dataset3D dataset) {
        double minValue = Double.POSITIVE_INFINITY;
        double maxValue = Double.NEGATIVE_INFINITY;

        for (int series = 0; series < dataset.getSeriesCount(); series++) {
            for (int item = 0; item < dataset.getItemCount(series); item++) {
                double z = dataset.getZValue(series, item);
                minValue = Math.min(minValue, z);
                maxValue = Math.max(maxValue, z);
            }
        }
        if (minValue == Double.POSITIVE_INFINITY || maxValue == Double.NEGATIVE_INFINITY) {
            return new Range(0, 0);
        }
        return new Range(minValue, maxValue);
    }

    /**
     * Calculates base Z value for 3D bar
     * @param dataset the dataset
     * @return base z value for 3D bar
     */
    public double getBaseZValue(Dataset3D dataset) {
        Range range = getBarRange(dataset);
        if (range.getLength() < 0.00001) {
            return range.getLowerBound() - BASE_Z_VALUE_FACTOR;
        }

        return range.getLowerBound() - range.getLength() * BASE_Z_VALUE_FACTOR;
    }

    /**
     * Builds bar from one point
     * @param obj container of triangles
     * @param point for building
     */
    private void doPrimitivesFromPoint(Object3D obj, Point3D point, int series, int item,
            int plottingMethod, int plottingDetails, double baseZ) {
        
        double x = item;
        double y = series;
        double z = point.getZ();

        Point3D A = new Point3D(x - BAR_WIDTH_HEIGHT, y + BAR_WIDTH_HEIGHT, baseZ);
        Point3D B = new Point3D(x + BAR_WIDTH_HEIGHT, y + BAR_WIDTH_HEIGHT, baseZ);
        Point3D C = new Point3D(x + BAR_WIDTH_HEIGHT, y - BAR_WIDTH_HEIGHT, baseZ);
        Point3D D = new Point3D(x - BAR_WIDTH_HEIGHT, y - BAR_WIDTH_HEIGHT, baseZ);

        Point3D A1 = new Point3D(x - BAR_WIDTH_HEIGHT, y + BAR_WIDTH_HEIGHT, z);
        Point3D B1 = new Point3D(x + BAR_WIDTH_HEIGHT, y + BAR_WIDTH_HEIGHT, z);
        Point3D C1 = new Point3D(x + BAR_WIDTH_HEIGHT, y - BAR_WIDTH_HEIGHT, z);
        Point3D D1 = new Point3D(x - BAR_WIDTH_HEIGHT, y - BAR_WIDTH_HEIGHT, z);

        if (plottingDetails == DETAILS_WIREFRAME && plottingMethod != BAR_SURFACE_AS_PIXELS) {
            plottingMethod = BAR_WIRE_FRAME;
        }

        Paint paint = getPaint(plottingMethod, series);
        Paint outlinePaint = getOutlinePaint(plottingMethod, series);

        EntityData3D entityData = new EntityData3D(point, series, item);

        if (plottingMethod == BAR_SURFACE_AS_PIXELS) {
            Shape shape = LineAndShapeRenderer3D.DEFAULT_SHAPE;

            obj.addPrimitive(createPointPrimitive(A, shape, paint, outlinePaint, entityData));
            obj.addPrimitive(createPointPrimitive(B, shape, paint, outlinePaint, entityData));
            obj.addPrimitive(createPointPrimitive(C, shape, paint, outlinePaint, entityData));
            obj.addPrimitive(createPointPrimitive(D, shape, paint, outlinePaint, entityData));
            
            obj.addPrimitive(createPointPrimitive(A1, shape, paint, outlinePaint, entityData));
            obj.addPrimitive(createPointPrimitive(B1, shape, paint, outlinePaint, entityData));
            obj.addPrimitive(createPointPrimitive(C1, shape, paint, outlinePaint, entityData));
            obj.addPrimitive(createPointPrimitive(D1, shape, paint, outlinePaint, entityData));
            
        } else {
            boolean shades = (plottingMethod == BAR_SURFACE_AND_SHADING);

            obj.addPrimitive(createPrimitive(A, B, C, D, paint, outlinePaint, entityData, shades));
            obj.addPrimitive(createPrimitive(B1, C1, D1, A1, paint, outlinePaint, entityData, shades));

            obj.addPrimitive(createPrimitive(B1, A1, A, B, paint, outlinePaint, entityData, shades));
            obj.addPrimitive(createPrimitive(D1, C1, C, D, paint, outlinePaint, entityData, shades));

            obj.addPrimitive(createPrimitive(C, C1, B1, B, paint, outlinePaint, entityData, shades));
            obj.addPrimitive(createPrimitive(A1, D1, D, A, paint, outlinePaint, entityData, shades));
        }
    }
    
    /**
     * Get Paint by plotting method
     * @param plottingMethod plotting method
     * @param series series number
     * @return Paint
     */
    private Paint getPaint(int plottingMethod, int series) {
        return BAR_WIRE_FRAME == plottingMethod ? null : getSeriesPaint(series);
    }

    /**
     * Get outline Paint by plotting method
     * @param plottingMethod plotting method
     * @param series series number
     * @return Paint
     */
    private Paint getOutlinePaint(int plottingMethod, int series) {
        return BAR_WIRE_FRAME == plottingMethod ||
                BAR_SURFACE == plottingMethod ? getSeriesOutlinePaint(series) : null;
    }

    /**
     * Creates ABCD rectangle primitive
     * @param a the A point
     * @param b the B point
     * @param c the C point
     * @param d the D point
     * @param paint the paint
     * @param outlinePaint the outline paint
     * @param entityData the entity data
     * @param shades are shades visible?
     * @return created primitive
     */
    private Rectangle3DPrimitive createPrimitive(Point3D a, Point3D b,
            Point3D c, Point3D d, Paint paint, Paint outlinePaint,
            EntityData3D entityData, boolean shades) {
        Rectangle3DPrimitive rect = new Rectangle3DPrimitive(d, c, b, a);
        rect.setPaint(paint);
        rect.setOutlinePaint(outlinePaint);
        rect.setEntityData(entityData);
        rect.setShadesVisible(shades);
        return rect;
    }

    /**
     * Creates point primitive
     * @param point the point
     * @param shape the shape
     * @param paint the paint
     * @param outlinePaint the outline paint 
     * @param entityData the entity data
     * @return the created point primitive
     */
    private Point3DPrimitive createPointPrimitive(Point3D point, Shape shape,
            Paint paint, Paint outlinePaint, EntityData3D entityData) {
        Point3DPrimitive primitive = new Point3DPrimitive(point, shape);
        primitive.setPaint(paint);
        primitive.setOutlinePaint(outlinePaint);
        primitive.setEntityData(entityData);
        return primitive;
    }

    /**
     * {@inheritDoc}
     */
    public void setSeriesPaint(int series, Paint paint) {
        if (paint instanceof Color) {
            Color color = (Color) paint;
            // make color transparent (alpha == 0x7F)
            paint = new Color(color.getRed(), color.getGreen(), color.getBlue(), 0x7F);
        }
        super.setSeriesPaint(series, paint);
    }

    /**
     * {@inheritDoc}
     */
    public LegendItem getLegendItem(String label, int series) {
        if (!isLegendSupported() || getSeriesPaint(series) == null) {
            return null;
        }
        Paint paint = getSeriesPaint(series);
        if (paint instanceof Color) {
            Color color = (Color) paint;
            paint = new Color(color.getRed(), color.getGreen(), color.getBlue());
        }
        
        Paint outlinePaint = getSeriesOutlinePaint(series);
        
        if (outlinePaint != null) {
            return new LegendItem(label, label, "", "", LEGEND_BAR, paint, LEGEND_STROKE, outlinePaint);
        }
        return new LegendItem(label, label, "", "", LEGEND_BAR, paint);
    }
}
