package gensym.charts.j3d;

import java.awt.Color;

/**
 * Class Shade3D makes colors with shades
 */
public class Shade3D {

    /**
     * Gets color(with shade) by triangle sun, view point and initial color
     * @param a point of ABC triangle
     * @param b point of ABC triangle
     * @param c point of ABC triangle
     * @param clearColor initial color
     * @param sun sun point
     * @param viewPoint view point
     * @return new color with shade
     */
    public static Color getColor3Points(Triangle3D triangle, Color clearColor, Point3D sun, ViewPoint viewPoint) {

        Point3D normal = normal(triangle);
        double dot = normal.dotProduct(sun);
        if (normal.getZ() < 0) {
            dot = -dot;
        }
        double shade = (dot + 1.0) / 2.0;
        if (shade > 1) {
            shade = 1;
        }
        int red = (int) (clearColor.getRed() * shade);
        int green = (int) (clearColor.getGreen() * shade);
        int blue = (int) (clearColor.getBlue() * shade);

        return new Color(red, green, blue, clearColor.getAlpha());
    }

    /**
     * Gets color(with shade) by rectangle sun, view point and initial color
     * @param a point of ABCD rectangle
     * @param b point of ABCD rectangle
     * @param c point of ABCD rectangle
     * @param d point of ABCD rectangle
     * @param clearColor initial color
     * @param sun sun point
     * @param viewPoint view point
     * @return new color with shade
     */
    public static Color getColor4Points(Point3D a, Point3D b, Point3D c,
            Point3D d, Color clearColor, Point3D sun, ViewPoint viewPoint) {

        Color cl1 = getColor3Points(new Triangle3D(a, b, c), clearColor, sun, viewPoint);
        Color cl2 = getColor3Points(new Triangle3D(a, d, c), clearColor, sun, viewPoint);

        int red = (int) ((cl1.getRed() + cl2.getRed()) / 2);
        int green = (int) ((cl1.getGreen() + cl2.getGreen()) / 2);
        int blue = (int) ((cl1.getBlue() + cl2.getBlue()) / 2);

        return new Color(red, green, blue, clearColor.getAlpha());
    }

    /**
     * Calculates cross product of two Point3D
     * @param u first point 
     * @param v second point
     * @return calculated cross product
     */
    private static Point3D crossProduct(Point3D u, Point3D v) {
        return new Point3D(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
    }

    /**
     * Calculates normal for triangle
     * @return triangle normal
     */
    private static Point3D normal(Triangle3D triangle) {
        Point3D a = triangle.getA();
        Point3D b = triangle.getB();
        Point3D c = triangle.getC();
        
        Point3D bMinusA = new Point3D(b.getX() - a.getX(), b.getY() - a.getY(), b.getZ() - a.getZ());
        Point3D cMinusA = new Point3D(c.getX() - a.getX(), c.getY() - a.getY(), c.getZ() - a.getZ());
        Point3D product = crossProduct(bMinusA, cMinusA);

        double length = product.length();
        return new Point3D(product.x / length, product.y / length, product.z / length);
    }
}
