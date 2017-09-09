package gensym.charts.j3d;

import java.awt.Graphics2D;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;

import org.jfree.chart.plot.PlotRenderingInfo;
import org.jfree.data.Range;

import gensym.charts.j3d.primitives.Object3DPrimitive;

/**
 * Object3D class consists from 3D primitives: point, line, triangle
 */
public class Object3D {

    /** Storage of object primitives */
    private List<Object3DPrimitive> primitives = new LinkedList<Object3DPrimitive>();

    /**
     * Sets new primitive into list
     * @param primitive to add
     */
    public void addPrimitive(Object3DPrimitive primitive) {
    	primitives.add(primitive);
    }

    /**
     * Tests if primitives list is empty
     * @return <tt>true</tt> if primitives list is empty  
     */
    public boolean isEmpty() {
        return primitives.isEmpty();
    }
    
    /**
     * Get primitives count
     * @return int value
     */
    public int getPrimitivesCount() {
        return primitives.size();
    }
    
    /**
     * Get primitive by specified index
     * @return The ObjectPrimitive object
     */
    public Object3DPrimitive getPrimitive(int index) {
        if ((index < 0) || (index >= getPrimitivesCount())) {
            throw new IllegalArgumentException("The primitives index out of bounds");
        }
        return primitives.get(index);
    }
    
    /**
     * Draws all graphics primitives from primitives list 
     * @param g2
     * @param sun
     * @param viewPoint
     */
    public void draw(Graphics2D g2, Point3D sun, ViewPoint viewPoint, PlotRenderingInfo info) {
        List<Object3DPrimitive> transformedPrimitives = new ArrayList<Object3DPrimitive>(primitives.size());
        for (Object3DPrimitive primitive : primitives) {
    	    transformedPrimitives.add(primitive.transform(viewPoint));
    	}
        Collections.sort(transformedPrimitives, new Comparator<Object3DPrimitive>() {

            public int compare(Object3DPrimitive a, Object3DPrimitive b) {
    	        double aZ = a.averageZValue();
    	        double bZ = b.averageZValue();
    	        if (aZ > bZ) {
    	            return -1;
    	        } else if (aZ < bZ) {
    	            return 1;
    	        }
    	        return 0;
            }
        });
    	
        for (Object3DPrimitive primitive : transformedPrimitives) {
    		primitive.draw(g2, sun, viewPoint);
    	}

       for (Object3DPrimitive primitive : transformedPrimitives) {
           EntityData3D data = primitive.getEntityData();

           if (data != null) {
               XYZItemEntity entity = new XYZItemEntity(primitive.getShape(viewPoint), null, null,
                       data.getItem(), data.getSeries(), data.getPoint());

                info.getOwner().getEntityCollection().add(entity);
            }
        }
    }
    
    /**
     * Calculates object bounds
     * @return the set of ranges bounding object (for X, Y and Z axes)
     */
    public Range[] getBounds() {
        Range xRange = null;
        Range yRange = null;
        Range zRange = null;
        
        for (Object3DPrimitive primitive : primitives) {
            for (Point3D point : primitive.getPoints()) {
                if (xRange == null || !xRange.contains(point.getX())) {
                    xRange = Range.expandToInclude(xRange, point.getX());
                }
                if (yRange == null || !yRange.contains(point.getY())) {
                    yRange = Range.expandToInclude(yRange, point.getY());
                }
                if (zRange == null || !zRange.contains(point.getZ())) {
                    zRange = Range.expandToInclude(zRange, point.getZ());
                }
            }
        }
        
        return new Range[] {xRange, yRange, zRange};
    }
}
