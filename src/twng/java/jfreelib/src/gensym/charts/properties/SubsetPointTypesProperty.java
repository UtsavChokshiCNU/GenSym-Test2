package gensym.charts.properties;

import gensym.charts.Chart3D;
import java.awt.Shape;
import java.awt.geom.AffineTransform;
import java.awt.geom.Ellipse2D;
import java.awt.geom.GeneralPath;
import java.awt.geom.Line2D;
import java.awt.geom.Rectangle2D;

import org.jfree.util.ShapeUtilities;

import gensym.charts.GraphChart;
import gensym.charts.JFreeChartHolder;
import gensym.charts.j3d.renderers.LineAndShapeRenderer3D;

/**
 * <b>subset-point-types</b> int property class.
 * Sets point type per each subset (series)
 */
public class SubsetPointTypesProperty extends PropValueBase<Integer> {
    /**
     * Point size
     */
    public static final float POINT_SIZE = 6;
    
    /**
     * Plus
     */
    public static final int PEPT_PLUS = 0;
    
    /**
     * Cross
     */
    public static final int PEPT_CROSS = 1;

    /**
     * Circle
     */
    public static final int PEPT_DOT = 2;

    /**
     * Solid Circle
     */
    public static final int PEPT_DOTSOLID = 3;
    
    /**
     * Square
     */
    public static final int PEPT_SQUARE = 4;

    /**
     * Solid Square
     */
    public static final int PEPT_SQUARESOLID = 5;

    /**
     * Diamond
     */
    public static final int PEPT_DIAMOND = 6;

    /**
     * Solid Diamond
     */
    public static final int PEPT_DIAMONDSOLID = 7;

    /**
     * Upward Triangle
     */
    public static final int PEPT_UPTRIANGLE = 8;

    /**
     * Solid Upward Triangle
     */
    public static final int PEPT_UPTRIANGLESOLID = 9;

    /**
     * Downward Triangle
     */
    public static final int PEPT_DOWNTRIANGLE = 10;

    /**
     * Solid Downward Triangle
     */
    public static final int PEPT_DOWNTRIANGLESOLID = 11;
    
    /**
     * Dash
     */
    public static final int PEPT_DASH = 72;

    /**
     * Pixel
     */
    public static final int PEPT_PIXEL = 73;

    /**
     * Arrow North
     */
    public static final int PEPT_ARROW_N = 92;

    /**
     * Arrow North East
     */
    public static final int PEPT_ARROW_NE = 93;

    /**
     * Arrow East
     */
    public static final int PEPT_ARROW_E = 94;

    /**
     * Arrow South East
     */
    public static final int PEPT_ARROW_SE = 95;

    /**
     * Arrow South
     */
    public static final int PEPT_ARROW_S = 96;

    /**
     * Arrow South West
     */
    public static final int PEPT_ARROW_SW = 97;

    /**
     * Arrow West
     */
    public static final int PEPT_ARROW_W = 98;

    /**
     * Arrow North West
     */
    public static final int PEPT_ARROW_NW = 99;

    /**
     * Constructor
     */
    public SubsetPointTypesProperty() {
        super(3270, "subset-point-types");
    }
    
    /**
     * Creates arrow shape
     * @param rotateAngle angle to rotate (in radians)
     * @param height arrow height
     * @return created arrow shape
     */
    private Shape createArrow(double rotateAngle, float height) {
        GeneralPath shape = new GeneralPath();
        shape.moveTo(-height / 2, 0);
        shape.lineTo(0, height / 2);
        shape.lineTo(height / 2, height / 2);
        shape.moveTo(0, height / 2);
        shape.lineTo(0, - height / 2);
        shape.closePath();
        
        AffineTransform rotate = new AffineTransform(0.0f, Math.cos(rotateAngle), Math.sin(rotateAngle),
                0.0f, 0.0f, 0.0f);
        
        return rotate.createTransformedShape(shape);
    }
    
    /**
     * Creates shape by specified point type
     * @param type point type
     * @return created shape
     */
    private Shape createShape(int type) {
        switch (type) {
        case PEPT_PLUS:
            return ShapeUtilities.createRegularCross(POINT_SIZE / 2, 1);
        case PEPT_CROSS:
            return ShapeUtilities.createRegularCross(POINT_SIZE / 2, 1);
        case PEPT_DOT:
        case PEPT_DOTSOLID:
            return new Ellipse2D.Float(-POINT_SIZE / 2, -POINT_SIZE / 2, POINT_SIZE, POINT_SIZE);
        case PEPT_SQUARE:
        case PEPT_SQUARESOLID:
            return new Rectangle2D.Float(-POINT_SIZE / 2, -POINT_SIZE / 2, POINT_SIZE, POINT_SIZE);
        case PEPT_DIAMOND:
        case PEPT_DIAMONDSOLID:
            return ShapeUtilities.createDiamond(POINT_SIZE / 2);
        case PEPT_UPTRIANGLE:
        case PEPT_UPTRIANGLESOLID:
            return ShapeUtilities.createUpTriangle(POINT_SIZE / 2);
        case PEPT_DOWNTRIANGLE:
        case PEPT_DOWNTRIANGLESOLID:
            return ShapeUtilities.createDownTriangle(POINT_SIZE / 2);
        case PEPT_DASH:
            return new Line2D.Float(-2, 0, 2, 0);
        case PEPT_PIXEL:
            return new Ellipse2D.Float(-0.5f, -0.5f, 1, 1);
        case PEPT_ARROW_N:
            return createArrow(0, POINT_SIZE);
        case PEPT_ARROW_NW:
            return createArrow(Math.PI / 4, POINT_SIZE);
        case PEPT_ARROW_W:
            return createArrow(Math.PI / 2, POINT_SIZE);
        case PEPT_ARROW_SW:
            return createArrow(3 * Math.PI / 4, POINT_SIZE);
        case PEPT_ARROW_S:
            return createArrow(Math.PI, POINT_SIZE);
        case PEPT_ARROW_SE:
            return createArrow(5 * Math.PI / 4, POINT_SIZE);
        case PEPT_ARROW_E:
            return createArrow(3 * Math.PI / 2, POINT_SIZE);
        case PEPT_ARROW_NE:
            return createArrow(7 * Math.PI / 4, POINT_SIZE);
        }
        return null;
    }
    
    /**
     * Tests if it needs to fill shape
     * @param type point type
     * @return true if it needs to fill shape
     */
    private boolean doFillShape(int type) {
        switch (type) {
        case PEPT_DOTSOLID:
        case PEPT_SQUARESOLID:
        case PEPT_DIAMONDSOLID:
        case PEPT_UPTRIANGLESOLID:
        case PEPT_DOWNTRIANGLESOLID:
            return true;
        }
        
        return false;
    }
    
    /**
     * {@inheritDoc}
     * Sets point type per each subset (series)
     */
    public void setValueImpl(JFreeChartHolder chart, int i, int j, Integer value) {
            Shape shape = createShape(value);
            if (shape != null) {
            if (chart.getChart() instanceof GraphChart) {
                GraphChart graph = (GraphChart) chart.getChart();
                graph.setSeriesPointShape(i, shape, doFillShape(value));
            } else if (chart.getChart() instanceof Chart3D) {
                Chart3D chart3D = (Chart3D) chart.getChart();
                if (chart3D.getPlot().getRenderer() instanceof LineAndShapeRenderer3D) {
                    LineAndShapeRenderer3D renderer =
                            (LineAndShapeRenderer3D)chart3D.getPlot().getRenderer();
                    renderer.setSeriesShape(i, shape);
                }
            }
        }
    }
}
