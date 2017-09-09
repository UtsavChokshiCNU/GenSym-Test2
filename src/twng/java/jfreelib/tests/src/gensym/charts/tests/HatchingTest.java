package gensym.charts.tests;

import java.awt.Color;
import java.awt.PaintContext;
import java.awt.Rectangle;
import java.awt.RenderingHints;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.awt.image.ColorModel;
import java.awt.image.Raster;
import junit.framework.TestCase;
import gensym.charts.hatching.*;
import gensym.charts.properties.hatching.SubsetHatchProperty;

/**
 * Tests hatching
 * @param <HatchedImage>
 */
public class HatchingTest extends TestCase {

    /**
     * Creating hatched paint test
     */
    public void testCreateHatchedPaint() {
        try {
            HatchedPaint hatchPaint = new HatchedPaint(HatchedPaint.HORIZONTAL_LINE, Color.BLACK, Color.RED);
            assertNotNull(hatchPaint);
            assertTrue(hatchPaint instanceof HatchedPaint);
            assertEquals(HatchedPaint.HORIZONTAL_LINE, hatchPaint.getHatchStyleMask());
            assertEquals(Color.BLACK, hatchPaint.getForegroundColor());
            assertEquals(Color.RED, hatchPaint.getBackgroundColor());

            hatchPaint = new HatchedPaint(HatchedPaint.LINE_NONE);
            assertEquals(HatchedPaint.LINE_NONE, hatchPaint.getHatchStyleMask());
            assertNotNull(hatchPaint.getForegroundColor());
            assertNotNull(hatchPaint.getBackgroundColor());

            Color cl = Color.DARK_GRAY;
            hatchPaint.setForegroundColor(cl);
            assertEquals(hatchPaint.getForegroundColor(), cl);
            hatchPaint.setForegroundColor(null);
            assertEquals(hatchPaint.getForegroundColor(), Color.BLACK);
            cl = Color.GREEN;
            hatchPaint.setBackgroundColor(cl);
            assertEquals(hatchPaint.getBackgroundColor(), cl);
        } catch (Exception e) {
            fail("Exception during running: " + e.getMessage());
        }
    }
    
    /**
     * Seters tests
     */
    public void testSetMethods() {
        HatchedPaint hatchPaint = new HatchedPaint(HatchedPaint.LINE_NONE);

        int styleMask = SubsetHatchProperty.getHatchStyleMaskFromPEHS(SubsetHatchProperty.PEHS_DIAGCROSS);
        hatchPaint.setHatchStyleMask(styleMask);
        assertEquals(hatchPaint.getHatchStyleMask(), styleMask);

        styleMask = SubsetHatchProperty.getHatchStyleMaskFromPEHS(SubsetHatchProperty.PEHS_CROSS);
        hatchPaint.setHatchStyleMask(styleMask);
        assertEquals(hatchPaint.getHatchStyleMask(), styleMask);        
        
        hatchPaint.setForegroundColor(Color.RED);
        assertEquals(Color.RED, hatchPaint.getForegroundColor());
        
        hatchPaint.setForegroundColor(null);
        assertEquals(Color.BLACK, hatchPaint.getForegroundColor()); //default
        
        hatchPaint.setBackgroundColor(Color.BLUE);
        assertEquals(hatchPaint.getBackgroundColor(), Color.BLUE);

        hatchPaint.setBackgroundColor(null);
        assertEquals(Color.WHITE, hatchPaint.getBackgroundColor()); //default
    }

    /**
     * Drawing test
     */
    public void testDrawing() {
        Color foregroundColor = Color.CYAN;
        Color backgroundColor = Color.WHITE;
        HatchedPaint hatchPaint = new HatchedPaint(HatchedPaint.LINE_NONE, foregroundColor, backgroundColor);
        BufferedImage image = hatchPaint.getImage(0, 0, 32, 21);
        assertNotNull(image);
        assertTrue(image instanceof HatchedImage);
        assertEquals(32, image.getWidth());
        assertEquals(32, image.getHeight());
        assertEquals(backgroundColor.getRGB(), image.getRGB(0, 0));

        hatchPaint.setHatchStyleMask(HatchedPaint.HORIZONTAL_LINE);
        image = hatchPaint.getImage(0, 0, 2, 21);
        assertEquals(32, image.getWidth());
        assertEquals(32, image.getHeight());

        assertEquals(backgroundColor.getRGB(), image.getRGB(1, 1));
        assertEquals(foregroundColor.getRGB(), image.getRGB(1, 4));
        
        hatchPaint.setHatchStyleMask(HatchedPaint.VERTICAL_LINE);
        image = hatchPaint.getImage(0, 0, 2, 21);
        assertEquals(foregroundColor.getRGB(), image.getRGB(4, 1));
        assertEquals(foregroundColor.getRGB(), image.getRGB(4, 20));
        
        hatchPaint.setHatchStyleMask(HatchedPaint.LB_RU_DIAGONAL_LINE);
        image = hatchPaint.getImage(0, 0, 2, 21);
        assertEquals(backgroundColor.getRGB(), image.getRGB(0, 3));
        assertEquals(foregroundColor.getRGB(), image.getRGB(0, 4));
        assertEquals(backgroundColor.getRGB(), image.getRGB(0, 5));
        assertEquals(foregroundColor.getRGB(), image.getRGB(4, 0));
        assertEquals(foregroundColor.getRGB(), image.getRGB(8, 4));
        assertEquals(foregroundColor.getRGB(), image.getRGB(4, 8));
        assertEquals(foregroundColor.getRGB(), image.getRGB(12, 0));

        hatchPaint.setHatchStyleMask(HatchedPaint.LU_RB_DIAGONAL_LINE);
        image = hatchPaint.getImage(0, 0, 2, 21);
        assertEquals(backgroundColor.getRGB(), image.getRGB(0, 3));
        assertEquals(foregroundColor.getRGB(), image.getRGB(0, 4));
        assertEquals(backgroundColor.getRGB(), image.getRGB(0, 5));
        assertEquals(foregroundColor.getRGB(), image.getRGB(4, 8));
        assertEquals(foregroundColor.getRGB(), image.getRGB(8, 4));
        assertEquals(foregroundColor.getRGB(), image.getRGB(2, 6));
        assertEquals(foregroundColor.getRGB(), image.getRGB(8, 12));
    }
    
    /**
     * Interface methods tests
     */
    public void testPaintInterfaceMethods() {
        Color foregroundColor = Color.CYAN;
        Color backgroundColor = Color.WHITE;
        HatchedPaint hatchPaint = new HatchedPaint(HatchedPaint.HORIZONTAL_LINE, foregroundColor, backgroundColor);
        BufferedImage bufImage = new BufferedImage(8, 8, BufferedImage.TYPE_INT_ARGB);
        
        PaintContext context = hatchPaint.createContext(bufImage.getColorModel(),
             bufImage.getRaster().getBounds(), new Rectangle.Double(0,0,bufImage.getWidth(), bufImage.getHeight()),
             new AffineTransform(), new RenderingHints(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_NEAREST_NEIGHBOR));
        assertNotNull(context);
        assertTrue(context instanceof HatchedPaintContext);
        
        Raster raster = context.getRaster(0, 0, 8, 10);
        assertNotNull(raster);
        assertEquals(10, raster.getWidth());
        assertEquals(10, raster.getHeight());
        
        ColorModel cm = context.getColorModel();
        assertEquals(backgroundColor.getRGB(), cm.getRGB(raster.getDataElements(0, 3, null)));
        assertEquals(foregroundColor.getRGB(), cm.getRGB(raster.getDataElements(0, 4, null)));
        assertEquals(foregroundColor.getRGB(), cm.getRGB(raster.getDataElements(2, 4, null)));
        assertEquals(foregroundColor.getRGB(), cm.getRGB(raster.getDataElements(8, 4, null)));

        assertEquals(ColorModel.getRGBdefault().getTransparency(), hatchPaint.getTransparency());
        
        context.dispose();
    }
}
