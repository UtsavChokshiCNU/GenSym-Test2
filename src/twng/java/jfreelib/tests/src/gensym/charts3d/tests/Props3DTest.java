package gensym.charts3d.tests;

import gensym.charts.Chart3D;
import gensym.charts.ChartsCommon;
import gensym.charts.actions.CreateChartAction;
import gensym.charts.properties.PolyModeProperty;
import gensym.charts.properties.SubsetPointTypesProperty;
import gensym.charts.properties.rotation.RotationIncrementProperty;
import gensym.charts.properties.rotation.RotationSpeedProperty;
import gensym.charts.scrolling.HorizontalScrolling3D;
import gensym.charts.scrolling.ScrollingListener;

import gensym.charts.tests.TestChartBase;
import gensym.charts.j3d.*;
import gensym.charts.j3d.renderers.*;

import java.awt.Color;
import java.awt.Shape;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Rectangle2D;

/**
 * Tests property's related with 3D charts
 */
public class Props3DTest extends TestChartBase {

    /**
     * Tests props: poly-mode, label-bold, zdata,
     * x-axis-label, y-axis-label, z-axis-label, plotting-method,
     * subset-point-types, subset-colors, allow-data-hot-spots,
     * subset-line-types, grid-line-control, subset-labels, degree-of-rotation,
     * viewing-height, rotation-speed, rotation-detail, rotation-increment, auto-rotation.
     */
    public final void testProps() {
        doCreateAction(CreateChartAction.PE_3D_CHART);
        assertNotNull(getHolder());
        assertTrue(getChart() instanceof Chart3D);
        Chart3D chart = (Chart3D) getChart();
        try {
            int subsets = 2, points = 2;

            // subsets
            runAction("SetInt", "property", 2115, "i", 0, "j", 0, "value", subsets);
            // points
            runAction("SetInt", "property", 2120, "i", 0, "j", 0, "value", points);

            // xdata
            double xvalues[] = new double[]{11, 12, 13, 14, 12, 12, 12, 12, 12, 12, };
            runActionDoubleArray(getHandle(), 2135, xvalues);

            // ydata
            double yvalues[] = new double[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
            runActionDoubleArray(getHandle(), 2140, yvalues);

            // zdata
            double zvalues[] = new double[]{111, 222, 333, 444, 34, -2, 342, -45, 23, 123, 14, 32};
            runActionDoubleArray(getHandle(), 2900, zvalues);

            // tests dataset
            chart.updateChart();
            assertEquals(subsets, chart.getPlot().getDataset().getSeriesCount());
            assertEquals(points, chart.getPlot().getDataset().getItemCount(0));
            assertEquals(points, chart.getPlot().getDataset().getItemCount(1));
            assertEquals(1.0, chart.getPlot().getDataset().getZ(0, 0));
            assertEquals(2.0, chart.getPlot().getDataset().getZ(0, 1));
            assertEquals(3.0, chart.getPlot().getDataset().getZ(1, 0));
            assertEquals(4.0, chart.getPlot().getDataset().getZ(1, 1));

            // label-bold
            runAction("SetInt", "property", 2530, "i", 0, "j", 0, "value", 1);
            assertTrue(chart.getPlot().getXAxis().getLabelFont().isBold());
            assertTrue(chart.getPlot().getYAxis().getLabelFont().isBold());
            assertTrue(chart.getPlot().getZAxis().getLabelFont().isBold());
            runAction("SetInt", "property", 2530, "i", 0, "j", 0, "value", 0);
            assertFalse(chart.getPlot().getXAxis().getLabelFont().isBold());
            assertFalse(chart.getPlot().getYAxis().getLabelFont().isBold());
            assertFalse(chart.getPlot().getZAxis().getLabelFont().isBold());

            // poly-mode
            runAction("SetInt", "property", 4013, "i", 0, "j", 0,
                    "value", PolyModeProperty.PEPM_SURFACEPOLYGONS);
            assertTrue(chart.getPlot().getRenderer() instanceof SurfaceRenderer3D);

            runAction("SetInt", "property", 4013, "i", 0, "j", 0,
                    "value", PolyModeProperty.PEPM_3DBAR);
            assertTrue(chart.getPlot().getRenderer() instanceof BarRenderer3D);

            runAction("SetInt", "property", 4013, "i", 0, "j", 0,
                    "value", PolyModeProperty.PEPM_POLYGONDATA);
            assertTrue(chart.getPlot().getRenderer() instanceof SurfaceRenderer3D);

            runAction("SetInt", "property", 4013, "i", 0, "j", 0,
                    "value", PolyModeProperty.PEPM_SCATTER);
            assertTrue(chart.getPlot().getRenderer() instanceof LineAndShapeRenderer3D);

            runAction("SetInt", "property", 4013, "i", 0, "j", 0,
                    "value", 9999);
            assertTrue(chart.getPlot().getRenderer() instanceof LineAndShapeRenderer3D);

            // manual-contour-line
            int step = 40, method = 4;
            runAction("SetInt", "property", 4013, "i", 0, "j", 0,
                    "value", PolyModeProperty.PEPM_SURFACEPOLYGONS);
            runAction("SetInt", "property", 3090, "i", 0, "j", 0,
                    "value", method);
            assertEquals(method, chart.getPlot().getPlottingMethod());
            runAction("SetDouble", "property", 4027, "i", 0, "j", 0,
                    "value", step);
            chart.updateChart();
            Thread.sleep(100);
            assertTrue(chart.getPlot().getRenderer() instanceof SurfaceRenderer3D);
            assertEquals(((SurfaceRenderer3D)chart.getPlot().getRenderer()).getDeltaZ(), step);

            // x-axis-label, y-axis-label, z-axis-label
            String label = "Hello World!";
            runAction("SetString", "property", 3000, "i", 0, "j", 0,
                    "value", label);
            runAction("SetString", "property", 3005, "i", 0, "j", 0,
                    "value", label);
            runAction("SetString", "property", 4000, "i", 0, "j", 0,
                    "value", label);
            assertEquals(chart.getPlot().getXAxis().getLabel(), label);
            assertEquals(chart.getPlot().getYAxis().getLabel(), label);
            assertEquals(chart.getPlot().getZAxis().getLabel(), label);

            // point-labels
            runAction("SetString", "property", 2130, "i", 0, "j", 0,
                    "value", "test");
            assertEquals(chart.getPlot().getXAxis().getLabelFormat().getLabels().size(), 1);

            // degree-of-rotation
            int horizontalAngle = 222, angle2 = 308;
            runAction("SetInt", "property", 4001, "i", 0, "j", 0,
                    "value", horizontalAngle);
            assertEquals(chart.getHorizontalScrollingInterface().getScrollItemPos(), angle2);

            // auto-rotation
            runAction("SetInt", "property", 4003, "i", 0, "j", 0,
                    "value", 0);
            assertFalse(chart.getAutoRotation().isRunning());

            runAction("SetInt", "property", 4003, "i", 0, "j", 0,
                    "value", 1);
            runAction("Update");
            assertTrue(chart.isAutoRotationDone());

            Thread.sleep(100);
            assertTrue(chart.getAutoRotation().isRunning());
            chart.getPlot().leaveRotationMode();
            assertEquals(chart.getPlot().getPlottingDetails(), Renderer3D.DETAILS_FULL);

            // rotation-increment
            int count = chart.getHorizontalScrollingInterface().getScrollItemsCount();
            runAction("SetInt", "property", 4004, "i", 0, "j", 0,
                    "value", RotationIncrementProperty.PERI_INCBY15);
            assertEquals(chart.getAutoRotation().getIncrement(), calcIncrement(count, 15));

            runAction("SetInt", "property", 4004, "i", 0, "j", 0,
                    "value", RotationIncrementProperty.PERI_INCBY10);
            assertEquals(chart.getAutoRotation().getIncrement(), calcIncrement(count, 10));

            runAction("SetInt", "property", 4004, "i", 0, "j", 0,
                    "value", RotationIncrementProperty.PERI_INCBY5);
            assertEquals(chart.getAutoRotation().getIncrement(), calcIncrement(count, 5));

            runAction("SetInt", "property", 4004, "i", 0, "j", 0,
                    "value", RotationIncrementProperty.PERI_INCBY2);
            assertEquals(chart.getAutoRotation().getIncrement(), calcIncrement(count, 2));

            runAction("SetInt", "property", 4004, "i", 0, "j", 0,
                    "value", RotationIncrementProperty.PERI_INCBY1);
            assertEquals(chart.getAutoRotation().getIncrement(), calcIncrement(count, 1));

            runAction("SetInt", "property", 4004, "i", 0, "j", 0,
                    "value", RotationIncrementProperty.PERI_DECBY1);
            assertEquals(chart.getAutoRotation().getIncrement(), calcIncrement(count, -1));

            runAction("SetInt", "property", 4004, "i", 0, "j", 0,
                    "value", RotationIncrementProperty.PERI_DECBY2);
            assertEquals(chart.getAutoRotation().getIncrement(), calcIncrement(count, -2));

            runAction("SetInt", "property", 4004, "i", 0, "j", 0,
                    "value", RotationIncrementProperty.PERI_DECBY5);
            assertEquals(chart.getAutoRotation().getIncrement(), calcIncrement(count, -5));

            runAction("SetInt", "property", 4004, "i", 0, "j", 0,
                    "value", RotationIncrementProperty.PERI_DECBY10);
            assertEquals(chart.getAutoRotation().getIncrement(), calcIncrement(count, -10));

            runAction("SetInt", "property", 4004, "i", 0, "j", 0,
                    "value", RotationIncrementProperty.PERI_DECBY15);
            assertEquals(chart.getAutoRotation().getIncrement(), calcIncrement(count, -15));
            Thread.sleep(100);

            // rotation-speed
            int speed = 2345;
            runAction("SetInt", "property", 4011, "i", 0, "j", 0,
                    "value", speed);
            assertEquals(chart.getAutoRotation().getSpeed(), speed);
            runAction("SetInt", "property", 4011, "i", 0, "j", 0,
                    "value", RotationSpeedProperty.maxValue + 1);
            assertEquals(chart.getAutoRotation().getSpeed(),
                    RotationSpeedProperty.defaultValue);
            Thread.currentThread();
            Thread.sleep(100);

            // rotation-detail
            assertEquals(chart.getPlot().getRotationDetail(), Renderer3D.DETAILS_WIREFRAME);
            int value = Renderer3D.DETAILS_FULL;
            runAction("SetInt", "property", 4005, "i", 0, "j", 0,
                    "value", value);
            assertEquals(chart.getPlot().getRotationDetail(), value);
            value = Renderer3D.DETAILS_PLOTTINGMETHOD;
            runAction("SetInt", "property", 4005, "i", 0, "j", 0,
                    "value", value);
            assertEquals(chart.getPlot().getRotationDetail(), value);
            runAction("SetInt", "property", 4005, "i", 0, "j", 0,
                    "value", 777);
            assertEquals(chart.getPlot().getRotationDetail(), value);

            // viewing-height
            int verticalAngle = 33, angle1 = 341;
            runAction("SetInt", "property", 4008, "i", 0, "j", 0,
                    "value", verticalAngle);
            assertEquals(chart.getVerticalScrollingInterface().getScrollItemPos(), angle1);

            // subset-labels
            String labelSeries = "Tests";
            runAction("SetString", "property", 2125, "i", 0, "j", 0,
                    "value", labelSeries);
            // grid-line-control
            runAction("SetInt", "property", 3100, "i", 0, "j", 0,
                    "value", 0);
            // subset-line-types
            runAction("SetInt", "property", 3271, "i", 0, "j", 0,
                    "value", 0);
            chart.updateChart();
            assertNotNull(chart.getPlot().getDataset().getSeries3D(0));

            // allow-data-hot-spots
            runAction("SetInt", "property", 3210, "i", 0, "j", 0,
                    "value", 1);
            assertTrue(chart.isDataHotSpotsAllowed() &&
                    chart.isSeriesHotSpotsAllowed() && chart.isPointHotSpotsAllowed());
            chart.setAllowDataHotSpots(false);
            chart.setAllowPointHotSpots(false);
            chart.setAllowSeriesHotSpots(false);
            assertFalse(chart.isDataHotSpotsAllowed());

            // subset-colors
            value = 44444;
            Color cl1 = new Color(ChartsCommon.convertBGRtoRGB(value));
            runAction("SetInt", "property", 2190, "i", 0, "j", 0,
                    "value", value);
            chart.updateChart();
            assertTrue(chart.getPlot().getRenderer().getSeriesPaint(0) instanceof Color);
            Color cl2 = (Color) chart.getPlot().getRenderer().getSeriesPaint(0);
            assertEquals(cl1.getRGB(), cl2.getRGB());
            // test colors again
            axisColorsTest(chart);

            // Sets LineAndShapeRenderer3D
            runAction("SetInt", "property", 4013, "i", 0, "j", 0,
                    "value", PolyModeProperty.PEPM_SCATTER);
            // subset-point-types
            runAction("SetInt", "property", 3270, "i", 0, "j", 0,
                    "value", SubsetPointTypesProperty.PEPT_SQUARE);
            assertTrue(chart.getPlot().getRenderer() instanceof LineAndShapeRenderer3D);
            LineAndShapeRenderer3D renderer =
                    (LineAndShapeRenderer3D) chart.getPlot().getRenderer();
            assertTrue(renderer.getSeriesShape(0) instanceof Rectangle2D.Float);

            // plotting-method
             method = 2;
            runAction("SetInt", "property", 3090, "i", 0, "j", 0,
                    "value", method);
            assertEquals(method, chart.getPlot().getPlottingMethod());

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Tests part of ChartScrolling3D class functionality
     */
    public final void testScrollingListener() {
        HorizontalScrolling3D scroll = new HorizontalScrolling3D(new Plot3D(new Dataset3D(), new Axis3D(), new Axis3D(), new Axis3D()));
        assertEquals(scroll.getListeners().size(), 0);

        ScrollingListener listener = new ScrollingListener(){
            public void itemsScrolled() {
            }};
        scroll.addListener(listener);
        assertEquals(scroll.getListeners().size(), 1);

        scroll.removeListener(listener);
        assertEquals(scroll.getListeners().size(), 0);
    }

    /**
     * Tests part of XYZItemEntity class functionality
     */
    public final void testXYZItemEntity() {
        Point3D point = new Point3D(12, 444.666, 2143324.003);
        Shape shape = new Ellipse2D.Double(point.getX(), point.getY(), 4, 4);
        int subset = 1;
        int index = 12;
        XYZItemEntity entity = new XYZItemEntity(shape, null, null, point, subset, index);
        assertEquals(point, entity.getItem());
        assertEquals(subset, entity.getSeries());
        assertEquals(index, entity.getPoint());
    }

    /**
     * Calculate increment
     */
    private final int calcIncrement(int count, int inc) {
        return (int) (inc * count / 360);
    }

    /**
     * Tests axis colors
     * @param chart to test
     */
    private final void axisColorsTest(Chart3D chart) {
        Color cl = Color.MAGENTA;
        chart.setAxisColor(cl);
        assertEquals(chart.getPlot().getXAxis().getLabelPaint(), cl);
        assertEquals(chart.getPlot().getYAxis().getLabelPaint(), cl);
        assertEquals(chart.getPlot().getZAxis().getLabelPaint(), cl);
    }
}
