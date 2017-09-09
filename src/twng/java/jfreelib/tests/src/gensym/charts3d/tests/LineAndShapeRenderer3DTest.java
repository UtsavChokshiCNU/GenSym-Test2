package gensym.charts3d.tests;

import gensym.charts.j3d.*;
import gensym.charts.j3d.renderers.*;

import junit.framework.TestCase;

import java.awt.Color;
import java.awt.Shape;
import java.awt.geom.Ellipse2D;
import org.jfree.chart.LegendItem;

/**
 *  Tests LineAndShapeRenderer3D class
 */
public class LineAndShapeRenderer3DTest extends TestCase {

    /**
     * Tests LineAndShapeRenderer3D all functionality
     */
    public final void testLineAndShapeRenderer3D() {
        LineAndShapeRenderer3D rendererToCopy = new LineAndShapeRenderer3D();
        LineAndShapeRenderer3D renderer = new LineAndShapeRenderer3D(rendererToCopy);

        renderer.setSeriesShape(0, null);
        assertEquals(renderer.getSeriesShape(0), LineAndShapeRenderer3D.DEFAULT_SHAPE);

        Shape testShape = new Ellipse2D.Float(-223, -32, 34, 534);
        renderer.setSeriesShape(0, testShape);
        assertEquals(renderer.getSeriesShape(0), testShape);

        renderer.setLinesVisible(true);
        assertTrue(renderer.isLinesVisible());

        renderer.setLinesVisible(false);
        assertFalse(renderer.isLinesVisible());

        renderer.setPointsVisible(true);
        assertTrue(renderer.isPointsVisible());

        renderer.setPointsVisible(false);
        assertFalse(renderer.isPointsVisible());

        renderer.setPointsVisible(true);
        renderer.setLinesVisible(true);
        Object3D object = renderer.createObject3D(Test3DUtils.doCreateSimpleDataset(2, 2, false),
                Renderer3D.DETAILS_PLOTTINGMETHOD, LineAndShapeRenderer3D.LINES);
        assertEquals(6, object.getPrimitivesCount());

        renderer.setPointsVisible(false);
        renderer.setLinesVisible(false);
        object = renderer.createObject3D(Test3DUtils.doCreateSimpleDataset(2, 2, false),
                Renderer3D.DETAILS_WIREFRAME, LineAndShapeRenderer3D.POINTS);
        assertEquals(object.getPrimitivesCount(), 4);

        renderer.setPointsVisible(true);
        renderer.setLinesVisible(true);
        object = renderer.createObject3D(Test3DUtils.doCreateSimpleDataset(2, 2, false),
                Renderer3D.DETAILS_FULL, LineAndShapeRenderer3D.POINTS_AND_LINES);
        assertEquals(object.getPrimitivesCount(), 6);
    }
    
    /**
     * Tests LineAndShape3D legend's support
     */
    public void testLineAndShape3DLegend() {
        try {
            LineAndShapeRenderer3D renderer = new LineAndShapeRenderer3D();
            String legendLabel = "Legen Label";
            int existedSeries = 0;
            int absentSeries = 1000;
            assertEquals(null, renderer.getLegendItem(legendLabel, absentSeries));

            assertEquals(LegendItem.class, renderer.getLegendItem(legendLabel, existedSeries).getClass());
            LegendItem legend = renderer.getLegendItem(legendLabel, existedSeries);
            assertNotNull(legend);
            assertEquals(legendLabel, legend.getLabel());
            assertEquals(legendLabel, legend.getDescription());
            assertEquals(legendLabel, legend.getDescription());
            assertEquals(true, legend.isShapeOutlineVisible());

            Color firstSeriesPaint = (Color)renderer.getSeriesPaint(existedSeries);
            legend = renderer.getLegendItem(legendLabel, existedSeries);
            
            assertEquals(new Color(firstSeriesPaint.getRed(), firstSeriesPaint.getGreen(), firstSeriesPaint.getBlue()) , legend.getFillPaint());
            assertEquals(renderer.getSeriesShape(existedSeries), legend.getShape());
            assertEquals(true, legend.isShapeOutlineVisible());
            assertEquals(legend.getFillPaint(), legend.getOutlinePaint());
            
            renderer.setPointsVisible(false);
            assertEquals(renderer.isPointsVisible(), renderer.getLegendItem(legendLabel, existedSeries).isShapeVisible());
            renderer.setPointsVisible(true);
            assertEquals(renderer.isPointsVisible(), renderer.getLegendItem(legendLabel, existedSeries).isShapeVisible());
            
            renderer.setLinesVisible(false);
            assertEquals(renderer.isLinesVisible(), renderer.getLegendItem(legendLabel, existedSeries).isLineVisible());
            renderer.setLinesVisible(true);
            assertEquals(renderer.isLinesVisible(), renderer.getLegendItem(legendLabel, existedSeries).isLineVisible());
            
            Color outlinePaint = Color.blue;
            renderer.setSeriesOutlinePaint(existedSeries, outlinePaint);
            legend = renderer.getLegendItem(legendLabel, existedSeries);
            assertEquals(true, legend.isShapeOutlineVisible());
            assertEquals(outlinePaint, legend.getOutlinePaint());
            assertEquals(renderer.getSeriesShape(existedSeries), legend.getShape());
            assertEquals(LineAndShapeRenderer3D.LEGEND_STROKE, legend.getOutlineStroke());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
}
