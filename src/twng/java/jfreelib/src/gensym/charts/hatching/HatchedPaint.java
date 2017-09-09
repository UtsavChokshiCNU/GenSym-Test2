package gensym.charts.hatching;

import java.awt.Color;
import java.awt.Paint;
import java.awt.PaintContext;
import java.awt.Rectangle;
import java.awt.RenderingHints;
import java.awt.geom.AffineTransform;
import java.awt.geom.Rectangle2D;
import java.awt.image.BufferedImage;
import java.awt.image.ColorModel;

/**
 * Simple hatched paint class
 */
public class HatchedPaint implements Paint {

    /** Draw no line */
    public static final int LINE_NONE = 0;
    /** Draw horizontal line */
    public static final int HORIZONTAL_LINE = 0x1;
    /** Draw vertical line */
    public static final int VERTICAL_LINE = 0x2;
    /** Draw diagonal line from left bottom corner to right upper corner */
    public static final int LB_RU_DIAGONAL_LINE = 0x4;
    /** Draw diagonal line from left upper corner to right bottom corner */
    public static final int LU_RB_DIAGONAL_LINE = 0x8;

    /** Foreground color that was set */
    private Color foregroundColor = Color.BLACK;
    /** Background color that was set */
    private Color backgroundColor = Color.WHITE;
    /** Hatch style mask that was set */
    private int hatchStyleMask = LINE_NONE;

    /** Paint context */
    private PaintContext theContext;
    
    /** Saved image */
    private HatchedImage savedImage;

    /**
     * Constructor with specified hatch style
     * @param style  the hatch style mask to set
     */
    public HatchedPaint(int style) {
        this(style, null, null);
    }

    /**
     * Constructor with specified parameters style, foreground and background color 
     * @param style  the hatch style mask to set
     * @param fgColor the foreground color
     * @param bgColor the background color
     */
    public HatchedPaint(int style, Color fgColor, Color bgColor) {
        if (fgColor != null) {
            foregroundColor = fgColor;
        }
        if (bgColor != null) {
            backgroundColor = bgColor;
        }
        hatchStyleMask = style;
        theContext = new HatchedPaintContext(this);
    }

    /**
     * Gets foreground color
     * @return the foregroundColor
     */
    public Color getForegroundColor() {
        return foregroundColor;
    }

    /**
     * Sets foreground color
     * @param foregroundColor the foregroundColor to set
     */
    public void setForegroundColor(Color fgColor) {
        if (fgColor != null) {
            foregroundColor = fgColor;
        } else {
            foregroundColor = Color.BLACK;
        }
    }

    /**
     * Gets background color
     * @return the backgroundColor
     */
    public Color getBackgroundColor() {
        return backgroundColor;
    }

    /**
     * Sets background color 
     * @param backgroundColor the backgroundColor to set
     */
    public void setBackgroundColor(Color bgColor) {
        if (bgColor != null) {
            backgroundColor = bgColor;
        } else {
            backgroundColor = Color.WHITE;
        }
    }

    /**
     * Gets hatch style mask
     * @return the hatchStyle mask
     */
    public int getHatchStyleMask() {
        return hatchStyleMask;
    }
    
    /**
     * Sets hatch style mask
     * @param hStyleMask the style mask to set
     */
    public void setHatchStyleMask(int hStyleMask) {
        hatchStyleMask = hStyleMask;
    }

    /**
     * Gets hatched image with specified width and height  
     * @param width the width of image
     * @param height the height of image
     */
    public BufferedImage getImage(int x, int y, int width, int height) {
        HatchedImage image = savedImage;
        if ((image == null) || (image.getWidth() < width) || (image.getHeight() < height)) {
            image = new HatchedImage(x, y, width, height);
            savedImage = image;
        }
        image.fillImage(backgroundColor);
        image.setPenColor(foregroundColor);
        
        if ((hatchStyleMask & HORIZONTAL_LINE) > 0) {
            image.drawHorizontalLines();
        }
        if ((hatchStyleMask & VERTICAL_LINE) > 0) {
            image.drawVerticalLines();
        }
        if ((hatchStyleMask & LB_RU_DIAGONAL_LINE) > 0) {
            image.drawLeftBottomRightUpperDiagLines();
        }
        if ((hatchStyleMask & LU_RB_DIAGONAL_LINE) > 0) {
            image.drawLeftUpperRightBottomDiagLines();
        }
        return image;
    }

    /**
     * {@inheritDoc}
     */
    public PaintContext createContext(ColorModel cm, Rectangle deviceBounds,
            Rectangle2D userBounds, AffineTransform xform, RenderingHints hints) {
        return theContext;
    }

    /**
     * {@inheritDoc}
     */
    public int getTransparency() {
        return (theContext.getColorModel()).getTransparency();
    }
}
