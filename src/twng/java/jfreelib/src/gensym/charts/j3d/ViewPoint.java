package gensym.charts.j3d;

import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.util.ArrayList;
import java.util.List;

import org.jfree.data.Range;

public class ViewPoint {

    /** Rotation angle around X axis */
    private double phi = 0;

    /** Rotation angle around Y axis */
    private double xi = 0;

    /** Rotation angle around Z axis */
    private double rho = 10;

    /** Zooming factor */
    private double zoom = 1;
    
    /** Scaling factor for X, Y and Z axis */
    private Point3D scaling = new Point3D(1, 1, 1);

    /** User zoom value */
    private double userZoom = 1;

    /**
     * Rotation and zooming matrix
     *  [RotationX]*[RotationY]*[RotationZ]*[Zoom]
     */
    private double[][] matrix;

    /** Camera distance */
    private double distance = -1000;

    /** Moving point */
    private Point3D movingPoint = new Point3D();

    /** User moving point */
    private Point2D userMoving = new Point2D.Double(0, 0);


    /** Screen moving point */
    private Point2D screenMoving = new Point2D.Double(0, 0);

    /**
     * Constructor
     */
    public ViewPoint() {
        updateMatrix();
    }
    
    /**
     * Updates rotation and zooming matrix
     */
    private void updateMatrix() {
        double sinPhi = Math.sin(phi);
        double cosPhi = Math.cos(phi);
        double sinXi = Math.sin(xi);
        double cosXi = Math.cos(xi);
        double sinRho = Math.sin(rho);
        double cosRho = Math.cos(rho);
        matrix = new double[][]{{cosXi*cosRho, cosXi*sinRho, -sinXi, 0},
                {(sinPhi*sinXi*cosRho-cosPhi*sinRho), (sinPhi*sinXi*sinRho+cosPhi*cosRho), sinPhi*cosXi, 0},
                {(cosPhi*sinXi*cosRho+sinPhi*sinRho), (cosPhi*sinXi*sinRho-sinPhi*cosRho), cosPhi*cosXi, 0},
                {0, 0, 0, 1}};
    }
    /**
     * Sets parameter phi, the rotation angle around X axis
     * @param phi he phi angle
     */
    public void setPhi(double phi) {
        this.phi = phi;
        updateMatrix();
    }

    /**
     * Gets parameter phi, the rotation angle around X axis.
     * @return the phi angle
     */
    public double getPhi() {
        return phi;
    }

    /**
     * Sets parameter xi, the rotation angle around Y axis.
     * @param xi he xi angle
     */
    public void setXi(double xi) {
        this.xi = xi;
        updateMatrix();
    }

    /**
     * Gets parameter xi, the rotation angle around Y axis.
     * @return he xi angle
     */
    public double getXi() {
        return xi;
    }
	
    /**
     * Sets parameter rho, the rotation angle around Z axis.
     * @param rho the rho angle
     */
    public void setRho(double rho) {
        this.rho = rho;
        updateMatrix();
    }

    /**
     * Gets parameter rho, the rotation angle around Z axis.
     * @return the rho angle
     */
    public double getRho() {
        return rho;
    }

    /**
     * Sets zoom parameter. Should be about zero.
     * @param zoom the zoom value
     */
    public void setZoom(double zoom) {
        if (zoom < 0) {
            throw new RuntimeException("Zoom parameter should be about zero");
        }
        userZoom = zoom;
    }

    /**
     * Gets zoom parameter.
     * @return zoom value
     */
    public double getZoom () {
        return userZoom;
    }

    /**
     * Transform Triangle3D to the new one according to parameters phi, xi, rho and zoom.
     * @param triangle triangle to transform
     * @return the transformed triangle
     */
    public Triangle3D transform(Triangle3D triangle) {        
        return new Triangle3D(transform(triangle.getA()),
                transform(triangle.getB()), transform(triangle.getC()));
    }

    /**
     * Transform Point3D to the new one according to parameters phi, xi, rho and zoom.
     * @param point point to transform
     * @return the transformed point
     */
    public Point3D transform(Point3D point) {
        return transform(point, true);
    }

    /**
     * Transform Point3D to the new one according to parameters phi, xi, rho and zoom.
     * @param point point to transform
     * @param useUserSettings user setting usage flag
     * @return the transformed point
     */
    public Point3D transform(Point3D point, boolean useUserSettings) {
        double dx = useUserSettings ? movingPoint.getX() : 0;
        double dy = useUserSettings ? movingPoint.getY() : 0;
        double dz = useUserSettings ? movingPoint.getZ() : 0;
	
        double pointX = point.getX() - dx;
        double pointY = point.getY() - dy;
        double pointZ = point.getZ() - dz;
        double x = matrix[0][0] * pointX * scaling.getX() + matrix[0][1] * pointY * scaling.getY() + matrix[0][2] * pointZ * scaling.getZ();
        double y = matrix[1][0] * pointX * scaling.getX() + matrix[1][1] * pointY * scaling.getY() + matrix[1][2] * pointZ * scaling.getZ();
        double z = matrix[2][0] * pointX * scaling.getX() + matrix[2][1] * pointY * scaling.getY() + matrix[2][2] * pointZ * scaling.getZ();

        double factor = useUserSettings ? zoom * userZoom : 1;

        return new Point3D(x * factor, y * factor, z * factor);
    }

    /**
     * Converts 3D coordinates to screen coordinates
     * @param point the point to convert
     * @return screen coordinates of 3D point
     */
    public Point2D toScreen(Point3D point) {
        double k = (1 / (1 - (point.z / distance)));
        double x = k * point.x + screenMoving.getX();
        double y = k * point.y + screenMoving.getY();
        return new Point2D.Double(x + userMoving.getX(), y + userMoving.getY());
    }
    
    /**
     * Moved 3D objects to along X axis
     * @param x the moving value
     */
    public void moveToX(double x) {
        movingPoint = new Point3D(x, movingPoint.getY(), movingPoint.getZ());
    }

    /**
     * Moved 3D objects to along Y axis
     * @param y the moving value
     */
    public void moveToY(double y) {
        movingPoint = new Point3D(movingPoint.getX(), y, movingPoint.getZ());
    }

    /**
     * Moved 3D objects to along Z axis
     * @param z the moving value
     */
    public void moveToZ(double z) {
        movingPoint = new Point3D(movingPoint.getX(), movingPoint.getY(), z);
    }
    
    /**
     * @param xSize the X data size
     * @param ySize the Y data size
     * @param zSize the Z data size
     * @param area area to fit 
     * @return new scaling value
     */
    private Point3D correctScaling(double xSize, double ySize, double zSize, Rectangle2D area) {
    	double scaleX = 1; 
    	double scaleY = 1;
    	double scaleZ = 1;
    	if (xSize > ySize) {
    		scaleY = ySize > 0 ? xSize / ySize : 1.0;
        } else {
        	scaleX = xSize > 0 ? ySize / xSize : 1.0;
        }
    	scaleZ = scaleX * xSize * area.getHeight() / area.getWidth() / zSize;
    	return new Point3D(scaleX, scaleY, scaleZ);
    }
    
    /**
     * Fits chart into screen area
     * @param xSize the X data size
     * @param ySize the Y data size
     * @param zSize the Z data size
     * @param area area to fit
     */
    public void fitIntoArea(double xSize, double ySize, double zSize, Rectangle2D area) {
        // save user parameters
        double userZoomValue = userZoom;
        Point2D userScreenMoving = userMoving;
        screenMoving = userMoving = new Point2D.Double(0, 0);
        setZoom(1);
        scaling = correctScaling(xSize, ySize, zSize, area);

        // create bounds
        zoom = 1;
        List<Point3D> verticles = new ArrayList<Point3D>(8);
        verticles.add(transform(new Point3D(xSize / 2, ySize / 2, zSize / 2)));
        verticles.add(transform(new Point3D(-xSize / 2, ySize / 2, zSize / 2)));
        verticles.add(transform(new Point3D(-xSize / 2, -ySize / 2, zSize / 2)));
        verticles.add(transform(new Point3D(xSize / 2, -ySize / 2, zSize / 2)));
        verticles.add(transform(new Point3D(-xSize / 2, -ySize / 2, -zSize / 2)));
        verticles.add(transform(new Point3D(xSize / 2, -ySize / 2, -zSize / 2)));
        verticles.add(transform(new Point3D(xSize / 2, ySize / 2, -zSize / 2)));
        verticles.add(transform(new Point3D(-xSize / 2, ySize / 2, -zSize / 2)));
        
        
        if (zSize > 1000) {
            distance = -zSize * 100;
        } else {
            distance = -1000;
        }
        
        // update zooming
        Range xRange = null;
        Range yRange = null;
        for (Point3D point : verticles) {
            Point2D newPoint = toScreen(point);
            if (xRange == null || !xRange.contains(newPoint.getX())) {
                xRange = Range.expandToInclude(xRange, newPoint.getX());
            }
            if (yRange == null || !yRange.contains(newPoint.getY())) {
                yRange = Range.expandToInclude(yRange, newPoint.getY());
            }
        }

        if (xRange == null || xRange.getLength() == 0) {
            xRange = new Range(0, 1);
        }
        if (yRange == null || yRange.getLength() == 0) {
            yRange = new Range(0, 1);
        }

        // Decrease zoom by 20%
        zoom = 0.8 * Math.min(area.getWidth() / xRange.getLength(), area.getHeight() / yRange.getLength());

        // restore user parameters
        setZoom(userZoomValue);
        userMoving = userScreenMoving;
        screenMoving = new Point2D.Double(area.getCenterX(), area.getCenterY());
    }
    
    /**
     * Moves screen area
     * @param dx x moving length
     * @param dy y moving length
     */
    public void moveScreen(double dx, double dy) {
        userMoving.setLocation(dx, dy);
    }
    
    /**
     * Returns screen moving
     * @return screen moving
     */
    public Point2D getScreenMoving() {
        return (Point2D) userMoving.clone();
    }

    /**
     * Returns moving point
     * @return the moving point
     */
    public Point3D getMovingPoint() {
        Point3D point = null;
        try {
            point = (Point3D) movingPoint.clone();
        } catch (Exception e) {
        }
        return point;
    }
    
    /**
     * Returns zoom factor
     * @return the zoom factor
     */
    public double getZoomFactor() {
        return zoom;
    }
}
