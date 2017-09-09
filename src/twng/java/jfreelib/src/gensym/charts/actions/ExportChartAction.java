package gensym.charts.actions;

import gensym.charts.*;
import java.awt.Graphics2D;
import java.awt.GraphicsConfiguration;
import java.awt.GraphicsDevice;
import java.awt.GraphicsEnvironment;
import java.awt.RenderingHints;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.io.File;
import javax.imageio.ImageIO;
import org.w3c.dom.Element;

/**
 * Export chart action: exports chart to image file
 */
public class ExportChartAction implements IChartAction {

    /** jpeg file format */
    public static final int JPEG = 1;

    /** png file format */
    public static final int PNG = 2;

    /** bmp file format */
    public static final int BMP = 3;

    /** wmf file format */
    public static final int WMF = 4;

    /** svg file format */
    public static final int SVG = 5;

    /** Image pathname*/
    private String pathname;
    
    /** Image extension */
    private String ext;

    /** Image format */
    private int format;

    /** Image width */
    private int width;

    /** Image height */
    private int height;

    /**
     * {@inheritDoc}
     */
    public void execute(JFreeChartHolder chart) throws ChartActionException {

        if (parsePathname()) {

            BufferedImage img = new BufferedImage(chart.getWidth(),
                    chart.getHeight(), BufferedImage.TYPE_INT_RGB);
            Graphics2D g2 = img.createGraphics();
            chart.printAll(g2);

            BufferedImage resized = resize(img,
                    width, height, RenderingHints.VALUE_INTERPOLATION_BICUBIC);

            save(resized, pathname, ext);
        }
    }

    /**
     * {@inheritDoc}
     */
    public Object clone() throws CloneNotSupportedException {
        return super.clone();
    }

    /**
     * {@inheritDoc}
     */
    public String getName() {
        return "Export";
    }

    /**
     * {@inheritDoc}
     */
    public boolean isChartRequired() {
        return true;
    }

    /**
     * {@inheritDoc}
     */
    public void setData(Element data) throws ChartActionException {
        width = ChartsCommon.getIntValue(data, "width");
        height = ChartsCommon.getIntValue(data, "height");
        format = ChartsCommon.getIntValue(data, "format");
        pathname = ChartsCommon.getElementValue(data, "pathname");

        if (width <= 0) {
            width = 640;
        }

        if (height <= 0) {
            height = 480;
        }
    }

    /**
     * Save image into image-file
     * @param image image to save
     * @param filename name of the file
     * @param ext extension of the file
     */
    private void save(BufferedImage image, String filename, String ext) {
        File file = new File(filename + "." + ext);
        try {
            ImageIO.write(image, ext, file);  // ignore returned boolean
            } catch (Exception e) {
            System.out.println("Write error for " + file.getPath() +
                    ": " + e.getMessage());
        }
    }

    /**
     * Resize image
     * @param source image to be resized
     * @param destWidth new width
     * @param destHeight new height
     * @param interpolation interpolation object
     * @return resized image
     */
    private BufferedImage resize(BufferedImage source,
            int destWidth, int destHeight, Object interpolation) {
        double xScale = ((double) destWidth) / (double) source.getWidth();
        double yScale = ((double) destHeight) / (double) source.getHeight();
        GraphicsConfiguration gc = getDefaultConfiguration();
        BufferedImage result = gc.createCompatibleImage(destWidth, destHeight, source.getColorModel().getTransparency());
        Graphics2D g2d = null;
        try {
            g2d = result.createGraphics();
            g2d.setRenderingHint(RenderingHints.KEY_INTERPOLATION, interpolation);
            AffineTransform at =
                    AffineTransform.getScaleInstance(xScale, yScale);
            g2d.drawRenderedImage(source, at);
        } finally {
            if (g2d != null) {
                g2d.dispose();
            }
        }
        return result;
    }

    /**
     * Gets default graphics configuration
     * @return default GraphicsConfiguration
     */
    private GraphicsConfiguration getDefaultConfiguration() {
        GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
        GraphicsDevice gd = ge.getDefaultScreenDevice();
        return gd.getDefaultConfiguration();
    }

    /**
     * Sets extension by image format
     */
    private void setExtensionByFormat() {
        switch (format) {
            case JPEG:
                ext = "jpeg";
                break;
            case PNG:
                ext = "png";
                break;
            case BMP:
                ext = "bmp";
                break;
            case WMF:
                ext = "wmf";
                break;
            case SVG:
                ext = "svg";
                break;
            default:
                ext = "jpeg";
                break;
        }
    }

    /**
     * Parse pathname (extension, path)
     * @return true, if passed ok
     */
    private boolean parsePathname() {
        String[] tokens = pathname.split("[.]");
        if (tokens.length > 1) {
            ext = tokens[tokens.length - 1];
            pathname = "";
            for (int i = 0; i < tokens.length - 1; i++) {
                pathname += tokens[i];
            }
        } else if (tokens.length == 1) {
            setExtensionByFormat();
        } else {
            return false;
        }
        return true;
    }
}
