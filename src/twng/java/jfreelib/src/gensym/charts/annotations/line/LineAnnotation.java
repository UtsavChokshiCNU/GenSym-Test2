package gensym.charts.annotations.line;

import gensym.charts.ChartLineTypes;

import java.awt.BasicStroke;
import java.awt.Color;

import org.jfree.chart.plot.ValueMarker;
import org.jfree.ui.RectangleAnchor;
import org.jfree.ui.TextAnchor;

/**
 * Line annotation class
 */
public class LineAnnotation {
    /**
     * Line annotation position
     */
    private Double position;
    
    /**
     * Line annotation type
     */
    private int type;
    
    /**
     * Line annotation text
     */
    private String text;
    
    /**
     * Line annotation color
     */
    private Color color;
    
    /**
     * Corresponding axis
     */
    int axis = 0;
    
    /**
     * Returns line position
     * @return the line annotation position
     */
    public Double getPosition() {
        return position;
    }
    
    /**
     * Sets line position
     * @param position the line annotation position
     */
    public void setPosition(double position) {
        this.position = position;
    }
    
    /**
     * Returns type
     * @return the type
     */
    public int getType() {
        return type;
    }
 
    /**
     * Sets type
     * @param type the new type
     */
    public void setType(int type) {
        this.type = type;
    }
    
    /**
     * Returns annotation text
     * @return the annotation text
     */
    public String getText() {
        return text;
    }
    
    /**
     * Sets annotation text
     * @param text the new text
     */
    public void setText(String text) {
        this.text = text;
    }
    
    /**
     * Returns annotation color
     * @return the annotation color
     */
    public Color getColor() {
        return color;
    }
    
    /**
     * Sets annotation color
     * @param color the new annotation color
     */
    public void setColor(Color color) {
        this.color = color;
    }
    
    /**
     * Returns corresponding axis
     * @return the corresponding axis
     */
    public int getAxis() {
        return axis;
    }
    
    /**
     * Sets corresponding axis
     * @param axis the axis number
     */
    public void setAxis(int axis) {
        this.axis = axis;
    }
    
    /**
     * Creates value marker
     * @return created value marker
     */
    public ValueMarker createMarker() {
        if (getPosition() == null) {
            return null;
        }
        ValueMarker marker = new ValueMarker(getPosition());
        if (getColor() != null) {
            marker.setPaint(getColor());
        }
        String text = getText();
        boolean right = text.toLowerCase().startsWith("|r");
        
        if (text.startsWith("|")) {
            text = text.substring(2);
        }
        
        marker.setLabel(text);
        
        marker.setLabelAnchor(right ? RectangleAnchor.TOP_RIGHT : RectangleAnchor.TOP_LEFT );
        marker.setLabelTextAnchor(right ? TextAnchor.BOTTOM_RIGHT : TextAnchor.BOTTOM_LEFT);

        BasicStroke stroke = null;
        switch (getType()) {
        case 7:  // PELAT_GRIDTICK
        case 14: // PELAT_GRIDTICKII
            stroke = new BasicStroke(0.5f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND, 1.0f, new float[] {4, 10000}, 0.0f);
            break;
        case 8:  // PELAT_GRIDLINE
        case 15: // PELAT_GRIDLINEII
            stroke = new BasicStroke(1.0f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND, 1.0f, new float[] {8, 10000}, 0.0f);
            break;
        default:
            stroke = ChartLineTypes.makeBasicStroke(getType());
        break;
        }
        
        if (stroke != null) {
            marker.setStroke(stroke);
        }
        
        return marker;
    }
}
