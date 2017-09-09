package gensym.charts.j3d;

import java.awt.Shape;
import org.jfree.chart.entity.ChartEntity;

/**
 * A chart entity that represents one item within an
 * {@link gensym.charts.j3d.Plot3D}.
 */
public class XYZItemEntity extends ChartEntity {
    /** Generated serial version UID */
    private static final long serialVersionUID = -5232957498456290616L;

    /** Item of the entity */
    private Point3D item;

    /** Series index */
    private int series;
    
    /** Point index */
    private int point;

    /**
     * Constructor of the class
     * @param area Shape area to add
     * @param toolTipText tooltip text to add
     * @param urlText url to add
     * @param item item to add
     * @param series item series index
     * @param point item point index
     */
    public XYZItemEntity(Shape area, String toolTipText, String urlText, Point3D item, int series, int point) {
        super(area, toolTipText, urlText);
        this.item = item;
        this.series = series;
        this.point = point;
    }

    /**
     * Gets item of the entity
     * @return the entity item
     */
    public Point3D getItem() {
        return item;
    }
    
    /**
     * Returns point number
     * @return the point number
     */
    public int getPoint() {
        return point;
    }
    
    /**
     * Returns series index
     * @return the series index
     */
    public int getSeries() {
        return series;
    }
}
