package gensym.charts.gradients;

import java.awt.Color;

public class GradientValues {

    /**
     * Start color of the gradient
     */
    protected Color start = null;

    /**
     * End color of the gradient
     */
    protected Color end = null;

    /**
     * Gradient style of the desk (see GradientStyle.java)
     */
    protected int style = 0;

    /**
     * Gets start gradient color
     * @return start color
     */
    public Color getStart() {
        return start;
    }

    /**
     * Sets start gradient color
     * @param cl new start color
     */
    public void setStart(Color cl) {
        start = cl;
    }

    /**
     * Gets end gradient color
     * @return end color
     */
    public Color getEnd() {
        return end;
    }

    /**
     * Sets end gradient color
     * @param cl new end color
     */
    public void setEnd(Color cl) {
        end = cl;
    }

    /**
     * Gets gradient style
     * @return style
     */
    public int getStyle() {
        return style;
    }

    /**
     * Sets gradient style
     * @param st new style
     */
    public void setStyle(int st) {
        style = st;
    }

    /**
     * Check values
     * @return true, if gradient needed
     */
    public boolean isGradientNeeded() {
        return getStyle() != 0 && getStart() != null && getEnd() != null;
    }
}
