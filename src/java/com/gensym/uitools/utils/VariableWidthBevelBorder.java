package com.gensym.uitools.utils;

import java.awt.Graphics;
import java.awt.Insets;
import java.awt.Rectangle;
import java.awt.Color;
import java.awt.Component;
import javax.swing.border.BevelBorder;


public class VariableWidthBevelBorder extends BevelBorder
{
  public VariableWidthBevelBorder(int bevelType) {
    super(bevelType);
    }

  public void setBorderWidth(int width) {
    this.borderWidth = borderWidth;
  }
  
    public VariableWidthBevelBorder(int bevelType, Color highlight, Color shadow) {
      super(bevelType, highlight, shadow);
    }
    public VariableWidthBevelBorder(int bevelType, Color highlightOuter, Color highlightInner,
                        Color shadowOuter, Color shadowInner) {
      super(bevelType, highlightOuter, highlightInner,
	    shadowOuter, shadowInner);
    }

    @Override
    public Insets getBorderInsets(Component c)       {
	return new Insets(borderWidth,
			  borderWidth,
			  borderWidth,
			  borderWidth);
    }

    /** 
     * Reinitialize the insets parameter with this Border's current Insets. 
     * @param c the component for which this border insets value applies
     * @param insets the object to be reinitialized
     */
    @Override
    public Insets getBorderInsets(Component c, Insets insets) {
        insets.left = insets.top = insets.right = insets.bottom = borderWidth;
        return insets;
    }

  private int borderWidth = 1;
    @Override
    protected void paintRaisedBevel(Component c, Graphics g, int x, int y,
                                    int width, int height)  {
      
        Color oldColor = g.getColor();
        int h = height;
        int w = width;

        g.translate(x, y);

        g.setColor(getHighlightOuterColor(c));
        g.drawLine(0, 0, 0, h-1);
        g.drawLine(1, 0, w-1, 0);

        if (borderWidth > 1) {
	  g.setColor(getHighlightInnerColor(c));
	  g.drawLine(1, 1, 1, h-borderWidth);
	  g.drawLine(borderWidth, 1, w-borderWidth, 1);
	}

        g.setColor(getShadowOuterColor(c));
        g.drawLine(1, h-1, w-1, h-1);
        g.drawLine(w-1, 1, w-1, h-borderWidth);

	if (borderWidth > 1) {
	  g.setColor(getShadowInnerColor(c));
	  g.drawLine(borderWidth, h-borderWidth, w-borderWidth, h-borderWidth);
	  g.drawLine(w-borderWidth, borderWidth, w-borderWidth, h-(borderWidth+1));
	}

        g.translate(-x, -y);
        g.setColor(oldColor);

    }

    @Override
    protected void paintLoweredBevel(Component c, Graphics g, int x, int y,
                                        int width, int height)  {
        Color oldColor = g.getColor();
        int h = height;
        int w = width;

        g.translate(x, y);

        g.setColor(getShadowInnerColor(c));
        g.drawLine(0, 0, 0, h-1);
        g.drawLine(1, 0, w-1, 0);

        g.setColor(getShadowOuterColor(c));
        g.drawLine(1, 1, 1, h-borderWidth);
        g.drawLine(borderWidth, 1, w-borderWidth, 1);

        g.setColor(getHighlightOuterColor(c));
        g.drawLine(1, h-1, w-1, h-1);
        g.drawLine(w-1, 1, w-1, h-borderWidth);

        g.setColor(getHighlightInnerColor(c));
        g.drawLine(borderWidth, h-borderWidth, w-borderWidth, h-borderWidth);
        g.drawLine(w-borderWidth, borderWidth, w-borderWidth, h-(borderWidth +1));

        g.translate(-x, -y);
        g.setColor(oldColor);

    }

}
