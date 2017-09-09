package gensym.charts3d.tests;

import java.awt.Color;
import java.awt.GradientPaint;
import java.awt.Paint;

import org.jfree.chart.LegendItem;

import gensym.charts.j3d.*;

import gensym.charts.j3d.primitives.*;
import gensym.charts.j3d.renderers.*;

import junit.framework.TestCase;

/**
 *  Tests BarRenderer3D class
 */
public class BarRenderer3DTest extends TestCase {
    
    /** Default outlinePaint for testing bar renderer */ 
    private Paint outlinePaint = Color.GRAY;

    /** The class for testing which extends BarRenderer3D */ 
    private class TestBarRenderer3D extends BarRenderer3D {
        /** Constructor */
        public TestBarRenderer3D() {
            super();
        }

        /** Tests copy constructor */
        public void testCopy() {
            BarRenderer3D renderer = new BarRenderer3D(this);
            assertNotNull(renderer);
            assertEquals(renderer.getSeriesPaint(0), this.getSeriesPaint(0));
        }
    }

    /**
     * Creates TestBarRenderer3D
     */
    public TestBarRenderer3D doCreateBarRenderer3D() throws Exception {
        TestBarRenderer3D br3d = new TestBarRenderer3D();
        br3d.testCopy();
        assertNotNull(br3d);
        assertTrue(br3d instanceof BarRenderer3D);
        return br3d;
    }
    
    /**
     * Creating BarRenderer3D test
     */
    public void testCreateBarRenderer3D() {
        try {
            doCreateBarRenderer3D();
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Check for equals 2 rectangle primitives
     * @param p1  the first rectangle primitive
     * @param p2  the second rectangle primitive
     * @param itemIndex the index of rectangle in object3D
     */
    private void checkEqualsRectPrimitives(Rectangle3DPrimitive p1, Rectangle3DPrimitive p2, int itemIndex) {
        String str = "The points %1s by triangles primitive (index = " + itemIndex + ") isn't equals.";
        assertEquals(String.format(str, "A"), p1.getA(), p2.getA());
        assertEquals(String.format(str, "B"), p1.getB(), p2.getB());
        assertEquals(String.format(str, "C"), p1.getC(), p2.getC());
        assertEquals(String.format(str, "D"), p1.getD(), p2.getD());
    }
    
    /**
     * Test 2 rectangle primitives from Object3D by specified points
     * @param A the point A
     * @param B the point B
     * @param C the point C
     * @param D the point B
     * @param o3d the Object3d object
     * @param itemIndex the index of tested primitives
     * @return index for next primitives
     */
    private int testRects(Point3D A, Point3D B, Point3D C, Point3D D, Object3D o3d, int itemIndex) {
        assertTrue(o3d.getPrimitive(itemIndex) instanceof Rectangle3DPrimitive);
        checkEqualsRectPrimitives(createPrimitive(A, B, C, D, Color.BLACK, Color.BLACK, true), 
                                   (Rectangle3DPrimitive) o3d.getPrimitive(itemIndex), itemIndex);
        return itemIndex + 1;
    }

    /**
     * Tests base Z value
     */
    public void testBaseZValue() {
        Dataset3D dataset = new Dataset3D();
        Series3D series = new Series3D("test");
        dataset.addSeries(series);
        double z1 = -1;
        double z2 = 1;
        double z3 = 2;
        series.addPoint3D(new Point3D(0, 0, z1));
        series.addPoint3D(new Point3D(0, 1, z2));
        series.addPoint3D(new Point3D(1, 0, z3));

        try {
            double baseZ = doCreateBarRenderer3D().getBaseZValue(dataset);
            assertEquals(z1 - (z3 - z1) * BarRenderer3D.BASE_Z_VALUE_FACTOR, baseZ);
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Creates ABCD rectangle primitive
     * @param a the A point
     * @param b the B point
     * @param c the C point
     * @param d the D point
     * @param paint the paint
     * @param outlinePaint the outline paint
     * @return created rectangle primitive
     */
    protected Rectangle3DPrimitive createPrimitive(Point3D a, Point3D b, Point3D c, Point3D d, Paint paint, Paint outlinePaint, boolean shades) {
        Rectangle3DPrimitive rect = new Rectangle3DPrimitive(d, c, b, a);
        rect.setPaint(paint);
        rect.setOutlinePaint(outlinePaint);
        rect.setShadesVisible(shades);
        return rect;
    }


    /**
     * Tests just created Object3D
     * @param d3d dataset for testing
     * @param o3d Object3D to compare
     */
    public void compareObjectAndDataset(Dataset3D d3d, Object3D o3d, double baseZ) {
        try {
            int itemIndex = 0;
            for (int series = 0; series < d3d.getSeriesCount(); series++) {
                for (int item = 0; item < d3d.getItemCount(series); item++) {
                    double x = item;
                    double y = series;
                    double z = d3d.getZValue(series, item);
                    Point3D A = new Point3D(x - BarRenderer3D.BAR_WIDTH_HEIGHT, y + BarRenderer3D.BAR_WIDTH_HEIGHT, baseZ);
                    Point3D B = new Point3D(x + BarRenderer3D.BAR_WIDTH_HEIGHT, y + BarRenderer3D.BAR_WIDTH_HEIGHT, baseZ);
                    Point3D C = new Point3D(x + BarRenderer3D.BAR_WIDTH_HEIGHT, y - BarRenderer3D.BAR_WIDTH_HEIGHT, baseZ);
                    Point3D D = new Point3D(x - BarRenderer3D.BAR_WIDTH_HEIGHT, y - BarRenderer3D.BAR_WIDTH_HEIGHT, baseZ);

                    Point3D A1 = new Point3D(x - BarRenderer3D.BAR_WIDTH_HEIGHT, y + BarRenderer3D.BAR_WIDTH_HEIGHT, z);
                    Point3D B1 = new Point3D(x + BarRenderer3D.BAR_WIDTH_HEIGHT, y + BarRenderer3D.BAR_WIDTH_HEIGHT, z);
                    Point3D C1 = new Point3D(x + BarRenderer3D.BAR_WIDTH_HEIGHT, y - BarRenderer3D.BAR_WIDTH_HEIGHT, z);
                    Point3D D1 = new Point3D(x - BarRenderer3D.BAR_WIDTH_HEIGHT, y - BarRenderer3D.BAR_WIDTH_HEIGHT, z);

                    itemIndex = testRects(A, B, C, D, o3d, itemIndex);
                    itemIndex = testRects(B1, C1, D1, A1, o3d, itemIndex);
                    itemIndex = testRects(B1, A1, A, B, o3d, itemIndex);
                    itemIndex = testRects(D1, C1, C, D, o3d, itemIndex);
                    itemIndex = testRects(C, C1, B1, B, o3d, itemIndex);
                    itemIndex = testRects(A1, D1, D, A, o3d, itemIndex);
                }
            }
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests BarRenderer3D legend's support
     */
    public void testBarRenderer3DLegend() {
        try {
            TestBarRenderer3D renderer = doCreateBarRenderer3D();
            //test geters/seters 
            assertEquals(false, renderer.isLegendSupported());
            renderer.setLegendSupported(true);
            assertEquals(true, renderer.isLegendSupported());
            String legendLabel = "Legen Label";

            //test getLegendItem
            renderer.setLegendSupported(false);
            int existedSeries = 0;
            assertEquals(null, renderer.getLegendItem(legendLabel, existedSeries));

            renderer.setLegendSupported(true);
            int absentSeries = 1000;
            assertEquals(null, renderer.getLegendItem(legendLabel, absentSeries));

            assertEquals(LegendItem.class, renderer.getLegendItem(legendLabel, existedSeries).getClass());
            LegendItem legend = renderer.getLegendItem(legendLabel, existedSeries);
            assertNotNull(legend);
            assertEquals(legendLabel, legend.getLabel());
            assertEquals(legendLabel, legend.getDescription());

            Color firstSeriesPaint = (Color)renderer.getSeriesPaint(existedSeries);
            legend = renderer.getLegendItem(legendLabel, existedSeries);
            assertEquals(new Color(firstSeriesPaint.getRed(), firstSeriesPaint.getGreen(), firstSeriesPaint.getBlue()), legend.getFillPaint());
            assertEquals(BarRenderer3D.LEGEND_BAR, legend.getShape());
            assertEquals(true, legend.isShapeOutlineVisible());
            
            GradientPaint gradientPaint = new GradientPaint(1, 5, Color.BLUE, 3, 6, Color.CYAN);
            renderer.setSeriesPaint(existedSeries, gradientPaint);
            assertEquals(gradientPaint, renderer.getLegendItem(legendLabel, existedSeries).getFillPaint());
            
            renderer.setSeriesOutlinePaint(existedSeries, outlinePaint);
            legend = renderer.getLegendItem(legendLabel, existedSeries);
            assertEquals(outlinePaint, legend.getOutlinePaint());
            assertEquals(true, legend.isShapeOutlineVisible());
            assertEquals(BarRenderer3D.LEGEND_STROKE, legend.getOutlineStroke());
            assertEquals(BarRenderer3D.LEGEND_BAR, legend.getShape());
            assertEquals(legendLabel, legend.getLabel());
            assertEquals(legendLabel, legend.getDescription());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Compare one point
     * @param object Point3DPrimitive primitive
     * @param point to compare
     */
    private final void testPointPrimitive(Object3DPrimitive object, Point3D point) {
        assertEquals(object.getClass(), Point3DPrimitive.class);
        assertEquals(((Point3DPrimitive)object).getPoints().length, 1);
        Point3D array[] = ((Point3DPrimitive)object).getPoints();
        assertEquals(array[0].getX(), point.getX());
        assertEquals(array[0].getY(), point.getY());
        assertEquals(array[0].getZ(), point.getZ());
        
    }

    /**
     * Compare points
     * @param d3d dataset for testing
     * @param o3d Object3D to compare
     */
    private final void comparePoints(Dataset3D d3d, Object3D o3d, double baseZ) {
        try {
            int itemIndex = 0;
            for (int series = 0; series < d3d.getSeriesCount(); series++) {
                for (int item = 0; item < d3d.getItemCount(series); item++) {
                    double x = item;
                    double y = series;
                    double z = d3d.getZValue(series, item);
                    
                    Point3D A = new Point3D(x - BarRenderer3D.BAR_WIDTH_HEIGHT, y + BarRenderer3D.BAR_WIDTH_HEIGHT, baseZ);
                    testPointPrimitive(o3d.getPrimitive(itemIndex++), A);
                    
                    Point3D B = new Point3D(x + BarRenderer3D.BAR_WIDTH_HEIGHT, y + BarRenderer3D.BAR_WIDTH_HEIGHT, baseZ);
                    testPointPrimitive(o3d.getPrimitive(itemIndex++), B);

                    Point3D C = new Point3D(x + BarRenderer3D.BAR_WIDTH_HEIGHT, y - BarRenderer3D.BAR_WIDTH_HEIGHT, baseZ);
                    testPointPrimitive(o3d.getPrimitive(itemIndex++), C);

                    Point3D D = new Point3D(x - BarRenderer3D.BAR_WIDTH_HEIGHT, y - BarRenderer3D.BAR_WIDTH_HEIGHT, baseZ);
                    testPointPrimitive(o3d.getPrimitive(itemIndex++), D);

                    Point3D A1 = new Point3D(x - BarRenderer3D.BAR_WIDTH_HEIGHT, y + BarRenderer3D.BAR_WIDTH_HEIGHT, z);
                    testPointPrimitive(o3d.getPrimitive(itemIndex++), A1);

                    Point3D B1 = new Point3D(x + BarRenderer3D.BAR_WIDTH_HEIGHT, y + BarRenderer3D.BAR_WIDTH_HEIGHT, z);
                    testPointPrimitive(o3d.getPrimitive(itemIndex++), B1);

                    Point3D C1 = new Point3D(x + BarRenderer3D.BAR_WIDTH_HEIGHT, y - BarRenderer3D.BAR_WIDTH_HEIGHT, z);
                    testPointPrimitive(o3d.getPrimitive(itemIndex++), C1);

                    Point3D D1 = new Point3D(x - BarRenderer3D.BAR_WIDTH_HEIGHT, y - BarRenderer3D.BAR_WIDTH_HEIGHT, z);
                    testPointPrimitive(o3d.getPrimitive(itemIndex++), D1);                    
                }
            }

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * CreateObject3D test
     */
    public void testBarRenderer3DCreateObject3D2() {
        try {
            TestBarRenderer3D br3d = doCreateBarRenderer3D();
            int seriesCount = 3;
            br3d.setSeriesOutlinePaint(1, outlinePaint);
            Dataset3D d3d = Test3DUtils.doCreateDataset3DWithData(seriesCount);
            Object3D o3d =  br3d.createObject3D(d3d,
                    BarRenderer3D.BAR_WIRE_FRAME, Renderer3D.DETAILS_WIREFRAME);

            Object3D o3d1 =  br3d.createObject3D(d3d,
                    BarRenderer3D.BAR_SURFACE, Renderer3D.DETAILS_WIREFRAME);

            double baseZ = br3d.getBaseZValue(d3d);
            compareObjectAndDataset(d3d, o3d, baseZ);
            compareObjectAndDataset(d3d, o3d1, baseZ);

            Object3D o3d2 =  br3d.createObject3D(d3d,
                    BarRenderer3D.BAR_SURFACE_AS_PIXELS, Renderer3D.DETAILS_WIREFRAME);
            comparePoints(d3d, o3d2, baseZ);

            int expectedCount = 6 * Test3DUtils.getItemCount(seriesCount); 
            assertEquals(expectedCount, o3d.getPrimitivesCount());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
}
