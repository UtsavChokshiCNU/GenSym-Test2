package gensym.charts.annotations.graph;

import java.awt.Color;

/**
 * Graph annotation info
 */
public class AnnotationInfo {

    /** Annotation ID */
    private int id = 0;
    
    /** Annotation X position */
    private double x = 0;

    /** Annotation Y position */
    private double y = 0;
    
    /** Annotation text */
    private String text = "";
    
    /** Annotation type */
    private int type = -1;
    
    /** Annotation color */
    private Color color = null;
    
    /** Factory */
    private AnnotationFactory factory = null;

    /** Coresponding axis */
    private int axis = 0;
    
    /**
     * Constructor 
     * @param id annotation ID
     */
    public AnnotationInfo(int id, AnnotationFactory factory) {
        this.id = id;
        this.factory = factory;
    }
    
    /**
     * Returns annotation X position
     * @return the X position
     */
    public double getX() {
        return x;
    }
    
    /**
     * Sets annotation X position
     * @param x the X position
     */
    public void setX(double x) {
        this.x = x;
    }
    
    /**
     * Returns annotation Y position
     * @return the Y position
     */
    public double getY() {
        return y;
    }
    
    /**
     * Sets annotation Y position
     * @param y the Y position
     */
    public void setY(double y) {
        this.y = y;
    }
    
    /**
     * Returns annotation id
     * @return the ID
     */
    public int getId() {
        return id;
    }
    
    /**
     * Returns annotation text
     * @return the text
     */
    public String getText() {
        return text;
    }
    
    /**
     * Sets annotation text
     * @param text the text
     */
    public void setText(String text) {
        this.text = text;
    }
    
    /**
     * Returns annotation type
     * @return the type
     */
    public int getType() {
        return type;
    }
    
    /**
     * Sets annotation type
     * @param type the new type
     */
    public void setType(int type) {
        this.type = type;
    }
    
    /**
     * Return annotation color
     * @return the color
     */
    public Color getColor() {
        return color;
    }
    
    /**
     * Sets annotation color
     * @param color the new color
     */
    public void setColor(Color color) {
        this.color = color;
    }
    
    /**
     * Returns graph annotation factory
     */
    public AnnotationFactory getFactory() {
        return factory;
    }

    /**
     * Returns corresponding axis
     * @return the corresponding axis
     */
    public int getAxis() {
        return axis;
    }

    /**
     * Set corresponding axis
     * @param axis  the corresponding axis to set
     */
    public void setAxis(int axis) {
        this.axis = axis;
    }
}
