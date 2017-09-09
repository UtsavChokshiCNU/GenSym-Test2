package gensym.charts.hatching;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;

/**
 * Simple Hatched buffered image class
 */
public class HatchedImage extends BufferedImage {

    /** Reference on Graphics2D */
    private Graphics2D g2;
    /** The X coordinate of left upper corner of image */
    private int x;
    /** The Y coordinate of left upper corner of image */
    private int y;
    
    /** The distance between 2 lines on image */
    public static final int linesDistance = 8;
    /** The half of distance between 2 lines on image */
    private static int halfDistance = linesDistance /2 + (linesDistance % 2);
    
    /**
     * Constructor with specified width, height and background color
     * @param width
     * @param height
     * @param bgColor the background color
     */
    public HatchedImage(int x, int y, int width, int height) {
        super(Math.max(width, height), Math.max(width, height), BufferedImage.TYPE_INT_ARGB);
        this.x = x;
        this.y = y;
        g2 = createGraphics();
    }

    /** Fill image by specified color */
    protected void fillImage(Color bgColor) {
        g2.setColor(bgColor);
        g2.fillRect(0, 0, getWidth(), getHeight());
    }
    
    /**
     * Set Pen color
     * @param color
     */
    protected void setPenColor(Color color) {
        if (g2.getColor() != color) {
            g2.setColor(color);
        }
    }
    
    /**
     * Gets first line coordinate aligned by half line distance
     * @param coord the coordinate 
     * @return the first line coordinate
     */
    protected int getStartValue(int coord) {
        int start = halfDistance - (coord % linesDistance);
        return start < 0 ? start + linesDistance : start;
    }
    
    /**
     * Horizontal line draw
     */
    protected void drawHorizontalLines() {
        for (int iy = getStartValue(y); iy < getHeight(); iy += linesDistance) {
            g2.drawLine(0, iy, getWidth(), iy);
        }
    }
    
    /**
     * Vertical line draw 
     */
    protected void drawVerticalLines() {
        for (int ix = getStartValue(x); ix < getWidth(); ix += linesDistance) {
            g2.drawLine(ix, 0, ix, getHeight());
        }
    }
    
    /**
     * Gets coordinates of diagonal line from left upper corner to right bottom corner 
     * @return an array of point coordinates {x1, y1, x2, y2}
     */
    protected void drawLeftUpperRightBottomDiagLines() {
        for (int ix = getStartValue(x); ix < getWidth(); ix += linesDistance) {
            g2.drawLine(ix, 0, getWidth(), getHeight()-ix);
        }
        for (int iy = linesDistance - getStartValue(x); iy < getHeight(); iy += linesDistance) {
            g2.drawLine(0, iy, getWidth()-iy, getHeight());
        }
    }
    
    /**
     * Gets coordinates of diagonal line from left bottom corner to right upper corner 
     * @return an array of point coordinates {x1, y1, x2, y2}
     */
    protected void drawLeftBottomRightUpperDiagLines() {
        for (int ixy = getStartValue(x); ixy < getWidth(); ixy += linesDistance) {
            g2.drawLine(0, ixy, ixy, 0);
            g2.drawLine(ixy, getHeight(), getWidth(), ixy);
        }
    }
}
