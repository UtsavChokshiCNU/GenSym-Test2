package gensym.charts.gradients;

import java.awt.*;
import java.awt.geom.Rectangle2D;
import java.awt.geom.Point2D;

/**
 * Gradient style
 */
public class GradientStyle {

    /**
     * NoGradient
     */
    public final static int PEGS_NO_GRADIENT = 0;

    /**
     * Gradient Top to Bottom
     */
    public final static int PEGS_VERTICAL = 1;

    /**
     * Gradient Left to Right
     */
    public final static int PEGS_HORIZONTAL = 2;

    /**
     * Linear Bar Vertical
     */
    public final static int PEGS_LINEAR_BAR_VERTICAL = 3;

    /**
     * Linear Bar Horizontal
     */
    public final static int PEGS_LINEAR_BAR_HORIZONTAL = 4;

    /**
     * Linear Bar Downward
     */
    public final static int PEGS_LINEAR_BAR_DOWN = 5;

    /**
     * Linear Bar Upward
     */
    public final static int PEGS_LINEAR_BAR_UP = 6;

    /**
     * Linear Diagonal Downward
     */
    public final static int PEGS_LINEAR_DIAGONAL_DOWN = 7;

    /**
     * Linear Diagonal Upward
     */
    public final static int PEGS_LINEAR_DIAGONAL_UP = 8;

    /**
     * Rectangular Cross Pattern
     */
    public final static int PEGS_RECTANGLE_CROSS = 9;

    /**
     * Rectangular Plus Pattern
     */
    public final static int PEGS_RECTANGLE_PLUS = 10;

    /**
     * Radial, Bright Spot Centered
     */
    public final static int PEGS_RADIAL_CENTERED = 11;

    /**
     * Radial, Bright Spot Bottom Right
     */
    public final static int PEGS_RADIAL_BOTTOM_RIGHT = 12;

    /**
     * Radial, Bright Spot Top Right
     */
    public final static int PEGS_RADIAL_TOP_RIGHT = 13;

    /**
     * Radial, Bright Spot Bottom Left
     */
    public final static int PEGS_RADIAL_BOTTOM_LEFT = 14;

    /**
     * Radial, Bright Spot Top Left
     */
    public final static int PEGS_RADIAL_TOP_LEFT = 15;

    /**
     * Numbers ranging from 0.0 to 1.0 specifying the
     * distribution of colors along the gradient.
     * Simple means that gradient has one crossingfrom color to color.
     */
    public final static float[] simpleFractions = {0.0f, 1.0f};

    /**
     * Numbers ranging from 0.0 to 1.0 specifying the
     * distribution of colors along the gradient.
     * Full means that gradient has two crossingfrom color to color.
     */
    public final static float[] fullFractions = {0.0f, 0.5f, 1.0f};

    /**
     * Coord of X-axis begin of chart or plot
     */
    public static float x = 0;

    /**
     * Coord of Y-axis begin of chart or plot
     */
    public static float y = 0;

    /**
     * Width of the chart or plot
     */
    public static float width = 0;

    /**
     * Height of the chart or plot
     */
    public static float height = 0;

    /**
     * Array of colors corresponding to each fractional value (simpleFractions)
     */
    public static Color[] simpleColors = null;

    /**
     * Array of colors corresponding to each fractional value (fullFractions)
     */
    public static Color[] fullColors = null;

    /**
     * Initialize main values
     * @param area
     * @param values of the gradient
     * @return true, if gradient the these values could be applied
     */
    public static boolean initValues(Rectangle2D area, GradientValues values) {
        x = (float)area.getX();
        y = (float)area.getY();
        width = (float)area.getWidth();
        height = (float)area.getHeight();
        simpleColors = new Color[]{values.getStart(), values.getEnd()};
        fullColors = new Color[]{values.getStart(), values.getEnd(), values.getStart()};
        return height != 0 && width != 0;
    }

    /**
     * Gets GradientPaint by style property
     * @param area of the chart or plot
     * @param values gradient proprieties
     * @return Paint for future draw
     */
    public static final Paint getGradientPaint(Rectangle2D area, GradientValues values) {
        if ( !initValues(area, values) ) {
            return null;
        }
        switch (values.getStyle()) {
            case PEGS_NO_GRADIENT:
                return null;

            case PEGS_VERTICAL:
                Point2D start1 = new Point2D.Float(x, y);
                Point2D end1 = new Point2D.Float(x, y + height);
                return new LinearGradientPaint(start1, end1, simpleFractions, simpleColors);

            case PEGS_HORIZONTAL:
                Point2D start2 = new Point2D.Float(x, y + height);
                Point2D end2 = new Point2D.Float(x + width, y + height);
                return new LinearGradientPaint(start2, end2, simpleFractions, simpleColors);

            case PEGS_LINEAR_BAR_VERTICAL:
                Point2D start3 = new Point2D.Float(x, y);
                Point2D end3 = new Point2D.Float(x, y + height);
                return new LinearGradientPaint(start3, end3, fullFractions, fullColors);

            case PEGS_LINEAR_BAR_HORIZONTAL:
                Point2D start4 = new Point2D.Float(x, y);
                Point2D end4 = new Point2D.Float(x + width, y);
                return new LinearGradientPaint(start4, end4, fullFractions, fullColors);

            case PEGS_LINEAR_BAR_DOWN:
                Point2D start5 = new Point2D.Float(x, y);
                Point2D end5 = new Point2D.Float(x + width, y + height);
                return new LinearGradientPaint(start5, end5, fullFractions, fullColors);

            case PEGS_LINEAR_BAR_UP:
                Point2D start6 = new Point2D.Float(x, y + height);
                Point2D end6 = new Point2D.Float(x + width, y);
                return new LinearGradientPaint(start6, end6, fullFractions, fullColors);

            case PEGS_LINEAR_DIAGONAL_DOWN:
                Point2D start7 = new Point2D.Float(x, y);
                Point2D end7 = new Point2D.Float(x + width, y + height);
                return new LinearGradientPaint(start7, end7, simpleFractions, simpleColors);

            case PEGS_LINEAR_DIAGONAL_UP:
                Point2D start8 = new Point2D.Float(x, y + height);
                Point2D end8 = new Point2D.Float(x + width, y);
                return new LinearGradientPaint(start8, end8, simpleFractions, simpleColors);

             // Need to implement this
            case PEGS_RECTANGLE_CROSS:
                return null;

             // Need to implement this
            case PEGS_RECTANGLE_PLUS:
                return null;

            case PEGS_RADIAL_CENTERED:
                return new RadialGradientPaint(x + width/2, y + height/2,
                        Math.min(width, height)/2, simpleFractions, simpleColors);
                
            case PEGS_RADIAL_BOTTOM_RIGHT:
                return new RadialGradientPaint(x + 5*width/6, y + 4*height/5,
                        2*Math.max(width, height)/3, simpleFractions, simpleColors);
                
            case PEGS_RADIAL_TOP_RIGHT:
                return new RadialGradientPaint(x + 5*width/6, y + height/5,
                        2*Math.max(width, height)/3, simpleFractions, simpleColors);
                
            case PEGS_RADIAL_BOTTOM_LEFT:
                return new RadialGradientPaint(x + width/6, y + 4*height/5,
                        2*Math.max(width, height)/3, simpleFractions, simpleColors);
                
            case PEGS_RADIAL_TOP_LEFT:
                return new RadialGradientPaint(x + width/6, y + height/5,
                        2*Math.max(width, height)/3, simpleFractions, simpleColors);
                
            default:
                return null;
        }
    }
}
