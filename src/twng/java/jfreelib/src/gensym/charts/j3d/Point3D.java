package gensym.charts.j3d;

/**
 * 3D point class, has three coordinates (x,y,z)
 */
public class Point3D implements Cloneable {

    /** Serial VersionUID */
    private static final long serialVersionUID = -8149113087665498616L;
    
    /** The X coordinate of this <code>Point3D</code> */
    protected Double x;
    
    /** The Y coordinate of this <code>Point3D</code> */
    protected Double y;
    
    /** The Z coordinate of this <code>Point3D</code> */
    protected Double z;

    /**
     * Constructs and initializes a <code>Point3D</code> with
     * coordinates (0, 0).
     */
    public Point3D() {
        this(0, 0, 0);
    }

    /**
     * Constructs and initializes a <code>Point3D</code> with the
     * specified coordinates.
     * 
     * @param x the X coordinate of the newly
     *          constructed <code>Point3D</code>
     * @param y the Y coordinate of the newly
     *          constructed <code>Point3D</code>
     * @param z the Z coordinate of the newly
     *          constructed <code>Point3D</code>
     */
    public Point3D(double x, double y, double z) {
        this.x = new Double(x);
        this.y = new Double(y);
        this.z = new Double(z);
    }

    /**
     * Get X coordinate of this <code>Point3D</code>.
     */
    public Double getX() {
        return x;
    }

    /**
     * Get Y coordinate of this <code>Point3D</code>.
     */
    public Double getY() {
        return y;
    }

    /**
     * Get Z coordinate of this <code>Point3D</code>.
     */
    public Double getZ() {
        return z;
    }

    /**
     * Creates a new object of the same class and with the
     * same contents as this object.
     * @return     a clone of this instance.
     * @exception  CloneNotSupportedException if there are clonning errors.
     */
    public Object clone() throws CloneNotSupportedException {
        return super.clone();
    }

    /**
     * Determines whether or not two points are equal. Two instances of
     * <code>Point3D</code> are equal if the values of their 
     * <code>x</code>, <code>y</code> and <code>z</code> member fields, 
     * representing their position in the coordinate space, are the same.
     * @param obj an object to be compared with this <code>Point3D</code>
     * @return <code>true</code> if the object to be compared is
     *         an instance of <code>Point3D</code> and has
     *         the same values; <code>false</code> otherwise.
     */
    public boolean equals(Object obj) {
        if (obj instanceof Point3D) {
            Point3D p3d = (Point3D) obj;
            return (this == p3d) || (getX().equals(p3d.getX()) && getY().equals(p3d.getY()) && getZ().equals(p3d.getZ()));
        }
        return false;
    }
    
    /**
     * Calculates absolute value of the point
     * @return the point absolute value
     */
    public double length() {
        return Math.sqrt(x*x + y*y + z*z);
    }
    
    /**
     * Calculates dot product
     * @param right point for dot product
     * @return the dot product
     */
    public double dotProduct(Point3D right) {
        return (x * right.x + y * right.y + z * right.z); 
    }
}
