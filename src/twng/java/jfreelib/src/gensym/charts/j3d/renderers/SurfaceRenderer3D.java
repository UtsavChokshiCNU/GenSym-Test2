package gensym.charts.j3d.renderers;

import java.awt.Paint;

import gensym.charts.j3d.*;
import gensym.charts.j3d.primitives.*;
import java.awt.Color;
import java.util.ArrayList;

import org.jfree.chart.LegendItem;
import org.jfree.data.Range;

/**
 * Renderer for surfaces
 */
public class SurfaceRenderer3D extends Renderer3D {

    /** Plotting method value: display just surface wire frame */
    public static final int SURFACE_WIRE_FRAME = 0;

    /** Plotting method value: display surface without shades */
    public static final int SURFACE = 1;

    /** Plotting method value: display surface with shades */
    public static final int SURFACE_AND_SHADING = 2;

    /** Plotting method value: display only surface pixels */
    public static final int SURFACE_AS_PIXELS = 3;

    /** Plotting method value: display only surface with colored contours */
    public static final int SURFACE_WITH_CONTOURS = 4;

    /** Delta z value (@see manual-contour-line) used with surface contours */
    private int deltaZ = 100;

    /**
     * Constructor
     */
    public SurfaceRenderer3D() {
    }

    /**
     * Copy constructor
     */
    public SurfaceRenderer3D(Renderer3D renderer) {
        super(renderer);
    }

    /**
     * Sets deltaZ value
     * @param deltaZ new deltaZ value
     */
    public void setDeltaZ(int deltaZ) {
        this.deltaZ = deltaZ;
    }

    /**
     * Gets deltaZ value
     * @return deltaZ value
     */
    public int getDeltaZ() {
        return deltaZ;
    }

    /**
     * {@inheritDoc}
     */
    public Object3D createObject3D(Dataset3D dataset, int plottingMethod, int plottingDetails) {
        Object3D obj = new Object3D();
        SurfaceHelper helper = new SurfaceHelper(dataset, getDeltaZ());

        if (plottingDetails == DETAILS_WIREFRAME && plottingMethod != SURFACE_AS_PIXELS) {
            plottingMethod = SURFACE_WIRE_FRAME;
        }

        Paint paint = getPaint(plottingMethod);
        Paint outlinePaint = getOutlinePaint(plottingMethod, paint);
        for (int series = 0; series < dataset.getSeriesCount() - 1; series++) {
            for (int item = 0; item < helper.getMinPointsPerSeries() - 1; item++) {

                Point3D p1 = dataset.getSeries3D(series).getPoint3D(item);
                Point3D p2 = dataset.getSeries3D(series).getPoint3D(item + 1);
                Point3D p3 = dataset.getSeries3D(series + 1).getPoint3D(item);
                Point3D p4 = dataset.getSeries3D(series + 1).getPoint3D(item + 1);

                EntityData3D entityData = new EntityData3D(p1, series, item);

                if (plottingMethod == SURFACE_AS_PIXELS) {
                    Point3DPrimitive point = new Point3DPrimitive(p1, LineAndShapeRenderer3D.DEFAULT_SHAPE);
                    point.setPaint(paint);
                    point.setOutlinePaint(outlinePaint);
                    point.setEntityData(entityData);
                    obj.addPrimitive(point);

                } else if (plottingMethod == SURFACE_AND_SHADING) {
                    Triangle3DPrimitive triangleOne = new Triangle3DPrimitive(new Triangle3D(p1, p2, p4));
                    triangleOne.setPaint(paint);
                    triangleOne.setOutlinePaint(outlinePaint);
                    triangleOne.setEntityData(entityData);
                    triangleOne.setShadesVisible(true);
                    obj.addPrimitive(triangleOne);

                    Triangle3DPrimitive triangleTwo = new Triangle3DPrimitive(new Triangle3D(p1, p4, p3));
                    triangleTwo.setPaint(paint);
                    triangleTwo.setOutlinePaint(outlinePaint);
                    triangleTwo.setEntityData(entityData);
                    triangleTwo.setShadesVisible(true);
                    obj.addPrimitive(triangleTwo);

                } else if (plottingMethod == SURFACE_WITH_CONTOURS) {
                    ArrayList<Double> planes = helper.getPlanes();
                    processOneTriangle(obj, new Triangle3DPrimitive(new Triangle3D(p1, p2, p4)), planes);
                    processOneTriangle(obj, new Triangle3DPrimitive(new Triangle3D(p1, p4, p3)), planes);
                    obj.addPrimitive(new SurfaceContour3DPrimitive(p1, p2, p4, p3));

                } else {
                    Rectangle3DPrimitive rect = new Rectangle3DPrimitive(p1, p2, p4, p3);
                    rect.setPaint(paint);
                    rect.setOutlinePaint(outlinePaint);
                    obj.addPrimitive(rect);
                }
            }
        }
        return obj;
    }

    /**
     * Divide triangle by planes and add it to obj
     * @param obj Object3D array
     * @param triangle triangle to divide
     * @param planes z-planes
     */
    public void processOneTriangle(Object3D obj, Triangle3DPrimitive triangle, ArrayList<Double> planes) {
        int planeNumber = getInterSection(triangle.getTriangle3D(), planes);
        if (planeNumber != -1) {
            Point3D A = triangle.getTriangle3D().getA();
            Point3D B = triangle.getTriangle3D().getB();
            Point3D C = triangle.getTriangle3D().getC();

            Point3D X = getInterSection(A, B, planes.get(planeNumber));
            Point3D Y = getInterSection(B, C, planes.get(planeNumber));
            Point3D Z = getInterSection(C, A, planes.get(planeNumber));

            Triangle3D tr1 = null;
            Triangle3D tr2 = null;
            Triangle3D tr3 = null;

            if (X == null) {
                tr1 = new Triangle3D(Z, Y, C);
                tr2 = new Triangle3D(A, Z, B);
                tr3 = new Triangle3D(Z, B, Y);
            } else if (Y == null) {
                tr1 = new Triangle3D(A, Z, X);
                tr2 = new Triangle3D(Z, X, C);
                tr3 = new Triangle3D(C, X, B);

            } else if (Z == null) {
                tr1 = new Triangle3D(X, Y, B);
                tr2 = new Triangle3D(C, Y, X);
                tr3 = new Triangle3D(A, C, X);
            }

            if (tr1 != null && tr2 != null && tr3 != null) {
                processOneTriangle(obj, new Triangle3DPrimitive(tr1), planes);
                processOneTriangle(obj, new Triangle3DPrimitive(tr2), planes);
                processOneTriangle(obj, new Triangle3DPrimitive(tr3), planes);
            }

        } else {
            triangle.setPaint(getColor(triangle.averageZValue(), planes));
            obj.addPrimitive(triangle);
        }
    }

    /**
     * Gets color by z-value
     * @param value value
     * @param planes z-planes
     * @return Color
     */
    public Color getColor(double value, ArrayList<Double> planes) {
        int number = 0;
        for (int i = 0; i < planes.size() - 1; i++) {
            Range range = new Range(planes.get(i), planes.get(i + 1));
            if (range.contains(value)) {
                number = i;
                break;
            }
        }

        int dev = (255 * number) / (planes.size() - 1);

        return new Color(dev, 255 - dev, 0);
    }

    /**
     * Gets number of the intersected plane
     * @param triangle to divide
     * @param planes z-planes
     * @return z-plane number
     */
    private int getInterSection(Triangle3D triangle, ArrayList<Double> planes) {
        Range localRange = triangle.getZRange();
        int planeNumber = -1;
        for (int i = 0; i < planes.size(); i++) {
            double z = planes.get(i);
            if (z != localRange.getLowerBound() &&
                    z != localRange.getUpperBound() && localRange.contains(z)) {
                planeNumber = i;
                break;
            }
        }
        return planeNumber;
    }

    /**
     * Get intersected point
     * @param M1 M1 point of M1M2 line
     * @param M2 M2 point of M1M2 line
     * @param z z-plane
     * @return intersected point
     */
    private Point3D getInterSection(Point3D M1, Point3D M2, double z) {
        if (M1.getZ() == M2.getZ()) {
            return M1.getZ() == z ? M1 : null;
        }

        Range localRange = null;
        localRange = Range.expandToInclude(localRange, M1.getZ());
        localRange = Range.expandToInclude(localRange, M2.getZ());

        if (localRange.contains(z)) {
            double x = M1.getX() + (M2.getX() - M1.getX()) * (z - M1.getZ()) / (M2.getZ() - M1.getZ());
            double y = M1.getY() + (M2.getY() - M1.getY()) * (z - M1.getZ()) / (M2.getZ() - M1.getZ());
            return new Point3D(x, y, z);
        } else {
            return null;
        }
    }

    /**
     * Get Paint by plotting method
     * @param plottingMethod plotting method
     * @return Paint
     */
    private Paint getPaint(int plottingMethod) {
        return SURFACE_WIRE_FRAME == plottingMethod ? null : getSeriesPaint(0);
    }

    /**
     * Get outline Paint by plotting method
     * @param plottingMethod plotting method
     * @return Paint
     */
    private Paint getOutlinePaint(int plottingMethod, Paint paint) {
        Paint outlinePaint = (SURFACE_WIRE_FRAME == plottingMethod ||
                SURFACE == plottingMethod) ? getSeriesOutlinePaint(0) : null;
        if (SURFACE == plottingMethod && paint == outlinePaint) {
            if (((Color)paint) == Color.BLACK) {
                outlinePaint = Color.WHITE;
            } else {
                outlinePaint = Color.BLACK;
            }
        }
        return outlinePaint;
    }

    /**
     * Class used for additional values calculation
     */
    static private class SurfaceHelper {

        /** Minimun points per one series */
        int minPointsPerSeries = 0;

        /** Z-planes, used for surface contours */
        public ArrayList<Double> planes = new ArrayList<Double>();

        /**
         * Constructor
         * @param dataset dataset
         * @param deltaZ delta z @see ManualContourLineProperty class
         */
        SurfaceHelper(Dataset3D dataset, int deltaZ) {

            for (int i = 0; i < dataset.getSeriesCount(); i++) {
                minPointsPerSeries = minPointsPerSeries == 0 ? dataset.getItemCount(i) : Math.min(minPointsPerSeries, dataset.getItemCount(i));
            }

            Range zRange = null;
            for (int series = 0; series < dataset.getSeriesCount() - 1; series++) {
                for (int item = 0; item < getMinPointsPerSeries() - 1; item++) {
                    Point3D p = dataset.getSeries3D(series).getPoint3D(item);
                    zRange = Range.expandToInclude(zRange, p.getZ());
                }
            }

            if (zRange != null) {
                double min = zRange.getLowerBound();
                while (min < zRange.getUpperBound()) {
                    planes.add(min);
                    min += deltaZ;
                }
                planes.add(zRange.getUpperBound());
            }
        }

        /**
         * Gets minimun points per one series
         * @return minimun points per one series value
         */
        public int getMinPointsPerSeries() {
            return minPointsPerSeries;
        }

        /**
         * Gets z-planes
         * @return z-planes
         */
        public ArrayList<Double> getPlanes() {
            return planes;
        }
    }

    @Override
    public LegendItem getLegendItem(String label, int series) {
        return null;
    }
}
