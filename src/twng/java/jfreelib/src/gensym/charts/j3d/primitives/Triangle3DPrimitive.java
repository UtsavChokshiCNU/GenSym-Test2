package gensym.charts.j3d.primitives;

import gensym.charts.j3d.*;
import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Paint;
import java.awt.Shape;
import java.awt.Stroke;
import java.awt.geom.GeneralPath;
import java.awt.geom.Point2D;

/**
 * Simple triangle class
 */
public class Triangle3DPrimitive extends Object3DPrimitive {

    /** Default rectangle stroke */
    public static final Stroke DEFAULT_TRIANGLE_STROKE = new BasicStroke(1.0f);

    /** Triangle3D values */
    private Triangle3D triangle;

    /** Is shade needed */
    private boolean showShades = false;

    /**
     * Constructor
     * @param p1 "A" value of the ABC triangle
     * @param p2 "B" value of the ABC triangle
     * @param p3 "C" value of the ABC triangle
     */
    public Triangle3DPrimitive(Triangle3D triangle) {
        this.triangle = triangle;
        setStroke(DEFAULT_TRIANGLE_STROKE);
    }

    public Triangle3D getTriangle3D() {
        return triangle;
    }

    /**
     * Tests whether shades are visible
     * @return true if shades are visible
     */
    public boolean isShadesVisible() {
        return showShades;
    }

    /**
     * Sets shades visibility flag
     * @param visible the new shades visibility flag
     */
    public void setShadesVisible(boolean visible) {
        showShades = visible;
    }

    /**
     * {@inheritDoc}
     */
    public double averageZValue() {
    	return getTriangle3D().averageZValue();
    }
    
    /**
     * {@inheritDoc}
     */
    public Object3DPrimitive transform(ViewPoint viewPoint) {
        Triangle3DPrimitive primitive =
                new Triangle3DPrimitive(viewPoint.transform(getTriangle3D()));

        primitive.copy(this);
        primitive.setShadesVisible(isShadesVisible());
        return primitive;
    }

    /**
     * {@inheritDoc}
     */
    public void draw(Graphics2D g2, Point3D sun, ViewPoint viewPoint) {
        Shape triangle = createTriangle(viewPoint);
        Paint newOutlinePaint = getOutlinePaint();
        if (getPaint() != null) {
            if (getPaint() instanceof Color) {
                Color newColor = isShadesVisible() ? Shade3D.getColor3Points(getTriangle3D(),
                        (Color) getPaint(), sun, viewPoint) : (Color) getPaint();

                g2.setPaint(newColor);
                g2.fill(triangle);

                if (newOutlinePaint == null) {
                    newOutlinePaint = newColor;
                }

            } else {
                g2.setPaint(getPaint());
                g2.fill(triangle);
            }
        }

        if (newOutlinePaint != null) {
            g2.setPaint(newOutlinePaint);
            g2.setStroke(getStroke());
            g2.draw(triangle);
        }
    }

    /**
     * Creates triangle shape
     * @param viewPoint view point
     * @return the triangle shape
     */
    private Shape createTriangle(ViewPoint viewPoint) {
        Point2D scrA = viewPoint.toScreen(getTriangle3D().getA());
        Point2D scrB = viewPoint.toScreen(getTriangle3D().getB());
        Point2D scrC = viewPoint.toScreen(getTriangle3D().getC());

        GeneralPath shapeTriangle = new GeneralPath();
        shapeTriangle.moveTo((float) scrA.getX(), (float) scrA.getY());
        shapeTriangle.lineTo((float) scrB.getX(), (float) scrB.getY());
        shapeTriangle.lineTo((float) scrC.getX(), (float) scrC.getY());
        shapeTriangle.lineTo((float) scrA.getX(), (float) scrA.getY());
        shapeTriangle.closePath();
        
        return shapeTriangle;
    }
    
    /**
     * {@inheritDoc}
     */
    public Point3D[] getPoints() {
        return new Point3D[] {getTriangle3D().getA(),
            getTriangle3D().getB(), getTriangle3D().getC()};
    }

    /**
     * {@inheritDoc}
     */
    public Shape getShape(ViewPoint viewPoint) {
        return createTriangle(viewPoint);
    }
}
