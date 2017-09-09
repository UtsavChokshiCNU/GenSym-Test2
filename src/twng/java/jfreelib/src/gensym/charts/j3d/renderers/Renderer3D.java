package gensym.charts.j3d.renderers;

import gensym.charts.j3d.Dataset3D;
import gensym.charts.j3d.Object3D;

import java.awt.Color;
import java.awt.Paint;
import java.util.LinkedHashMap;
import java.util.Map;

import org.jfree.chart.LegendItem;

/**
 * Renderer3D class depends for rendering 3D objects
 */
public abstract class Renderer3D {

    /** Need to display only wireframe */
    public static final int DETAILS_WIREFRAME = 0;

    /** For displaying need to use plotting method */
    public static final int DETAILS_PLOTTINGMETHOD = 1;

    /** For displaying need to use plotting method and axis */
    public static final int DETAILS_FULL = 2;
    
    /** Map of the series paints */
    private Map<Integer, Paint> paintsMap = new LinkedHashMap<Integer, Paint>();

    /** Map of the series outline paints */
    private Map<Integer, Paint> outlinePaintsMap = new LinkedHashMap<Integer, Paint>();

    /**
     * Constructor of the class, init paintsMap
     */
    public Renderer3D() {
        // initialize paints
        for (int i = 0; i < 100; i+= 9) {
            setSeriesPaint(i, Color.BLUE);
            setSeriesOutlinePaint(i, Color.BLUE);

            setSeriesPaint(i + 1, Color.CYAN);
            setSeriesOutlinePaint(i + 1, Color.CYAN);

            setSeriesPaint(i + 2, Color.GRAY);
            setSeriesOutlinePaint(i + 2, Color.GRAY);

            setSeriesPaint(i + 3, Color.GREEN);
            setSeriesOutlinePaint(i + 3, Color.GREEN);

            setSeriesPaint(i + 4, Color.MAGENTA);
            setSeriesOutlinePaint(i + 4, Color.MAGENTA);

            setSeriesPaint(i + 5, Color.ORANGE);
            setSeriesOutlinePaint(i + 5, Color.ORANGE);

            setSeriesPaint(i + 6, Color.PINK);
            setSeriesOutlinePaint(i + 6, Color.PINK);

            setSeriesPaint(i + 7, Color.RED);
            setSeriesOutlinePaint(i + 7, Color.RED);

            setSeriesPaint(i + 8, Color.YELLOW);
            setSeriesOutlinePaint(i + 8, Color.YELLOW);
        }
    }

    /**
     * Copy constructor
     */
    public Renderer3D(Renderer3D renderer) {
        this.paintsMap = renderer.paintsMap;
        this.outlinePaintsMap = renderer.outlinePaintsMap;
    }

    /**
     * Sets paint per series
     * @param series to set
     * @param paint of the series
     */
    public void setSeriesPaint(int series, Paint paint) {
        paintsMap.put(series, paint);
    }

    /**
     * Gets paint of the some series
     * @param series with paint
     * @return paint of the series
     */
    public Paint getSeriesPaint(int series) {
        return paintsMap.get(series);
    }

    /**
     * Sets outline paint per series
     * @param series series index
     * @param paint outline paint of the series
     */
    public final void setSeriesOutlinePaint(int series, Paint paint) {
        outlinePaintsMap.put(series, paint);
    }

    /**
     * Gets outline paint of the specified series
     * @param series series index
     * @return paint of the series
     */
    public Paint getSeriesOutlinePaint(int series) {
        return outlinePaintsMap.get(series);
    }

    /**
     * Created 3D object depending on current renderer instance
     */
    public abstract Object3D createObject3D(Dataset3D dataset, int plottingMethod, int plottingDetails);

    /**
     * Get legend item for specified series
     * @param series series index
     * @param label series label
     * @return legend item
     */
    public abstract LegendItem getLegendItem(String label, int series);
}
