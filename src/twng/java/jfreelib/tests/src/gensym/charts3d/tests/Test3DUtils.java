package gensym.charts3d.tests;

import java.awt.Frame;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.geom.Rectangle2D;

import gensym.charts.j3d.Dataset3D;
import gensym.charts.j3d.Point3D;
import gensym.charts.j3d.Series3D;

/**
 * Dataset3D test utilities
 */
public class Test3DUtils {

    /**
     * Enumerates for axes {X, Y, Z} 
     */
    public static enum AxisEnum {
        X, Y, Z
    };
    /**
     * Base value for X coordinates of Point3D
     */
    public static int X_BASE = 10;
    /**
     * Base value for Y coordinates of Point3D
     */
    public static int Y_BASE = 21;
    /**
     * Base value for Z coordinates of Point3D
     */
    public static int Z_BASE = 32;

    /**
     * Generating series key for specified index 
     * @param index the specified index
     * @return String series key
     */
    public static String genKeyByIndex(int index) {
        return "series" + index;
    }

    /**
     * Generating series description for specified index 
     * @param index the specified index
     * @return String series description
     */
    public static String genDescrByIndex(int index) {
        return "Series 3D #" + index;
    }

    /**
     * Generating double point position for specified axis and index 
     * @param a the specified axis
     * @param index the specified index
     * @return double value by point position
     */
    public static double genValueByIndex(AxisEnum a, int index) {
        switch (a) {
            case X:
                return index + X_BASE;
            case Y:
                return index + Y_BASE;
            case Z:
                return index + Z_BASE;
            default:
                return 0;
        }
    }

    /**
     * Get series items count
     * @param seriesCount the count of series 
     * @return int
     */
    public static int getItemCount(int seriesCount) {
        if (seriesCount > 1) {
            int sum = 0;
            for (int i = 1; i < seriesCount; i++) {
                sum = sum + i;
            }
            return sum;
        }
        return 0;
    }

    /**
     * Creates Series3D for the specified series index
     * @param series the specified series index
     * @return The Series3D object
     */
    public static Series3D doCreateSeries3D(int series) {
        Series3D s3d = new Series3D(genKeyByIndex(series), genDescrByIndex(series));
        for (int index = 0; index < series; index++) {
            Point3D p3d = new Point3D(genValueByIndex(AxisEnum.X, index),
                    genValueByIndex(AxisEnum.Y, index),
                    genValueByIndex(AxisEnum.Z, index));
            s3d.addPoint3D(p3d);
        }
        return s3d;
    }

    /**
     * Creates simple dataset, subsets*points size
     * @param subsets subsets quantity to add
     * @param points points quantity to add
     * @param flag false if points must have zero z value
     * @return Dataset3D to test
     */
    public static Dataset3D doCreateSimpleDataset(int subsets, int points, boolean flag) {
        Dataset3D dataset = new Dataset3D();

        for (int s = 0; s < subsets; s++) {
            Series3D series = new Series3D("series" + s);
            for (int p = 0; p < points; p++) {
                double x = s;
                double y = p;
                double z = flag ? s*p : 0;
                series.addPoint3D(new Point3D(x, y, z));
            }
            dataset.addSeries(series);
        }
        return dataset;
    }

    /**
     * Creates Dataset3D with data for specified series
     * @param series the specified series count
     * @return The Dataset3D object
     */
    public static Dataset3D doCreateDataset3DWithData(int series) {
        Dataset3D d3d = new Dataset3D();
        for (int i = 0; i < series; i++) {
            d3d.addSeries(doCreateSeries3D(i));
        }
        return d3d;
    }
    
    /**
     * Get Graphics2D for frame (100 x 100)
     * @return The Graphics2D instance
     */
    public static Graphics2D genGraphics2D() {
        Frame f = new Frame();
        f.setBounds((Rectangle)genRectangle2D());
        f.setVisible(true);
        return (Graphics2D) f.getGraphics().create(); 
    }

    /**
     * Get Rectangle2D for Rectangle (100 x 100)
     * @return The Rectangle instance as Rectangle2D
     */
    public static Rectangle2D genRectangle2D() {
        return new Rectangle(0, 0, 100, 100); 
    }
    
    /**
     * Get Sun Point3D
     * @return Point3D
     */
    public static Point3D defaultSunPoint() {
        return new Point3D(-0.57735, -0.57735, 0.57735);
    }
}
