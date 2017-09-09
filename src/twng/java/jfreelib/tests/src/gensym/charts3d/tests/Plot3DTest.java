package gensym.charts3d.tests;

import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;

import org.jfree.chart.ChartRenderingInfo;
import org.jfree.chart.LegendItem;
import org.jfree.chart.LegendItemCollection;
import org.jfree.chart.plot.Plot;
import org.jfree.chart.plot.PlotRenderingInfo;
import org.jfree.chart.plot.ValueAxisPlot;
import org.jfree.data.Range;

import gensym.charts.j3d.*;
import gensym.charts.j3d.renderers.*;

import junit.framework.TestCase;

/**
 * Tests for simple Plot3D class
 */
public class Plot3DTest extends TestCase {
    /**
     * Creates Plot3D with defaults: dataSet and axes
     */
    public Plot3D doCreatePlot3D() throws Exception {
        Dataset3D dataset = new Dataset3D();
        Axis3D xAxis = new Axis3D();
        Axis3D yAxis = new Axis3D();
        Axis3D zAxis = new Axis3D();
        Plot3D p3d = new Plot3D(dataset, xAxis, yAxis, zAxis);
        assertEquals(dataset, p3d.getDataset());
        assertEquals(xAxis, p3d.getXAxis());
        assertEquals(yAxis, p3d.getYAxis());
        assertEquals(zAxis, p3d.getZAxis());
        p3d.setPlottingMethod(0);
        p3d.setPlottingDetails(0);
        p3d.setContourVisible(false);
        assertEquals(p3d.getPlottingMethod(), 0);
        assertEquals(p3d.getPlottingDetails(), 0);
        assertEquals(p3d.isContourVisible(), false);
        return p3d;
    }
    
    /**
     * Creating Plot3D test
     */
    public void testCreatePlot3D() {
        try {
            Plot3D p3d = doCreatePlot3D();
            assertEquals("assert #1", "Plot3D", p3d.getPlotType());

            // create plot with nullable X axis
            try {
                p3d = new Plot3D(new Dataset3D(), null, new Axis3D(), new Axis3D());
                fail("This should never happen");
            }
            catch (IllegalArgumentException e) {
                ; //this Ok
            }
            catch (Exception e) {
                fail("Wrong exception (1): " + e.getMessage());
            }

            // create plot with nullable Y axis
            try {
                p3d = new Plot3D(new Dataset3D(), new Axis3D(), null, new Axis3D());
                fail("This should never happen");
            }
            catch (IllegalArgumentException e) {
                ; //this Ok
            }
            catch (Exception e) {
                fail("Wrong exception (1): " + e.getMessage());
            }
            
            // create plot with nullable Z axis
            try {
                p3d = new Plot3D(new Dataset3D(), new Axis3D(), new Axis3D(), null);
                fail("This should never happen");
            }
            catch (IllegalArgumentException e) {
                ; //this Ok
            }
            catch (Exception e) {
                fail("Wrong exception (2): " + e.getMessage());
            }
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Plot3D Axes seters test (with correct values)
     */
    public void testPlot3DAxesSets1() {
        try {
            Plot3D p3d = doCreatePlot3D();
            
            Dataset3D d3d = new Dataset3D();
            Axis3D xAxis = new Axis3D();
            Axis3D yAxis = new Axis3D();
            Axis3D zAxis = new Axis3D();
            
            p3d.setDataset(d3d);
            assertEquals(d3d, p3d.getDataset());
            
            p3d.setXAxis(xAxis);
            assertEquals(xAxis, p3d.getXAxis());
            
            p3d.setYAxis(yAxis);
            assertEquals(yAxis, p3d.getYAxis());
            
            p3d.setZAxis(zAxis);
            assertEquals(zAxis, p3d.getZAxis());

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Plot3D Axes seters test (with incorrect values)
     */
    public void testPlot3DAxesSets2() {
        try {
            Plot3D p3d = doCreatePlot3D();
            
            // set nullable X axis
            try {
                p3d.setXAxis(null);
                fail("This should never happen");
            }
            catch (IllegalArgumentException e) {
                ; //this Ok
            }
            catch (Exception e) {
                fail("Wrong exception : " + e.getMessage());
            }

            // set nullable Y axis
            try {
                p3d.setYAxis(null);
                fail("This should never happen");
            }
            catch (IllegalArgumentException e) {
                ; //this Ok
            }
            catch (Exception e) {
                fail("Wrong exception : " + e.getMessage());
            }
            
            // set nullable Z axis
            try {
                p3d.setZAxis(null);
                fail("This should never happen");
            }
            catch (IllegalArgumentException e) {
                ; //this Ok
            }
            catch (Exception e) {
                fail("Wrong exception : " + e.getMessage());
            }

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    

    /**
     * ValueAxisPlot interface test
     */
    public void testPlot3DValueAxisPlot() {
        try {
            Plot3D p3d = doCreatePlot3D();
            assertTrue("The 'p3d' type doesn't implements ValueAxisPlot interface", p3d instanceof ValueAxisPlot);

            p3d.setDataset(Test3DUtils.doCreateDataset3DWithData(4));

            Range rX = new Range(Test3DUtils.X_BASE, Test3DUtils.X_BASE + 2);
            Range rY = new Range(Test3DUtils.Y_BASE, Test3DUtils.Y_BASE + 2);
            Range rZ = new Range(Test3DUtils.Z_BASE, Test3DUtils.Z_BASE + 2);
            
            assertEquals(rX, p3d.getDataRange(p3d.getXAxis()));
            assertEquals(rY, p3d.getDataRange(p3d.getYAxis()));
            assertEquals(rZ, p3d.getDataRange(p3d.getZAxis()));
            
            // get data range axis isn't belong to plot
            Axis3D a3d = new Axis3D();
            try {
                p3d.getDataRange(a3d);
                fail("This should never happen");
            }
            catch (IllegalArgumentException e) {
                ; //this Ok
            }
            catch (Exception e) {
                fail("Wrong exception: " + e.getMessage());
            }
            
            p3d.setDataset(null);
            assertNull(p3d.getDataRange(p3d.getXAxis()));
            assertNull(p3d.getDataRange(p3d.getYAxis()));
            assertNull(p3d.getDataRange(p3d.getZAxis()));
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Renderer test
     */
    public void testPlot3DRenderer() {
        try {
            Plot3D p3d = doCreatePlot3D();
            assertNotNull(p3d.getRenderer());
            assertTrue(p3d.getRenderer() instanceof LineAndShapeRenderer3D);
            p3d.setRenderer(null);
            assertNull(p3d.getRenderer());
            p3d.setRenderer(new BarRenderer3D());
            assertTrue(p3d.getRenderer() instanceof BarRenderer3D);
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Moving test
     */
    public void testPlot3DMove() {
        try {
            Plot3D p3d = doCreatePlot3D();

            // zoom parameter should be about zero
            try {
                p3d.zoom(-10);
                fail("This should never happen");
            }
            catch (RuntimeException e) {
                ; //this Ok
            }
            catch (Exception e) {
                fail("Wrong exception: " + e.getMessage());
            }

            // zoom parameter should be about zero
            try {
                p3d.zoom(-10, true);
            }
            catch (Exception e) {
                fail("This should never happen");
            }
            
            p3d.zoom(1.5);
            p3d.getZoom();
            assertEquals(1.5, p3d.getZoom(), 0.0001D);

            p3d.zoom(2.5);
            p3d.getZoom();
            assertEquals(2.5, p3d.getZoom(), 0.0001D);

            p3d.zoom(2.5, true);
            p3d.getZoom();
            assertEquals(5.0, p3d.getZoom(), 0.0001D);
            
            p3d.moveScreen(0, 0, false);
            assertEquals(new Point2D.Double(0, 0), p3d.getScreenMoving());

            p3d.moveScreen(5, 4, false);
            assertEquals(new Point2D.Double(5, 4), p3d.getScreenMoving());
            
            p3d.moveScreen(10, 2, true);
            assertEquals(new Point2D.Double(15, 6), p3d.getScreenMoving());
            
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Rotating test
     */
    public void testPlot3DRotate() {
        try {
            Plot3D p3d = doCreatePlot3D();
            double phi = 10.5;
            p3d.rotateAroundX(phi);
            assertEquals(phi, p3d.getXAngle());
            
            double xi = 11.5;
            p3d.rotateAroundY(xi);
            assertEquals(xi, p3d.getYAngle());

            double rho = 11.5;
            p3d.rotateAroundZ(rho);
            assertEquals(rho, p3d.getZAngle());

        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Drawing Plot3D test
     */
    public void testDrawMethod() {
        try {
            Plot3D p3d = doCreatePlot3D();
            assertNull("assert #1", p3d.getObject3D());
            
            p3d.setDataset(Test3DUtils.doCreateDataset3DWithData(5));
            p3d.setRenderer(new SurfaceRenderer3D());
            Graphics2D g2 = Test3DUtils.genGraphics2D();

            assertNull(p3d.getObject3D());
            p3d.setPlottingDetails(Renderer3D.DETAILS_FULL);
            p3d.setContourVisible(true);
            p3d.draw(g2, new Rectangle(0, 0, 100, Plot.MINIMUM_HEIGHT_TO_DRAW), null, null, null);
            assertNull(p3d.getObject3D());
            p3d.draw(g2, new Rectangle(0, 0, Plot.MINIMUM_WIDTH_TO_DRAW, 100), null, null, null);
            assertNull(p3d.getObject3D());
            
            PlotRenderingInfo pri = new PlotRenderingInfo(new ChartRenderingInfo());
            Rectangle2D area = Test3DUtils.genRectangle2D();
            p3d.draw(g2, area, null, null, pri);
            assertNotNull(p3d.getObject3D());
            assertEquals(area, pri.getPlotArea());
            assertEquals(area, pri.getDataArea());

            p3d.datasetChanged(null);
            assertNull(p3d.getObject3D());
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }

    /**
     * Test legend items
     */
    public void testLegendItems() {
        try {
            Plot3D p3d = doCreatePlot3D();
            Dataset3D d3d = Test3DUtils.doCreateDataset3DWithData(5); 
            p3d.setDataset(d3d);
            BarRenderer3D renderer = new BarRenderer3D();
            p3d.setRenderer(renderer);

            LegendItemCollection legends = p3d.getLegendItems();
            assertEquals(0, legends.getItemCount());

            renderer.setLegendSupported(true);
            legends = p3d.getLegendItems();
            assertEquals(d3d.getSeriesCount(), legends.getItemCount());
            
            for (int i = 0; i < legends.getItemCount(); i++) {
                LegendItem item = legends.get(i);
                assertEquals(LegendItem.class, item.getClass());
                assertEquals(d3d.getSeriesKey(i).toString(), item.getLabel());
                assertEquals(d3d, item.getDataset());
                assertEquals(0, item.getDatasetIndex());
                assertEquals(d3d.getSeriesKey(i).toString(), item.getSeriesKey().toString());
            }
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
}
