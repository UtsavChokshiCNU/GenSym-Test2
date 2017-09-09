package gensym.charts.j3d.primitives;

import gensym.charts.j3d.*;
import java.awt.Graphics2D;
import java.awt.Shape;
import java.awt.Paint;
import java.awt.Stroke;

/**
 * Graphic primitive abstract class
 */
public abstract class Object3DPrimitive {
    
    /** Entity data */
    private EntityData3D entityData = null;
    
    /** Primitive fill paint*/
    private Paint paint = null;

    /** Primitive Outline paint */
    private Paint outlinePaint = null;

    /** Primitive Outline stroke */
    private Stroke stroke = null;

    /**
     * Sets entity data
     * @param data the entity data
     */
    public void setEntityData(EntityData3D data) {
        entityData = data;
    }
    
    /**
     * Returns entity data
     * @return the entity data
     */
    public EntityData3D getEntityData() {
        return entityData;
    }

    /**
     * Sets primitive fill paint
     * @param paint new primitive fill paint
     */
    public void setPaint(Paint paint) {
        this.paint = paint;
    }

    /**
     * Gets primitive fill paint
     * @return the primitive fill paint
     */
    public Paint getPaint() {
        return paint;
    }

    /**
     * Sets primitive outline paint
     * @param outlinePaint new primitive outline paint
     */
    public void setOutlinePaint(Paint outlinePaint) {
        this.outlinePaint = outlinePaint;
    }

    /**
     * Gets primitive outline paint
     * @return the primitive outline paint
     */
    public Paint getOutlinePaint() {
        return outlinePaint;
    }

    /**
     * Returns stroke
     * @return the stroke
     */
    public Stroke getStroke() {
        return stroke;
    }

    /**
     * Sets stroke
     * @param stroke the new stroke
     */
    public void setStroke(Stroke stroke) {
        this.stroke = stroke;
    }

    /**
     * Function copy main Object3DPrimitive value
     * @param prim Object3DPrimitive to copy from
     */
    protected void copy(Object3DPrimitive prim) {
        setEntityData(prim.getEntityData());
        setPaint(prim.getPaint());
        setOutlinePaint(prim.getOutlinePaint());
        setStroke(prim.getStroke());
    }

    /**
     * Returns average Z value of primitive
     * @return the average Z value of primitive
     */
    public abstract double averageZValue();
    
    /**
     * Transforms primitive
     * @param viewPoint view point
     * @return the new transformed primitive
     */
    public abstract Object3DPrimitive transform(ViewPoint viewPoint);
    
    /**
     * Draws primitive
     * @param g2 graphic
     * @param sun sun point
     * @param viewPoint view point
     */
    public abstract void draw(Graphics2D g2, Point3D sun, ViewPoint viewPoint);
    
    /**
     * Returns list of primitive's points
     * @return the list of primitive's points
     */
    public abstract Point3D[] getPoints();
    
    /**
     * Returns shape of primitive
     * @param viewPoint view point
     * @return the shape of primitive
     */
    public abstract Shape getShape(ViewPoint viewPoint);
}
