package gensym.charts.annotations.graph.ext;

import java.awt.Shape;
import java.awt.geom.GeneralPath;
import java.awt.geom.Point2D;
import java.util.LinkedList;
import java.util.List;

import org.jfree.util.ShapeUtilities;

/**
 * Builder for Pointer, Vector and Arrow shapes, 
 * that uses from Pointer and Arrow annotations
 */
public class PointerShapeBuilder {

    /** The length of shape */
    private double length = 100.0;
    
    /** The ratio by arrow length to full length */
    private double arrowToLengthRatio = 1.0 / 3.0;
    
    /** The angle between base and arrow lines */
    private double arrowAngle = Math.PI / 4.0;
    
    /** The thickness of line */
    private double lineThickness = 0.0;

    /**
     * Gets shape length
     * @return the length
     */
    public double getLength() {
        return length;
    }

    /**
     * Sets shape length
     * @param length the length to set
     */
    public void setLength(double length) {
        this.length = length;
    }

    /**
     * Gets arrow to full length ratio
     * @return the ratio
     */
    public double getArrowToLengthRatio() {
        return arrowToLengthRatio;
    }

    /**
     * Sets arrow to full length ratio
     * @param arrowToLengthRatio the ratio to set
     */
    public void setArrowToLengthRatio(double arrowToLengthRatio) {
        this.arrowToLengthRatio = arrowToLengthRatio;
    }

    /**
     * Gets angle between base and arrow lines
     * @return the angle
     */
    public double getArrowAngle() {
        return arrowAngle;
    }

    /**
     * Sets angle between base and arrow lines
     * @param arrowAngle the angle to set
     */
    public void setArrowAngle(double arrowAngle) {
        this.arrowAngle = arrowAngle;
    }

    /**
     * Gets line thickness
     * @return the line thickness value
     */
    public double getLineThickness() {
        return lineThickness;
    }

    /**
     * Sets line thickness
     * @param lineThickness the thickness to set
     */
    public void setLineThickness(double lineThickness) {
        this.lineThickness = lineThickness;
    }

    /**
     * Gets list with 2D points for Vector or Arrow shape
     * @param arrow  the flag that controls adding points for second arrow line  
     * @return list of points
     */
    private List<Point2D> getPoints(boolean arrow) {
        List<Point2D> points = new LinkedList<Point2D>();
        points.add(new Point2D.Double(0.0, 0.0));
        
        double tanOfArrowAngle = Math.tan(arrowAngle); 
        double h = lineThickness / 2.0;
        double origY = h / tanOfArrowAngle;
        double lastX = h;
        double lastY = origY;
        double maxArrowY = origY + arrowToLengthRatio * length; 
        lastX = -maxArrowY*tanOfArrowAngle;
        lastY = maxArrowY;
        points.add(new Point2D.Double(lastX, lastY));

        lastX += lineThickness; 
        points.add(new Point2D.Double(lastX, lastY));

        lastY -= (Math.abs(lastX) - h)/tanOfArrowAngle;
        lastX = h;
        points.add(new Point2D.Double(-lastX, lastY));
        
        points.add(new Point2D.Double(-lastX, length));
        points.add(new Point2D.Double(lastX, length));
        
        if (arrow) {
            lastY = maxArrowY - (maxArrowY*tanOfArrowAngle - 3*h)/tanOfArrowAngle;
            points.add(new Point2D.Double(lastX, lastY));
    
            lastY = maxArrowY;
            lastX = maxArrowY*tanOfArrowAngle - lineThickness;
            points.add(new Point2D.Double(lastX, lastY));
    
            lastX = maxArrowY*tanOfArrowAngle;
            points.add(new Point2D.Double(lastX, lastY));
        } else {
            points.add(new Point2D.Double(h, origY));
        }
        
        return points;
    }
    
    /**
     * Calculates X coordinate for specified radius and angle
     * @param r  the radius
     * @param angle the angle
     * @return the value of X coordinate
     */
    private static double calcX(double r, double angle) {
        return r * Math.cos(angle);
    }
    
    /**
     * Calculates Y coordinate for specified radius and angle
     * @param r  the radius
     * @param angle the angle
     * @return the value of Y coordinate
     */
    private static double calcY(double r, double angle) {
        return r * Math.sin(angle);
    }
    
    /**
     * Gets points for simple pointer shape
     * @return list
     */
    private List<Point2D> getPointerPoints() {
        final double h = lineThickness / 2.0;
        final double r = arrowToLengthRatio * length;
        double angle = 0.0;
        final double fullCircle = Math.PI * 2;
        final double deltaAngle = fullCircle / (int)(r * 2);
        List<Point2D> points = new LinkedList<Point2D>();
        points.add(new Point2D.Double(r, 0.0));

        while (angle < fullCircle) {
            angle += deltaAngle;
            points.add(new Point2D.Double(calcX(r, angle), calcY(r, angle)));
        }
        points.add(new Point2D.Double(length, -h));
        points.add(new Point2D.Double(length, h));
        return points;
    }
    
    /**
     * Builds shape by list of point coordinates
     * @param points  the list
     * @return the Shape
     */
    private Shape buildShape(List<Point2D> points) {
        GeneralPath path = new GeneralPath();
        Point2D p2d = points.get(0);
        path.moveTo(p2d.getX(), p2d.getY());
        
        for (int i = 1; i < points.size(); i++) {
            p2d = points.get(i);
            path.lineTo(p2d.getX(), p2d.getY());
        }
        path.closePath();
        return path;
    }
    
    /**
     * Builds default Arrow shape
     * @return the Shape
     */
    public Shape buildArrow() {
        return ShapeUtilities.rotateShape(buildShape(getPoints(true)), -Math.PI/2, 0, 0);
    }
    
    /**
     * Builds Arrow shape, which rotated on specified angle
     * @param angle the rotation angle
     * @return the Shape
     */
    public Shape buildArrow(double angle) {
        return ShapeUtilities.rotateShape(buildArrow(), angle, 0, 0);
    }
    
    /**
     * Builds default Vector shape
     * @return the Shape
     */
    public Shape buildVector() {
        return ShapeUtilities.rotateShape(buildShape(getPoints(false)), -Math.PI/2, 0, 0);
    }
    
    /**
     * Builds Vector shape, which rotated on specified angle
     * @param angle the rotation angle
     * @return the Shape
     */
    public Shape buildVector(double angle) {
        return ShapeUtilities.rotateShape(buildVector(), angle, 0, 0);
    }
    
    /**
     * Builds default Pointer shape
     * @return the Shape
     */
    public Shape buildPointer() {
        return buildShape(getPointerPoints());
    }
    
    /**
     * Builds Pointer shape, which rotated on specified angle
     * @param angle the rotation angle
     * @return the Shape
     */
    public Shape buildPointer(double angle) {
        return ShapeUtilities.rotateShape(buildPointer(), angle, 0, 0);
    }
}
