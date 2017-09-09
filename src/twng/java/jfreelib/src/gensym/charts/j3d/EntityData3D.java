package gensym.charts.j3d;

/**
 * 3D hot spot data
 */
public class EntityData3D {

    /** Hot spot point */
    private Point3D item;
    
    /** Series index */
    private int series;
    
    /** Point index */
    private int point;
    
    /**
     * Constructor
     * @param item hot spot item
     * @param series item series index
     * @param point item point index
     */
    public EntityData3D(Point3D item, int series, int point) {
        this.item = item;
        this.series = series;
        this.point = point;
    }
    
    /**
     * Returns item
     * @return the item
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
