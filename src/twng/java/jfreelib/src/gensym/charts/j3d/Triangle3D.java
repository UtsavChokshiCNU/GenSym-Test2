package gensym.charts.j3d;

import org.jfree.data.Range;

/**
 * 3D triangle class, has three 3d points ABC
 */
public class Triangle3D implements Cloneable {

    /** The triangle A point */
    private Point3D a;

    /** The triangle B point */
    private Point3D b;

    /** The triangle C point */
    private Point3D c;

    private Range zRange = null;

    /**
     * Constructor
     * @param p1 "A" value of the ABC triangle
     * @param p2 "B" value of the ABC triangle
     * @param p3 "C" value of the ABC triangle
     */
    public Triangle3D(Point3D a, Point3D b, Point3D c) {
        this.a = a;
        this.b = b;
        this.c = c;

        zRange = Range.expandToInclude(zRange, a.getZ());
        zRange = Range.expandToInclude(zRange, b.getZ());
        zRange = Range.expandToInclude(zRange, c.getZ());
    }

    /**
     * Gets the A point
     * @return the A point
     */
    public Point3D getA() {
        return a;
    }

    /**
     * Gets the B point
     * @return the B point
     */
    public Point3D getB() {
        return b;
    }

    /**
     * Gets the C point
     * @return the C point
     */
    public Point3D getC() {
        return c;
    }

    /**
     * Gets range of the triangle z values
     * @return range of z values
     */
    public Range getZRange() {
        return zRange;
    }

    /**
     * {@inheritDoc}
     * Creates a new object of the same class and with the
     * same contents as this object.
     * @return     a clone of this instance.
     * @exception  CloneNotSupportedException if there are clonning errors.
     */
    public Object clone() throws CloneNotSupportedException {
        return super.clone();
    }

    /**
     * Determines whether or not two triangles are equal. Two instances of
     * <code>Triangle3D</code> are equal if the values of their
     * <code>A</code>, <code>B</code> and <code>C</code> member fields,
     * representing their position in the coordinate space, are the same.
     * @param obj an object to be compared with this <code>Triangle3D</code>
     * @return <code>true</code> if the object to be compared is
     *         an instance of <code>Triangle3D</code> and has
     *         the same values; <code>false</code> otherwise.
     */
    public boolean equals(Object obj) {
        if (obj instanceof Triangle3D) {
            Triangle3D triangle = (Triangle3D) obj;
            return (this == triangle) || (getA().equals(triangle.getA())
                    && getB().equals(triangle.getB()) && getC().equals(triangle.getC()));
        }
        return false;
    }

    /**
     * Returns average Z value of primitive
     * @return the average Z value of primitive
     */
    public double averageZValue() {
    	return (getA().getZ() + getB().getZ() + getC().getZ()) / 3;
    }
}
