package gensym.charts.j3d.renderers;

import java.awt.BasicStroke;
import java.awt.Paint;
import java.awt.Shape;
import java.awt.Stroke;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;
import java.util.LinkedHashMap;
import java.util.Map;

import org.jfree.chart.LegendItem;
import gensym.charts.j3d.*;
import gensym.charts.j3d.primitives.*;

/**
 * Renderer for lines and shapes (points)
 */
public class LineAndShapeRenderer3D extends Renderer3D {

    /** Plotting method value: display just points */
    public static final int POINTS = 0;

    /** Plotting method value: display just lines */
    public static final int LINES = 1;

    /** Plotting method value: display points and lines*/
    public static final int POINTS_AND_LINES = 2;

    /** Default shape */
    public static final Shape DEFAULT_SHAPE = new Ellipse2D.Float(-2, -2, 4, 4);
    
    /** Entity shape */
    private static final Shape ENTITY_SHAPE = new Ellipse2D.Float(-1, -1, 2, 2);

    /** Legend line */
    public static final Shape LEGEND_LINE = new Line2D.Double(-7.0, 0.0, 7.0, 0.0);
    
    /** Legend stroke */
    public static final Stroke LEGEND_STROKE = new BasicStroke(1.0f);;

    /** Series shapes map */
    private Map<Integer, Shape> shapes = new LinkedHashMap<Integer, Shape>();

    /** Points showing flag */
    private boolean showPoints = true;

    /** Lines showing flag */
    private boolean showLines = true;
    
    /**
     * Constructor
     */
    public LineAndShapeRenderer3D() {
    }

    /**
     * Copy constructor
     */
    public LineAndShapeRenderer3D(Renderer3D renderer) {
        super(renderer);
    }

    /**
     * {@inheritDoc}
     */
    public Object3D createObject3D(Dataset3D dataset, int plottingMethod, int plottingDetails) {
        setPlottingMethod(plottingMethod);

        Object3D obj = new Object3D();
        if (isLinesVisible()) {
            fillLines(obj, dataset);
        }
        
        if (isLinesVisible() || isPointsVisible()) {
            fillPointsAndEntities(obj, dataset);
        }
        
        return obj;
    }

    /**
     * Sets plotting method: setup renderer values
     * @param plottingMethod new plotting method
     */
    private void setPlottingMethod(int plottingMethod) {
        switch (plottingMethod) {
            case POINTS:
                setPointsVisible(true);
                setLinesVisible(false);
                break;
            case LINES:
                setPointsVisible(false);
                setLinesVisible(true);
                break;
            case POINTS_AND_LINES:
            default:
                setPointsVisible(true);
                setLinesVisible(true);
                break;
        }
    }

    /**
     * Fills points
     * @param obj
     * @param dataset
     */
    private void fillPointsAndEntities(Object3D obj, Dataset3D dataset) {
        for (int series = 0; series < dataset.getSeriesCount(); series++) {
            Paint paint = getSeriesPaint(series);
            Paint outlinePaint = getSeriesOutlinePaint(series);
            Shape seriesShape = getSeriesShape(series);
            Series3D series3D = dataset.getSeries3D(series);
            
            for (int item = 0; item < series3D.getItemCount(); item++) {
                Point3D point = series3D.getPoint3D(item);
                
                Shape shape = ENTITY_SHAPE;
                if (isPointsVisible()) {
                    shape = seriesShape;
                }
                Point3DPrimitive primitive = new Point3DPrimitive(point, shape);
                primitive.setPaint(paint);
                primitive.setOutlinePaint(outlinePaint);
                primitive.setEntityData(new EntityData3D(point, series, item));

                obj.addPrimitive(primitive);
            }
        }
    }

    /**
     * Fills lines
     * @param obj
     * @param dataset
     */
    private void fillLines(Object3D obj, Dataset3D dataset) {
        for (int i = 0; i < dataset.getSeriesCount(); i++) {
            for (int j = 0; j < dataset.getSeries3D(i).getItemCount() - 1; j++) {
                Point3D A = dataset.getSeries3D(i).getPoint3D(j);
                Point3D B = dataset.getSeries3D(i).getPoint3D(j + 1);

                Line3DPrimitive primitive = new Line3DPrimitive(A, B);
                primitive.setPaint(getSeriesPaint(i));
                obj.addPrimitive(primitive);
            }
        }
    }
    
    /**
     * Sets series shape
     * @param series series index
     * @param shape the series shape
     */
    public void setSeriesShape(int series, Shape shape) {
        shapes.put(series, shape);
    }
    
    /**
     * Returns series shape
     * @param series series index
     * @return the series shape
     */
    public Shape getSeriesShape(int series) {
        Shape shape = shapes.get(series);
        return shape != null ? shape : DEFAULT_SHAPE;
    }
    
    /**
     * Tests if lines are visible
     * @return true if lines are visible
     */
    public boolean isLinesVisible() {
        return showLines;
    }
    
    /**
     * Sets lines visibility
     * @param visible the lines visibility flag
     */
    public void setLinesVisible(boolean visible) {
        showLines = visible;
    }

    /**
     * Tests if points are visible
     * @return true if points are visible
     */
    public boolean isPointsVisible() {
        return showPoints;
    }
    
    /**
     * Sets points visibility
     * @param visible the points visibility flag
     */
    public void setPointsVisible(boolean visible) {
        showPoints = visible;
    }
    
    /**
     * {@inheritDoc}
     */
    public LegendItem getLegendItem(String label, int series) {
        if (getSeriesPaint(series) == null) {
            return null;
        }
        Paint paint = getSeriesPaint(series);
        
        Paint outlinePaint = getSeriesOutlinePaint(series);
        boolean outline = true;
        if (outlinePaint == null) {
            outlinePaint = paint;
            outline = false;
        }
        
        return new LegendItem(label, label, "", "",
                isPointsVisible(), getSeriesShape(series), true, paint,
                outline, outlinePaint, LEGEND_STROKE, 
                isLinesVisible(), LEGEND_LINE, LEGEND_STROKE, paint);
    }
}
